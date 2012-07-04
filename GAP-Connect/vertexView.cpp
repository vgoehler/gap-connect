#include "StdAfx.h"
#include "vertexView.h"


namespace GAPConnect {
	vertexView::vertexView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools):basicView(inParent, inDrawTools), vertexType(0)
	{
		this->IsEnabled = true;//Zuweisen um Zeichenfarbe zu initialisieren
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
			g->FillEllipse(this->m_vertexSolidBrush, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::EllipsisCharacter;
		}else{//square
			g->FillRectangle(this->m_vertexSolidBrush, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::Character;
		}
		if (this->IsMarked)
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

	void vertexView::startConfigDialog( void )
	{
		//vertexChangeDialog Instanz als Modaler Dialog starten
		VertexChangeDialog^ configDialog = gcnew VertexChangeDialog();
		//Dialog initialisieren
		this->InitializeValues(configDialog);
		System::Windows::Forms::DialogResult action = configDialog->ShowDialog( this->Parent );
		if ( action == System::Windows::Forms::DialogResult::OK )
		{
			//Werte setzen
			this->SetValues(configDialog);
			//Größenanpassung max. bis MaxSize min bis MinSize
			if (configDialog->DoAdjustSize){
				this->ScaleVertex();
			}
			//toggle redraw um Änderungen anzuzeigen
			this->refreshParent();
		}else if (action == System::Windows::Forms::DialogResult::Yes)//Löschen
		{
			this->Text = L"Löschen";
		}
		delete configDialog;
	}

	void vertexView::InitializeValues(System::Windows::Forms::Form^ configDialog)
	{
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		dialog->Knotenbeschriftung = this->Text;
		dialog->Kommentar = this->Kommentar;
		dialog->Knotenart = this->vertexType;
		dialog->VertexEnabled = this->IsEnabled;
	}
	void vertexView::SetValues(System::Windows::Forms::Form^ configDialog){
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		//Art des Knoten
		this->kindOf = dialog->Knotenart;
		//Knotentext
		this->Text = dialog->Knotenbeschriftung;
		//Kommentartext
		this->Kommentar = dialog->Kommentar;
		//Enablement
		this->IsEnabled = dialog->VertexEnabled;
	}
	void vertexView::ScaleVertex(void){
		System::Drawing::Graphics^ g = this->Parent->CreateGraphics();
		System::Drawing::SizeF sizeOfTextF = g->MeasureString(this->Text, this->m_drawTools->m_drawFont);
		System::Drawing::Size sizeOfText = sizeOfTextF.ToSize();
		this->Width = sizeOfText.Width;
		this->Height = sizeOfText.Width;//soll Gleichmässig werden
	}



}//namespace end
