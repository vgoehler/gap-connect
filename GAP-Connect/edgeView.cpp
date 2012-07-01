#include "StdAfx.h"
#include "edgeView.h"


namespace GAPConnect {
edgeView::edgeView(System::Windows::Forms::Form^ inParent, vertexView^ startVertex, vertexView^ endVertex, int mode):basicView(inParent), lineMode(mode)
{
	this->startVertex = startVertex;
	this->endVertex = endVertex;
	if (this->startVertex != this->endVertex)//Normaler Modus
	{
		this->Location = this->createLocation();
		this->Size = this->createSize();
	} 
	else//Schlinge - TODO
	{
	}
}

System::Drawing::Size edgeView::createSize( void )
{
	int width, height;
	//breite und Höhe müssen um jeweils Hälfte der beiden weniger sein
	width =	abs(this->startVertex->Location.X - this->endVertex->Location.X);
	height = abs(this->startVertex->Location.Y - this->endVertex->Location.Y);
	return(System::Drawing::Size(width, height));
}

System::Void edgeView::paintEdge( System::Windows::Forms::PaintEventArgs^ e )
{
	// Location und Size updaten, falls dies von außen getriggert wird.
	this->Location = this->createLocation();
	this->Size = this->createSize();
	//Dockpunkte der Kanten berechnen immer Mitte
	Point startP, endP;
	this->calculateDockingPoint(startP, endP);
	//Linie
	e->Graphics->DrawLine(gcnew System::Drawing::Pen(System::Drawing::Color::BlueViolet, 2), startP, endP);
	//Modus beachten

}

System::Drawing::Point edgeView::createLocation( void ){
	int locX, locY;
	//rechts oben ist Location, also kleinstes X und kleinstes Y + Hälfte der breite bzw. höhe der entsprechenden Schaltfläche
	locX = this->startVertex->Location.X < this->endVertex->Location.X ? this->startVertex->Location.X + this->startVertex->Width /2 : this->endVertex->Location.X + this->endVertex->Width /2;
	locY = this->startVertex->Location.Y < this->endVertex->Location.Y ? this->startVertex->Location.Y + this->startVertex->Height /2 : this->endVertex->Location.Y + this->endVertex->Height/2;
	return (System::Drawing::Point(locX, locY));
}

void edgeView::calculateDockingPoint( Point& startP, Point& endP)
{
	//Dockpunkte der Kanten berechnen immer Mitte
	//mitte oben  + width /2
	//mitte unten + width /2 + height
	//mitte links + height /2
	//mitte rechts + width + height /2
	//für mitte oben muss x des ziels kleiner sein und größer als die y differenz
	//für mitte links muss y des ziels größer sein und größer als die x differenz
	Int32 startPXMitte, startPYMitte, endPXMitte, endPYMitte;
	startPXMitte = this->startVertex->Location.X + this->startVertex->Width /2;
	endPXMitte = this->endVertex->Location.X + this->endVertex->Width /2;
	startPYMitte = this->startVertex->Location.Y + this->startVertex->Height /2;
	endPYMitte = this->endVertex->Location.Y + this->endVertex->Height /2;
	//Unterscheidung ob von oben zu unten oder links nach rechts
	if (abs(startPXMitte-endPXMitte) < abs(startPYMitte-endPYMitte)){
		//y entfernung größer also links recht
		if (startPYMitte > endPYMitte){
			//rechtsnach links
			startP = Point(this->startVertex->Location.X, this->startVertex->Location.Y + this->startVertex->Height /2);
			endP = Point(this->endVertex->Location.X + this->endVertex->Width, this->endVertex->Location.Y + this->endVertex->Height /2);
		}else{
			//links nach rechts
			startP = Point(this->endVertex->Location.X + this->endVertex->Width, this->endVertex->Location.Y + this->endVertex->Height /2);
			endP = Point(this->startVertex->Location.X, this->startVertex->Location.Y + this->startVertex->Height /2);
		}
	}else{
		//x entfernung größer also oben unten
		if (startPXMitte > endPXMitte)
		{
			startP = Point(this->startVertex->Location.X + this->startVertex->Width /2, this->startVertex->Location.Y);
			endP = Point(this->endVertex->Location.X + this->endVertex->Width /2, this->endVertex->Location.Y + this->endVertex->Height);
		}else{
			startP = Point(this->endVertex->Location.X + this->endVertex->Width /2, this->endVertex->Location.Y + this->endVertex->Height);
			endP = Point(this->startVertex->Location.X + this->startVertex->Width /2, this->startVertex->Location.Y);
		}
	}
}

}