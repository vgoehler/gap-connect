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
	public:
		property System::String^ Knotenbeschriftung{
			void set(System::String^ inText){
				this->knotenText->Text = inText;
			}
			System::String^ get(void){
				return (this->knotenText->Text);
			}
		}
		property System::String^ Kommentar{
			void set(System::String^ inText){
				this->kommentar->Text = inText;
			}
			System::String^ get(void){
				return (this->kommentar->Text);
			}
		}
		property bool DoAdjustSize{
			void set(bool inValue){
				this->adjustSize->Checked = inValue;
			}
			bool get(void){
				return(this->adjustSize->Checked);
			}
		}
		property int Knotenart{
			void set(int inValue){
				this->cbType->SelectedIndex = inValue;
			}
			int get(void){
				return(this->cbType->SelectedIndex);
			}
		}
		property bool VertexEnabled{
			void set( bool inValue ){
				this->cBEnabled->Checked = inValue;
			}
			bool get(void){
				return(this->cBEnabled->Checked);
			}
		}

	private: System::Windows::Forms::TextBox^  knotenText;
	private: System::Windows::Forms::TextBox^  kommentar;
	private: System::Windows::Forms::CheckBox^  adjustSize;
	private: System::Windows::Forms::ComboBox^  cbType;

	private: System::Windows::Forms::Button^  Ok;
	private: System::Windows::Forms::Button^  cancel;
	private: System::Windows::Forms::CheckBox^  cBEnabled;




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
			this->knotenText = (gcnew System::Windows::Forms::TextBox());
			this->kommentar = (gcnew System::Windows::Forms::TextBox());
			this->adjustSize = (gcnew System::Windows::Forms::CheckBox());
			this->cbType = (gcnew System::Windows::Forms::ComboBox());
			this->Ok = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->cBEnabled = (gcnew System::Windows::Forms::CheckBox());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
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
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(13, 89);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(53, 13);
			label3->TabIndex = 6;
			label3->Text = L"Knotenart";
			// 
			// knotenText
			// 
			this->knotenText->Location = System::Drawing::Point(12, 32);
			this->knotenText->Name = L"knotenText";
			this->knotenText->Size = System::Drawing::Size(183, 20);
			this->knotenText->TabIndex = 0;
			// 
			// kommentar
			// 
			this->kommentar->Location = System::Drawing::Point(202, 32);
			this->kommentar->Multiline = true;
			this->kommentar->Name = L"kommentar";
			this->kommentar->Size = System::Drawing::Size(221, 218);
			this->kommentar->TabIndex = 4;
			// 
			// adjustSize
			// 
			this->adjustSize->AutoSize = true;
			this->adjustSize->Location = System::Drawing::Point(13, 58);
			this->adjustSize->Name = L"adjustSize";
			this->adjustSize->Size = System::Drawing::Size(181, 17);
			this->adjustSize->TabIndex = 1;
			this->adjustSize->Text = L"Größe an Beschriftung anpassen";
			this->adjustSize->UseVisualStyleBackColor = true;
			// 
			// cbType
			// 
			this->cbType->FormattingEnabled = true;
			this->cbType->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Kreis", L"Rechteck"});
			this->cbType->Location = System::Drawing::Point(13, 108);
			this->cbType->Name = L"cbType";
			this->cbType->Size = System::Drawing::Size(182, 21);
			this->cbType->TabIndex = 3;
			// 
			// Ok
			// 
			this->Ok->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->Ok->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Ok->Location = System::Drawing::Point(107, 227);
			this->Ok->Name = L"Ok";
			this->Ok->Size = System::Drawing::Size(88, 23);
			this->Ok->TabIndex = 6;
			this->Ok->Text = L"Übernehmen";
			this->Ok->UseVisualStyleBackColor = true;
			// 
			// cancel
			// 
			this->cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancel->Location = System::Drawing::Point(12, 227);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(88, 23);
			this->cancel->TabIndex = 5;
			this->cancel->Text = L"Abbrechen";
			this->cancel->UseVisualStyleBackColor = true;
			// 
			// cBEnabled
			// 
			this->cBEnabled->AutoSize = true;
			this->cBEnabled->Checked = true;
			this->cBEnabled->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBEnabled->Location = System::Drawing::Point(12, 136);
			this->cBEnabled->Name = L"cBEnabled";
			this->cBEnabled->Size = System::Drawing::Size(64, 17);
			this->cBEnabled->TabIndex = 7;
			this->cBEnabled->Text = L"Aktiviert";
			this->cBEnabled->UseVisualStyleBackColor = true;
			// 
			// VertexChangeDialog
			// 
			this->AcceptButton = this->Ok;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancel;
			this->ClientSize = System::Drawing::Size(434, 265);
			this->Controls->Add(this->cBEnabled);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->Ok);
			this->Controls->Add(label3);
			this->Controls->Add(this->cbType);
			this->Controls->Add(label2);
			this->Controls->Add(label1);
			this->Controls->Add(this->adjustSize);
			this->Controls->Add(this->kommentar);
			this->Controls->Add(this->knotenText);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"VertexChangeDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Knotenbearbeitung";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
