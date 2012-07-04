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
	property bool IsLoop{
		bool get(void){
			return(this->m_startVertex == this->m_endVertex ? true : false);
		}
		void set(bool inValue){
			if (inValue){//Gleich setzen geht
				this->EndVertex = this->StartVertex;
			}else{//Können aus einer Schlinge keine Kanten machen
			}
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
	///<summary> Aktivierungszustand des Elements kann gesetzt werden bzw. abgefragt. Überschrieben.</summary>
	property bool IsEnabled{
		bool get( void ){
			return(basicView::IsEnabled);
		}
		void set(bool inValue){
			basicView::IsEnabled = inValue;
			if (inValue){
				this->m_edgePen = this->m_drawTools->m_edge;
			}else{
				this->m_edgePen = this->m_drawTools->m_edgeDeactivated;
			}
		}
	}
	///<summary> Methode zum Aufrufen des Konfigurationsdialogs</summary>
	void startConfigDialog( void );
	///<summary> Property gibt an ob mode auf Bogen zeichnen gesetzt ist, bzw. läßt sich setzen, oder wenn als false gesetzt normaler Modus </summary>
	property bool IsArc{
		bool get ( void ){
			return(this->m_lineMode == 1 ? true:false);
		}
		void set ( bool inValue){
			this->m_lineMode = (inValue ? 1 : 0);
		}
	}
	///<summary> Contains Methode des Parent hier Überschrieben</summary>
	bool Contains (System::Drawing::Point pkt){
		bool inRectangle = basicView::Contains(pkt);
		if (inRectangle)//verfeinerung der Detection nur Notwendig wenn auch in Control Rectangle geklickt wurde
		{
			//Länge der Linie zu dem geklickten Punkt (liegt auf jedenfall im Rechteck)
			double lengthtoPkt= sqrt(pow(double(this->m_startDock.X-pkt.X),2)+pow(double(this->m_startDock.Y-pkt.Y),2));
			//Projektion dieses Punktes auf die Verbindungslinie zwischen den Dockpunkten
			double angle = this->getRadianStartToEnd(this->m_startDock,this->m_endDock);
			Point projection = this->calculatePointFromAngle(angle-PI, lengthtoPkt, this->m_startDock);
			//nun Entfernung von projection zu pkt betrachten; 5px alle Richtungen
			int xdiff = abs(projection.X - pkt.X);
			int ydiff = abs(projection.Y - pkt.Y);
			if (xdiff <= 5 && ydiff <= 5)
			{
				return(true);
			}
		}
		return(false);
	}

private:
	vertexView^ m_startVertex;
	vertexView^ m_endVertex;
	System::Drawing::Point createLocation( void );
	System::Drawing::Size createSize( void );
	///<summary> Linien Modus 0 - Normal, 1 - gerichtet </summary>
	int m_lineMode;
	///<summary> Dockpunkt berechnen </summary>
	void calculateDockingPoint( void );
	///<summary> Dockpunkt Start </summary>
	Point m_startDock;
	///<summary> Dockpunkt End </summary>
	Point m_endDock;
	///<summary> Winkel von Start zu End jeweils Knoten Mitte</summary>
	double getRadianStartToEnd(void);
	///<summary> berechnet Winkel zwischen 2 beliebigen Punkten </summary>
	double getRadianStartToEnd(Point^, Point^);
	///<summary> Errechnet KoordinatenPaar aus Winkel und Länge </summary>
	Point calculatePointFromAngle(double angle, double hypothenuse, Point origin);
	///<summary> Kalkuliert Punkte für Pfeil und Zeichnet diesen</summary>
	void drawArrow(System::Windows::Forms::PaintEventArgs^ e);
	///<summary> Zeichentool zum Zeichnen der Linie </summary>
	System::Drawing::Pen^ m_edgePen;
	///<summary> Methode zum Initialisieren der DialogWerte</summary>
	void InitializeValues(System::Windows::Forms::Form^ configDialog);
	///<summary> Methode, die die Kante aus den Werten des Dialogs initialisiert</summary>
	void SetValues (System::Windows::Forms::Form^ configDialog);
};

}//namespace