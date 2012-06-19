#pragma once
#include "about.h"
#include "stdafx.h"

namespace GAPConnect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für menu
	/// </summary>
	public ref class menu : public System::Windows::Forms::Form
	{
	public:
		menu(void){
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			this->aboutDialog = gcnew about();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~menu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  mainmenuStrip;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  dateiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ansichtToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fensterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hilfeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  maintoolStrip;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::StatusStrip^  mainstatusStrip;

	private: about^ aboutDialog;//enthält den about Dialog

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::ToolStripMenuItem^  dockingToolStripMenuItem;

	///<summary> Status der Dockeigenschaft </summary>
	public: property bool Docked{
				bool get (void){
					return(this->dockingToolStripMenuItem->Checked);
				}
			}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(menu::typeid));
			this->mainmenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ansichtToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fensterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dockingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hilfeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->maintoolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->mainstatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->mainmenuStrip->SuspendLayout();
			this->maintoolStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainmenuStrip
			// 
			this->mainmenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->dateiToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem, this->ansichtToolStripMenuItem, this->optionenToolStripMenuItem, this->fensterToolStripMenuItem, 
				this->hilfeToolStripMenuItem});
			this->mainmenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainmenuStrip->Name = L"mainmenuStrip";
			this->mainmenuStrip->Size = System::Drawing::Size(428, 24);
			this->mainmenuStrip->TabIndex = 1;
			this->mainmenuStrip->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->dateiToolStripMenuItem->Text = L"&Datei";
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
			// fensterToolStripMenuItem
			// 
			this->fensterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->dockingToolStripMenuItem});
			this->fensterToolStripMenuItem->Name = L"fensterToolStripMenuItem";
			this->fensterToolStripMenuItem->Size = System::Drawing::Size(57, 20);
			this->fensterToolStripMenuItem->Text = L"&Fenster";
			// 
			// dockingToolStripMenuItem
			// 
			this->dockingToolStripMenuItem->AutoToolTip = true;
			this->dockingToolStripMenuItem->CheckOnClick = true;
			this->dockingToolStripMenuItem->Name = L"dockingToolStripMenuItem";
			this->dockingToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F12));
			this->dockingToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->dockingToolStripMenuItem->Text = L"&Docking";
			this->dockingToolStripMenuItem->ToolTipText = L"Darstellung als gedockte oder freie Fenster.";
			this->dockingToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &menu::dockingToolStripMenuItem_CheckedChanged);
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
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &menu::aboutToolStripMenuItem_Click);
			// 
			// maintoolStrip
			// 
			this->maintoolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->maintoolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripButton1, 
				this->toolStripButton2});
			this->maintoolStrip->Location = System::Drawing::Point(0, 24);
			this->maintoolStrip->Name = L"maintoolStrip";
			this->maintoolStrip->Size = System::Drawing::Size(428, 25);
			this->maintoolStrip->TabIndex = 3;
			this->maintoolStrip->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
			// 
			// mainstatusStrip
			// 
			this->mainstatusStrip->Location = System::Drawing::Point(0, 76);
			this->mainstatusStrip->Name = L"mainstatusStrip";
			this->mainstatusStrip->Size = System::Drawing::Size(428, 22);
			this->mainstatusStrip->SizingGrip = false;
			this->mainstatusStrip->TabIndex = 4;
			this->mainstatusStrip->Text = L"statusStrip1";
			// 
			// menu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(428, 98);
			this->ControlBox = false;
			this->Controls->Add(this->mainstatusStrip);
			this->Controls->Add(this->maintoolStrip);
			this->Controls->Add(this->mainmenuStrip);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Location = System::Drawing::Point(0, 100);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"menu";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"menu";
			this->mainmenuStrip->ResumeLayout(false);
			this->mainmenuStrip->PerformLayout();
			this->maintoolStrip->ResumeLayout(false);
			this->maintoolStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {//KLICK auf About Button im Menü
				 if (this->aboutDialog->Visible == false) this->aboutDialog->Show(this);//Anzeige des About Dialogs
			 }
	private: System::Void dockingToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e);//Modus Wechsel - Docking
};
}
