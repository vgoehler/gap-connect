#include "StdAfx.h"
#include "graphView.h"				 

namespace GAPConnect {

graphView::graphView(System::Windows::Forms::Form^ inParent): m_parent(inParent), m_startedDrawing(nullptr), m_lastMarkedElement(nullptr), m_backupPositions(nullptr)
{
	this->vertexList = gcnew System::Collections::Generic::List< GAPConnect::vertexView^ >();
	this->edgeList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
	this->m_drawTools = gcnew GAPConnect::drawTools();
	this->m_dataGraph = gcnew Graph();
}

graphView::graphView( void ): m_parent(nullptr), m_startedDrawing(nullptr), m_backupPositions(nullptr)
{
}

graphView::~graphView( void )
{
	delete this->edgeList;
	delete this->vertexList;
	delete this->m_drawTools;
	delete this->m_dataGraph;
}

void graphView::unmarkElement( GAPConnect::basicView^ element){
	if (element != nullptr){
		bool isMarked;
		do{//Nur zur Sicherheit, da markVertex switched
			isMarked = element->Mark();
		}while(isMarked);
	}
}
void graphView::unmarkElement( void ){
	this->unmarkElement(this->m_startedDrawing);
	this->m_startedDrawing = nullptr;
}

bool graphView::CreateEdge( Point location, bool isArc, bool withConfigDialog, bool forceConfigDialog )
{
	GAPConnect::vertexView^ clickedVertex = this->getHandleOfVertex(location);
	if (clickedVertex != nullptr)//nur wenn auch auf einen Vertex geklickt wurde
	{
		//wenn Knoten wieder deaktiviert, dann wurde wohl falscher startknoten ausgewählt und wieder deaktiviert
		if (!clickedVertex->IsMarked){
			this->m_startedDrawing = nullptr;
		}
		if (this->m_startedDrawing == nullptr){//Edge zeichnen noch nicht gestartet
			//speichern des starts wenn noch nicht gestartet
			this->m_startedDrawing = clickedVertex;
		}else{
			//auf Doppelkanten testen und ignorieren
			if (this->EdgeAllreadyThere(this->m_startedDrawing, clickedVertex)){
				return(false);
			}
			//wenn bereits gestartet dann ende vermerken und objekt initialisieren
			edgeView^ edge = gcnew edgeView(this->m_parent, this->m_drawTools, this->m_startedDrawing, clickedVertex, isArc?1:0, this->m_dataGraph);

			this->edgeList->Add(edge);

			//ende muss noch markierungen entfernen auf Knoten (Startknoten wird von checkstate change entfernt); geht mit mark Weil dieser vorher markiert ist, also der letzte
			this->markElement(clickedVertex);


			//Dialog zum Beschriften einblenden
			if (withConfigDialog || forceConfigDialog)
			{
				edge->startConfigDialog(false);
			}


			return(true);
		}
	}
	return(false);
}

void graphView::CreateVertex( Point location, bool isRound, bool withConfigDialog )
{
	//Vertex schreiben
	vertexView^ vertex = (gcnew vertexView(this->m_parent, this->m_drawTools, this->m_dataGraph));
	vertex->LocationCenter = location;

	//VertexArt
	vertex->TypeofVertex = isRound ? 0 : 1;

	//Button Drawpanel hinzufügen
	this->vertexList->Add(vertex);

	//Refresh um Knoten anzuzeigen
	dynamic_cast<GAPConnect::Form1^ >(this->m_parent)->RefreshDrawBox();

	//Dialog zum Beschriften einblenden
	if (withConfigDialog){
		vertex->startConfigDialog(false);
	}

}

void graphView::markElement( GAPConnect::basicView^ element )
{
	bool sameAsLastElement = this->m_lastMarkedElement != element;
	unmarkElement(this->m_lastMarkedElement);
	this->m_lastMarkedElement = nullptr;
	if (sameAsLastElement)
	{
		element->Mark();
		this->m_lastMarkedElement = element;
	}
}

void graphView::drawGraph( System::Windows::Forms::PaintEventArgs^ e )
{
	//Knoten zeichnen
	for each (GAPConnect::vertexView^ vertex in this->vertexList){
		vertex->drawVertex(e);
	}
	//Kanten zeichnen
	for each (GAPConnect::edgeView^ edge in this->edgeList){
		edge->drawEdge(e);
	}
}

GAPConnect::basicView^ graphView::getHandleOfElement( System::Drawing::Point pkt, bool Edges, bool Vertex)
{
	//Liste für Ergebnisse
	System::Collections::Generic::List< GAPConnect::basicView^ > tmpList = gcnew System::Collections::Generic::List< GAPConnect::basicView^ >();
	if (Vertex)
	{
		for each (GAPConnect::vertexView^ element in this->vertexList){
			if (element->Contains(pkt)){
				tmpList.Add(dynamic_cast<GAPConnect::basicView^>(element));
			}
		}
	}
	if (Edges)
	{
		for each (GAPConnect::edgeView^ element in this->edgeList){
			if (element->Contains(pkt)){
				tmpList.Add(dynamic_cast<GAPConnect::basicView^>(element));
			}
		}
	}
	//Ergebnissbehandlung
	if (tmpList.Count == 1){
		return (tmpList[0]);//bei nur einem Ergebniss einfach 
	}else if (tmpList.Count > 1){
		//mehrere! Fallunterscheidung!
		System::Collections::Generic::List< GAPConnect::basicView^ > tmpLoops = gcnew System::Collections::Generic::List< GAPConnect::basicView^ >();
		for each(GAPConnect::basicView^ element in tmpList){
			if (dynamic_cast<GAPConnect::vertexView^ > (element) != nullptr){//Vertex bevorzugen
				return(element);
			}else{
				edgeView^ testEdge = dynamic_cast<GAPConnect::edgeView^ >(element);
				if (testEdge != nullptr){
					//Normale Kanten vor Loops
					if (! testEdge->IsLoop){
						return(element);
					}else{
						tmpLoops.Add(element);
					}
				}
			}
		}
		//wenn wir hier noch nicht zurückgegeben sind müssen wir den ersten Loop zurückgeben
		return (tmpLoops[0]);
	}
	//in allen anderen Fällen
	return (nullptr);
}

GAPConnect::basicView^ graphView::getHandleOfElement( System::Drawing::Point pkt )
{
	return(this->getHandleOfElement(pkt, true, true));
}

GAPConnect::edgeView^ graphView::getHandleOfEdge( System::Drawing::Point pkt )
{
	return (dynamic_cast<GAPConnect::edgeView^ >(this->getHandleOfElement(pkt, true, false)));
}

GAPConnect::vertexView^ graphView::getHandleOfVertex( System::Drawing::Point pkt )
{
	return (dynamic_cast<GAPConnect::vertexView^ >(this->getHandleOfElement(pkt, false, true)));
}

void graphView::deleteDrawnElement( GAPConnect::basicView^ element )
{
	GAPConnect::vertexView^ vertex;
	GAPConnect::edgeView^ edge;
	if (( vertex = dynamic_cast<GAPConnect::vertexView^ >(element))!= nullptr){
		//bei Knoten müssen auch alle angeschlossenen Kanten entfernt werden
		System::Collections::Generic::List< GAPConnect::edgeView^ > tmpEdgeList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
		//Suchen der Kanten von vertex ausgehen
		for each (GAPConnect::edgeView^ edge in this->edgeList){
			if (vertex == edge->StartVertex || vertex == edge->EndVertex){
				tmpEdgeList.Add(edge);
			}
		}
		//Löschen der Kanten
		for each (GAPConnect::edgeView^ edge in tmpEdgeList){
			this->edgeList->Remove(edge);
		}
		tmpEdgeList.Clear();
		this->vertexList->Remove(vertex);
	}else if (( edge = dynamic_cast<GAPConnect::edgeView^ >(element)) != nullptr){
		this->edgeList->Remove(edge);
	}
	delete element;
}

bool graphView::IsSomethingMarked( void )
{
	return(this->m_lastMarkedElement != nullptr);
}

bool graphView::IsEdgeCrossing( edgeView^ inEdge )
{
	for each(edgeView^ edge in this->edgeList){
		if (edge->Crosses(inEdge)){//sobald sich eine Kante kreuzt rückgabe!
			return (true);
		}
	}
	return(false);
}

void graphView::CreateCompleteGraph( void )
{
	//bestehende Kanten löschen
	delete this->edgeList;
	this->edgeList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
	for each (GAPConnect::vertexView^ vertex in this->vertexList){
		for each (GAPConnect::vertexView^ neighbor in this->vertexList){
			if (vertex != neighbor && ! this->EdgeAllreadyThere(vertex, neighbor)){//wenn wir nicht wir selber sind: Kante; noch überprüfen ob wir entsprechende Kante bereits haben
				GAPConnect::edgeView^ edge = gcnew GAPConnect::edgeView(this->m_parent, this->m_drawTools, vertex, neighbor, 0, this->m_dataGraph);
				this->edgeList->Add(edge);
			}
		}
	}
}

void graphView::ReCalcDockingPoints( GAPConnect::vertexView^ vertex )
{
	for each (GAPConnect::edgeView^ edge in this->edgeList){
		if (edge->StartVertex == vertex || edge->EndVertex == vertex){
			edge->calculateDockingPoint();
		}
	}
}

bool graphView::vertexTooClose( Point pkt, Size sz )
{
	return(this->vertexTooClose(pkt, sz, nullptr));
}

bool graphView::vertexTooClose( Point pkt, Size sz, vertexView^ vertex )
{
	//KontrollRechteck zum Überprüfen holen; input size modifizieren, da Pixel dazwischen bleiben müssen,
	System::Drawing::Rectangle OwnRectangle = Rectangle(pkt.X-(sz.Width+15)/2 , pkt.Y-(sz.Height+15)/2, sz.Width+15, sz.Height+15);
	//mit anderen auf Überschneidungen testen
	for each (GAPConnect::vertexView^ vertexFromList in this->vertexList){
		if (vertexFromList->GetBorderRectangle.IntersectsWith(OwnRectangle)){
			if (vertex != vertexFromList){
				return(true);
			}
		}
	}
	return(false);
}

void graphView::BuildViewFromData( void )
{
	//Alle Knoten durchlaufen und Erschaffen
	for each (Knoten^ vtx in this->m_dataGraph->verticles){
		this->vertexList->Add(gcnew GAPConnect::vertexView(this->m_parent, this->m_drawTools, this->m_dataGraph, vtx));
	}
	//Alle Kanten durchlaufen und Erschaffen
	for each (Kante^ edge in this->m_dataGraph->edges){
		edgeView^ eV = gcnew edgeView(this->m_parent, this->m_drawTools, this->m_dataGraph, edge);
		//start und Ziel suchen
		vertexView^ startV = nullptr;
		vertexView^ endV = nullptr;
		Knoten^ startK = edge->get_knoten_start();
		Knoten^ endK = edge->get_knoten_end();
		for each (vertexView^ tmpV in this->vertexList){
			if (tmpV->DataVertex == startK){
				startV = tmpV;
			}
			if (tmpV->DataVertex == endK){
				endV = tmpV;
			}
			if (startV != nullptr && endV != nullptr)
			{
				break;//Abbruchkriterium
			}
		}
		if (edge->gerichtet == -1){
			eV->StartVertex = endV;
			eV->EndVertex = startV;
			edge->gerichtet = 1;
		}else{
			eV->StartVertex = startV;
			eV->EndVertex = endV;
		}
		this->edgeList->Add(eV);
	}
}

bool graphView::LoadGraph( String^ filename )
{
	this->m_dataGraph = Graph::load_graph(filename);
	if (this->m_dataGraph == nullptr)
	{// wenn nullptr dann neuen Graph erstellen und Falsch zurückgeben
		this->m_dataGraph = gcnew Graph();
		return(false);
	}
	this->BuildViewFromData();

	return(true);
}

bool graphView::SaveGraph( String^ filename )
{
	return(this->m_dataGraph->save_graph(filename));
}

bool graphView::ExportGraph( String^ filename )
{
	array<int, 2>^ arrTmp = this->m_dataGraph->convert_graph_to_adjacency();
	if(arrTmp == nullptr){
		return(false);
	}
	try
	{
		this->m_dataGraph->write_adjacency_to_file(filename, arrTmp);
	}
	catch (Exception^ e)
	{
		return(false);
	}
	return (true);
}

bool graphView::ImportGraph( String^ filename )
{
	array<int, 2>^ arrTmp = this->m_dataGraph->read_file_to_adjacency(filename);
	if (arrTmp == nullptr){
		return(false);//Fehler beim Einlesen
	}
	this->m_dataGraph->convert_adjacency_to_graph(arrTmp);
	this->m_dataGraph->optimize(6666, false);//Anzahl, false == keine Platzierten knoten

	//ViewObjekte bauen
	this->BuildViewFromData();

	return (true);
}

bool graphView::StartRandomize( Int32 maximum )
{
	Int32 outer = Int32(float(maximum) /100);
	Int32 step = Int32(float(maximum) /10000);
	for (int i = 0; i< outer; i++){
		if (this->m_dataGraph->optimize(step, true) == 0){
			return true;
		}
		dynamic_cast<GAPConnect::Form1^ > (this->m_parent)->OptimizerPanel = step;
	}
	return false;
}

void graphView::UpdateLocationsFromData( void )
{
	for each (GAPConnect::vertexView^ vertex in this->vertexList){//Über ganze Knotenliste iterieren
		vertex->updateLocationFromDataVertex();
	}//Da sich nun alle Locations geändert haben, müssen auch alle Dockpunkte neu berechnet werden
	for each (GAPConnect::vertexView^ vertex in this->vertexList){
		this->ReCalcDockingPoints(vertex);
	}
}

bool graphView::EdgeAllreadyThere( vertexView^ One, vertexView^ Two )
{
	for each (edgeView^ edge in this->edgeList){
		if (edge->StartVertex == One && edge->EndVertex == Two || edge->StartVertex == Two && edge->EndVertex == One){//wenn beide Knoten übereinstimmen
			return(true);
		}
	}
	return(false);
}

bool graphView::HasBackup( void )
{
	if (this->m_backupPositions != nullptr){
		return(true);
	}
	return(false);
}

void graphView::BackupSecure( void )
{
	this->m_backupPositions = gcnew List<System::Drawing::Point>();
	int vCount = this->m_dataGraph->verticles->Count;
	for(int i=0;i<vCount;i++){
		this->m_backupPositions->Add(this->m_dataGraph->verticles[i]->coords);
	}
}

void graphView::BackupWriteBack( void )
{
	int vCount = this->m_dataGraph->verticles->Count;
	for(int i=0;i<vCount;i++){
		this->m_dataGraph->verticles[i]->coords = this->m_backupPositions[i];
	}
	this->m_backupPositions = nullptr;
}

}//namespace