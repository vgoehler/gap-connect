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
	/// Zusammenfassung für toolbar
	/// </summary>
	public ref class toolbar : public System::Windows::Forms::Form
	{
	public:
		toolbar(void){
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~toolbar()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^  tooltoolStrip;
	protected: 
	private: System::Windows::Forms::StatusStrip^  toolstatusStrip;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tooltoolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->toolstatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->SuspendLayout();
			// 
			// tooltoolStrip
			// 
			this->tooltoolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tooltoolStrip->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Table;
			this->tooltoolStrip->Location = System::Drawing::Point(0, 0);
			this->tooltoolStrip->Name = L"tooltoolStrip";
			this->tooltoolStrip->Size = System::Drawing::Size(185, 0);
			this->tooltoolStrip->TabIndex = 0;
			// 
			// toolstatusStrip
			// 
			this->toolstatusStrip->Location = System::Drawing::Point(0, 329);
			this->toolstatusStrip->Name = L"toolstatusStrip";
			this->toolstatusStrip->Size = System::Drawing::Size(185, 22);
			this->toolstatusStrip->SizingGrip = false;
			this->toolstatusStrip->TabIndex = 1;
			// 
			// toolbar
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(185, 351);
			this->ControlBox = false;
			this->Controls->Add(this->toolstatusStrip);
			this->Controls->Add(this->tooltoolStrip);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"toolbar";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Toolbar";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
