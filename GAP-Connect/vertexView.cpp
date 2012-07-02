#include "StdAfx.h"
#include "vertexView.h"


namespace GAPConnect {
	vertexView::vertexView(System::Windows::Forms::Form^ inParent):basicView(inParent), vertexType(0), isMarked(false)
	{
		this->Size = System::Drawing::Size(25,25);
		this->MinSize = System::Drawing::Size(20,20);
		this->MaxSize = System::Drawing::Size(100,100);
		this->Text = L"";
		this->Kommentar = L"";
	}

	void vertexView::paintVertex(System::Windows::Forms::PaintEventArgs^ e)
	{
		//graphic
		System::Drawing::Graphics^ g = e->Graphics;
		//stringFormat
		System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
		sf->Alignment = System::Drawing::StringAlignment::Center;
		sf->LineAlignment = System::Drawing::StringAlignment::Center;

		if (this->vertexType == 0)//round
		{
			g->FillEllipse(this->m_drawTools->m_vertexFill, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::EllipsisCharacter;
		}else{//square
			g->FillRectangle(this->m_drawTools->m_vertexFill, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::Character;
		}
		if (this->isMarked)
		{
			if (this->vertexType == 0)
			{
				g->DrawEllipse(this->m_drawTools->m_vertexMarked, this->GetBorderRectangle);
			} 
			else
			{
				g->DrawRectangle(this->m_drawTools->m_vertexMarked, this->GetBorderRectangle);
			}
		}

		g->DrawString( this->Text, this->m_drawTools->m_drawFont, System::Drawing::Brushes::AntiqueWhite, this->GetBorderRectangle, sf);
	}

	bool vertexView::markVertex( void )
	{
		this->isMarked = !this->isMarked;
		return (this->isMarked);
	}

	void vertexView::startConfigDialog( void )
	{
		//vertexChangeDialog Instanz als Modaler Dialog starten
		VertexChangeDialog^ configDialog = gcnew VertexChangeDialog();
		this->InitializeValues(configDialog);
		if ( configDialog->ShowDialog( this->Parent ) == System::Windows::Forms::DialogResult::OK )
		{
			//TODO Daten ändern
			if (this->vertexType != configDialog->Knotenart)
			{
				this->kindOf = configDialog->Knotenart;
			}
			this->Text = configDialog->Knotenbeschriftung;
			//TODO Größenanpassung max. bis MaxSize min bis MinSize
			if (configDialog->DoAdjustSize){
				System::Drawing::Graphics^ g = this->Parent->CreateGraphics();
				System::Drawing::SizeF sizeOfTextF = g->MeasureString(this->Text, this->m_drawTools->m_drawFont);
				System::Drawing::Size sizeOfText = sizeOfTextF.ToSize();
				this->Width = sizeOfText.Width;
				this->Height = sizeOfText.Width;//soll Gleichmässig werden
			}
			//TODO Kommentartext
			this->Kommentar = configDialog->Kommentar;
			//toggle redraw um Änderungen anzuzeigen
			this->refreshParent();
		}

		delete configDialog;
	}

	void vertexView::InitializeValues(System::Windows::Forms::Form^ configDialog)
	{
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		dialog->Knotenbeschriftung = this->Text;
		dialog->Kommentar = this->Kommentar;
		dialog->Knotenart = this->vertexType;
	}

	void vertexView::refreshParent( void )
	{
		dynamic_cast<GAPConnect::Form1^ >(this->Parent)->Refresh();
	}


}//namespace end
