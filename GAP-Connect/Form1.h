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
		Form1(void):startedDrawing(nullptr),dragBoxFromMouseDown(System::Drawing::Rectangle::Empty)
		{
			InitializeComponent();

			this->changedGraph = false;
			this->vertexList = gcnew System::Collections::Generic::List< GAPConnect::vertexView^ >();
			this->edgeList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
			this->m_drawTools = gcnew GAPConnect::drawTools();
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
				delete this->vertexList;
			}
		}
	private:
	///<summary>Member um Veränderungen im Inhalt zu charakterisieren</summary>
		bool m_unsavedChanges;
	///<summary>Handle um edge Zeichnen in progress zu signalisieren, speichert den Start, ansonsten nullptr</summary>
		vertexView^ startedDrawing;
	///<summary> Drag and Drop Variable</summary>
		GAPConnect::vertexView^ handleOfVertexUnderMouseToDrag;
	///<summary> Drag and Drop Rectangle - Größe des Bereichs ab dem die DaD Operation startet</summary>
		System::Drawing::Rectangle dragBoxFromMouseDown;
	///<summary> enthält die vorhandenen Vertexe</summary>
		System::Collections::Generic::List< GAPConnect::vertexView^ >^ vertexList;
	///<summary> enthält alle Kanten </summary>
		System::Collections::Generic::List< GAPConnect::edgeView^ >^ edgeList;
	///<summary> Definition von Zeichentools </summary>
		GAPConnect::drawTools^ m_drawTools;

	private: System::Windows::Forms::MenuStrip^  mainmenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  dateiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ansichtToolStripMenuItem;
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
	private: System::Windows::Forms::ContextMenuStrip^  vertexRightClickMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripConfig;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripKnotentext;
	private: System::Windows::Forms::ToolStripComboBox^  toolStripCBKindofVertex;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripVertexSizeAdjustment;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelModus;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexAutoEdit;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdgeAutoEdit;





	private: System::Windows::Forms::ImageList^  imageListToolbar;

	///<summary>Änderungen am Graph in Property vermerken. set routine setzt auch enable im Menü</summary>
	private: property bool changedGraph{
				 void set(bool value){
					 this->m_unsavedChanges = value;
					 //änderungen im graph triggern zulassen des speicherns
					 this->speichernToolStripMenuItem->Enabled = value;
					 this->speichernalsToolStripMenuItem->Enabled = value;
					 this->toolStripButtonSave->Enabled = value;
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
	///<summary> gibt das Rechtsklick Menü für die Knoten zurück</summary>
	public: property System::Windows::Forms::ContextMenuStrip^ MenuforVertex{
				System::Windows::Forms::ContextMenuStrip^ get(void){
					return(this->vertexRightClickMenu);
				}
			}
	///<summary> Property gibt Instanz der Zeichentools Klasse über</summary>
	public: property GAPConnect::drawTools^ getDrawTools{
				GAPConnect::drawTools^ get(void){
					return(this->m_drawTools);
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
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->mainmenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->neuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ladenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernalsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->beendenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ansichtToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gridDeAktivierenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gridArretierungToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->mainstatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripLabelMouseX = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripLabelMouseY = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelModus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->control = (gcnew System::Windows::Forms::Panel());
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
			this->vertexRightClickMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripKnotentext = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripCBKindofVertex = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->toolStripVertexSizeAdjustment = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripConfig = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageListToolbar = (gcnew System::Windows::Forms::ImageList(this->components));
			toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->mainmenuStrip->SuspendLayout();
			this->maintoolStrip->SuspendLayout();
			this->mainstatusStrip->SuspendLayout();
			this->control->SuspendLayout();
			this->zeichentools->SuspendLayout();
			this->zeichnenEdge->SuspendLayout();
			this->zeichnenVertex->SuspendLayout();
			this->vertexRightClickMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1->Name = L"toolStripSeparator1";
			toolStripSeparator1->Size = System::Drawing::Size(140, 6);
			// 
			// toolStripSeparator2
			// 
			toolStripSeparator2->Name = L"toolStripSeparator2";
			toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripSeparator3
			// 
			toolStripSeparator3->Name = L"toolStripSeparator3";
			toolStripSeparator3->Size = System::Drawing::Size(156, 6);
			// 
			// toolStripSeparator4
			// 
			toolStripSeparator4->Name = L"toolStripSeparator4";
			toolStripSeparator4->Size = System::Drawing::Size(6, 25);
			// 
			// mainmenuStrip
			// 
			this->mainmenuStrip->BackColor = System::Drawing::SystemColors::MenuBar;
			this->mainmenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->dateiToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem, this->ansichtToolStripMenuItem, this->optionenToolStripMenuItem, this->hilfeToolStripMenuItem});
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
			this->neuToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->neuToolStripMenuItem->Text = L"&Neu";
			this->neuToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::neuMenu_Click);
			// 
			// ladenToolStripMenuItem
			// 
			this->ladenToolStripMenuItem->Name = L"ladenToolStripMenuItem";
			this->ladenToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->ladenToolStripMenuItem->Text = L"&Laden";
			this->ladenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ladenMenu_Click);
			// 
			// speichernToolStripMenuItem
			// 
			this->speichernToolStripMenuItem->Name = L"speichernToolStripMenuItem";
			this->speichernToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->speichernToolStripMenuItem->Text = L"&Speichern";
			this->speichernToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::speichernMenu_Click);
			// 
			// speichernalsToolStripMenuItem
			// 
			this->speichernalsToolStripMenuItem->Name = L"speichernalsToolStripMenuItem";
			this->speichernalsToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->speichernalsToolStripMenuItem->Text = L"Speichern &als";
			this->speichernalsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::speichernMenu_Click);
			// 
			// beendenToolStripMenuItem
			// 
			this->beendenToolStripMenuItem->Name = L"beendenToolStripMenuItem";
			this->beendenToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->beendenToolStripMenuItem->Text = L"&Beenden";
			this->beendenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::beendenToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(75, 20);
			this->bearbeitenToolStripMenuItem->Text = L"&Bearbeiten";
			// 
			// ansichtToolStripMenuItem
			// 
			this->ansichtToolStripMenuItem->Name = L"ansichtToolStripMenuItem";
			this->ansichtToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->ansichtToolStripMenuItem->Text = L"&Ansicht";
			// 
			// optionenToolStripMenuItem
			// 
			this->optionenToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->gridDeAktivierenToolStripMenuItem, 
				this->gridArretierungToolStripMenuItem});
			this->optionenToolStripMenuItem->Name = L"optionenToolStripMenuItem";
			this->optionenToolStripMenuItem->Size = System::Drawing::Size(69, 20);
			this->optionenToolStripMenuItem->Text = L"&Optionen";
			// 
			// gridDeAktivierenToolStripMenuItem
			// 
			this->gridDeAktivierenToolStripMenuItem->Name = L"gridDeAktivierenToolStripMenuItem";
			this->gridDeAktivierenToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->gridDeAktivierenToolStripMenuItem->Text = L"Grid De-/Aktivieren";
			this->gridDeAktivierenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridControl_Click);
			// 
			// gridArretierungToolStripMenuItem
			// 
			this->gridArretierungToolStripMenuItem->Name = L"gridArretierungToolStripMenuItem";
			this->gridArretierungToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->gridArretierungToolStripMenuItem->Text = L"Gridarretierung";
			this->gridArretierungToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonGridFixed_Click);
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
			this->maintoolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {this->toolStripButtonNew, 
				this->toolStripButtonOpen, this->toolStripButtonSave, toolStripSeparator2, this->toolStripButtonGridControl, this->toolStripButtonGridFixed, 
				toolStripSeparator4, this->toolStripButtonVertexAutoEdit, this->toolStripButtonEdgeAutoEdit});
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
			this->openFileDialog1->InitialDirectory = L".";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->InitialDirectory = L".";
			// 
			// control
			// 
			this->control->BackColor = System::Drawing::SystemColors::Control;
			this->control->Controls->Add(this->zeichentools);
			this->control->Dock = System::Windows::Forms::DockStyle::Left;
			this->control->Location = System::Drawing::Point(0, 49);
			this->control->Name = L"control";
			this->control->Size = System::Drawing::Size(198, 691);
			this->control->TabIndex = 6;
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
			this->drawPanel->ContextMenuStrip = this->vertexRightClickMenu;
			this->drawPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->drawPanel->Location = System::Drawing::Point(198, 49);
			this->drawPanel->MinimumSize = System::Drawing::Size(500, 500);
			this->drawPanel->Name = L"drawPanel";
			this->drawPanel->Size = System::Drawing::Size(810, 691);
			this->drawPanel->TabIndex = 7;
			this->drawPanel->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::drawPanel_Scroll);
			this->drawPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::drawPanel_Paint);
			this->drawPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawPanel_MouseDown);
			this->drawPanel->MouseEnter += gcnew System::EventHandler(this, &Form1::drawPanel_MouseEnter);
			this->drawPanel->MouseLeave += gcnew System::EventHandler(this, &Form1::drawPanel_MouseLeave);
			this->drawPanel->MouseHover += gcnew System::EventHandler(this, &Form1::drawPanel_MouseHover);
			this->drawPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawPanel_MouseMove);
			this->drawPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::drawPanel_MouseUp);
			// 
			// vertexRightClickMenu
			// 
			this->vertexRightClickMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->toolStripKnotentext, 
				this->toolStripCBKindofVertex, this->toolStripVertexSizeAdjustment, toolStripSeparator3, this->toolStripConfig});
			this->vertexRightClickMenu->Name = L"vertexRightClickMenu";
			this->vertexRightClickMenu->ShowImageMargin = false;
			this->vertexRightClickMenu->Size = System::Drawing::Size(160, 106);
			// 
			// toolStripKnotentext
			// 
			this->toolStripKnotentext->AutoToolTip = true;
			this->toolStripKnotentext->BackColor = System::Drawing::SystemColors::Menu;
			this->toolStripKnotentext->Name = L"toolStripKnotentext";
			this->toolStripKnotentext->Size = System::Drawing::Size(100, 23);
			this->toolStripKnotentext->Text = L"Knotentext";
			this->toolStripKnotentext->ToolTipText = L"Text des Knotens";
			// 
			// toolStripCBKindofVertex
			// 
			this->toolStripCBKindofVertex->AutoToolTip = true;
			this->toolStripCBKindofVertex->BackColor = System::Drawing::SystemColors::Menu;
			this->toolStripCBKindofVertex->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Kreis", L"Rechteck"});
			this->toolStripCBKindofVertex->Name = L"toolStripCBKindofVertex";
			this->toolStripCBKindofVertex->Size = System::Drawing::Size(121, 23);
			this->toolStripCBKindofVertex->ToolTipText = L"Art des Knotens";
			// 
			// toolStripVertexSizeAdjustment
			// 
			this->toolStripVertexSizeAdjustment->AutoToolTip = true;
			this->toolStripVertexSizeAdjustment->Name = L"toolStripVertexSizeAdjustment";
			this->toolStripVertexSizeAdjustment->Size = System::Drawing::Size(159, 22);
			this->toolStripVertexSizeAdjustment->Text = L"Größe anpassen";
			this->toolStripVertexSizeAdjustment->ToolTipText = L"Paßt Größe an den Inhalt an.";
			// 
			// toolStripConfig
			// 
			this->toolStripConfig->AutoToolTip = true;
			this->toolStripConfig->Name = L"toolStripConfig";
			this->toolStripConfig->Size = System::Drawing::Size(159, 22);
			this->toolStripConfig->Text = L"Knotenkonfiguration";
			this->toolStripConfig->ToolTipText = L"Zeigt einen Dialog um den Knoten weiter zu konfigurieren.";
			this->toolStripConfig->Click += gcnew System::EventHandler(this, &Form1::vertexRightClickMenu_Config_Click);
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
			this->zeichentools->ResumeLayout(false);
			this->zeichentools->PerformLayout();
			this->zeichnenEdge->ResumeLayout(false);
			this->zeichnenEdge->PerformLayout();
			this->zeichnenVertex->ResumeLayout(false);
			this->zeichnenVertex->PerformLayout();
			this->vertexRightClickMenu->ResumeLayout(false);
			this->vertexRightClickMenu->PerformLayout();
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
			 if (m_unsavedChanges){
				 if(MessageBox::Show(L"Es sind Änderungen vorhanden! Diese werden beim Schließen gelöscht! Wollen Sie das Schließen abbrechen?", L"Änderungen vorhanden!", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes){
					//user will Schließen abbrechen
					 e->Cancel = true;
				 }
			 }
		 }
///<summary> Laden einer Datei </summary>
private: System::Void ladenMenu_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::IO::Stream^ inputStream;

			 if(this->openFileDialog1->ShowDialog(this) == System::Windows::Forms::DialogResult::OK){
				 if( (inputStream = this->openFileDialog1->OpenFile()) != nullptr ){//sanity check
					 //TODO Modus unterscheiden
					 //TODO lesen
					 inputStream->Close();
					 //zuletzt
					 m_unsavedChanges=false;
					 this->toolStripButtonEdgesEnable();
				 }
			 }
		 }
///<summary> Speichern des Graphen </summary>
private: System::Void speichernMenu_Click(System::Object^ sender, System::EventArgs^ e){
			 if(this->saveFileDialog1->ShowDialog(this) == System::Windows::Forms::DialogResult::OK){
				 //TODO hier speichern initialisieren
				 //this->Text = this->saveFileDialog1->FileName;
			 }
		 }
///<summary> Maus Bewegung im Zeichenbereich Zeigt Koordinaten im Tooltip an. Plus Drag and Drop Behandlung</summary>
private: System::Void drawPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //label update immer!
			 this->toolStripLabelMouseX->Text = String::Concat(L"X: ", e->X );
			 this->toolStripLabelMouseY->Text = String::Concat(L"Y: ", e->Y );
			 //linke Maustaste gedrückt
			 if( (e->Button & System::Windows::Forms::MouseButtons::Left) == System::Windows::Forms::MouseButtons::Left){
				 //mouse außerhalb der dragBox ereigniss auslösen
				 if (dragBoxFromMouseDown != System::Drawing::Rectangle::Empty && !dragBoxFromMouseDown.Contains(e->X,e->Y)){
					 this->toolStripStatusLabelModus->Text = String::Concat(L"Dragging X = ",abs(this->dragBoxFromMouseDown.X - e->X), L" Y = ", abs(this->dragBoxFromMouseDown.Y - e->Y));
				 }
			 }
		 }
///<summary> Maus verläßt Zeichenbereich. Koordinatenwerte auf Defaults </summary>
private: System::Void drawPanel_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->toolStripLabelMouseX->Text = L"X: ";
			 this->toolStripLabelMouseY->Text = L"Y: ";
		 }
///<summary> Neues Dokument </summary>
 private: System::Void neuMenu_Click(System::Object^ sender, System::EventArgs^ e){
			  //TODO nachfragen ob gespeichert werden soll

			  //Zeichenbereich löschen
			  this->drawPanel->Controls->Clear();

			  //zuLetzt!
			  m_unsavedChanges = false;
			  this->toolStripButtonEdgesEnable();
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
			 //Edge Zeichnen
			 //deaktivieren der Auswahl des gespeicherten Knotens und des Knotens selbst
			 if (this->startedDrawing != nullptr)
			 {
				 bool isMarked;
				 do{//Nur zur Sicherheit, da markVertex switched
					 isMarked = this->startedDrawing->Mark();
				 }while(isMarked);
				 this->startedDrawing = nullptr;
			 }
		 }
///<summary> Schaltet das Grid ein bzw. aus </summary>
private: System::Void toolStripButtonGridControl_Click(System::Object^  sender, System::EventArgs^  e) {
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			//TODO
			this->drawPanel->BackgroundImage = this->isGridActivated ? (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"drawPanel.BackgroundImage"))) : nullptr;
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
			 if (this->vertexList->Count > 0){
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
		 }
///<summary> Scrollen des Draw Panels muss redraw triggern</summary>
private: System::Void drawPanel_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->drawPanel->Refresh();
		 }
///<summary> MouseEnter muss je nach ausgewähltem Button den Cursor ändern. </summary>
public: System::Void drawPanel_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			//hole ausgewähltes
			System::Windows::Forms::ToolStripButton^ active = this->toolBarChosen;
			//nichts aktiv
			if(active==nullptr){
				this->drawPanel->Cursor = System::Windows::Forms::Cursors::Default;
			}else if(active==this->toolStripButtonVertexRound){
				this->drawPanel->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_round.cur");
			}else if(active==this->toolStripButtonVertexSquare){
				this->drawPanel->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_square.cur");
			}else if(active==this->toolStripButtonEdge || active==this->toolStripButtonEdgeCapacity){
				this->drawPanel->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_edge.cur");
			}else if(active== this->toolStripButtonArc || active==this->toolStripButtonArcCapacity){
				this->drawPanel->Cursor = gcnew System::Windows::Forms::Cursor(L"cursor_arc.cur");
			}
		 }
		 ///<summary> mit Beenden des Klicks (Up) zeichnen des Objekts an der Stelle des Mousecursors. </summary>
private: System::Void drawPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //nur executen wenn auch Zeichnen Modus ausgewählt
			 System::Windows::Forms::ToolStripButton^ chosenOption = this->toolBarChosen;
			 if(chosenOption != nullptr){
				 //Mouse Koordinaten an Situation anpassen - Lock Modus beachten
				 int mouseX = e->X;
				 int mouseY = e->Y;
				 if (this->isGridFixed){//TODO
					 mouseX = mouseX%50 > 25 ? mouseX-mouseX%50 +50 : mouseX - mouseX%50;
					 mouseY = mouseY%50 > 25 ? mouseY-mouseY%50 +50 : mouseY - mouseY%50;
				 }

				if (chosenOption == this->toolStripButtonVertexRound || chosenOption == this->toolStripButtonVertexSquare)
				{
					//Vertex schreiben
					vertexView^ vertex = (gcnew vertexView(this));
					vertex->LocationCenter = System::Drawing::Point(mouseX, mouseY);
				
					//VertexArt
					vertex->kindOf = chosenOption == this->toolStripButtonVertexRound ? 0 : 1;

					//Button Drawpanel hinzufügen
					this->vertexList->Add(vertex);

					//Auswahl deaktivieren
					chosenOption->Checked=false;

					//Veränderungen markieren
					m_unsavedChanges = true;
					this->toolStripButtonEdgesEnable();

					//Dialog zum Beschriften einblenden
					if (this->toolStripButtonVertexAutoEdit->Checked)
					{
						vertex->startConfigDialog();
					}
				}else if (chosenOption == this->toolStripButtonArc || chosenOption == this->toolStripButtonArcCapacity || chosenOption == toolStripButtonEdge || chosenOption == toolStripButtonEdgeCapacity)
				{
					//Kanten Zeichnen Modus
					GAPConnect::vertexView^ clickedVertex = this->getHandleOfVertex(e->Location);
					if (clickedVertex != nullptr)//nur wenn auch auf einen Vertex geklickt wurde
					{
						bool vertexMarked = clickedVertex->Mark();	
						//wenn Knoten wieder deaktiviert, dann wurde wohl falscher startknoten ausgewählt und wieder deaktiviert
						if (!vertexMarked){
							this->startedDrawing = nullptr;
						}
						if (this->startedDrawing == nullptr){//Edge zeichnen noch nicht gestartet
								//speichern des starts wenn noch nicht gestartet
								this->startedDrawing = clickedVertex;
						}else{
								//wenn bereits gestartet dann ende vermerken und objekt initialisieren
								edgeView^ edge = gcnew edgeView(this, this->startedDrawing, clickedVertex, (chosenOption == this->toolStripButtonArc || chosenOption == this->toolStripButtonArcCapacity)?1:0);//TODO
								//Methode zum Location , Placing und Direction des Panelträgers und des Pfeiles

								this->edgeList->Add(edge);

								//ende muss noch markierungen entfernen auf Knoten (Startknoten wird von checkstate change entfernt)
								do{
									vertexMarked = clickedVertex->Mark();
								}while(vertexMarked);

								//Auswahl deaktivieren
								chosenOption->Checked=false;
								//Veränderungen markieren
								m_unsavedChanges = true;

								//Dialog zum Beschriften einblenden
								if (this->toolStripButtonEdgeAutoEdit->Checked)
								{
									edge->startConfigDialog();
								}
							}
					}

				}
				//Refresh im Zeichnenmodus
				this->Refresh();
			 }else{
				 //nicht im ZeichnenModus dann ist es Drag and Drop - TODO
				 this->dragBoxFromMouseDown = System::Drawing::Rectangle::Empty;
				 //Status
				 this->toolStripStatusLabelModus->Text = L"";
			 }
		 }
		///<summary> löst das Konfigurationsereigniss auf Knoten aus</summary>
private: System::Void vertexRightClickMenu_Config_Click(System::Object^  sender, System::EventArgs^  e) {
			 //parent des geklickten Feldes holen und auf ContextMenu casten
			 System::Windows::Forms::ContextMenuStrip^ parent = dynamic_cast<System::Windows::Forms::ContextMenuStrip^ > (dynamic_cast<System::Windows::Forms::ToolStripMenuItem^ >(sender)->GetCurrentParent());
			 //Ursprung des Klicks holen, diesen als vertexView casten und Dialog ausführen
			 //TODO
			 dynamic_cast<GAPConnect::vertexView^ >(parent->SourceControl)->startConfigDialog();
		 }
//dragging
///<summary> Auswahl von Element, Möglicherweise Drag and Drop, vielleicht auch sonstige Elemente</summary>
 public: System::Void drawPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->handleOfVertexUnderMouseToDrag = this->getHandleOfVertex(e->Location);
			 if (this->handleOfVertexUnderMouseToDrag != nullptr){
				 //Drag Rectangle generieren
				 System::Drawing::Size dragSize = System::Windows::Forms::SystemInformation::DragSize;
				 //D&D Rechteck hat mouse click koords in der Mitte, müssen noch auf Koordinaten von drawPanel umgerechnet werden
				 System::Drawing::Point l = this->handleOfVertexUnderMouseToDrag->Location;
				 System::Drawing::Point ddRectangleLocation = System::Drawing::Point(l.X + e->X - (dragSize.Width /2), l.Y + e->Y - (dragSize.Height /2));
				 this->dragBoxFromMouseDown = Rectangle(ddRectangleLocation, dragSize);
				 //Status
				 this->toolStripStatusLabelModus->Text = L"Dragging";
			 }else{
				 //also kein Vertex, vielleicht also edge Auswahl
				 GAPConnect::edgeView^ chosenEdge = this->getHandleOfEdge(e->Location);
				 if (chosenEdge != nullptr)
				 {
					 //also doch Kante
					 chosenEdge->Mark();
					 this->Refresh();
				 }
			 }
		 }
		 ///<summary> Mouse betritt die Zeichenfläche. </summary>
private: System::Void drawPanel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->drawPanel_MouseHover(sender, e);
		 }
private: System::Void drawPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 //Anti Aliasing
			 e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			 //Knoten zeichnen
			 for each (GAPConnect::vertexView^ vertex in this->vertexList){
				 vertex->paintVertex(e);
			 }
			 //Kanten zeichnen
			 for each (GAPConnect::edgeView^ edge in this->edgeList){
				 edge->paintEdge(e);
			 }
		 }
		 ///<summary> holt ein Handle auf ein gezeichnetes Objekt wo der mousezeiger draufzeigt </summary>
private: GAPConnect::edgeView^ getHandleOfEdge(System::Drawing::Point pkt){
			 //Liste um Sucherergebnisse festzuhalten
			 System::Collections::Generic::List< GAPConnect::edgeView^ > tmpList = gcnew System::Collections::Generic::List< GAPConnect::edgeView^ >();
			 //Edges durchsuchen
			 for each (GAPConnect::edgeView^ element in this->edgeList){
				 if (element->Contains(pkt))
				 {
					 tmpList.Add(element);
				 }
			 }
			 //Behandlung der Ergebnisse
			 if (tmpList.Count == 1)
			 {//bei nur einem Ergebniss einfach dieses zurückgeben
				 return tmpList[0];
			 }else if (tmpList.Count > 1)
			 {//TODO Mehrere: Hier Fallbehandlung um das Richtige herauszufinden
				 return tmpList[0];
			 } 
			 else
			 {//nichts!
				 return nullptr;
			 }
		 }
		///<summary> Handle auf Vertex </summary>
private: GAPConnect::vertexView^ getHandleOfVertex (System::Drawing::Point pkt){
			 //Liste um Sucherergebnisse festzuhalten
			 System::Collections::Generic::List< GAPConnect::vertexView^ > tmpList = gcnew System::Collections::Generic::List< GAPConnect::vertexView^ >();
			 //Vertexe durchsuchen
			 for each (GAPConnect::vertexView^ element in this->vertexList){
				 if (element->Contains(pkt))
				 {
					 tmpList.Add(element);
				 }
			 }
			 //Behandlung der Ergebnisse
			 if (tmpList.Count == 1)
			 {//bei nur einem Ergebniss einfach dieses zurückgeben
				 return tmpList[0];
			 }else if (tmpList.Count > 1)
			 {//TODO Mehrere: Hier Fallbehandlung um das Richtige herauszufinden
				 return tmpList[0];
			 } 
			 else
			 {//nichts!
				 return nullptr;
			 }
		 }
		 ///<summary> Löscht über ein Handle ein Objekt </summary>
private: void deleteDrawnElement(GAPConnect::basicView^ element){
			 GAPConnect::vertexView^ vertex;
			 GAPConnect::edgeView^ edge;
			 if (( vertex = dynamic_cast<GAPConnect::vertexView^ >(element))!= nullptr){
				 this->vertexList->Remove(vertex);
			 }else if (( edge = dynamic_cast<GAPConnect::edgeView^ >(element)) != nullptr){
				 this->edgeList->Remove(edge);
			 }
			 this->Refresh();
		 }

};

}

