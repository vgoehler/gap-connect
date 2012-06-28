#include "StdAfx.h"
#include "edgeView.h"
#include <cstdlib>


namespace GAPConnect {
edgeView::edgeView(System::Windows::Forms::Form^ inParent, System::Windows::Forms::Button^ startVertex, System::Windows::Forms::Button^ endVertex, int mode):lineMode(mode)
{
	this->Parent = inParent;
	this->startVertex = startVertex;
	this->endVertex = endVertex;
	InitializeComponent();
}

System::Drawing::Size edgeView::createSize( void )
{
	int width, height;
	//breite und Höhe müssen um jeweils Hälfte der beiden weniger sein
	width =	abs(this->startVertex->Location.X - this->endVertex->Location.X);
	height = abs(this->startVertex->Location.Y - this->endVertex->Location.Y);
	return(System::Drawing::Size(width, height));
}

void edgeView::InitializeComponent( void )
{
	this->BackColor = System::Drawing::Color::Transparent;
	if (this->startVertex != this->endVertex)//Normaler Modus
	{
		this->Location = this->createLocation();
		this->Size = this->createSize();
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &edgeView::drawEdge_Paint);
	} 
	else//Schlinge - TODO
	{
	}
}

System::Void edgeView::drawEdge_Paint( System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e )
{
	// Location und Size updaten, falls dies von außen getriggert wird.
	this->Location = this->createLocation();
	this->Size = this->createSize();
	//Richtung berechnen
	int lineStartX, lineStartY, lineEndX, lineEndY;
	if (this->startVertex->Location.X < this->endVertex->Location.X)//Start links von Ende
	{
		lineStartX = 0;
		lineEndX = this->Width;
	} 
	else//Start recht von Ende
	{
		lineStartX = this->Width;
		lineEndX = 0;
	}
	if (this->startVertex->Location.Y < this->endVertex->Location.Y)//Start über Ende
	{
		lineStartY = 0;
		lineEndY = this->Height;
	} 
	else//Start unter Ende
	{
		lineStartY = this->Height;
		lineEndY = 0;
	}
	//Linie
	e->Graphics->DrawLine(System::Drawing::Pens::Black, lineStartX, lineStartY, lineEndX, lineEndY);
	//Modus beachten

}

System::Drawing::Point edgeView::createLocation( void ){
	int locX, locY;
	//rechts oben ist Location, also kleinstes X und kleinstes Y + Hälfte der breite bzw. höhe der entsprechenden Schaltfläche
	locX = this->startVertex->Location.X < this->endVertex->Location.X ? this->startVertex->Location.X + this->startVertex->Width /2 : this->endVertex->Location.X + this->endVertex->Width /2;
	locY = this->startVertex->Location.Y < this->endVertex->Location.Y ? this->startVertex->Location.Y + this->startVertex->Height /2 : this->endVertex->Location.Y + this->endVertex->Height/2;
	return (System::Drawing::Point(locX, locY));
}
}