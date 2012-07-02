#pragma once
#include "vertexView.h"
#include <cmath>
#define PI 3.14159265

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
	///<summary> Ist eine Schlinge </summary>
	property bool isLoop{
		bool get(void){
			return(this->m_startVertex == this->m_endVertex ? true : false);
		}
	}
	///<summary> Weist den neuen StartVertex zu und führt notwendige Berechnungen aus </summary>
	property vertexView^ StartVertex{
		void set(vertexView^ inValue){
			this->m_startVertex = inValue;
			if (this->m_endVertex != nullptr)
			{//Vermeiden von Initialiserungsfehlern
				this->calculateDockingPoint();
				this->Location = this->createLocation();
				this->Size = this->createSize();
			}
		}
		vertexView^ get(void){
			return(this->m_startVertex);
		}
	}
	///<summary> Weist den neuen EndVertex zu und führt notwendige Berechnungen aus </summary>
	property vertexView^ EndVertex{
		void set(vertexView^ inValue){
			this->m_endVertex = inValue;
			this->calculateDockingPoint();
			this->Location = this->createLocation();
			this->Size = this->createSize();
		}
		vertexView^ get(void){
			return(this->m_endVertex);
		}
	}

private:
	vertexView^ m_startVertex;
	vertexView^ m_endVertex;
	System::Drawing::Point createLocation( void );
	System::Drawing::Size createSize( void );
	///<summary> Linien Modus 0 - Normal, 1 - gerichtet </summary>
	int lineMode;
	///<summary> Dockpunkt berechnen </summary>
	void calculateDockingPoint( void );
	///<summary> Dockpunkt Start </summary>
	Point m_startDock;
	///<summary> Dockpunkt End </summary>
	Point m_endDock;
	///<summary> Winkel von Start zu End </summary>
	double getRadianStartToEnd(void);
	///<summary> Errechnet KoordinatenPaar aus Winkel und Länge </summary>
	Point calculatePointFromAngle(double angle, double hypothenuse, Point origin);
	///<summary> Kalkuliert Punkte für Pfeil und Zeichnet diesen</summary>
	void drawArrow(System::Windows::Forms::PaintEventArgs^ e);
};

}//namespace