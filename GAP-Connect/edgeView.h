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
	edgeView(System::Windows::Forms::Form^ , GAPConnect::drawTools^, vertexView^ ,vertexView^ , int, Graph^ parentDataGraph);
	///<summary> Konstruktor aus Daten </summary>
	edgeView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, Graph^ parentDataGraph, Kante^ dataEdge);
	///<summary> Destruktor </summary>
	~edgeView();
	///<summary> Methode zum Zeichnen der Kanten </summary>
	System::Void drawEdge(System::Windows::Forms::PaintEventArgs^  e);
	///<summary> Ist eine Schlinge </summary>
	property bool IsLoop{
		bool get(void){
			if (this->StartVertex != nullptr && this->EndVertex != nullptr){
				return(this->m_startVertex == this->m_endVertex ? true : false);
			}else{
				return(false);//wenn wir keine Knoten definiert haben falsch zur�ckgeben; kann nur im Ladefall passieren.
			}
		}
		void set(bool inValue){
			if (inValue){//Gleich setzen geht
				this->EndVertex = this->StartVertex;
			}else{//K�nnen aus einer Schlinge keine Kanten machen
				//throw gcnew Exception("K�nnen aus einer Schlinge keine Kante machen!");
			}
		}
	}
	///<summary> Weist den neuen StartVertex zu und f�hrt notwendige Berechnungen aus </summary>
	property vertexView^ StartVertex{
		void set(vertexView^ inValue){
			this->m_startVertex = inValue;
			if (this->m_endVertex != nullptr)
			{//Vermeiden von Initialiserungsfehlern
				this->calculateDockingPoint();
			}
		}
		vertexView^ get(void){
			return(this->m_startVertex);
		}
	}
	///<summary> Weist den neuen EndVertex zu und f�hrt notwendige Berechnungen aus </summary>
	property vertexView^ EndVertex{
		void set(vertexView^ inValue){
			this->m_endVertex = inValue;
			this->calculateDockingPoint();
		}
		vertexView^ get(void){
			return(this->m_endVertex);
		}
	}
	///<summary> Aktivierungszustand des Elements kann gesetzt werden bzw. abgefragt. �berschrieben.</summary>
	property bool IsEnabled{
		bool get( void ){
			return(basicView::IsEnabled);
		}
		virtual void set(bool inValue) override{
			basicView::IsEnabled = inValue;
			if (inValue){
				this->m_edgePen = this->m_drawTools->m_edge;
			}else{
				this->m_edgePen = this->m_drawTools->m_edgeDeactivated;
			}
			this->m_dataEdge->shape = inValue ? NORMAL : DISABLED;
		}
	}
	///<summary> Methode zum Aufrufen des Konfigurationsdialogs</summary>
	virtual void startConfigDialog( bool refreshAfterDialog ) override;
	///<summary> Property gibt an ob mode auf Bogen zeichnen gesetzt ist, bzw. l��t sich setzen, oder wenn als false gesetzt normaler Modus </summary>
	property bool IsArc{
		bool get ( void ){
			return(this->m_lineMode == 1 ? true:false);
		}
		void set ( bool inValue){
			this->m_lineMode = (inValue ? 1 : 0);
			this->m_dataEdge->gerichtet = this->m_lineMode;
		}
	}
	///<summary> Contains Methode des Parent hier �berschrieben</summary>
	bool Contains (System::Drawing::Point pkt);
	///<summary> Dockpunkt berechnen </summary>
	void calculateDockingPoint( void );
	///<summary> Gibt Daten Kante zur�ck, kann auch gesetzt werden </summary>
	property Kante^ DataEdge{
		Kante^ get( void ){
			return(this->m_dataEdge);
		}
	}
	///<summary> Eintrag f�r die Wertung </summary>
	property System::String^ Text{
			void set (System::String^ inValue){
				this->m_dataEdge->string_wertung = inValue;
			}
			System::String^ get (void){
				return(this->m_dataEdge->string_wertung);
			}
		}
	///<summary> Eintrag f�r den Kommentar </summary>
	property System::String^ Kommentar{
			void set (System::String^ inValue){
				this->m_dataEdge->comment->label = inValue;
			}
			System::String^ get (void){
				return(this->m_dataEdge->comment->label);
			}
		}
	///<summary> Hilfslinie an/aus</summary>
	property bool AidLine{
		void set(bool inValue){
			this->m_aidLine = inValue;
			if (this->DataEdge != nullptr)
			{
				this->DataEdge->aid_line = inValue;
			}
		}
	}
	///<summary> Schreibt den Winkel </summary>
	property double LoopAngle{
		void set(double inValue){
			this->m_dataEdge->loop_direction = inValue;
			if (this->IsLoop){
				this->calculateLoopPosition();
			}
		}
		double get(void){
			if (this->m_dataEdge == nullptr)
			{
				return(0);
			}else{
				return(this->m_dataEdge->loop_direction);
			}
		}
	}
	///<summary> Holt den Winkel vom Zentrum bis zum �bergebennen Punkt </summary>
	double getAngleCenterToPoint(Point^ pkt);


private:
	vertexView^ m_startVertex;
	vertexView^ m_endVertex;
	System::Drawing::Point createLocation( void );
	System::Drawing::Size createSize( void );
	///<summary> Linien Modus 0 - Normal, 1 - gerichtet </summary>
	int m_lineMode;
	///<summary> Dockpunkt Start </summary>
	Point m_startDock;
	///<summary> Dockpunkt End </summary>
	Point m_endDock;
	///<summary> berechnet Winkel zwischen 2 beliebigen Punkten </summary>
	double getAnglePointToPoint(Point^, Point^);
	///<summary> Errechnet KoordinatenPaar aus Winkel und L�nge </summary>
	Point calculatePointFromAngle(double angle, double hypothenuse, Point origin);
	///<summary> Kalkuliert Punkte f�r Pfeil und Zeichnet diesen</summary>
	void drawArrow(System::Windows::Forms::PaintEventArgs^ e);
	///<summary> Zeichentool zum Zeichnen der Linie </summary>
	System::Drawing::Pen^ m_edgePen;
	///<summary> Methode zum Initialisieren der DialogWerte</summary>
	void InitializeDialogValues(System::Windows::Forms::Form^ configDialog);
	///<summary> Methode, die die Kante aus den Werten des Dialogs initialisiert</summary>
	void SetDialogValues (System::Windows::Forms::Form^ configDialog);
	///<summary> schreibt die Kantenbewertung </summary>
	void drawText ( System::Windows::Forms::PaintEventArgs^ e, bool straightToCenter);
	///<summary> berechnet die Entfernung zwischen 2 Punkten </summary>
	double edgeView::LengthFromPointToPoint(Point^ pkt1, Point^ pkt2);
	///<summary> Zeichnet einen Loop </summary>
	void edgeView::drawLoop( System::Windows::Forms::PaintEventArgs^ e);
	///<summary> sollen Hilfslinien von der Kante zum Text angezeigt werden </summary>
	bool m_aidLine;
	///<summary> Anschlu� an Datenmember </summary>
	Kante^ m_dataEdge;
	///<summary> oberer Kontrollpunkt f�r Loop </summary>
	Point m_startLoopCtrlPt;
	///<summary> unterer Kontrollpunkt f�r Loop </summary>
	Point m_endLoopCtrlPt;
	///<summary> berechnet die Rahmenpunkte des Loop und die Position des Kontrollrechtecks</summary>
	void calculateLoopPosition( void );
};

}//namespace