#pragma once

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

public ref class graphView
{
public:
	graphView( void );
	graphView(System::Windows::Forms::Form^);
	~graphView(void);
	///<summary> demarked den Last Marked Element</summary>
	void unmarkLastMarked( void ){
		this->unmarkElement(this->m_lastMarkedElement);
		this->m_lastMarkedElement = nullptr;
	}
	///<summary> Unmark and remove Edge Start Vertex, only in Draw Line usefull.</summary>
	void unmarkElement( void );
	///<summary> Unmark beliebigen übergebenen Vertex </summary>
	void unmarkElement( GAPConnect::basicView^ element);
	///<summary> Gibt Anzahl der Vertexe zurück</summary>
	property Int32 CountVertex{
		Int32 get ( void ){
			return (this->vertexList->Count);
		}
	}
	///<summary> erzeugt einen knoten </summary>
	void CreateVertex(Point location, bool isRound, bool withConfigDialog);
	///<summary> Erschafft eine Kante </summary>
	bool CreateEdge(Point location, bool isArc, bool withConfigDialog, bool forceConfigDialog);
	///<summary> Markiert einen Vertex oder eine Kante und stellt sicher das auch nur ein Objekt ausgewählt ist</summary>
	void markElement( GAPConnect::basicView^ element);
	///<summary> Zeichnet alle Elemente des Graph </summary>
	void drawGraph( System::Windows::Forms::PaintEventArgs^  e );
	///<summary> holt ein Handle auf ein gezeichnetes Objekt wo der mousezeiger draufzeigt </summary>
	GAPConnect::edgeView^ getHandleOfEdge(System::Drawing::Point pkt);
	///<summary> Handle auf Vertex </summary>
	GAPConnect::vertexView^ getHandleOfVertex (System::Drawing::Point pkt);
	///<summary> Löscht über ein Handle ein Objekt </summary>
	void deleteDrawnElement(GAPConnect::basicView^ element);
	///<summary> Gibt letztes markiertes Objekt zurück </summary>
	property GAPConnect::basicView^ getMarkedElement{
		GAPConnect::basicView^ get( void ){
			return(this->m_lastMarkedElement);
		}
	}
	///<summary> Gibt an ob noch ein Element ausgewählt ist </summary>
	bool IsSomethingMarked( void );
	///<summary> Gibt Wahrheitswert zurück wenn sich Übergabekante mit irgendeiner anderen Kante schneidet. </summary>
	bool IsEdgeCrossing( edgeView^ inEdge );
	///<summary> Löscht alle Kanten und Zeichnet dann alle Möglichen! Kompletter Graph!</summary>
	void CreateCompleteGraph( void );
	///<summary> Zeigt an ob wir uns im Linienzeichnen befinden </summary>
	property bool IsDrawingLine{
		bool get (void){
			return((this->m_startedDrawing == nullptr) ? false : true );
		}
	}
	///<summary> Gibt Anzahl der Kanten zurück </summary>
	property Int32 CountEdges{
		Int32 get ( void ){
			return(this->edgeList->Count);
		}
	}
	///<summary> Berechnet die Dockpunkte einer Kante zu einem Knoten neu </summary>
	void ReCalcDockingPoints(GAPConnect::vertexView^ vertex);

private:
	///<summary>Handle um edge Zeichnen in progress zu signalisieren, speichert den Start, ansonsten nullptr</summary>
	vertexView^ m_startedDrawing;
	///<summary> enthält die vorhandenen Vertexe</summary>
	System::Collections::Generic::List< GAPConnect::vertexView^ >^ vertexList;
	///<summary> enthält alle Kanten </summary>
	System::Collections::Generic::List< GAPConnect::edgeView^ >^ edgeList;
	///<summary> Definition von Zeichentools </summary>
	GAPConnect::drawTools^ m_drawTools;
	///<summary> Parent </summary>
	System::Windows::Forms::Form^ m_parent;
	///<summary> lastMarked Element</summary>
	GAPConnect::basicView^ m_lastMarkedElement;
};

}//namespace