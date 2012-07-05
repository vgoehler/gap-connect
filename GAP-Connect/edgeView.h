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
	edgeView(System::Windows::Forms::Form^ , GAPConnect::drawTools^, vertexView^ ,vertexView^ , int);

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
	property PointF RichtungsVektor{
		PointF get( void ){
			return(PointF(float(this->m_endDock.X - this->m_startDock.X), float(this->m_endDock.Y - this->m_startDock.Y)));
		}
	}
	property PointF Ortsvektor{
		PointF get(void){
			return(PointF(float(this->m_startDock.X), float(this->m_startDock.Y)));
		}
	}

	///<summary> Contains Methode des Parent hier Überschrieben</summary>
	bool Contains (System::Drawing::Point pkt);
	///<summary> Zwei Ecken kreuzen einander </summary>
	bool Crosses (GAPConnect::edgeView^ otherEdge){
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
			//wenn Richtungsvektor linear abhängig zu einander dann Parallel


			PointF ov1 = this->Ortsvektor;
			PointF ov2 = otherEdge->Ortsvektor;
			float faktor1, faktor2;
			Point schnittpunkt;
			//Richtungsvektoren die eine Komponente gleich 0 haben beachten
			if (rv1.X == 0 || rv1.Y == 0){
				if (rv1.X == 0){
					faktor2 = (ov1.X - ov2.X)/rv2.X;
				}else if (rv1.Y == 0){
					faktor2 = (ov1.Y - ov2.Y)/rv2.Y;
				}
				schnittpunkt = Point(int(ceil(ov2.X + faktor2*rv2.X)), int(ceil(ov2.Y + faktor2*rv2.Y)));
			}else{
				//Umgestelltes Gleichungssystem ov1 + faktor1 * rv1 = ov2 + faktor2 * rv2
				faktor2 = (rv1.Y / rv1.X) * (ov1.X - ov2.X + (rv1.X / rv1.Y) * (ov2.Y - ov1.Y))/((rv1.Y / rv1.X) * rv2.X - rv2.Y);
				faktor1 = (ov2.Y - ov1.Y + faktor2*rv2.Y)/rv1.Y;
				//Schnittpunkt
				schnittpunkt = Point(int(ceil(ov1.X+faktor1*rv1.X)), int(ceil(ov1.Y+faktor1*rv1.Y)));
			}
			if (this->GetBorderRectangle.Contains(schnittpunkt))
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
	///<summary> schreibt die Kantenbewertung </summary>
	void drawText ( System::Windows::Forms::PaintEventArgs^ e);
	///<summary> berechnet die Entfernung zwischen 2 Punkten </summary>
	double edgeView::LengthFromPointToPoint(Point^ pkt1, Point^ pkt2);
};

}//namespace