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
		this->UseVisualStyleBackColor = false;
		this->CausesValidation = false;
		this->Enabled = true;
		this->FlatAppearance->BorderColor = System::Drawing::Color::Black;
		this->FlatAppearance->BorderSize = 0;
		this->TabStop = false;
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
			this->Text = L"Y";
			this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
		}else{
			this->BackgroundImage = nullptr;
			this->BackColor = System::Drawing::Color::Black;
			this->Text = L"x";
			this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Black;
		}
	}

	bool vertexView::markVertex( void )
	{
		this->isMarked = !this->isMarked;
		this->ForeColor = this->isMarked ? System::Drawing::Color::Red : System::Drawing::Color::White;
		return (this->isMarked);
	}

}
