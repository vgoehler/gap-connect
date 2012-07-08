#pragma once
#include "stdafx.h"

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Hauptexecutable für GAP-Connect
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void):dragBoxFromMouseDown(System::Drawing::Rectangle::Empty), dragAndDropVertexOldLocation(System::Drawing::Point::Empty), m_graph(nullptr), filename(L"")
		{
			InitializeComponent();
			this->changedGraph = false;
			this->m_graph = gcnew GAPConnect::graphView(this);
			this->toolStripTextBoxGraphenname->Text = this->m_graph->Graphname;
			//TODO Werte aus Ini Laden
			this->loadDefaultValues();
			//Disablen
			this->toolStripButtonEdgesEnable();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
				delete this->m_graph;
			}
		}
	private:
	///<summary>Member um Veränderungen im Inhalt zu charakterisieren</summary>
		bool m_unsavedChanges;
	///<summary> Drag and Drop Variable</summary>
		GAPConnect::vertexView^ dragAndDropHandleOfVertex;
	///<summary> Drag and Drop Rectangle - Größe des Bereichs ab dem die DaD Operation startet</summary>
		System::Drawing::Rectangle dragBoxFromMouseDown;
	///<summary> Enthält den zu Zeichnenden Graphen</summary>
		GAPConnect::graphView^ m_graph;
	///<summary> Drag and Drop - speichern der Ursprungslokation für Rücksetzen </summary>
		System::Drawing::Point dragAndDropVertexOldLocation; 
	///<summary> Filename der Datei </summary>
		String^ filename;

	private: System::Windows::Forms::MenuStrip^  mainmenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  dateiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zeichnenToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  optionenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hilfeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  maintoolStrip;
	private: System::Windows::Forms::StatusStrip^  mainstatusStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  neuToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  beendenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonNew;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonOpen;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripLabelMouseX;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripLabelMouseY;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  ladenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  speichernToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  speichernalsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonSave;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::Panel^  control;
	private: System::Windows::Forms::Panel^  drawPanel;
	private: System::Windows::Forms::GroupBox^  zeichentools;
	private: System::Windows::Forms::ToolStrip^  zeichnenVertex;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexRound;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexSquare;
	private: System::Windows::Forms::ToolStrip^  zeichnenEdge;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdge;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonArc;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdgeCapacity;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonArcCapacity;

	private: System::Windows::Forms::ToolStripButton^  toolStripButtonGridControl;
	private: System::Windows::Forms::ToolStripMenuItem^  gridDeAktivierenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gridArretierungToolStripMenuItem;

	private: System::Windows::Forms::ToolStripButton^  toolStripButtonGridFixed;





	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelModus;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexAutoEdit;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdgeAutoEdit;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonDelete;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;

	private: System::Windows::Forms::ToolStripButton^  toolStripButtonCompleteGraph;

	private: System::Windows::Forms::ToolStripMenuItem^  kompletterGraphToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  objekteditierenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdit;
	private: System::Windows::Forms::ToolStripMenuItem^  sicherheitsabfrageBeimLöschenToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  drawBox;
	private: System::Windows::Forms::GroupBox^  gBStatus;
	private: System::Windows::Forms::TextBox^  tBKommentar;


	private: System::Windows::Forms::TextBox^  tbTyp;
private: System::Windows::Forms::ToolStripMenuItem^  runderKnotenToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  eckigerKnotenToolStripMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  kanteToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  kanteMitWertToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  bogenToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  bogenMitWertToolStripMenuItem;
private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBoxGraphenname;









	private: System::Windows::Forms::ImageList^  imageListToolbar;

	///<summary>Änderungen am Graph in Property vermerken. set routine setzt auch enable im Menü</summary>
	private: property bool changedGraph{
				 void set(bool InValue){
					 this->m_unsavedChanges = InValue;
					 //änderungen im graph triggern zulassen des speicherns
					 this->speichernToolStripMenuItem->Enabled = InValue;
					 this->speichernalsToolStripMenuItem->Enabled = InValue;
					 this->toolStripButtonSave->Enabled = InValue;
				 }
				 bool get(void){
					 return(this->m_unsavedChanges);
				 }
			 }
	///<summary> Wenn checked auf Grid anzeigen Button vom Programm aus gesetzt wird muss Grid auch geändert werden. Setzt auch Menü Einträge. </summary>
	private: property bool isGridActivated{
				 void set(bool value){
					 this->toolStripButtonGridControl->Checked = value;
					 this->gridDeAktivierenToolStripMenuItem->Checked = value;
					 this->toolStripButtonGridControl_Click(dynamic_cast<System::Object^>(this->toolStripButtonGridControl), nullptr);
				 }
				 bool get(void){
					 return(this->toolStripButtonGridControl->Checked);
				 }
			 }
	///<summary> Wenn checked auf Glue to Grid vom Programm gesetzt wird, wird auch ButtonImg geändert. Setzt auch Menü Einträge. </summary>
	private: property bool isGridFixed{
				 void set(bool value){
					 this->toolStripButtonGridFixed->Checked = value;
					 this->gridArretierungToolStripMenuItem->Checked = value;
					 this->toolStripButtonGridFixed_Click(dynamic_cast<System::Object^>(this->toolStripButtonGridFixed), nullptr);
				 }
				 bool get(void){
					 return(this->toolStripButtonGridFixed->Checked);
				 }
			 }
	///<summary> Gibt aus Toolbar ausgewähltes Handle zurück oder den nullptr</summary>
	private: property System::Windows::Forms::ToolStripButton^ toolBarChosen{
				 System::Windows::Forms::ToolStripButton^ get(void){
					 //iteriert über alle Container
					 for each (System::Object^ element in this->zeichentools->Controls){
						 //iteriert über alle Buttons
						 for each (System::Object^ toolbarButton in dynamic_cast<System::Windows::Forms::ToolStrip^>(element)->Items){
							if (dynamic_cast<System::Windows::Forms::ToolStripButton^>(toolbarButton)->Checked){
								//kann nur eines ausgewählt sein!
								return(dynamic_cast<System::Windows::Forms::ToolStripButton^>(toolbarButton));
							}
						 }
					 }
					 //wenn wir hier hergekommen sind, dann gibt es keine ausgewählten
					 return(nullptr);
				 }
			 }

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
			System::Windows::Forms::Label^  Kommentar;
			System::Windows::Forms::Label^  Typ;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
			System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->mainmenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->neuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ladenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernalsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->beendenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kompletterGraphToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->objekteditierenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zeichnenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runderKnotenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eckigerKnotenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kanteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kanteMitWertToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bogenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bogenMitWertToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gridDeAktivierenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gridArretierungToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hilfeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->maintoolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonNew = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonGridControl = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonGridFixed = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonVertexAutoEdit = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonEdgeAutoEdit = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButtonDelete = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonCompleteGraph = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonEdit = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripTextBoxGraphenname = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->mainstatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripLabelMouseX = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripLabelMouseY = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelModus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->control = (gcnew System::Windows::Forms::Panel());
			this->gBStatus = (gcnew System::Windows::Forms::GroupBox());
			this->tbTyp = (gcnew System::Windows::Forms::TextBox());
			this->tBKommentar = (gcnew System::Windows::Forms::TextBox());
			this->zeichentools = (gcnew System::Windows::Forms::GroupBox());
			this->zeichnenEdge = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonEdge = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonEdgeCapacity = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonArc = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonArcCapacity = (gcnew System::Windows::Forms::ToolStripButton());
			this->zeichnenVertex = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonVertexRound = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonVertexSquare = (gcnew System::Windows::Forms::ToolStripButton());
			this->drawPanel = (gcnew System::Windows::Forms::Panel());
			this->drawBox = (gcnew System::Windows::Forms::PictureBox());
			this->imageListToolbar = (gcnew System::Windows::Forms::ImageList(this->components));
			toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			Kommentar = (gcnew System::Windows::Forms::Label());
			Typ = (gcnew System::Windows::Forms::Label());
			toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->mainmenuStrip->SuspendLayout();
			this->maintoolStrip->SuspendLayout();
			this->mainstatusStrip->SuspendLayout();
			this->control->SuspendLayout();
			this->gBStatus->SuspendLayout();
			this->zeichentools->SuspendLayout();
			this->zeichnenEdge->SuspendLayout();
			this->zeichnenVertex->SuspendLayout();
			this->drawPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->drawBox))->BeginInit();
			this->SuspendLayout();
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1->Name = L"toolStripSeparator1";
			toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// toolStripSeparator2
			// 
			toolStripSeparator2->Name = L"toolStripSeparator2";
			toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripSeparator4
			// 
			toolStripSeparator4->Name = L"toolStripSeparator4";
			toolStripSeparator4->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripSeparator7
			// 
			toolStripSeparator7->Name = L"toolStripSeparator7";
			toolStripSeparator7->Size = System::Drawing::Size(212, 6);
			// 
			// toolStripSeparator6
			// 
			toolStripSeparator6->Name = L"toolStripSeparator6";
			toolStripSeparator6->Size = System::Drawing::Size(6, 25);
			// 
			// Kommentar
			// 
			Kommentar->AutoSize = true;
			Kommentar->Location = System::Drawing::Point(3, 33);
			Kommentar->Name = L"Kommentar";
			Kommentar->Size = System::Drawing::Size(66, 13);
			Kommentar->TabIndex = 2;
			Kommentar->Text = L"Kommentar :";
			// 
			// Typ
			// 
			Typ->AutoSize = true;
			Typ->Location = System::Drawing::Point(4, 16);
			Typ->Name = L"Typ";
			Typ->Size = System::Drawing::Size(25, 13);
			Typ->TabIndex = 4;
			Typ->Text = L"Typ";
			// 
			// toolStripSeparator3
			// 
			toolStripSeparator3->Name = L"toolStripSeparator3";
			toolStripSeparator3->Size = System::Drawing::Size(179, 6);
			// 
			// toolStripLabel1
			// 
			toolStripLabel1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			toolStripLabel1->Name = L"toolStripLabel1";
			toolStripLabel1->Size = System::Drawing::Size(111, 22);
			toolStripLabel1->Text = L"Name des Graphen:";
			// 
			// mainmenuStrip
			// 
			this->mainmenuStrip->BackColor = System::Drawing::SystemColors::MenuBar;
			this->mainmenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->dateiToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem, this->zeichnenToolStripMenuItem, this->optionenToolStripMenuItem, this->hilfeToolStripMenuItem});
			this->mainmenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainmenuStrip->Name = L"mainmenuStrip";
			this->mainmenuStrip->Size = System::Drawing::Size(1008, 24);
			this->mainmenuStrip->TabIndex = 1;
			this->mainmenuStrip->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->neuToolStripMenuItem, 
				this->ladenToolStripMenuItem, this->speichernToolStripMenuItem, this->speichernalsToolStripMenuItem, toolStripSeparator1, this->beendenToolStripMenuItem});
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->dateiToolStripMenuItem->Text = L"&Datei";
			// 
			// neuToolStripMenuItem
			// 
			this->neuToolStripMenuItem->Name = L"neuToolStripMenuItem";
			this->neuToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->neuToolStripMenuItem->Text = L"&Neu";
			this->neuToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::neuMenu_Click);
			// 
			// ladenToolStripMenuItem
			// 
			this->ladenToolStripMenuItem->Name = L"ladenToolStripMenuItem";
			this->ladenToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->ladenToolStripMenuItem->Text = L"&Laden";
			this->ladenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ladenMenu_Click);
			// 
			// speichernToolStripMenuItem
			// 
			this->speichernToolStripMenuItem->Name = L"speichernToolStripMenuItem";
			this->speichernToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->speichernToolStripMenuItem->Text = L"&Speichern";
			this->speichernToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::speichernMenu_Click);
			// 
			// speichernalsToolStripMenuItem
			// 
			this->speichernalsToolStripMenuItem->Name = L"speichernalsToolStripMenuItem";
			this->speichernalsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->speichernalsToolStripMenuItem->Text = L"Speichern &als";
			this->speichernalsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::speichernMenu_Click);
			// 
			// beendenToolStripMenuItem
			// 
			this->beendenToolStripMenuItem->Name = L"beendenToolStripMenuItem";
			this->beendenToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->beendenToolStripMenuItem->Text = L"&Beenden";
			this->beendenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::beendenToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->deleteToolStripMenuItem, 
				toolStripSeparator7, this->kompletterGraphToolStripMenuItem, this->objekteditierenToolStripMenuItem});
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(75, 20);
			this->bearbeitenToolStripMenuItem->Text = L"&Bearbeiten";
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->AutoToolTip = true;
			this->deleteToolStripMenuItem->Enabled = false;
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::Delete;
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->deleteToolStripMenuItem->Text = L"&Löschen";
			this->deleteToolStripMenuItem->ToolTipText = L"Löschen des markierten Objekts";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteMarkedElement_Click);
			// 
			// kompletterGraphToolStripMenuItem
			// 
			this->kompletterGraphToolStripMenuItem->Enabled = false;
			this->kompletterGraphToolStripMenuItem->Name = L"kompletterGraphToolStripMenuItem";
			this->kompletterGraphToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->kompletterGraphToolStripMenuItem->Text = L"&Kompletter Graph erstellen";
			this->kompletterGraphToolStripMenuItem->ToolTipText = L"Zeichnet einen kompletten Graphen unter Entfernung vorhandener Kanten";
			this->kompletterGraphToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::CompleteGraph_Click);
			// 
			// objekteditierenToolStripMenuItem
			// 
			this->objekteditierenToolStripMenuItem->Enabled = false;
			this->objekteditierenToolStripMenuItem->Name = L"objekteditierenToolStripMenuItem";
			this->objekteditierenToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F2;
			this->objekteditierenToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->objekteditierenToolStripMenuItem->Text = L"Objekt &editieren";
			this->objekteditierenToolStripMenuItem->ToolTipText = L"Öffnet einen Dialog der Daten des Knoten oder der Kante einblenden und die dann V" 
				L"eränderbar sind";
			this->objekteditierenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::EditMarkedObject_Click);
			// 
			// zeichnenToolStripMenuItem
			// 
			this->zeichnenToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->runderKnotenToolStripMenuItem, 
				this->eckigerKnotenToolStripMenuItem, toolStripSeparator3, this->kanteToolStripMenuItem, this->kanteMitWertToolStripMenuItem, 
				this->bogenToolStripMenuItem, this->bogenMitWertToolStripMenuItem});
			this->zeichnenToolStripMenuItem->Name = L"zeichnenToolStripMenuItem";
			this->zeichnenToolStripMenuItem->Size = System::Drawing::Size(68, 20);
			this->zeichnenToolStripMenuItem->Text = L"&Zeichnen";
			// 
			// runderKnotenToolStripMenuItem
			// 
			this->runderKnotenToolStripMenuItem->Name = L"runderKnotenToolStripMenuItem";
			this->runderKnotenToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F5;
			this->runderKnotenToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->runderKnotenToolStripMenuItem->Text = L"Runder Knoten";
			this->runderKnotenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// eckigerKnotenToolStripMenuItem
			// 
			this->eckigerKnotenToolStripMenuItem->Name = L"eckigerKnotenToolStripMenuItem";
			this->eckigerKnotenToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F6;
			this->eckigerKnotenToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->eckigerKnotenToolStripMenuItem->Text = L"Eckiger Knoten";
			this->eckigerKnotenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// kanteToolStripMenuItem
			// 
			this->kanteToolStripMenuItem->Enabled = false;
			this->kanteToolStripMenuItem->Name = L"kanteToolStripMenuItem";
			this->kanteToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F9;
			this->kanteToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->kanteToolStripMenuItem->Text = L"Kante";
			this->kanteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// kanteMitWertToolStripMenuItem
			// 
			this->kanteMitWertToolStripMenuItem->Enabled = false;
			this->kanteMitWertToolStripMenuItem->Name = L"kanteMitWertToolStripMenuItem";
			this->kanteMitWertToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F10;
			this->kanteMitWertToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->kanteMitWertToolStripMenuItem->Text = L"Kante mit Wert";
			this->kanteMitWertToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// bogenToolStripMenuItem
			// 
			this->bogenToolStripMenuItem->Enabled = false;
			this->bogenToolStripMenuItem->Name = L"bogenToolStripMenuItem";
			this->bogenToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F11;
			this->bogenToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->bogenToolStripMenuItem->Text = L"Bogen";
			this->bogenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// bogenMitWertToolStripMenuItem
			// 
			this->bogenMitWertToolStripMenuItem->Enabled = false;
			this->bogenMitWertToolStripMenuItem->Name = L"bogenMitWertToolStripMenuItem";
			this->bogenMitWertToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F12;
			this->bogenMitWertToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->bogenMitWertToolStripMenuItem->Text = L"Bogen mit Wert";
			this->bogenMitWertToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::zeichnenToolStripMenuItems_Click);
			// 
			// optionenToolStripMenuItem
			// 
			this->optionenToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->gridDeAktivierenToolStripMenuItem, 
				this->gridArretierungToolStripMenuItem, this->sicherheitsabfrageBeimLöschenToolStripMenuItem});
			this->optionenToolStripMenuItem->Name = L"optionenToolStripMenuItem";
			this->optionenToolStripMenuItem->Size = System::Drawing::Size(69, 20);
			this->optionenToolStripMenuItem->Text = L"&Optionen";
			// 
			// gridDeAktivierenToolStripMenuItem
			// 
			this->gridDeAktivierenToolStripMenuItem->Name = L"gridDeAktivierenToolStripMenuItem";
			this->gridDeAktivierenToolStripMenuItem->Size = System::Drawing::Size(248, 22);
			this->gridDeAktivierenToolStripMenuItem->Text = L"Grid De-/Aktivieren";
			this->gridDeAktivierenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridControl_Click);
			// 
			// gridArretierungToolStripMenuItem
			// 
			this->gridArretierungToolStripMenuItem->Name = L"gridArretierungToolStripMenuItem";
			this->gridArretierungToolStripMenuItem->Size = System::Drawing::Size(248, 22);
			this->gridArretierungToolStripMenuItem->Text = L"Gridarretierung";
			this->gridArretierungToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridFixed_Click);
			// 
			// sicherheitsabfrageBeimLöschenToolStripMenuItem
			// 
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->Checked = true;
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->CheckOnClick = true;
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->Name = L"sicherheitsabfrageBeimLöschenToolStripMenuItem";
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->Size = System::Drawing::Size(248, 22);
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->Text = L"Sicherheitsabfrage beim Löschen";
			this->sicherheitsabfrageBeimLöschenToolStripMenuItem->ToolTipText = L"Soll die Sicherheitsabfrage beim Löschen von Objekten angezeigt werden\?";
			// 
			// hilfeToolStripMenuItem
			// 
			this->hilfeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->hilfeToolStripMenuItem->Name = L"hilfeToolStripMenuItem";
			this->hilfeToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->hilfeToolStripMenuItem->Text = L"&Hilfe";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"&About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// maintoolStrip
			// 
			this->maintoolStrip->BackColor = System::Drawing::SystemColors::MenuBar;
			this->maintoolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->maintoolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(16) {this->toolStripButtonNew, 
				this->toolStripButtonOpen, this->toolStripButtonSave, toolStripSeparator2, this->toolStripButtonGridControl, this->toolStripButtonGridFixed, 
				toolStripSeparator4, this->toolStripButtonVertexAutoEdit, this->toolStripButtonEdgeAutoEdit, this->toolStripSeparator5, this->toolStripButtonDelete, 
				toolStripSeparator6, this->toolStripButtonCompleteGraph, this->toolStripButtonEdit, this->toolStripTextBoxGraphenname, toolStripLabel1});
			this->maintoolStrip->Location = System::Drawing::Point(0, 24);
			this->maintoolStrip->Name = L"maintoolStrip";
			this->maintoolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->maintoolStrip->Size = System::Drawing::Size(1008, 25);
			this->maintoolStrip->TabIndex = 3;
			this->maintoolStrip->Text = L"toolStrip1";
			// 
			// toolStripButtonNew
			// 
			this->toolStripButtonNew->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonNew->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonNew.Image")));
			this->toolStripButtonNew->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonNew->Name = L"toolStripButtonNew";
			this->toolStripButtonNew->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonNew->Text = L"Neuer Graph";
			this->toolStripButtonNew->ToolTipText = L"Legt einen neuen Graphen an.";
			this->toolStripButtonNew->Click += gcnew System::EventHandler(this, &Form1::neuMenu_Click);
			// 
			// toolStripButtonOpen
			// 
			this->toolStripButtonOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonOpen->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonOpen.Image")));
			this->toolStripButtonOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonOpen->Name = L"toolStripButtonOpen";
			this->toolStripButtonOpen->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonOpen->Text = L"Laden";
			this->toolStripButtonOpen->ToolTipText = L"Lädt einen Graph.";
			this->toolStripButtonOpen->Click += gcnew System::EventHandler(this, &Form1::ladenMenu_Click);
			// 
			// toolStripButtonSave
			// 
			this->toolStripButtonSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonSave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonSave.Image")));
			this->toolStripButtonSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonSave->Name = L"toolStripButtonSave";
			this->toolStripButtonSave->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonSave->Text = L"Speichern";
			this->toolStripButtonSave->ToolTipText = L"Speichert den aktiven Graph.";
			this->toolStripButtonSave->Click += gcnew System::EventHandler(this, &Form1::speichernMenu_Click);
			// 
			// toolStripButtonGridControl
			// 
			this->toolStripButtonGridControl->Checked = true;
			this->toolStripButtonGridControl->CheckState = System::Windows::Forms::CheckState::Checked;
			this->toolStripButtonGridControl->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonGridControl->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonGridControl.Image")));
			this->toolStripButtonGridControl->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonGridControl->Name = L"toolStripButtonGridControl";
			this->toolStripButtonGridControl->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonGridControl->Text = L"Grid Aktivieren";
			this->toolStripButtonGridControl->ToolTipText = L"Aktiviert oder Deaktiviert das Grid.";
			this->toolStripButtonGridControl->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridControl_Click);
			// 
			// toolStripButtonGridFixed
			// 
			this->toolStripButtonGridFixed->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonGridFixed.BackgroundImage")));
			this->toolStripButtonGridFixed->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonGridFixed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonGridFixed->Name = L"toolStripButtonGridFixed";
			this->toolStripButtonGridFixed->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonGridFixed->Text = L"Gridaretierung";
			this->toolStripButtonGridFixed->ToolTipText = L"Aktiviert die Gridarretierung";
			this->toolStripButtonGridFixed->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridFixed_Click);
			// 
			// toolStripButtonVertexAutoEdit
			// 
			this->toolStripButtonVertexAutoEdit->Checked = true;
			this->toolStripButtonVertexAutoEdit->CheckOnClick = true;
			this->toolStripButtonVertexAutoEdit->CheckState = System::Windows::Forms::CheckState::Checked;
			this->toolStripButtonVertexAutoEdit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonVertexAutoEdit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonVertexAutoEdit.Image")));
			this->toolStripButtonVertexAutoEdit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonVertexAutoEdit->Name = L"toolStripButtonVertexAutoEdit";
			this->toolStripButtonVertexAutoEdit->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonVertexAutoEdit->Text = L"Automatisches Editieren der Knoten";
			this->toolStripButtonVertexAutoEdit->ToolTipText = L"Automatisches Editieren der Knoten beim Erstellen de-/aktivieren";
			// 
			// toolStripButtonEdgeAutoEdit
			// 
			this->toolStripButtonEdgeAutoEdit->CheckOnClick = true;
			this->toolStripButtonEdgeAutoEdit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonEdgeAutoEdit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonEdgeAutoEdit.Image")));
			this->toolStripButtonEdgeAutoEdit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonEdgeAutoEdit->Name = L"toolStripButtonEdgeAutoEdit";
			this->toolStripButtonEdgeAutoEdit->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonEdgeAutoEdit->Text = L"Automatisches Editieren der Kanten";
			this->toolStripButtonEdgeAutoEdit->ToolTipText = L"Automatisches Editieren der Kanten beim Erstellen de-/aktivieren";
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripButtonDelete
			// 
			this->toolStripButtonDelete->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonDelete->Enabled = false;
			this->toolStripButtonDelete->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonDelete.Image")));
			this->toolStripButtonDelete->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonDelete->Name = L"toolStripButtonDelete";
			this->toolStripButtonDelete->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonDelete->Text = L"Entferne Objekt";
			this->toolStripButtonDelete->ToolTipText = L"Entferne markiertes Objekt (Entf)";
			this->toolStripButtonDelete->Click += gcnew System::EventHandler(this, &Form1::deleteMarkedElement_Click);
			// 
			// toolStripButtonCompleteGraph
			// 
			this->toolStripButtonCompleteGraph->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonCompleteGraph->Enabled = false;
			this->toolStripButtonCompleteGraph->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonCompleteGraph.Image")));
			this->toolStripButtonCompleteGraph->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonCompleteGraph->Name = L"toolStripButtonCompleteGraph";
			this->toolStripButtonCompleteGraph->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonCompleteGraph->Text = L"Kompletter Graph";
			this->toolStripButtonCompleteGraph->ToolTipText = L"Zeichnet einen kompletten Graphen unter Entfernung vorhandener Kanten";
			this->toolStripButtonCompleteGraph->Click += gcnew System::EventHandler(this, &Form1::CompleteGraph_Click);
			// 
			// toolStripButtonEdit
			// 
			this->toolStripButtonEdit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonEdit->Enabled = false;
			this->toolStripButtonEdit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonEdit.Image")));
			this->toolStripButtonEdit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonEdit->Name = L"toolStripButtonEdit";
			this->toolStripButtonEdit->Size = System::Drawing::Size(23, 22);
			this->toolStripButtonEdit->Text = L"markiertes Objekt editieren";
			this->toolStripButtonEdit->ToolTipText = L"Öffnet einen Dialog der Daten des Knoten oder der Kante einblenden und die dann V" 
				L"eränderbar sind";
			this->toolStripButtonEdit->Click += gcnew System::EventHandler(this, &Form1::EditMarkedObject_Click);
			// 
			// toolStripTextBoxGraphenname
			// 
			this->toolStripTextBoxGraphenname->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripTextBoxGraphenname->Name = L"toolStripTextBoxGraphenname";
			this->toolStripTextBoxGraphenname->Size = System::Drawing::Size(100, 25);
			this->toolStripTextBoxGraphenname->TextChanged += gcnew System::EventHandler(this, &Form1::toolStripTextBoxGraphenname_TextChanged);
			// 
			// mainstatusStrip
			// 
			this->mainstatusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripLabelMouseX, 
				this->toolStripLabelMouseY, this->toolStripStatusLabelModus});
			this->mainstatusStrip->Location = System::Drawing::Point(0, 740);
			this->mainstatusStrip->Name = L"mainstatusStrip";
			this->mainstatusStrip->Size = System::Drawing::Size(1008, 22);
			this->mainstatusStrip->TabIndex = 4;
			this->mainstatusStrip->Text = L"statusStrip1";
			// 
			// toolStripLabelMouseX
			// 
			this->toolStripLabelMouseX->Name = L"toolStripLabelMouseX";
			this->toolStripLabelMouseX->Size = System::Drawing::Size(20, 17);
			this->toolStripLabelMouseX->Text = L"X: ";
			// 
			// toolStripLabelMouseY
			// 
			this->toolStripLabelMouseY->Name = L"toolStripLabelMouseY";
			this->toolStripLabelMouseY->Size = System::Drawing::Size(20, 17);
			this->toolStripLabelMouseY->Text = L"Y: ";
			// 
			// toolStripStatusLabelModus
			// 
			this->toolStripStatusLabelModus->Name = L"toolStripStatusLabelModus";
			this->toolStripStatusLabelModus->Size = System::Drawing::Size(0, 17);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"*.gra";
			this->openFileDialog1->Filter = L"Graphdateien|*.gra";
			this->openFileDialog1->InitialDirectory = L".";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"*.gra";
			this->saveFileDialog1->Filter = L"Graphdateien|*.gra";
			this->saveFileDialog1->InitialDirectory = L".";
			// 
			// control
			// 
			this->control->BackColor = System::Drawing::SystemColors::Control;
			this->control->Controls->Add(this->gBStatus);
			this->control->Controls->Add(this->zeichentools);
			this->control->Dock = System::Windows::Forms::DockStyle::Left;
			this->control->Location = System::Drawing::Point(0, 49);
			this->control->Name = L"control";
			this->control->Size = System::Drawing::Size(198, 691);
			this->control->TabIndex = 6;
			// 
			// gBStatus
			// 
			this->gBStatus->Controls->Add(this->tbTyp);
			this->gBStatus->Controls->Add(Typ);
			this->gBStatus->Controls->Add(this->tBKommentar);
			this->gBStatus->Controls->Add(Kommentar);
			this->gBStatus->Location = System::Drawing::Point(0, 237);
			this->gBStatus->Name = L"gBStatus";
			this->gBStatus->Size = System::Drawing::Size(198, 156);
			this->gBStatus->TabIndex = 1;
			this->gBStatus->TabStop = false;
			this->gBStatus->Text = L"Status";
			// 
			// tbTyp
			// 
			this->tbTyp->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->tbTyp->Location = System::Drawing::Point(75, 13);
			this->tbTyp->Name = L"tbTyp";
			this->tbTyp->ReadOnly = true;
			this->tbTyp->Size = System::Drawing::Size(118, 20);
			this->tbTyp->TabIndex = 5;
			this->tbTyp->TabStop = false;
			// 
			// tBKommentar
			// 
			this->tBKommentar->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->tBKommentar->Location = System::Drawing::Point(7, 50);
			this->tBKommentar->Multiline = true;
			this->tBKommentar->Name = L"tBKommentar";
			this->tBKommentar->ReadOnly = true;
			this->tBKommentar->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tBKommentar->Size = System::Drawing::Size(186, 100);
			this->tBKommentar->TabIndex = 3;
			this->tBKommentar->TabStop = false;
			// 
			// zeichentools
			// 
			this->zeichentools->AutoSize = true;
			this->zeichentools->Controls->Add(this->zeichnenEdge);
			this->zeichentools->Controls->Add(this->zeichnenVertex);
			this->zeichentools->Dock = System::Windows::Forms::DockStyle::Top;
			this->zeichentools->Location = System::Drawing::Point(0, 0);
			this->zeichentools->Name = L"zeichentools";
			this->zeichentools->Size = System::Drawing::Size(198, 231);
			this->zeichentools->TabIndex = 0;
			this->zeichentools->TabStop = false;
			this->zeichentools->Text = L"Zeichnen";
			// 
			// zeichnenEdge
			// 
			this->zeichnenEdge->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->zeichnenEdge->ImageScalingSize = System::Drawing::Size(32, 32);
			this->zeichnenEdge->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripButtonEdge, 
				this->toolStripButtonEdgeCapacity, this->toolStripButtonArc, this->toolStripButtonArcCapacity});
			this->zeichnenEdge->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->zeichnenEdge->Location = System::Drawing::Point(3, 70);
			this->zeichnenEdge->Name = L"zeichnenEdge";
			this->zeichnenEdge->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->zeichnenEdge->Size = System::Drawing::Size(192, 158);
			this->zeichnenEdge->TabIndex = 1;
			// 
			// toolStripButtonEdge
			// 
			this->toolStripButtonEdge->CheckOnClick = true;
			this->toolStripButtonEdge->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonEdge.Image")));
			this->toolStripButtonEdge->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdge->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonEdge->Name = L"toolStripButtonEdge";
			this->toolStripButtonEdge->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonEdge->Text = L"Kante";
			this->toolStripButtonEdge->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdge->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonEdgeCapacity
			// 
			this->toolStripButtonEdgeCapacity->CheckOnClick = true;
			this->toolStripButtonEdgeCapacity->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonEdgeCapacity.Image")));
			this->toolStripButtonEdgeCapacity->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdgeCapacity->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonEdgeCapacity->Name = L"toolStripButtonEdgeCapacity";
			this->toolStripButtonEdgeCapacity->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonEdgeCapacity->Text = L"Kante mit Wert";
			this->toolStripButtonEdgeCapacity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdgeCapacity->ToolTipText = L"Zeichnet eine Kante mit Kantenbewertung";
			this->toolStripButtonEdgeCapacity->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonArc
			// 
			this->toolStripButtonArc->CheckOnClick = true;
			this->toolStripButtonArc->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonArc.Image")));
			this->toolStripButtonArc->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonArc->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonArc->Name = L"toolStripButtonArc";
			this->toolStripButtonArc->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonArc->Text = L"gerichtete Kante";
			this->toolStripButtonArc->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonArc->ToolTipText = L"Zeichnet eine gerichtete Kante";
			this->toolStripButtonArc->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonArcCapacity
			// 
			this->toolStripButtonArcCapacity->CheckOnClick = true;
			this->toolStripButtonArcCapacity->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonArcCapacity.Image")));
			this->toolStripButtonArcCapacity->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonArcCapacity->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonArcCapacity->Name = L"toolStripButtonArcCapacity";
			this->toolStripButtonArcCapacity->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonArcCapacity->Text = L"gerichtete Kante mit Wert";
			this->toolStripButtonArcCapacity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonArcCapacity->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// zeichnenVertex
			// 
			this->zeichnenVertex->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->zeichnenVertex->ImageScalingSize = System::Drawing::Size(32, 32);
			this->zeichnenVertex->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripButtonVertexRound, 
				this->toolStripButtonVertexSquare});
			this->zeichnenVertex->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Flow;
			this->zeichnenVertex->Location = System::Drawing::Point(3, 16);
			this->zeichnenVertex->Margin = System::Windows::Forms::Padding(0, 0, 0, 5);
			this->zeichnenVertex->Name = L"zeichnenVertex";
			this->zeichnenVertex->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->zeichnenVertex->Size = System::Drawing::Size(192, 54);
			this->zeichnenVertex->TabIndex = 0;
			// 
			// toolStripButtonVertexRound
			// 
			this->toolStripButtonVertexRound->CheckOnClick = true;
			this->toolStripButtonVertexRound->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonVertexRound.Image")));
			this->toolStripButtonVertexRound->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonVertexRound->Name = L"toolStripButtonVertexRound";
			this->toolStripButtonVertexRound->Size = System::Drawing::Size(90, 51);
			this->toolStripButtonVertexRound->Text = L"Runder Knoten";
			this->toolStripButtonVertexRound->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->toolStripButtonVertexRound->ToolTipText = L"Zeichnet einen runden Knoten";
			this->toolStripButtonVertexRound->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonVertexSquare
			// 
			this->toolStripButtonVertexSquare->CheckOnClick = true;
			this->toolStripButtonVertexSquare->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonVertexSquare.Image")));
			this->toolStripButtonVertexSquare->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonVertexSquare->Name = L"toolStripButtonVertexSquare";
			this->toolStripButtonVertexSquare->Size = System::Drawing::Size(90, 51);
			this->toolStripButtonVertexSquare->Text = L"Eckiger Knoten";
			this->toolStripButtonVertexSquare->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->toolStripButtonVertexSquare->ToolTipText = L"Zeichnet einen eckigen Knoten";
			this->toolStripButtonVertexSquare->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// drawPanel
			// 
			this->drawPanel->AllowDrop = true;
			this->drawPanel->AutoScroll = true;
			this->drawPanel->AutoScrollMinSize = System::Drawing::Size(3000, 3000);
			this->drawPanel->BackColor = System::Drawing::SystemColors::Window;
			this->drawPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"drawPanel.BackgroundImage")));
			this->drawPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->drawPanel->Controls->Add(this->drawBox);
			this->drawPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->drawPanel->Location = System::Drawing::Point(198, 49);
			this->drawPanel->MinimumSize = System::Drawing::Size(500, 500);
			this->drawPanel->Name = L"drawPanel";
			this->drawPanel->Size = System::Drawing::Size(810, 691);
			this->drawPanel->TabIndex = 7;
			// 
			// drawBox
			// 
			this->drawBox->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"drawBox.BackgroundImage")));
			this->drawBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->drawBox->Location = System::Drawing::Point(0, 0);
			this->drawBox->Name = L"drawBox";
			this->drawBox->Size = System::Drawing::Size(3000, 3000);
			this->drawBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->drawBox->TabIndex = 0;
			this->drawBox->TabStop = false;
			this->drawBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::drawBox_Paint);
			this->drawBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawBox_MouseDown);
			this->drawBox->MouseLeave += gcnew System::EventHandler(this, &Form1::drawBox_MouseLeave);
			this->drawBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawBox_MouseMove);
			this->drawBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawBox_MouseUp);
			// 
			// imageListToolbar
			// 
			this->imageListToolbar->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageListToolbar.ImageStream")));
			this->imageListToolbar->TransparentColor = System::Drawing::Color::Transparent;
			this->imageListToolbar->Images->SetKeyName(0, L"grid_activated.png");
			this->imageListToolbar->Images->SetKeyName(1, L"grid_deactivated.png");
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1008, 762);
			this->Controls->Add(this->drawPanel);
			this->Controls->Add(this->control);
			this->Controls->Add(this->mainstatusStrip);
			this->Controls->Add(this->maintoolStrip);
			this->Controls->Add(this->mainmenuStrip);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(500, 600);
			this->Name = L"Form1";
			this->Text = L"GAP-Connect";
			this->TopMost = true;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->mainmenuStrip->ResumeLayout(false);
			this->mainmenuStrip->PerformLayout();
			this->maintoolStrip->ResumeLayout(false);
			this->maintoolStrip->PerformLayout();
			this->mainstatusStrip->ResumeLayout(false);
			this->mainstatusStrip->PerformLayout();
			this->control->ResumeLayout(false);
			this->control->PerformLayout();
			this->gBStatus->ResumeLayout(false);
			this->gBStatus->PerformLayout();
			this->zeichentools->ResumeLayout(false);
			this->zeichentools->PerformLayout();
			this->zeichnenEdge->ResumeLayout(false);
			this->zeichnenEdge->PerformLayout();
			this->zeichnenVertex->ResumeLayout(false);
			this->zeichnenVertex->PerformLayout();
			this->drawPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->drawBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
///<summary> Laden der Iniwerte </summary>
public: void loadDefaultValues(void){
			/*isGridActivated
			isGridFixed*/
		}

///<summary> zeigt nach Menü Klick den About Dialog an.</summary>
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 about^ aboutDialog = gcnew about();
			 aboutDialog->Show(this);//Anzeige des About Dialogs
			 delete aboutDialog;
		 }
///<summary> Schließen-Schaltfläche des Menü. </summary>
private: System::Void beendenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
///<summary> Vor dem Schließen des Formulars auf Nichtgesicherte Eingaben achten.</summary>
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 if (!this->isGraphChangedDialog())
			 {
				 e->Cancel = true;
			 }
		 }
 ///<summary> Änderungen am Graph dialog einblenden, gibt true zurück wenn abgebrochen werden soll. </summary>
private: bool isGraphChangedDialog( void ){
			 if (this->changedGraph){
				 if(MessageBox::Show(L"Es sind Änderungen vorhanden! Diese werden durch ihre Aktion verworfen! Wollen Sie vorher Abspeichern?", L"Änderungen vorhanden!", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No){
					 return(true);
				 }
				 return(false);
			 }
			 return(true);
		 }

///<summary> Laden einer Datei </summary>
private: System::Void ladenMenu_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(this->openFileDialog1->ShowDialog(this) == System::Windows::Forms::DialogResult::OK){
				 if (RemoveGraphAndStartAnew()){//Graph gelöscht; können laden
					 if(!this->m_graph->LoadGraph(this->openFileDialog1->FileName)){
						 //irgendein Fehler passiert; nichts geladen
						 MessageBox::Show(L"Außerordentlicher Fehler. Keine Daten geladen.",L"Fehler beim Laden",MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }else{


						 this->toolStripButtonEdgesEnable();
						 this->RefreshDrawBox();
						 this->filename = this->openFileDialog1->FileName;//falls Datei lädt
						 this->toolStripTextBoxGraphenname->Text = this->m_graph->Graphname;
					 }
				 }
			 }
		 }
///<summary> Speichern des Graphen </summary>
private: System::Void speichernMenu_Click(System::Object^ sender, System::EventArgs^ e){
			 bool answer = true;
			 if (filename == L"" || sender == this->speichernalsToolStripMenuItem){
				 answer = this->saveFileDialog1->ShowDialog(this) == System::Windows::Forms::DialogResult::OK;
			 }
			 if(answer){
				 //Speichern
				 if(!this->m_graph->SaveGraph(this->saveFileDialog1->FileName)){
					 //Fehler passiert
					 MessageBox::Show(L"Fehler beim Speichern. Keine Daten geschrieben.", L"Fehler beim Speichern", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
				 this->changedGraph = false;
			 }
		 }
///<summary> Maus Bewegung im Zeichenbereich Zeigt Koordinaten im Tooltip an. Plus Drag and Drop Behandlung</summary>
private: System::Void drawBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //label update immer!
			 this->toolStripLabelMouseX->Text = String::Concat(L"X: ", e->X );
			 this->toolStripLabelMouseY->Text = String::Concat(L"Y: ", e->Y );
			 //Kommentare schreiben
			 this->ExtractCommentFromElement(e->Location);

			 //linke Maustaste gedrückt - Drag and Drop
			 if( (e->Button & System::Windows::Forms::MouseButtons::Left) == System::Windows::Forms::MouseButtons::Left){
				 this->DoDrag(e->Location);
			 }
		 }
///<summary> Maus verläßt Zeichenbereich. Koordinatenwerte auf Defaults </summary>
private: System::Void drawBox_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->toolStripLabelMouseX->Text = L"X: ";
			 this->toolStripLabelMouseY->Text = L"Y: ";
			 //drag Operation abbrechen
			 this->ResetDragAndDrop();
			 //Kommentar Text Reseten
			 tbTyp->Text = L"";
			 tBKommentar->Text = L"";
		 }
///<summary> Graph elemenieren und Neuladen </summary>
private: bool RemoveGraphAndStartAnew( void ){
			 if (this->isGraphChangedDialog())
			 {
				//Graph löschen
				delete this->m_graph;
				//neu initialisieren
				this->m_graph = gcnew GAPConnect::graphView(this);
				this->toolStripTextBoxGraphenname->Text = this->m_graph->Graphname;

				//Kanten je nach vorhandenen Knoten enablen
				this->toolStripButtonEdgesEnable();
				this->changedGraph = false;
				this->RefreshDrawBox();
				this->filename = "";
				return (true);
			 }
			 return(false);
		 }
///<summary> Neues Dokument </summary>
 private: System::Void neuMenu_Click(System::Object^ sender, System::EventArgs^ e){
			  //TODO nachfragen ob gespeichert werden soll
			  this->RemoveGraphAndStartAnew();
		  }
///<summary> Überprüft beim Auswählen von Toolbuttons, dass auch nur einer ausgewählt ist.</summary>
private: System::Void toolStripButtonsOnlyOneChecked(System::Object^  sender, System::EventArgs^  e) {
			 if (dynamic_cast<System::Windows::Forms::ToolStripButton^ >(sender)->Checked){
				 //2 fache lauf schleife, erst durch alle container dann durch toolbar items; Deaktivieren aller Elemente
				 for each (System::Object^ element in this->zeichentools->Controls){
					 for each (System::Object^ toolbarButton in dynamic_cast<System::Windows::Forms::ToolStrip^>(element)->Items){
						if (sender!=toolbarButton){
							dynamic_cast<System::Windows::Forms::ToolStripButton^>(toolbarButton)->Checked = false;
						}
					 }
				 }
			 }
			 //Edge Zeichnen aufräumen; kann sein das noch ausgewählter Knoten vorhanden ist
			 //deaktivieren der Auswahl des gespeicherten Knotens und des Knotens selbst
			 this->m_graph->unmarkElement();
			 //und der markierung sollte eine vorhanden sein
			 this->m_graph->unmarkLastMarked();
			 //ZeichenCursor setzen
			 this->drawBoxCursorChange();
			 //neu zeichnen
			 this->RefreshDrawBox();
		 }
///<summary> Schaltet das Grid ein bzw. aus </summary>
private: System::Void toolStripButtonGridControl_Click(System::Object^  sender, System::EventArgs^  e) {
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->drawBox->BackgroundImage = this->isGridActivated ? (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"drawBox.BackgroundImage"))) : nullptr;
			//markierungen setzen
			if (e != nullptr){
				this->isGridActivated = !this->isGridActivated;
			}
		 }
///<summary> Click auf Glue to Grid Button, Bild wechseln! </summary>
private: System::Void toolStripButtonGridFixed_Click(System::Object^  sender, System::EventArgs^  e) {
			 int idx = this->isGridFixed ? 0 : 1;
			 this->toolStripButtonGridFixed->BackgroundImage = cli::safe_cast<System::Drawing::Image^ >(this->imageListToolbar->Images[idx]);
			 //markierungen setzen
			 if (e != nullptr){
				 this->isGridFixed = !this->isGridFixed;
			 }
		 }
///<summary> Enabled bzw. Disabled ToolStripButtons die Kanten zeichnen.</summary>
private: void toolStripButtonEdgesEnable(){
			 //Toolbox Schalter
			 if (this->m_graph->CountVertex > 0){
				 for each (System::Windows::Forms::ToolStripButton^ element in this->zeichnenEdge->Items)
				 {
					 element->Enabled = true;
				 }
			 }else{
				 for each (System::Windows::Forms::ToolStripButton^ element in this->zeichnenEdge->Items)
				 {
					 element->Enabled = false;
				 }
			 }
			 //Menü Einträge auf enbling der ToolButtons abstimmen
			 this->kanteToolStripMenuItem->Enabled = this->toolStripButtonArc->Enabled;
			 this->kanteMitWertToolStripMenuItem->Enabled = this->toolStripButtonArc->Enabled;
			 this->bogenToolStripMenuItem->Enabled = this->toolStripButtonArc->Enabled;
			 this->bogenMitWertToolStripMenuItem->Enabled = this->toolStripButtonArc->Enabled;

			 //Kompletter Graph macht nur Sinn mit mindestens 2 Knoten
			 if (this->m_graph->CountVertex > 2){
				 this->kompletterGraphToolStripMenuItem->Enabled = true;
				 this->toolStripButtonCompleteGraph->Enabled = true;
			 }else{
				 this->kompletterGraphToolStripMenuItem->Enabled = false;
				 this->toolStripButtonCompleteGraph->Enabled = false;
			 }
		 }
///<summary> weist je nach ausgewähltem ZeichenModus dem drawBox cursor einen neuen Cursor zu</summary>
private: void drawBoxCursorChange( void ){
			//hole ausgewähltes
			System::Windows::Forms::ToolStripButton^ active = this->toolBarChosen;
			//nichts aktiv
			if(active==nullptr){
				this->drawBox->Cursor = System::Windows::Forms::Cursors::Default;
			}else if(active==this->toolStripButtonVertexRound){
				this->drawBox->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_round.cur");
			}else if(active==this->toolStripButtonVertexSquare){
				this->drawBox->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_square.cur");
			}else if(active==this->toolStripButtonEdge || active==this->toolStripButtonEdgeCapacity){
				this->drawBox->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_edge.cur");
			}else if(active== this->toolStripButtonArc || active==this->toolStripButtonArcCapacity){
				this->drawBox->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_arc.cur");
			}
		 }

///<summary> mit Beenden des Klicks (Up) zeichnen des Objekts an der Stelle des Mousecursors. </summary>
private: System::Void drawBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //nur executen wenn auch Zeichnen Modus ausgewählt
			 System::Windows::Forms::ToolStripButton^ chosenOption = this->toolBarChosen;
			 //mouseKoords an Lock Modus von grid anpassen
			 int mouseX = e->X;
			 int mouseY = e->Y;
			 if (this->isGridFixed){
				 mouseX = mouseX%50 > 25 ? mouseX-mouseX%50 +50 : mouseX - mouseX%50;
				 mouseY = mouseY%50 > 25 ? mouseY-mouseY%50 +50 : mouseY - mouseY%50;
			 }
			 if(chosenOption != nullptr){
				if (chosenOption == this->toolStripButtonVertexRound || chosenOption == this->toolStripButtonVertexSquare)
				{
					//auf Überschneidungen achten
					if (this->m_graph->vertexTooClose(Drawing::Point(mouseX,mouseY), Drawing::Size(25,25))){//andere Kontrollzone eines Vertex im Weg
						MessageBox::Show(L"Knoten zu nah an anderem Knoten Positioniert! Beachten Sie bitte, das der Mouse Pointer die Mitte des zu Platzierenden Knoten darstellt.", L"Knoten Überschneidungen!", MessageBoxButtons::OK , MessageBoxIcon::Hand);
					}else{
						//Vertex schreiben
						this->m_graph->CreateVertex(System::Drawing::Point(mouseX, mouseY), chosenOption == this->toolStripButtonVertexRound, this->toolStripButtonVertexAutoEdit->Checked);
						//Auswahl deaktivieren
						chosenOption->Checked=false;
						//Veränderungen markieren
						this->changedGraph = true;
						this->toolStripButtonEdgesEnable();
					}
				}else if (chosenOption == this->toolStripButtonArc || chosenOption == this->toolStripButtonArcCapacity || chosenOption == toolStripButtonEdge || chosenOption == toolStripButtonEdgeCapacity)
				{
					//Kanten Zeichnen Modus - nicht die durch Grid veränderten Mouse Koords nehmen!
					bool created = this->m_graph->CreateEdge(e->Location, (chosenOption == this->toolStripButtonArc || chosenOption == this->toolStripButtonArcCapacity), this->toolStripButtonEdgeAutoEdit->Checked, (chosenOption == this->toolStripButtonEdgeCapacity || chosenOption == this->toolStripButtonArcCapacity));
					if (created)
					{
						//Auswahl deaktivieren
						chosenOption->Checked=false;
						//Veränderungen markieren
						this->changedGraph = true;
					}
				}
				//Refresh im Zeichnenmodus
				this->RefreshDrawBox();
			 }else{
				 //nicht im ZeichnenModus
				 if (this->dragAndDropHandleOfVertex != nullptr){
					 //DnD Vertex gesetzt, also Drop
					 this->DoDrop(Point(mouseX, mouseY));
				 }
			 }
		 }
///<summary> Versucht an Punkt ein Element zu markieren (demarkieren) und gibt zurück ob es Änderungen gegeben hat. Initialisiert das Drag and Drop bei klick auf Knoten </summary>
private: bool markElementAtKoords(System::Drawing::Point pkt){
			 GAPConnect::vertexView^ vertex = this->m_graph->getHandleOfVertex(pkt);
			 System::Windows::Forms::ToolStripButton^ chosenOption = this->toolBarChosen;
			 if (vertex != nullptr){
				 //Markieren
				 this->m_graph->markElement(vertex);
				 //Drag and Drop Start - nur wenn kein Zeichnen
				 if (chosenOption == nullptr)
				 {
					 this->StartDragAndDrop(vertex, pkt);
				 }
				 //Änderungen gegeben
				 return(true);
			 }else{
				 //also kein Vertex, vielleicht also edge Auswahl
				 GAPConnect::edgeView^ edge = this->m_graph->getHandleOfEdge(pkt);
				 if (edge != nullptr)
				 {
					 //also doch Kante
					 this->m_graph->markElement(edge);
					 return(true);
				 }else{
					 //kein Knoten und keine Kante
					 if (this->m_graph->IsSomethingMarked() && ! this->m_graph->IsDrawingLine)//nicht wenn Kanten Zeichnen modus
					 {
						 this->m_graph->unmarkElement(this->m_graph->getMarkedElement);
						 return(true);
					 }
				 }
			 }
			 return(false);
		 }
///<summary> Auswahl von Element, Möglicherweise Drag and Drop, vielleicht auch sonstige Elemente</summary>
private: System::Void drawBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //neu Zeichnen wenn Änderungen
			 if (this->markElementAtKoords(e->Location)){
				 this->RefreshDrawBox();
			 }
		 }
///<summary> OnPaint Ereigniss, muß Zeichenfeld zeichnen </summary>
private: System::Void drawBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 e->Graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::HighQuality;
			 //Anti Aliasing
			 e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			 //Graph zeichnen
			 this->m_graph->drawGraph(e);
		 }
///<summary> Aktiviert oder Deaktiviert alle Löschen und Edit Steuerelemente </summary>
private: void activateItemsOnMark( bool active ){
			 //lösch Items
			 this->toolStripButtonDelete->Enabled = active;
			 this->deleteToolStripMenuItem->Enabled = active;
			 //Edit Items
			 this->toolStripButtonEdit->Enabled = active;
			 this->objekteditierenToolStripMenuItem->Enabled = active;
		 }
///<summary> Löscht das markierte Element </summary>
private: System::Void deleteMarkedElement_Click(System::Object^  sender, System::EventArgs^  e) {
			 bool security = false;
			 if (this->sicherheitsabfrageBeimLöschenToolStripMenuItem->Checked){//Sicherheitsabfrage
				 security = (MessageBox::Show(L"Markiertes Element soll gelöscht werden. Wollen Sie dies wirklich?", L"Löschen von Element", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes);
			 }
			 if (security)
			 {
				 this->m_graph->deleteDrawnElement(this->m_graph->getMarkedElement);
				 this->RefreshDrawBox();
				 this->toolStripButtonEdgesEnable();
			 }
		 }
///<summary> Refresh auf dem DrawPanel </summary>
public: void RefreshDrawBox( void ){
			this->activateItemsOnMark(this->m_graph->IsSomethingMarked() && ! this->m_graph->IsDrawingLine);//Items nur aktivieren wenn Objekt markiert, aber nicht wenn dies nur zum linien ziehen genutzt wird
			this->drawBox->Refresh();
		}
///<summary>Zeichnen eines Vollständigen Graphen</summary>
private: System::Void CompleteGraph_Click(System::Object^  sender, System::EventArgs^  e) {
			 bool yes = true;
			 if (this->m_graph->CountEdges != 0){//wenn Kanten dann Warnungsdialog
				 yes = (MessageBox::Show(L"Es wird ein kompletter Graph erstellt. Dazu werden alle vorhanden Kanten entfernt. Wollen Sie dies wirklich?", L"Kompletter Graph", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes);
			 }
			 if (yes)
			 {
					 this->m_graph->CreateCompleteGraph();
					 this->RefreshDrawBox();
			 }
		 }
///<summary> Startet den Edit Dialog des Markierten Objectes </summary>
private: System::Void EditMarkedObject_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->m_graph->getMarkedElement != nullptr){//Absicherung, normalerweise sollten alle Elemente disabled sein die dies ausführen können
				 this->m_graph->getMarkedElement->startConfigDialog(false);
				 //wenn markedElement ein Knoten ist müssen alle Dockpunkte von Edges upgedated werden
				 if (dynamic_cast<GAPConnect::vertexView^ >(this->m_graph->getMarkedElement) != nullptr){
					 this->m_graph->ReCalcDockingPoints(dynamic_cast<GAPConnect::vertexView^>(this->m_graph->getMarkedElement));
				 }
				 this->RefreshDrawBox();
			 }
		 }
///<summary> Setzt das Drag and Drop zurück</summary>
private: void ResetDragAndDrop( void ){
			 if (this->dragAndDropHandleOfVertex != nullptr){//Gibts überhaupt einen Drag
				 this->dragAndDropHandleOfVertex->Location = this->dragAndDropVertexOldLocation;
				 this->m_graph->ReCalcDockingPoints(this->dragAndDropHandleOfVertex);
				 this->RefreshDrawBox();
				 this->dragAndDropHandleOfVertex = nullptr;
				 this->dragAndDropVertexOldLocation = Point::Empty;
				 this->dragBoxFromMouseDown = System::Drawing::Rectangle::Empty;
				 this->toolStripStatusLabelModus->Text = L"";
			 }
		 }
private: void StartDragAndDrop( vertexView^ vertexToDrag, Point pkt ){
			 //Drag Rectangle generieren
			 System::Drawing::Size dragSize = System::Windows::Forms::SystemInformation::DragSize;
			 //Drag Vertex merken im Falle es ist ein Drag
			 this->dragAndDropHandleOfVertex = vertexToDrag;
			 this->dragAndDropVertexOldLocation = vertexToDrag->Location;
			 //D&D Rechteck hat mouse click koords in der Mitte
			 System::Drawing::Point ddRectangleLocation = System::Drawing::Point(pkt.X - (dragSize.Width /2), pkt.Y - (dragSize.Height /2));
			 this->dragBoxFromMouseDown = Rectangle(ddRectangleLocation, dragSize);
			 //D&D Status
			 this->toolStripStatusLabelModus->Text = L"Dragging";
		 }
///<summary> ziehen eines Knotens </summary>
private: void DoDrag( Point pkt ){
		 //haben wir eine dragBox ?
		 if (this->dragBoxFromMouseDown != System::Drawing::Rectangle::Empty){
			 //mouse außerhalb der dragBox ->  dragging
			 if ( !this->dragBoxFromMouseDown.Contains(pkt) ){
				 //Label updaten
				 this->toolStripStatusLabelModus->Text = String::Concat(L"Dragging X = ",abs(this->dragBoxFromMouseDown.X - pkt.X), L" Y = ", abs(this->dragBoxFromMouseDown.Y - pkt.Y));
				 //neue Position an Knoten übergeben
				 this->dragAndDropHandleOfVertex->LocationCenter = pkt;
				 this->m_graph->ReCalcDockingPoints(this->dragAndDropHandleOfVertex);
				 //Änderungen Darstellen
				 this->RefreshDrawBox();
			 }
		 }
		 }
///<summary> führt ablegen des Knotens aus </summary>
private: void DoDrop( Point pkt ){
			 //testen ob dragBox verlassen
			 if (this->dragBoxFromMouseDown != System::Drawing::Rectangle::Empty && !this->dragBoxFromMouseDown.Contains(pkt))
			 {
				 //In bounds der Anwendung
				 if (!this->drawBox->Bounds.Contains(pkt))
				 {
					 MessageBox::Show(L"Kein Ablegen außerhalb des Zeichenbereichs.", L"Knoten Außerhalb!", MessageBoxButtons::OK, MessageBoxIcon::Hand);
				 }else if (this->m_graph->vertexTooClose(pkt, this->dragAndDropHandleOfVertex->Size, this->dragAndDropHandleOfVertex)){
					 //testen ob aktuelle Position gut zum ablegen ist - Nähe zu anderem Knoten
					 MessageBox::Show(L"Sie können keinen Knoten auf einem Anderen oder in seiner Nähe ablegen!", L"Knoten Konflikt!", MessageBoxButtons::OK, MessageBoxIcon::Hand);
				 }else{
					 //ablegen, Punkt modifizieren, so dass er auf die Mitte weist um Refresh zu verhindern
					 this->dragAndDropVertexOldLocation = Point(pkt.X - this->dragAndDropHandleOfVertex->Width/2, pkt.Y - this->dragAndDropHandleOfVertex->Height/2);
					 this->changedGraph = true;
				 }
			 }
			 this->ResetDragAndDrop();
		 }
///<summary> Exrahiert Kommentar aus dem Element und schreibt ihn im Formular </summary>
private: void ExtractCommentFromElement(Point pkt){
			 GAPConnect::basicView^ element = this->m_graph->getHandleOfElement(pkt);
			 if (element != nullptr)
			 {
				 GAPConnect::vertexView^ vertex = dynamic_cast<GAPConnect::vertexView^ > (element);
				 if ( vertex != nullptr){
					 this->tBKommentar->Text = vertex->Kommentar;
					 this->tbTyp->Text = String::Concat(L"Knoten", L" ", vertex->TypeofVertex == 0 ? L"(Rund)" : L"(Eckig)");
				 } 
				 else{
					 this->tbTyp->Text = L"Kante";
					 GAPConnect::edgeView^ edge = dynamic_cast<GAPConnect::edgeView^ >(element);
					 this->tBKommentar->Text = edge->Kommentar;
				 }
			 }else{
				 this->tbTyp->Text = L"";
				 this->tBKommentar->Text = L"";
			 }
		 }
	
///<summary> Gleichschaltung des Zeichnen Menüs und der entsprechenden Toolbox</summary>
private: System::Void zeichnenToolStripMenuItems_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (sender == this->runderKnotenToolStripMenuItem)
			 {
				 this->toolStripButtonVertexRound->Checked = !this->toolStripButtonVertexRound->Checked;
			 }else if(sender == this->eckigerKnotenToolStripMenuItem)
			 {
				 this->toolStripButtonVertexSquare->Checked = !this->toolStripButtonVertexSquare->Checked;
			 }else if(sender == this->kanteToolStripMenuItem)
			 {
				 this->toolStripButtonEdge->Checked = !this->toolStripButtonEdge->Checked;
			 }else if(sender ==	this->kanteMitWertToolStripMenuItem)
			 {
				 this->toolStripButtonEdgeCapacity->Checked = !this->toolStripButtonEdgeCapacity->Checked;
			 }else if(sender == this->bogenToolStripMenuItem)
			 {
				 this->toolStripButtonArc->Checked = !this->toolStripButtonArc->Checked;
			 }else if(sender == this->bogenMitWertToolStripMenuItem){
				 this->toolStripButtonArcCapacity->Checked = !this->toolStripButtonArcCapacity->Checked;
			 }else{
				 throw gcnew Exception("Falscher Sender in zeichenToolStripMenuItems_Click!");
			 }
		 }
///<summary> Updaten des Namens des Graphen </summary>
private: System::Void toolStripTextBoxGraphenname_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			if (this->m_graph != nullptr){
				this->m_graph->Graphname = this->toolStripTextBoxGraphenname->Text;
			}
		 }
};//Form1 class
}//namespace

