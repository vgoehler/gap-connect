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
	///<summary> Destruktor </summary>
	~edgeView();
	///<summary> Methode zum Zeichnen der Kanten </summary>
	System::Void drawEdge(System::Windows::Forms::PaintEventArgs^  e);
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
	virtual void startConfigDialog( bool refreshAfterDialog ) override;
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
	bool Crosses (GAPConnect::edgeView^ otherEdge);
	///<summary> Dockpunkt berechnen </summary>
	void calculateDockingPoint( void );
	///<summary> Gibt Daten Kante zurück, kann auch gesetzt werden </summary>
	property Kante^ DataEdge{
		Kante^ get( void ){
			return(this->m_dataEdge);
		}
	}
	///<summary> Eintrag für die Wertung </summary>
	property System::String^ Text{
			void set (System::String^ inValue){
				this->m_dataEdge->string_wertung = inValue;
			}
			System::String^ get (void){
				return(this->m_dataEdge->string_wertung);
			}
		}
	///<summary> Eintrag für den Kommentar </summary>
	property System::String^ Kommentar{
			void set (System::String^ inValue){
				this->m_dataEdge->comment->label = inValue;
			}
			System::String^ get (void){
				return(this->m_dataEdge->comment->label);
			}
		}

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
	///<summary> Errechnet KoordinatenPaar aus Winkel und Länge </summary>
	Point calculatePointFromAngle(double angle, double hypothenuse, Point origin);
	///<summary> Kalkuliert Punkte für Pfeil und Zeichnet diesen</summary>
	void drawArrow(System::Windows::Forms::PaintEventArgs^ e);
	///<summary> Zeichentool zum Zeichnen der Linie </summary>
	System::Drawing::Pen^ m_edgePen;
	///<summary> Methode zum Initialisieren der DialogWerte</summary>
	void InitializeDialogValues(System::Windows::Forms::Form^ configDialog);
	///<summary> Methode, die die Kante aus den Werten des Dialogs initialisiert</summary>
	void SetDialogValues (System::Windows::Forms::Form^ configDialog);
	///<summary> schreibt die Kantenbewertung </summary>
	void drawText ( System::Windows::Forms::PaintEventArgs^ e);
	///<summary> berechnet die Entfernung zwischen 2 Punkten </summary>
	double edgeView::LengthFromPointToPoint(Point^ pkt1, Point^ pkt2);
	///<summary> sollen Hilfslinien von der Kante zum Text angezeigt werden </summary>
	bool m_aidLine;
	///<summary> Anschluß an Datenmember </summary>
	Kante^ m_dataEdge;
};

}//namespace