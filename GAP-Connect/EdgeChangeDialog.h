#pragma once

namespace GAPConnect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für EdgeChangeDialog
	/// </summary>
	public ref class EdgeChangeDialog : public System::Windows::Forms::Form
	{
	public:
		EdgeChangeDialog(void)
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
		~EdgeChangeDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tBValue;
	protected: 

	private: System::Windows::Forms::TextBox^  tBkommentar;
	protected: 




	private: System::Windows::Forms::CheckBox^  cBArc;

	private: System::Windows::Forms::Button^  Cancel;
	private: System::Windows::Forms::Button^  Ok;
	private: System::Windows::Forms::CheckBox^  cBChangeDirection;

	private: System::Windows::Forms::CheckBox^  cBEnabled;
	private: System::Windows::Forms::CheckBox^  cBLoop;
	private: System::Windows::Forms::CheckBox^  cBaidLine;






	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

	public:
		property System::String^ Kommentar{
			System::String^ get( void ){
				return( this->tBkommentar->Text);
			}
			void set (System::String^ inValue){
				this->tBkommentar->Text = inValue;
			}
		}
		property System::String^ Wichtung{
			System::String^ get( void ){
				return( this->tBValue->Text);
			}
			void set (System::String^ inValue){
				this->tBValue->Text = inValue;
			}
		}
		property bool IsArc {
			bool get (void){
				return(this->cBArc->Checked);
			}
			void set (bool inValue){
				this->cBArc->Checked = inValue;
			}
		}
		property bool EdgeEnabled{
			bool get ( void ){
				return(this->cBEnabled->Checked);
			}
			void set (bool inValue){
				this->cBEnabled->Checked = inValue;
			}
		}
		property bool RevertDirection{
			bool get ( void ){
				if (this->cBChangeDirection->Enabled){
					return(this->cBChangeDirection->Checked);
				}else{
					return(false);
				}
			}
		}
		property bool IsLoop{
			bool get (void){
				return(this->cBLoop->Checked);
			}
			void set (bool inValue){
				this->cBLoop->Checked = inValue;
			}

		}
		property bool withAidLine{
			bool get (void){
				return(this->cBaidLine->Checked);
			}
			void set (bool inValue){
				this->cBaidLine->Checked = inValue;
			}
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Label^  label2;
			this->tBValue = (gcnew System::Windows::Forms::TextBox());
			this->tBkommentar = (gcnew System::Windows::Forms::TextBox());
			this->cBArc = (gcnew System::Windows::Forms::CheckBox());
			this->Cancel = (gcnew System::Windows::Forms::Button());
			this->Ok = (gcnew System::Windows::Forms::Button());
			this->cBChangeDirection = (gcnew System::Windows::Forms::CheckBox());
			this->cBEnabled = (gcnew System::Windows::Forms::CheckBox());
			this->cBLoop = (gcnew System::Windows::Forms::CheckBox());
			this->cBaidLine = (gcnew System::Windows::Forms::CheckBox());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(8, 9);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(91, 13);
			label1->TabIndex = 2;
			label1->Text = L"Kantenbewertung";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(188, 9);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(60, 13);
			label2->TabIndex = 7;
			label2->Text = L"Kommentar";
			// 
			// tBValue
			// 
			this->tBValue->Location = System::Drawing::Point(4, 25);
			this->tBValue->Name = L"tBValue";
			this->tBValue->Size = System::Drawing::Size(172, 20);
			this->tBValue->TabIndex = 0;
			// 
			// tBkommentar
			// 
			this->tBkommentar->AcceptsReturn = true;
			this->tBkommentar->Location = System::Drawing::Point(184, 25);
			this->tBkommentar->Multiline = true;
			this->tBkommentar->Name = L"tBkommentar";
			this->tBkommentar->Size = System::Drawing::Size(172, 224);
			this->tBkommentar->TabIndex = 1;
			// 
			// cBArc
			// 
			this->cBArc->AutoSize = true;
			this->cBArc->Location = System::Drawing::Point(12, 84);
			this->cBArc->Name = L"cBArc";
			this->cBArc->Size = System::Drawing::Size(69, 17);
			this->cBArc->TabIndex = 3;
			this->cBArc->Text = L"Gerichtet";
			this->cBArc->UseVisualStyleBackColor = true;
			this->cBArc->CheckedChanged += gcnew System::EventHandler(this, &EdgeChangeDialog::cBArc_CheckedChanged);
			// 
			// Cancel
			// 
			this->Cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Cancel->Location = System::Drawing::Point(13, 226);
			this->Cancel->Name = L"Cancel";
			this->Cancel->Size = System::Drawing::Size(75, 23);
			this->Cancel->TabIndex = 4;
			this->Cancel->Text = L"Abbrechen";
			this->Cancel->UseVisualStyleBackColor = true;
			// 
			// Ok
			// 
			this->Ok->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Ok->Location = System::Drawing::Point(95, 226);
			this->Ok->Name = L"Ok";
			this->Ok->Size = System::Drawing::Size(75, 23);
			this->Ok->TabIndex = 5;
			this->Ok->Text = L"Ok";
			this->Ok->UseVisualStyleBackColor = true;
			// 
			// cBChangeDirection
			// 
			this->cBChangeDirection->AutoSize = true;
			this->cBChangeDirection->Enabled = false;
			this->cBChangeDirection->Location = System::Drawing::Point(32, 109);
			this->cBChangeDirection->Name = L"cBChangeDirection";
			this->cBChangeDirection->Size = System::Drawing::Size(117, 17);
			this->cBChangeDirection->TabIndex = 6;
			this->cBChangeDirection->Text = L"Richtung wechseln";
			this->cBChangeDirection->UseVisualStyleBackColor = true;
			// 
			// cBEnabled
			// 
			this->cBEnabled->AutoSize = true;
			this->cBEnabled->Checked = true;
			this->cBEnabled->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBEnabled->Location = System::Drawing::Point(12, 142);
			this->cBEnabled->Name = L"cBEnabled";
			this->cBEnabled->Size = System::Drawing::Size(64, 17);
			this->cBEnabled->TabIndex = 8;
			this->cBEnabled->Text = L"Aktiviert";
			this->cBEnabled->UseVisualStyleBackColor = true;
			// 
			// cBLoop
			// 
			this->cBLoop->AutoSize = true;
			this->cBLoop->Location = System::Drawing::Point(12, 175);
			this->cBLoop->Name = L"cBLoop";
			this->cBLoop->Size = System::Drawing::Size(143, 17);
			this->cBLoop->TabIndex = 9;
			this->cBLoop->Text = L"zu Schlinge konvertieren";
			this->cBLoop->UseVisualStyleBackColor = true;
			this->cBLoop->CheckedChanged += gcnew System::EventHandler(this, &EdgeChangeDialog::cBLoop_CheckedChanged);
			// 
			// cBaidLine
			// 
			this->cBaidLine->AutoSize = true;
			this->cBaidLine->Location = System::Drawing::Point(12, 51);
			this->cBaidLine->Name = L"cBaidLine";
			this->cBaidLine->Size = System::Drawing::Size(64, 17);
			this->cBaidLine->TabIndex = 10;
			this->cBaidLine->Text = L"Hilfslinie";
			this->cBaidLine->UseVisualStyleBackColor = true;
			// 
			// EdgeChangeDialog
			// 
			this->AcceptButton = this->Ok;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->Cancel;
			this->ClientSize = System::Drawing::Size(362, 262);
			this->Controls->Add(this->cBaidLine);
			this->Controls->Add(this->cBLoop);
			this->Controls->Add(this->cBEnabled);
			this->Controls->Add(label2);
			this->Controls->Add(this->cBChangeDirection);
			this->Controls->Add(this->Ok);
			this->Controls->Add(this->Cancel);
			this->Controls->Add(this->cBArc);
			this->Controls->Add(label1);
			this->Controls->Add(this->tBkommentar);
			this->Controls->Add(this->tBValue);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"EdgeChangeDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Kantenbearbeitung";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void cBArc_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->cBChangeDirection->Enabled = this->IsArc;
			 }
private: System::Void cBLoop_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (this->IsLoop)
			 {
				 this->cBLoop->Enabled = false;
				 this->cBLoop->Text = L"ist eine Schlinge";
			 }
		 }
};
}
