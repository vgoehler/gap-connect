#include "StdAfx.h"
#include "vertexView.h"


namespace GAPConnect {
	vertexView::vertexView(System::Windows::Forms::Form^ inParent):vertexType(0), isMarked(false)
	{
		this->Parent = inParent;
		InitializeComponent();
	}

	void vertexView::InitializeComponent( void )
	{
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->ForeColor = System::Drawing::Color::White;
		this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->Size = System::Drawing::Size(25, 25);
		this->Text = L"";
		this->MaximumSize = System::Drawing::Size(100, 100);
		this->MinimumSize = System::Drawing::Size(25, 25);
		this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->UseVisualStyleBackColor = false;
		this->CausesValidation = false;
		this->Enabled = true;
		this->FlatAppearance->BorderColor = System::Drawing::Color::Firebrick;
		this->FlatAppearance->BorderSize = 0;
		this->TabStop = false;
		this->ContextMenuStrip = (dynamic_cast<GAPConnect::Form1^ >(this->Parent))->MenuforVertex;
		this->changeAppearance();

		//event
		this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(dynamic_cast<GAPConnect::Form1^ >(this->Parent), &Form1::vertex_MouseUp);
	}

	void vertexView::changeAppearance( void )
	{
		if (this->vertexType == 0)//round
		{
			this->BackgroundImage = System::Drawing::Image::FromFile(L"./Images/vertexHard.png");
			this->BackColor = System::Drawing::Color::Transparent;
			this->Text = L"";
			this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
		}else{
			this->BackgroundImage = nullptr;
			this->BackColor = System::Drawing::Color::Black;
			this->Text = L"";
			this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Black;
		}
	}

	bool vertexView::markVertex( void )
	{
		this->isMarked = !this->isMarked;
		this->FlatAppearance->BorderSize = this->isMarked ? 3 : 0;
		return (this->isMarked);
	}

	void vertexView::startConfigDialog( void )
	{
		//vertexChangeDialog Instanz als Modaler Dialog starten
		VertexChangeDialog^ configDialog = gcnew VertexChangeDialog();
		this->InitializeValues(configDialog);
		if ( configDialog->ShowDialog( this ) == System::Windows::Forms::DialogResult::OK )
		{
			//TODO Daten ändern
			this->SuspendLayout();
			if (this->vertexType != configDialog->Knotenart)
			{
				this->kindOf = configDialog->Knotenart;
			}
			this->Text = configDialog->Knotenbeschriftung;
			//TODO Größenanpassung max. bis MaxSize min bis MinSize
			if (configDialog->DoAdjustSize){
				this->Size = System::Drawing::Size(this->PreferredSize.Width,this->PreferredSize.Width);
			}
			this->ResumeLayout();
			//TODO Kommentartext
			this->Refresh();
		}

		delete configDialog;
	}

	void vertexView::InitializeValues(System::Windows::Forms::Form^ configDialog)
	{
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		dialog->Knotenbeschriftung = this->Text;
		dialog->Kommentar = L"Kommentar";//TODO
		dialog->Knotenart = this->vertexType;
	}

}//namespace end
