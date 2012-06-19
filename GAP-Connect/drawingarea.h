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
	/// Zusammenfassung für drawingarea
	/// </summary>
	public ref class drawingarea : public System::Windows::Forms::Form
	{
	public:
		drawingarea(void): m_changed(false), m_closing(false), m_new(true)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~drawingarea()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;
		///<summary>Anzeigen der Änderung am Inhalt</summary>
		bool m_changed;//auf True wenn sich Inhalt geändert hat
		///<summary>Anzeigen ob neu Erzeugtes Fenster</summary>
		bool m_new;//auf True wenn es sich um ein leeres Fenster handelt
		///<summary>Zeigt an ob das Form sich am schließen ist.</summary>
		bool m_closing;

	public:
		property bool isNew{
			bool get(){
				return(this->m_new);
			}
		}
		property bool isChanged{
			bool get(){
				return(this->m_changed);
			}
		}
		property bool isClosing{
			bool get(){
				return(this->m_closing);
			}
			void set(bool value){
				this->m_closing = value;
			}
		}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// drawingarea
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(617, 567);
			this->DoubleBuffered = true;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(400, 38);
			this->Name = L"drawingarea";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &drawingarea::drawingarea_FormClosing);
			this->ResumeLayout(false);

		}
#pragma endregion
		///<subject>Schließen der Drawing Area</subject>
	private: System::Void drawingarea_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	};
}
