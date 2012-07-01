#pragma once
#include "vertexView.h"

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

///<summary> Klasse zur Darstellung der Knoten </summary>
public ref class edgeView:
public basicView
{
public:
	///<summary> Konstruktor </summary>
	edgeView(System::Windows::Forms::Form^ , vertexView^ ,vertexView^ , int);

	///<summary> Methode zum Zeichnen der Kanten </summary>
	System::Void paintEdge(System::Windows::Forms::PaintEventArgs^  e);

private:
	vertexView^ startVertex;
	vertexView^ endVertex;
	System::Drawing::Point createLocation( void );
	System::Drawing::Size createSize( void );
	///<summary> Linien Modus 0 - Normal, 1 - gerichtet </summary>
	int lineMode;
	///<summary> Dockpunkt berechnen </summary>
	void calculateDockingPoint( Point&, Point&);
};

}