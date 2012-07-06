#include "StdAfx.h"
#include "graphView.h"

namespace GAPConnect {

graphView::graphView(System::Windows::Forms::Form^ inParent): parent(inParent), startedDrawing(nullptr), m_lastMarkedElement(nullptr)
{
	this->vertexList = gcnew System::Collections::Generic::List< GAPConnect::vertexView^ >();
	this->edgeList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
	this->m_drawTools = gcnew GAPConnect::drawTools();
}

graphView::graphView( void ): parent(nullptr), startedDrawing(nullptr)
{
}

graphView::~graphView( void )
{
	delete this->edgeList;
	delete this->vertexList;
	delete this->m_drawTools;
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
	this->unmarkElement(this->startedDrawing);
	this->startedDrawing = nullptr;
}

bool graphView::CreateEdge( Point location, bool isArc, bool withConfigDialog, bool forceConfigDialog )
{
	GAPConnect::vertexView^ clickedVertex = this->getHandleOfVertex(location);
	if (clickedVertex != nullptr)//nur wenn auch auf einen Vertex geklickt wurde
	{
		//wenn Knoten wieder deaktiviert, dann wurde wohl falscher startknoten ausgewählt und wieder deaktiviert
		if (!clickedVertex->IsMarked){
			this->startedDrawing = nullptr;
		}
		if (this->startedDrawing == nullptr){//Edge zeichnen noch nicht gestartet
			//speichern des starts wenn noch nicht gestartet
			this->startedDrawing = clickedVertex;
		}else{
			//wenn bereits gestartet dann ende vermerken und objekt initialisieren
			edgeView^ edge = gcnew edgeView(this->parent, this->m_drawTools, this->startedDrawing, clickedVertex, isArc?1:0);

			this->edgeList->Add(edge);

			//ende muss noch markierungen entfernen auf Knoten (Startknoten wird von checkstate change entfernt); geht mit mark Weil dieser vorher markiert ist, also der letzte
			this->markElement(clickedVertex);

			//Dialog zum Beschriften einblenden
			if (withConfigDialog || forceConfigDialog)
			{
				edge->startConfigDialog();
			}
			return(true);
		}
	}
	return(false);
}

void graphView::CreateVertex( Point location, bool isRound, bool withConfigDialog )
{
	//Vertex schreiben
	vertexView^ vertex = (gcnew vertexView(this->parent, this->m_drawTools));
	vertex->LocationCenter = location;

	//VertexArt
	vertex->kindOf = isRound ? 0 : 1;

	//Button Drawpanel hinzufügen
	this->vertexList->Add(vertex);

	//Dialog zum Beschriften einblenden
	if (withConfigDialog){
		vertex->startConfigDialog();
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
		vertex->paintVertex(e);
	}
	//Kanten zeichnen
	for each (GAPConnect::edgeView^ edge in this->edgeList){
		edge->paintEdge(e);
	}
}

GAPConnect::edgeView^ graphView::getHandleOfEdge( System::Drawing::Point pkt )
{
	//Liste um Sucherergebnisse festzuhalten
	System::Collections::Generic::List< GAPConnect::edgeView^ > tmpList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
	//Edges durchsuchen
	for each (GAPConnect::edgeView^ element in this->edgeList){
		if (element->Contains(pkt))
		{
			tmpList.Add(element);
		}
	}
	//Behandlung der Ergebnisse
	if (tmpList.Count == 1)
	{//bei nur einem Ergebniss einfach dieses zurückgeben
		return tmpList[0];
	}else if (tmpList.Count > 1)
	{//TODO Mehrere: Hier Fallbehandlung um das Richtige herauszufinden
		return tmpList[0];
	} 
	else
	{//nichts!
		return nullptr;
	}
}

GAPConnect::vertexView^ graphView::getHandleOfVertex( System::Drawing::Point pkt )
{
	//Liste um Sucherergebnisse festzuhalten
	System::Collections::Generic::List< GAPConnect::vertexView^ > tmpList = gcnew System::Collections::Generic::List< GAPConnect::vertexView^ >();
	//Vertexe durchsuchen
	for each (GAPConnect::vertexView^ element in this->vertexList){
		if (element->Contains(pkt))
		{
			tmpList.Add(element);
		}
	}
	//Behandlung der Ergebnisse
	if (tmpList.Count == 1)
	{//bei nur einem Ergebniss einfach dieses zurückgeben
		return tmpList[0];
	}else if (tmpList.Count > 1)
	{//TODO Mehrere: Hier Fallbehandlung um das Richtige herauszufinden
		return tmpList[0];
	} 
	else
	{//nichts!
		return nullptr;
	}
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

}//namespace