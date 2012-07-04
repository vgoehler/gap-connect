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
	///<summary> Unmark and remove Edge Start Vertex </summary>
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
	bool CreateEdge(Point location, bool isArc, bool withConfigDialog);
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


private:
	///<summary>Handle um edge Zeichnen in progress zu signalisieren, speichert den Start, ansonsten nullptr</summary>
	vertexView^ startedDrawing;
	///<summary> enthält die vorhandenen Vertexe</summary>
	System::Collections::Generic::List< GAPConnect::vertexView^ >^ vertexList;
	///<summary> enthält alle Kanten </summary>
	System::Collections::Generic::List< GAPConnect::edgeView^ >^ edgeList;
	///<summary> Definition von Zeichentools </summary>
	GAPConnect::drawTools^ m_drawTools;
	///<summary> Parent </summary>
	System::Windows::Forms::Form^ parent;
	///<summary> lastMarked Element</summary>
	GAPConnect::basicView^ m_lastMarkedElement;
};

}//namespace