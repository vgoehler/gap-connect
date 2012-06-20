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
		Form1(void)
		{
			InitializeComponent();

			this->aboutDialog = gcnew about();
			this->changedGraph = false;
			//TODO Werte aus Ini Laden
			this->loadDefaultValues();
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
			}
		}
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
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  beendenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonNew;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonOpen;


	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripLabelMouseX;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripLabelMouseY;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

	///<summary>Handle für den About Dialog</summary>
	private: about^ aboutDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  ladenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  speichernToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  speichernalsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonSave;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  control;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::GroupBox^  zeichentools;
	private: System::Windows::Forms::ToolStrip^  zeichnenVertex;

	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexRound;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonVertexSquare;
	private: System::Windows::Forms::ToolStrip^  zeichnenEdge;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdge;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonDirection;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonEdgeValue;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonDirectionValue;

















	///<summary>Member um Veränderungen im Inhalt zu charakterisieren</summary>
	private: bool m_unsavedChanges;

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
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->mainmenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->neuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ladenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speichernalsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->beendenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ansichtToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hilfeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->maintoolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonNew = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->mainstatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripLabelMouseX = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripLabelMouseY = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->control = (gcnew System::Windows::Forms::Panel());
			this->zeichentools = (gcnew System::Windows::Forms::GroupBox());
			this->zeichnenEdge = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonEdge = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonEdgeValue = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonDirection = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonDirectionValue = (gcnew System::Windows::Forms::ToolStripButton());
			this->zeichnenVertex = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButtonVertexRound = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonVertexSquare = (gcnew System::Windows::Forms::ToolStripButton());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->mainmenuStrip->SuspendLayout();
			this->maintoolStrip->SuspendLayout();
			this->mainstatusStrip->SuspendLayout();
			this->control->SuspendLayout();
			this->zeichentools->SuspendLayout();
			this->zeichnenEdge->SuspendLayout();
			this->zeichnenVertex->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainmenuStrip
			// 
			this->mainmenuStrip->BackColor = System::Drawing::SystemColors::MenuBar;
			this->mainmenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->dateiToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem, this->ansichtToolStripMenuItem, this->optionenToolStripMenuItem, this->hilfeToolStripMenuItem});
			this->mainmenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainmenuStrip->Name = L"mainmenuStrip";
			this->mainmenuStrip->Size = System::Drawing::Size(992, 24);
			this->mainmenuStrip->TabIndex = 1;
			this->mainmenuStrip->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->neuToolStripMenuItem, 
				this->ladenToolStripMenuItem, this->speichernToolStripMenuItem, this->speichernalsToolStripMenuItem, this->toolStripSeparator1, 
				this->beendenToolStripMenuItem});
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
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(140, 6);
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
			this->optionenToolStripMenuItem->Name = L"optionenToolStripMenuItem";
			this->optionenToolStripMenuItem->Size = System::Drawing::Size(69, 20);
			this->optionenToolStripMenuItem->Text = L"&Optionen";
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
			this->maintoolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripButtonNew, 
				this->toolStripButtonOpen, this->toolStripButtonSave});
			this->maintoolStrip->Location = System::Drawing::Point(0, 24);
			this->maintoolStrip->Name = L"maintoolStrip";
			this->maintoolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->maintoolStrip->Size = System::Drawing::Size(992, 25);
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
			// mainstatusStrip
			// 
			this->mainstatusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripLabelMouseX, 
				this->toolStripLabelMouseY});
			this->mainstatusStrip->Location = System::Drawing::Point(0, 633);
			this->mainstatusStrip->Name = L"mainstatusStrip";
			this->mainstatusStrip->Size = System::Drawing::Size(992, 22);
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
			// openFileDialog1
			// 
			this->openFileDialog1->InitialDirectory = L".";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->InitialDirectory = L".";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(693, 27);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"DEBUG";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// control
			// 
			this->control->BackColor = System::Drawing::SystemColors::Control;
			this->control->Controls->Add(this->zeichentools);
			this->control->Dock = System::Windows::Forms::DockStyle::Left;
			this->control->Location = System::Drawing::Point(0, 49);
			this->control->Name = L"control";
			this->control->Size = System::Drawing::Size(198, 584);
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
				this->toolStripButtonEdgeValue, this->toolStripButtonDirection, this->toolStripButtonDirectionValue});
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
			this->toolStripButtonEdge->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonEdgeValue
			// 
			this->toolStripButtonEdgeValue->CheckOnClick = true;
			this->toolStripButtonEdgeValue->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonEdgeValue.Image")));
			this->toolStripButtonEdgeValue->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdgeValue->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonEdgeValue->Name = L"toolStripButtonEdgeValue";
			this->toolStripButtonEdgeValue->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonEdgeValue->Text = L"Kante mit Wert";
			this->toolStripButtonEdgeValue->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonEdgeValue->ToolTipText = L"Zeichnet eine Kante mit Kantenbewertung";
			this->toolStripButtonEdgeValue->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonDirection
			// 
			this->toolStripButtonDirection->CheckOnClick = true;
			this->toolStripButtonDirection->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonDirection.Image")));
			this->toolStripButtonDirection->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonDirection->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonDirection->Name = L"toolStripButtonDirection";
			this->toolStripButtonDirection->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonDirection->Text = L"gerichtete Kante";
			this->toolStripButtonDirection->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonDirection->ToolTipText = L"Zeichnet eine gerichtete Kante";
			this->toolStripButtonDirection->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// toolStripButtonDirectionValue
			// 
			this->toolStripButtonDirectionValue->CheckOnClick = true;
			this->toolStripButtonDirectionValue->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonDirectionValue.Image")));
			this->toolStripButtonDirectionValue->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonDirectionValue->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonDirectionValue->Name = L"toolStripButtonDirectionValue";
			this->toolStripButtonDirectionValue->Size = System::Drawing::Size(190, 36);
			this->toolStripButtonDirectionValue->Text = L"gerichtete Kante mit Wert";
			this->toolStripButtonDirectionValue->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripButtonDirectionValue->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
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
			this->toolStripButtonVertexRound->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
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
			this->toolStripButtonVertexSquare->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonsOnlyOneChecked);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Window;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(198, 49);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(794, 584);
			this->panel1->TabIndex = 7;
			this->panel1->MouseLeave += gcnew System::EventHandler(this, &Form1::DrawArea_MouseLeave);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::DrawArea_MouseMove);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(992, 655);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->control);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->mainstatusStrip);
			this->Controls->Add(this->maintoolStrip);
			this->Controls->Add(this->mainmenuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(400, 110);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
///<summary> Laden der Iniwerte </summary>
public: void loadDefaultValues(void){
		}

///<summary> zeigt nach Menü Klick den About Dialog an.</summary>
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->aboutDialog->Visible == false) this->aboutDialog->Show(this);//Anzeige des About Dialogs
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
///<summary> DEBUG BUTTON TODO</summary>
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->changedGraph = !this->changedGraph;
		 }
///<summary> Maus Bewegung im Zeichenbereich Zeigt Koordinaten im Tooltip an TODO</summary>
private: System::Void DrawArea_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 System::String^ start = L"X: ";
			 this->toolStripLabelMouseX->Text = L"X: "+Convert::ToString(e->X);
			 this->toolStripLabelMouseY->Text = L"Y: "+Convert::ToString(e->Y);
		 }
///<summary> Maus verläßt Zeichenbereich. Koordinatenwerte auf Defaults </summary>
private: System::Void DrawArea_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->toolStripLabelMouseX->Text = L"X: ";
			 this->toolStripLabelMouseY->Text = L"Y: ";
		 }
///<summary> Neues Dokument </summary>
 private: System::Void neuMenu_Click(System::Object^ sender, System::EventArgs^ e){
			  //TODO alle daten löschen, nachfragen ob gespeichert werden soll

		  }
///<summary> Überprüft beim Auswählen von Toolbuttons, dass auch nur einer ausgewählt ist.</summary>
private: System::Void toolStripButtonsOnlyOneChecked(System::Object^  sender, System::EventArgs^  e) {
			 this->zeichentools->Controls;
		 }
};
}

