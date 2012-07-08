#include "StdAfx.h"
#include "edgeView.h"


namespace GAPConnect {
edgeView::edgeView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, vertexView^ startVertex, vertexView^ endVertex, int mode, Graph^ parentDataGraph):basicView(inParent, inDrawTools, parentDataGraph), m_startVertex(nullptr), m_endVertex(nullptr), m_aidLine(false)
{
	this->StartVertex = startVertex;
	this->EndVertex = endVertex;
	//Datenrepräsentation verknüpfen
	this->m_dataEdge = this->m_dataGraph->create_edge(startVertex->DataVertex, endVertex->DataVertex);
	this->IsArc = (mode == 0)? false:true;//hier setzen um auch Daten mit entsprechenden Informationen zu füllen
	this->IsEnabled = true;//Enablen um Stift zu initialisieren
}

edgeView::edgeView( System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, Graph^ parentDataGraph, Kante^ dataEdge ):basicView(inParent, inDrawTools, parentDataGraph), m_startVertex(nullptr), m_endVertex(nullptr), m_aidLine(false), m_dataEdge(dataEdge)
{
	this->m_lineMode = this->m_dataEdge->gerichtet == 0 ? 0 : 1;//ignorieren hier alle anderen Werte
	this->IsEnabled = this->m_dataEdge->shape == DISABLED ? true : false;
}

System::Drawing::Size edgeView::createSize( void )
{
	int width, height;
	//breite und Höhe müssen um jeweils Hälfte der beiden weniger sein
	width =	abs(this->m_startDock.X - this->m_endDock.X);
	height = abs(this->m_startDock.Y - this->m_endDock.Y);
	return(System::Drawing::Size(width, height));
}

System::Void edgeView::drawEdge( System::Windows::Forms::PaintEventArgs^ e )
{
	//Markieren
	if (this->IsMarked)
	{
		//Markierungslinie untendrunter zeichnen
		e->Graphics->DrawLine(this->m_drawTools->m_edgeMarked, this->m_startDock, this->m_endDock);
	}
	//Linie
	e->Graphics->DrawLine(this->m_edgePen, this->m_startDock, this->m_endDock);
	//Modus beachten
	if (this->IsArc)//Gerichtet
	{
		this->drawArrow(e);
	}
	if (!String::IsNullOrWhiteSpace(this->Text))
	{
		this->drawText(e);
	}
}

System::Drawing::Point edgeView::createLocation( void ){
	int locX, locY;
	//rechts oben ist Location, also kleinstes X und kleinstes Y + Hälfte der breite bzw. höhe der entsprechenden Schaltfläche
	locX = this->m_startDock.X < this->m_endDock.X ? this->m_startDock.X : this->m_endDock.X;
	locY = this->m_startDock.Y < this->m_endDock.Y ? this->m_startDock.Y : this->m_endDock.Y;
	return (System::Drawing::Point(locX, locY));
}

void edgeView::calculateDockingPoint( void ){
	if (! this->IsLoop)//nur Gültig für Nicht LOOP Modus
	{
		//Winkel zu Ziel berechnen
		double angle = this->getAnglePointToPoint(this->StartVertex->LocationCenter, this->EndVertex->LocationCenter);
		this->m_startDock = this->StartVertex->getDockPoint( angle );
		angle = this->getAnglePointToPoint(this->EndVertex->LocationCenter, this->StartVertex->LocationCenter);
		this->m_endDock = this->EndVertex->getDockPoint( angle );
	}
	}

double edgeView::getAnglePointToPoint( Point^ startPoint, Point^ endPoint ){
	double xDiff,yDiff,winkel;
	xDiff = double (startPoint->X - endPoint->X);
	yDiff = double (startPoint->Y - endPoint->Y); 
	winkel = atan2(yDiff, xDiff);
	return(winkel);
}

void edgeView::drawArrow( System::Windows::Forms::PaintEventArgs^ e ){
	//außerhalb des LOOP Modus
	if (! this->IsLoop)
	{
		double angleStart;
		//Winkel bei Start holen Richtung Ende
		angleStart = this->getAnglePointToPoint(this->m_startDock, this->m_endDock);

		Point arrowPeakOne, arrowPeakTwo;
		arrowPeakOne = this->calculatePointFromAngle(angleStart-.20, 15.0, this->m_endDock);
		arrowPeakTwo = this->calculatePointFromAngle(angleStart+.20, 15.0, this->m_endDock);

		//Zeichnen
		e->Graphics->DrawLine(this->m_edgePen, this->m_endDock, arrowPeakOne);
		e->Graphics->DrawLine(this->m_edgePen, this->m_endDock, arrowPeakTwo);
	}
}

Point edgeView::calculatePointFromAngle( double angle, double hypothenuse, Point origin )
{
	double xdiff, ydiff;
	ydiff = sin(angle) * hypothenuse;
	xdiff = cos(angle) * hypothenuse;
	
	return(Point(origin.X + int(xdiff), origin.Y + int(ydiff)));
}

void edgeView::startConfigDialog( bool refreshAfterDialog)
{
	//initialisiert Dialog
	EdgeChangeDialog^ configDialog = gcnew EdgeChangeDialog();
	this->InitializeDialogValues(configDialog);
	//auf Ok test-Schleife
	if ( configDialog->ShowDialog( this->Parent ) == System::Windows::Forms::DialogResult::OK )
	{
		//Werte setzen
		this->SetDialogValues(configDialog);
		//Richtungstausch Modus
		if (configDialog->RevertDirection){
			vertexView^ realEnd = this->m_endVertex;
			this->m_endVertex = this->m_startVertex;//hier über Variablen gehen, um reDraw zu verhindern
			this->StartVertex = realEnd;
		}
		//toggle redraw um Änderungen anzuzeigen
		if (refreshAfterDialog)
		{
			this->refreshParent();
		}
	}
	delete configDialog;

}

void edgeView::InitializeDialogValues( System::Windows::Forms::Form^ configDialog )
{
	GAPConnect::EdgeChangeDialog^ dialog = dynamic_cast<GAPConnect::EdgeChangeDialog^ >(configDialog);
	dialog->IsArc = this->IsArc;
	dialog->EdgeEnabled = this->IsEnabled;
	dialog->Wichtung = this->Text;
	dialog->Kommentar = this->Kommentar;
	dialog->IsLoop = this->IsLoop;
	dialog->withAidLine = this->m_aidLine;
}

void edgeView::SetDialogValues( System::Windows::Forms::Form^ configDialog )
{
	GAPConnect::EdgeChangeDialog^ dialog = dynamic_cast<GAPConnect::EdgeChangeDialog^ >(configDialog);
	this->Text = dialog->Wichtung;
	this->IsArc = dialog->IsArc;
	this->Kommentar = dialog->Kommentar;
	this->IsEnabled = dialog->EdgeEnabled;
	this->IsLoop = dialog->IsLoop;
	this->m_aidLine = dialog->withAidLine;
}

void edgeView::drawText( System::Windows::Forms::PaintEventArgs^ e )
{
	//Mitte berechnen
	System::Drawing::Point mitteEdge = Point(this->Location.X + this->Width / 2, this->Location.Y + this->Height / 2);
	//Länge berechnen
	double lengthToMitte = this->LengthFromPointToPoint(m_startDock, mitteEdge);
	//20 px als Entfernung für den zu schreibenden Text und dann den inneren Winkel berechnen
	double angleRotation = atan2(10.0, lengthToMitte);
	//originaler WInkel
	double angleOriginal = this->getAnglePointToPoint(this->m_startDock,this->m_endDock);
	//Berechnungen des Textpunktes
	Int32 ydiff = int(sin(angleOriginal-angleRotation-PI)*lengthToMitte);
	Int32 xdiff = int(cos(angleOriginal-angleRotation-PI)*lengthToMitte);
	Point textPkt = Point(this->m_startDock.X + xdiff,this->m_startDock.Y + ydiff);
	//stringFormat
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	//schreibt Text
	if (this->m_aidLine){
		e->Graphics->DrawLine(this->m_drawTools->m_edgeAidLine, textPkt, mitteEdge);
	}
	e->Graphics->DrawString( this->Text, this->m_drawTools->m_drawFont, System::Drawing::Brushes::Black, textPkt, sf);
}

bool edgeView::Contains( System::Drawing::Point pkt )
{
	bool inRectangle = basicView::Contains(pkt);
	if (inRectangle)//verfeinerung der Detection nur Notwendig wenn auch in Control Rectangle geklickt wurde
	{
		//Länge der Linie zu dem geklickten Punkt (liegt auf jedenfall im Rechteck)
		double lengthtoPkt= this->LengthFromPointToPoint(this->m_startDock, pkt);
		//Projektion dieses Punktes auf die Verbindungslinie zwischen den Dockpunkten
		double angle = this->getAnglePointToPoint(this->m_startDock,this->m_endDock);
		Point projection = this->calculatePointFromAngle(angle-PI, lengthtoPkt, this->m_startDock);
		//nun Entfernung von projection zu pkt betrachten; 5px alle Richtungen
		Int32 xdiff, ydiff;
		xdiff = abs(projection.X - pkt.X);
		ydiff = abs(projection.Y - pkt.Y);
		if (xdiff <= 5 && ydiff <= 5)
		{
			return(true);
		}
	}
	return(false);
}

double edgeView::LengthFromPointToPoint(Point^ pkt1, Point^ pkt2){
		//Differenzen
		Int32 xdiff, ydiff;
		xdiff = pkt1->X - pkt2->X;
		ydiff = pkt1->Y - pkt2->Y;
		//Länge
		return( sqrt(double(xdiff*xdiff + ydiff*ydiff)));
}

bool edgeView::Crosses( GAPConnect::edgeView^ otherEdge )
{
	//testen ob das selbe
	if (this == otherEdge){
		return(false);
	}
	//Kontrollrechtecke müssen sich überschneiden
	if (this->GetBorderRectangle.IntersectsWith(otherEdge->GetBorderRectangle))
	{
		if ((this->StartVertex == otherEdge->StartVertex && this->EndVertex == otherEdge->EndVertex || this->StartVertex == otherEdge->EndVertex && this->EndVertex == otherEdge->StartVertex)){
			//Doppelkante, Falsch zurückgeben, da diese durch Knotenverschiebung nicht behoben wird
			return(false);
		}else if (this->StartVertex == otherEdge->StartVertex || this->StartVertex == otherEdge->EndVertex || this->EndVertex == otherEdge->StartVertex || this->EndVertex == otherEdge->EndVertex){
			//wenn startpunkt oder endpunkt gleich, dann kann es keine crossings geben, lediglich inclusionen wenn ein rechteck im anderen ist
			if (this->GetBorderRectangle.Contains(otherEdge->GetBorderRectangle) || otherEdge->GetBorderRectangle.Contains(this->GetBorderRectangle))
			{
				return(true);
			}
			return(false);
		}
		//Geradengleichung aufstellen
		PointF rv1 = this->RichtungsVektor;
		PointF rv2 = otherEdge->RichtungsVektor;
		//wenn Richtungsvektor linear abhängig zu einander dann Parallel; keine Fallunterscheidung, einfach rechnen lassen, findet in dem fall keinen schnittpunkt
		PointF ov1 = this->Ortsvektor;
		PointF ov2 = otherEdge->Ortsvektor;
		//Umgestelltes Gleichungssystem ov1 + faktor1 * rv1 = ov2 + faktor2 * rv2
		float faktor2 = (rv1.Y * (ov1.X-ov2.X) + rv1.X * (ov2.Y - ov1.Y)) / (rv1.Y * rv2.X - rv1.X * rv2.Y);
		float faktor1 = (ov2.Y - ov1.Y + faktor2*rv2.Y)/rv1.Y;
		//Schnittpunkt
		Point schnittpunkt = Point(int(ceil(ov1.X+faktor1*rv1.X)), int(ceil(ov1.Y+faktor1*rv1.Y)));
		if (this->GetBorderRectangle.Contains(schnittpunkt))
		{
			return(true);
		}
	}
	return(false);
}

edgeView::~edgeView()
{
	delete this->m_dataEdge;
	this->m_dataEdge = nullptr;
}

}//namespace ende