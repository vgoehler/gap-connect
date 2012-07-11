#pragma once

namespace GAPConnect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für AlgorithmusRunDialog
	/// </summary>
	public ref class AlgorithmusRunDialog : public System::Windows::Forms::Form
	{
	public:
		AlgorithmusRunDialog(void)
		{
			InitializeComponent();

			this->toolTip->SetToolTip(this->CancelButton, L"Bricht den laufenden Algorithmus ab.");
			this->toolTip->SetToolTip(this->NextButton, L"Führt den nächsten Schritt im Algorithmus durch.");
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~AlgorithmusRunDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  CancelButton;
	protected: 
	private: System::Windows::Forms::Button^  NextButton;
	private: System::Windows::Forms::ToolTip^  toolTip;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::TextBox^  textBox1;
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->NextButton = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			textBox1->BackColor = System::Drawing::SystemColors::Control;
			textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			textBox1->Enabled = false;
			textBox1->Location = System::Drawing::Point(12, 41);
			textBox1->Multiline = true;
			textBox1->Name = L"textBox1";
			textBox1->Size = System::Drawing::Size(176, 56);
			textBox1->TabIndex = 9;
			textBox1->Text = L"Achtung: nicht-Integer Kantenbewertungen werden als 0 gewertet, weiterhin werden " 
				L"Bögen als Kanten behandelt.";
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(104, 12);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(86, 23);
			this->CancelButton->TabIndex = 7;
			this->CancelButton->Text = L"Abbrechen";
			this->CancelButton->UseVisualStyleBackColor = true;
			// 
			// NextButton
			// 
			this->NextButton->Location = System::Drawing::Point(12, 12);
			this->NextButton->Name = L"NextButton";
			this->NextButton->Size = System::Drawing::Size(86, 23);
			this->NextButton->TabIndex = 6;
			this->NextButton->Text = L"Weiter";
			this->NextButton->UseVisualStyleBackColor = true;
			this->NextButton->Click += gcnew System::EventHandler(this, &AlgorithmusRunDialog::NextButton_Click);
			// 
			// AlgorithmusRunDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(200, 100);
			this->ControlBox = false;
			this->Controls->Add(textBox1);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->NextButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"AlgorithmusRunDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Dijkstra Algorithmus";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		///<summary> Nächster Schritt im Algorithmus </summary>
	private: System::Void NextButton_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
