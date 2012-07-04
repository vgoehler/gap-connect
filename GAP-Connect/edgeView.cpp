#include "StdAfx.h"
#include "edgeView.h"


namespace GAPConnect {
edgeView::edgeView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, vertexView^ startVertex, vertexView^ endVertex, int mode):basicView(inParent, inDrawTools), m_lineMode(mode), m_startVertex(nullptr), m_endVertex(nullptr)
{
	this->IsEnabled = true;//Enablen um Stift zu initialisieren
	this->StartVertex = startVertex;
	this->EndVertex = endVertex;
}

System::Drawing::Size edgeView::createSize( void )
{
	int width, height;
	//breite und Höhe müssen um jeweils Hälfte der beiden weniger sein
	width =	abs(this->m_startDock.X - this->m_endDock.X);
	height = abs(this->m_startDock.Y - this->m_endDock.Y);
	return(System::Drawing::Size(width, height));
}

System::Void edgeView::paintEdge( System::Windows::Forms::PaintEventArgs^ e )
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
	if (this->Text != L"")
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
		double winkel;
		winkel = this->getRadianStartToEnd();
		if (winkel >= -1*PI/4 && winkel < PI/4){
			//Linker Dockpunkt beim Start
			this->m_startDock = Point(this->m_startVertex->Location.X, this->m_startVertex->Location.Y + this->m_startVertex->Height/2);
			//Rechter Dockpunkt bei Ende
			this->m_endDock = Point(this->m_endVertex->Location.X + this->m_endVertex->Width, this->m_endVertex->Location.Y + this->m_endVertex->Height/2);
		}else if (winkel >= PI/4 && winkel < 3*PI/4){
			//Oberer Dockpunkt bei Start
			this->m_startDock = Point(this->m_startVertex->Location.X + this->m_startVertex->Width/2, this->m_startVertex->Location.Y);
			//Unterer Dockpunkt bei Ende
			this->m_endDock = Point(this->m_endVertex->Location.X + this->m_endVertex->Width/2, this->m_endVertex->Location.Y + this->m_endVertex->Height);
		}else if (winkel >= -3*PI/4 && winkel < -1*PI/4 ){
			//Unterer Dockpunkt bei Start
			this->m_startDock = Point(this->m_startVertex->Location.X + this->m_startVertex->Width/2, this->m_startVertex->Location.Y + this->m_startVertex->Height);
			//Oberer Dockpunkt bei Ende
			this->m_endDock = Point(this->m_endVertex->Location.X + this->m_endVertex->Width/2, this->m_endVertex->Location.Y);
		}else{
			//Rechter Dockpunkt bei Start
			this->m_startDock = Point(this->m_startVertex->Location.X + this->m_startVertex->Width, this->m_startVertex->Location.Y + this->m_startVertex->Height/2);
			//Linker Dockpunkt bei Ende
			this->m_endDock = Point(this->m_endVertex->Location.X, this->m_endVertex->Location.Y + this->m_endVertex->Height/2);
		}
	}
	}

double edgeView::getRadianStartToEnd( void ){
	return(this->getRadianStartToEnd(this->m_startVertex->LocationCenter, this->m_endVertex->LocationCenter));
}

double edgeView::getRadianStartToEnd( Point^ startPoint, Point^ endPoint ){
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
		angleStart = this->getRadianStartToEnd(this->m_startDock, this->m_endDock);

		Point arrowPeakOne, arrowPeakTwo;
		arrowPeakOne = this->calculatePointFromAngle(angleStart-.20, 15.0, this->m_endDock);
		arrowPeakTwo = this->calculatePointFromAngle(angleStart+.20, 15.0, this->m_endDock);

		//Zeichnen
		e->Graphics->DrawLine(this->m_drawTools->m_edge, this->m_endDock, arrowPeakOne);
		e->Graphics->DrawLine(this->m_drawTools->m_edge, this->m_endDock, arrowPeakTwo);
	}
}

Point edgeView::calculatePointFromAngle( double angle, double hypothenuse, Point origin )
{
	double xdiff, ydiff;
	ydiff = sin(angle) * hypothenuse;
	xdiff = cos(angle) * hypothenuse;
	
	return(Point(origin.X + int(xdiff), origin.Y + int(ydiff)));
}

void edgeView::startConfigDialog( void )
{
	//initialisiert Dialog
	EdgeChangeDialog^ configDialog = gcnew EdgeChangeDialog();
	this->InitializeValues(configDialog);
	//auf Ok test-Schleife
	if ( configDialog->ShowDialog( this->Parent ) == System::Windows::Forms::DialogResult::OK )
	{
		//Werte setzen
		this->SetValues(configDialog);
		//Richtungstausch Modus
		if (configDialog->RevertDirection){
			vertexView^ realEnd = this->m_endVertex;
			this->m_endVertex = this->m_startVertex;//hier über Variablen gehen, um reDraw zu verhindern
			this->StartVertex = realEnd;
		}
		//toggle redraw um Änderungen anzuzeigen
		this->refreshParent();
	}
	delete configDialog;

}

void edgeView::InitializeValues( System::Windows::Forms::Form^ configDialog )
{
	GAPConnect::EdgeChangeDialog^ dialog = dynamic_cast<GAPConnect::EdgeChangeDialog^ >(configDialog);
	dialog->IsArc = this->IsArc;
	dialog->EdgeEnabled = this->IsEnabled;
	dialog->Wichtung = this->Text;
	dialog->Kommentar = this->Kommentar;
	dialog->IsLoop = this->IsLoop;
}

void edgeView::SetValues( System::Windows::Forms::Form^ configDialog )
{
	GAPConnect::EdgeChangeDialog^ dialog = dynamic_cast<GAPConnect::EdgeChangeDialog^ >(configDialog);
	this->Text = dialog->Wichtung;
	this->IsArc = dialog->IsArc;
	this->Kommentar = dialog->Kommentar;
	this->IsEnabled = dialog->EdgeEnabled;
	this->IsLoop = dialog->IsLoop;
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
	double angleOriginal = this->getRadianStartToEnd(this->m_startDock,this->m_endDock);
	//Berechnungen des Textpunktes
	Int32 ydiff = int(sin(angleOriginal-angleRotation-PI)*lengthToMitte);
	Int32 xdiff = int(cos(angleOriginal-angleRotation-PI)*lengthToMitte);
	Point textPkt = Point(this->m_startDock.X + xdiff,this->m_startDock.Y + ydiff);
	//stringFormat
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	//schreibt Text
	e->Graphics->DrawLine(this->m_drawTools->m_edgeHilfslinie, textPkt, mitteEdge);
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
		double angle = this->getRadianStartToEnd(this->m_startDock,this->m_endDock);
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

}//namespace ende