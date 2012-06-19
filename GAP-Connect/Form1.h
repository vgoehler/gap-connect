#pragma once
#include "stdafx.h"
#define DRAWINGAREA_W 0
#define DRAWINGAREA_H 1
#define CONTROLAREA_W 2
#define CONTROLAREA_H 3
#define TOOLBAR_W 4
#define TOOLBAR_H 5
#define DRAWINGAREA_X 0
#define DRAWINGAREA_Y 1
#define CONTROLAREA_X 2
#define CONTROLAREA_Y 3
#define TOOLBAR_X 4
#define TOOLBAR_Y 5

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			this->drawingArea = gcnew drawingarea();
			this->toolBar = gcnew toolbar();
			this->controlArea = gcnew menu();

			//Positionen setzen
			//TODO Werte aus Ini Laden
			this->loadDefaultValues();
			this->setWindowLayout();

			//Anzeigen
			this->toolBar->Show(this);
			this->drawingArea->Show(this);
			this->controlArea->Show(this);

			//Focus
			this->controlArea->Focus();
		}
	public:
		/// <summary>
		/// Die Methode ist zum Schließen von Subareas oder auch zum Schließen des Hauptprogrammes gedacht.
		/// </summary>
		/// <param name="drawingAreatoClose">Objekthandle auf die drawingArea die das Schließen angeordnet hat</param>
		void doOnDrawingAreaClose(drawingarea^ drawingAreatoClose){
			 drawingAreatoClose->isClosing = true;
			 if (drawingAreatoClose->isNew){
				 //Alles schließen, TODO: im Multi Mode muss hier noch auf weitere getestet werden
				 this->DebugText = L"Versuche zu Schließen!";
				 this->Close();
			 }else{
				 //TODO nur Fenster schließen und Neu initialisieren
				 drawingAreatoClose->Close();
				 this->drawingArea = gcnew drawingarea();
				 this->drawingArea->Show(this);
			 }
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

	/// <summary>Handle für den Zeichenbereich</summary>
	private: drawingarea^ drawingArea;//Hauptzeichenbereich

	///<summary> Handle für die Zeichenpalette</summary>
	private: toolbar^ toolBar;//Zeichenpalette

	///<summary> Handle für das Menü</summary>
	private: menu^	controlArea;//Menue-Toolbar-System

	///<summary> KoordinatenWerte für Fenster im FreeMode </summary>
	private: array<int>^ arrFreeKoords;
	///<summary> Breiten und Höhen für Fenster im FreeMode. Breite und Höhe der drawing Area, control Area und Tool Bar </summary>
	private: array<int>^ arrFreeWidthHeight;

	private: System::Windows::Forms::Label^  label1;//insignifikant!!!

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

//////////////////////////////////////////////////////////////////////////

	///<summary>Ändert zu DebugZwecken den Inhalt des Label1. Nicht Wichtig!</summary>
	public: property String^ DebugText{
				void set(String^ value){
					this->label1->Text = value;
					this->Refresh();
				}
			}

//////////////////////////////////////////////////////////////////////////

			///<summary> Laden der Iniwerte für Fensterposition und Andere </summary>
	public: void loadDefaultValues(void){//TODO
		this->arrFreeKoords = gcnew array<int>{1281,470,1087,363,1088,476};
		this->arrFreeWidthHeight = gcnew array<int>{633,605,434,136,191,375};
		}

			///<summary> momentane Koordinaten werden im Free Mode array gesichert </summary>
	public: void saveWindowPositions(void){
				delete(this->arrFreeKoords);
				this->arrFreeKoords = gcnew array<int>{this->drawingArea->Location.X, this->drawingArea->Location.Y,
														this->controlArea->Location.X, this->controlArea->Location.Y,
														this->toolBar->Location.X, this->toolBar->Location.Y};
			}

			///<summary> Setzt das Layout der Fenster im Free Mode. Für Restore aus den Optionen und Reset.</summary>
	public: void setWindowLayout(void){
				//Layout Deaktivieren
				this->drawingArea->SuspendLayout();
				this->controlArea->SuspendLayout();
				this->toolBar->SuspendLayout();

				if (this->controlArea->Docked == false){//Freier Modus
					//Styles
					this->drawingArea->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
					//Größen setzen
					this->controlArea->Width = this->arrFreeWidthHeight[CONTROLAREA_W];
					this->toolBar->Height = this->arrFreeWidthHeight[TOOLBAR_H];
					//Positionen setzen
					this->drawingArea->Location = Point(this->arrFreeKoords[DRAWINGAREA_X],this->arrFreeKoords[DRAWINGAREA_Y]);
					this->controlArea->Location = Point(this->arrFreeKoords[CONTROLAREA_X],this->arrFreeKoords[CONTROLAREA_Y]);
					this->toolBar->Location = Point(this->arrFreeKoords[TOOLBAR_X],this->arrFreeKoords[TOOLBAR_Y]);
				}else{//Dock Modus 
					//Styles
					this->drawingArea->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
					//Höhen Breiten sichern
					this->arrFreeWidthHeight[CONTROLAREA_W] = this->controlArea->Width;
					this->arrFreeWidthHeight[TOOLBAR_H] = this->toolBar->Width;
					//new Positions
					int new_x = this->drawingArea->Location.X - this->toolBar->Width;
					int new_y = this->drawingArea->Location.Y - this->controlArea->Height;
					this->toolBar->Location = Point(new_x, this->drawingArea->Location.Y);
					this->controlArea->Location = Point(new_x, new_y);
					//Höhen bzw. Breiten anpassen
					//controlArea Breite = toolbar + drawingArea
					this->controlArea->Width = this->toolBar->Width + this->drawingArea->Width;
					//toolbar Höhe = drawing Area
					this->toolBar->Height = this->drawingArea->Height;
				}

				//Layout Aktivieren
				this->drawingArea->ResumeLayout();
				this->controlArea->ResumeLayout();
				this->toolBar->ResumeLayout();
			}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(103, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(152, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"You Should not see this Dialog";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(394, 86);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MinimumSize = System::Drawing::Size(400, 110);
			this->Name = L"Form1";
			this->ShowInTaskbar = false;
			this->Text = L"Main";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}

