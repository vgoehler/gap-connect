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
	///<summary> Unmark beliebigen �bergebenen Vertex </summary>
	void unmarkElement( GAPConnect::basicView^ element);
	///<summary> Gibt Anzahl der Vertexe zur�ck</summary>
	property Int32 CountVertex{
		Int32 get ( void ){
			return (this->vertexList->Count);
		}
	}
	///<summary> erzeugt einen knoten </summary>
	void CreateVertex(Point location, bool isRound, bool withConfigDialog);
	///<summary> Erschafft eine Kante </summary>
	bool CreateEdge(Point location, bool isArc, bool withConfigDialog, bool forceConfigDialog);
	///<summary> Markiert einen Vertex oder eine Kante und stellt sicher das auch nur ein Objekt ausgew�hlt ist</summary>
	void markElement( GAPConnect::basicView^ element);
	///<summary> Zeichnet alle Elemente des Graph </summary>
	void drawGraph( System::Windows::Forms::PaintEventArgs^  e );
	///<summary> �berladen, holt ein Handle auf erstes Element unter pkt </summary>
	GAPConnect::basicView^ getHandleOfElement(System::Drawing::Point pkt);
	///<summary> Holt ein Handle auf ein generisches Element, je nach Wahrheitswerten aus Kanten und/oder Knoten </summary>
	GAPConnect::basicView^ getHandleOfElement(System::Drawing::Point pkt, bool Edges, bool Vertex);
	///<summary> Handle auf Kante </summary>
	GAPConnect::edgeView^ getHandleOfEdge(System::Drawing::Point pkt);
	///<summary> Handle auf Vertex </summary>
	GAPConnect::vertexView^ getHandleOfVertex (System::Drawing::Point pkt);
	///<summary> L�scht �ber ein Handle ein Objekt </summary>
	void deleteDrawnElement(GAPConnect::basicView^ element);
	///<summary> Gibt letztes markiertes Objekt zur�ck </summary>
	property GAPConnect::basicView^ getMarkedElement{
		GAPConnect::basicView^ get( void ){
			return(this->m_lastMarkedElement);
		}
	}
	///<summary> Gibt an ob noch ein Element ausgew�hlt ist </summary>
	bool IsSomethingMarked( void );
	///<summary> Gibt an ob ein Knoten markiert ist</summary>
	bool IsVertexMarked( void );
	///<summary> L�scht alle Kanten und Zeichnet dann alle M�glichen! Kompletter Graph!</summary>
	void CreateCompleteGraph( void );
	///<summary> Zeigt an ob wir uns im Linienzeichnen befinden </summary>
	property bool IsDrawingLine{
		bool get (void){
			return((this->m_startedDrawing == nullptr) ? false : true );
		}
	}
	///<summary> Gibt Anzahl der Kanten zur�ck </summary>
	property Int32 CountEdges{
		Int32 get ( void ){
			return(this->edgeList->Count);
		}
	}
	///<summary> Berechnet die Dockpunkte einer Kante zu einem Knoten neu </summary>
	void ReCalcDockingPoints(GAPConnect::vertexView^ vertex);
	///<summary> �berpr�ft einen Punkt, an dem ein Vertex gezeichnet werden soll, auf G�ltigkeit </summary>
	bool vertexTooClose( Point pkt, Size sz);
	///<summary> weitere Version von vertexTooClose allerdings wird noch ein initialisierender Knoten �bergeben - Drag'nDrop</summary>
	bool vertexTooClose( Point pkt, Size sz, vertexView^ vertex);
	///<summary> holt/setzt den Namen des Graphen </summary>
	property System::String^ Graphname{
		void set(System::String^ inValue){
			this->m_dataGraph->name = inValue;
		}
		System::String^ get( void ){
			return(this->m_dataGraph->name);
		}
	}
	///<summary> schreibt den Datengraphen in eine Datei </summary>
	bool SaveGraph( String^ filename );
	///<summary> einlesen des Datengraphen </summary>
	bool LoadGraph( String^ filename );
	///<summary> Erstellt aus dem dataGraph Member einen View-Graphen </summary>
	void BuildViewFromData( void );
	///<summary> Zum Importieren von Graphen aus einer Adjazenzmatrix </summary>
	bool ImportGraph( String^ filename );
	///<summary> Zum Exportieren von Graphen in eine Adjazenzmatrix </summary>
	bool ExportGraph( String^ filename );
	///<summary> Startet die Optimisierung des Datengraphen </summary>
	bool StartRandomize( Int32 maximum );
	///<summary> Schreibt die Locationen aus den Daten wieder in die Darstellungsknoten </summary>
	void UpdateLocationsFromData (void);
	///<summary> �berpr�ft ob zwischen gegebenen vertexen eine Kante bereits vorhanden ist </summary>
	bool EdgeAllreadyThere ( vertexView^ One, vertexView^ Two );
	///<summary> gibt an ob der Graph eine Positionen gebackuped hat</summary>
	bool HasBackup ( void );
	///<summary> schreibt Backup </summary>
	void BackupSecure( void );
	///<summary> liest das Backup wieder ein</summary>
	void BackupWriteBack( void );
	///<summary> Initialisiert den Djikstra Algorithmus </summary>
	void InitDijkstra ( void );
	///<summary> f�hrt jeweils einen Dijkstra Schritt durch und gibt falsch zur�ck, wenn Algorithmus am Ende ist.</summary>
	bool DijkstraStep ( void );
	///<summary> Beendet den Djikstra Algorithmus </summary>
	void DijkstraCancel (void);

	///<summary> holt die Korrespondierende Kante zu einer Datenkante </summary>
	edgeView^ GetEdgeFromData( Kante^ dataEdge);

	///<summary> entfernt das Backup </summary>
	void RemoveBackup( void );

private:
	///<summary>Handle um edge Zeichnen in progress zu signalisieren, speichert den Start, ansonsten nullptr</summary>
	vertexView^ m_startedDrawing;
	///<summary> enth�lt die vorhandenen Vertexe</summary>
	System::Collections::Generic::List< GAPConnect::vertexView^ >^ vertexList;
	///<summary> enth�lt alle Kanten </summary>
	System::Collections::Generic::List< GAPConnect::edgeView^ >^ edgeList;
	///<summary> Definition von Zeichentools </summary>
	GAPConnect::drawTools^ m_drawTools;
	///<summary> Parent </summary>
	System::Windows::Forms::Form^ m_parent;
	///<summary> lastMarked Element</summary>
	GAPConnect::basicView^ m_lastMarkedElement;
	///<summary> Anschlu� an den Datenteil </summary>
	Graph^ m_dataGraph;
	///<summary> Positionen Backup </summary>
	System::Collections::Generic::List<System::Drawing::Point>^ m_backupPositions;
	///<summary> Djikstra Variable </summary>
	Dijkstra^ m_Dijkstra;

};

}//namespace