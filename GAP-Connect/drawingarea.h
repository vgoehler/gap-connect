#pragma once

namespace GAPConnect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung f�r drawingarea
	/// </summary>
	public ref class drawingarea : public System::Windows::Forms::Form
	{
	public:
		drawingarea(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzuf�gen.
			//
			this->isChanged=false;
			this->isNew=true;
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
		bool isChanged;//auf True wenn sich Inhalt ge�ndert hat
		bool isNew;//auf True wenn es sich um ein leeres Fenster handelt

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// drawingarea
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(617, 567);
			this->DoubleBuffered = true;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(400, 38);
			this->Name = L"drawingarea";
			this->ShowIcon = false;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &drawingarea::drawingarea_FormClosing);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void drawingarea_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if (this->isChanged){
					 //TODO SavePrompt Dialog
				 }else{
					 //keine �nderungen
					 if (this->isNew){
						 //TODO Alles schlie�en
						 //event raisen hier
					 }else{
						 //TODO nur Fenster schlie�en und Neu initialisieren
					 }
				 }
			 }
	};
}
