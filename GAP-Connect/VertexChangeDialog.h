#pragma once

namespace GAPConnect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für VertexChangeDialog
	/// </summary>
	public ref class VertexChangeDialog : public System::Windows::Forms::Form
	{
	public:
		VertexChangeDialog(void)
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
		~VertexChangeDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::CheckBox^  adjustSize;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  Ok;
	private: System::Windows::Forms::Button^  cancel;



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
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Label^  label2;
			System::Windows::Forms::Label^  label3;
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->adjustSize = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->Ok = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 32);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(183, 20);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(202, 32);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(221, 218);
			this->textBox2->TabIndex = 1;
			// 
			// adjustSize
			// 
			this->adjustSize->AutoSize = true;
			this->adjustSize->Location = System::Drawing::Point(13, 58);
			this->adjustSize->Name = L"adjustSize";
			this->adjustSize->Size = System::Drawing::Size(181, 17);
			this->adjustSize->TabIndex = 2;
			this->adjustSize->Text = L"Größe an Beschriftung anpassen";
			this->adjustSize->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(12, 9);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(99, 13);
			label1->TabIndex = 3;
			label1->Text = L"Knotenbeschriftung";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(199, 9);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(60, 13);
			label2->TabIndex = 4;
			label2->Text = L"Kommentar";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Rechteck", L"Kreis"});
			this->comboBox1->Location = System::Drawing::Point(13, 108);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(182, 21);
			this->comboBox1->TabIndex = 5;
			// 
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(13, 89);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(53, 13);
			label3->TabIndex = 6;
			label3->Text = L"Knotenart";
			// 
			// Ok
			// 
			this->Ok->Location = System::Drawing::Point(107, 227);
			this->Ok->Name = L"Ok";
			this->Ok->Size = System::Drawing::Size(88, 23);
			this->Ok->TabIndex = 7;
			this->Ok->Text = L"Übernehmen";
			this->Ok->UseVisualStyleBackColor = true;
			// 
			// cancel
			// 
			this->cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancel->Location = System::Drawing::Point(12, 227);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(88, 23);
			this->cancel->TabIndex = 8;
			this->cancel->Text = L"Abbrechen";
			this->cancel->UseVisualStyleBackColor = true;
			// 
			// VertexChangeDialog
			// 
			this->AcceptButton = this->Ok;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancel;
			this->ClientSize = System::Drawing::Size(434, 265);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->Ok);
			this->Controls->Add(label3);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(label2);
			this->Controls->Add(label1);
			this->Controls->Add(this->adjustSize);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"VertexChangeDialog";
			this->Text = L"Knotenbearbeitung";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
