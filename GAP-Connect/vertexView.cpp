#include "StdAfx.h"
#include "vertexView.h"


namespace GAPConnect {
	vertexView::vertexView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, Graph^ parentDataGraph):basicView(inParent, inDrawTools, parentDataGraph), m_vertexType(0), m_dataVertex(nullptr)
	{
		this->IsEnabled = true;//Zuweisen um Zeichenfarbe zu initialisieren
		this->Size = System::Drawing::Size(25,25);
		this->MinSize = System::Drawing::Size(20,20);
		this->MaxSize = System::Drawing::Size(100,100);

		//Datenrepräsentation verknüpfen
		if(this->m_vertexType == 0){
			this->m_dataVertex = this->m_dataGraph->create_vertex(L"", double(this->Height)/2);
		}else{
			this->m_dataVertex = this->m_dataGraph->create_vertex(L"", double(this->Height), double(this->Width));
		}

		this->Text = L"";
		this->Kommentar = L"";
	}

	vertexView::vertexView( System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, Graph^ parentDataGraph, Knoten^ inKnoten ):basicView(inParent, inDrawTools, parentDataGraph), m_dataVertex(nullptr)
	{
		this->MinSize = System::Drawing::Size(20,20);
		this->MaxSize = System::Drawing::Size(100,100);

		this->m_dataVertex = inKnoten;

		KnotenEckig^ eckig = dynamic_cast<KnotenEckig^ >(this->m_dataVertex);
		if(eckig != nullptr){//eckig
			this->m_vertexType = 1;
			this->Size = System::Drawing::Size(Int32(eckig->width),Int32(eckig->height));
		}else{
			KnotenRund^ rund = dynamic_cast<KnotenRund^ >(this->m_dataVertex);
			if (rund != nullptr){//rund
				this->m_vertexType = 0;
				this->Size = System::Drawing::Size(Int32(rund->radius)*2,Int32(rund->radius)*2);
			}else{
				throw gcnew Exception("Kann Typ nicht casten. Im Konstruktor.");
			}
		}
		//Zuweisen TODO
		this->IsEnabled = this->DataVertex->enabled;
		this->Location = this->m_dataVertex->coords;
	}

	void vertexView::paintVertex(System::Windows::Forms::PaintEventArgs^ e)
	{
		//graphic
		System::Drawing::Graphics^ g = e->Graphics;
		//stringFormat
		System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
		sf->Alignment = System::Drawing::StringAlignment::Center;
		sf->LineAlignment = System::Drawing::StringAlignment::Center;

		if (this->m_vertexType == 0)//round
		{
			g->FillEllipse(this->m_vertexSolidBrush, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::EllipsisCharacter;
		}else{//square
			g->FillRectangle(this->m_vertexSolidBrush, this->GetBorderRectangle);
			sf->Trimming = System::Drawing::StringTrimming::Character;
		}
		if (this->IsMarked)
		{
			if (this->m_vertexType == 0)
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

	void vertexView::startConfigDialog( bool refreshAfterDialog )
	{
		//vertexChangeDialog Instanz als Modaler Dialog starten
		VertexChangeDialog^ configDialog = gcnew VertexChangeDialog();
		//Dialog initialisieren
		this->InitializeDialogValues(configDialog);
		if ( configDialog->ShowDialog( this->Parent ) == System::Windows::Forms::DialogResult::OK )
		{
			//Werte setzen
			this->SetDialogValues(configDialog);
			//toggle redraw um Änderungen anzuzeigen
			if (refreshAfterDialog)
			{
				this->refreshParent();
			}
		}
		delete configDialog;
	}

	void vertexView::InitializeDialogValues(System::Windows::Forms::Form^ configDialog)
	{
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		dialog->Knotenbeschriftung = this->Text;
		dialog->Kommentar = this->Kommentar;
		dialog->Knotenart = this->m_vertexType;
		dialog->VertexEnabled = this->IsEnabled;
		dialog->InitializeSizeControl(this->MinSize.Width, this->MaxSize.Width, this->Width);
	}
	void vertexView::SetDialogValues(System::Windows::Forms::Form^ configDialog){
		GAPConnect::VertexChangeDialog^ dialog = dynamic_cast<GAPConnect::VertexChangeDialog^ >(configDialog);
		//Art des Knoten
		this->TypeofVertex = dialog->Knotenart;
		//Knotentext
		this->Text = dialog->Knotenbeschriftung;
		//Kommentartext
		this->Kommentar = dialog->Kommentar;
		//Enablement
		this->IsEnabled = dialog->VertexEnabled;
		//Größenanpassung max. bis MaxSize min bis MinSize
		if (dialog->DoAdjustSize){
			this->ScaleVertex();
		}else{
			this->Size = dialog->VertexSize;
		}
	}
	void vertexView::ScaleVertex(void){
		System::Drawing::Graphics^ g = this->Parent->CreateGraphics();
		System::Drawing::SizeF sizeOfTextF = g->MeasureString(this->Text, this->m_drawTools->m_drawFont);
		System::Drawing::Size sizeOfText = sizeOfTextF.ToSize();
		this->Width = sizeOfText.Width;
		this->Height = sizeOfText.Width;//soll Gleichmässig werden
	}

	System::Drawing::Point vertexView::getDockPoint( double angle )
	{
		double xdiff, ydiff;
		if (this->m_vertexType== 0){//Rund
			double hypothenuse = double(this->Height) / 2;
			xdiff = cos(angle) * hypothenuse;
			ydiff = sin(angle) * hypothenuse;
		}else{//squared
			if (abs(angle) >= PI/4 && abs(angle) < 3*PI/4){//y konst bei pi/4 bis 3pi/4 und korrespondierende im negativen! (oberer Halbkreis ist 0 bis pi und unterer halbkreis bis -pi)
				ydiff = angle > 0 ? double(this->Height) /2 : double(this->Height) /2 * -1; //entweder obere Kante oder untere
				xdiff = ydiff / tan( angle );//tan beta = ydiff / xdiff
			}else if (abs(angle) < PI/4 || abs(angle)>= 3*PI/4){//x konst
				if ( abs(angle) < PI/4){//vorne
					xdiff = double(this->Width) /2 ;
				} 
				else{//hinten
					xdiff = double(this->Width) /2 * -1;
				}
				ydiff = tan(angle)*xdiff;
			}else{
				throw 666;
			}
		}
		if (xdiff < 0 && ydiff < 0)// in Sektor 4 muss aufgerundet werden um bei ungeraden durchmessern nicht in den Knoten zu zeichnen
		{
			return(Point(this->LocationCenter.X - int(ceil(xdiff)), this->LocationCenter.Y - int(ceil(ydiff))));
		}else{
			return(Point(this->LocationCenter.X - int(xdiff), this->LocationCenter.Y - int(ydiff)));
		}
		return(Point::Empty);
	}

	vertexView::~vertexView()
	{
		delete this->m_dataVertex;
		this->m_dataVertex = nullptr;
	}

	void vertexView::updateDataVertex( void )
	{
		if (this->m_dataVertex != nullptr)//Absichern gegen Konstruktor aufrufung
		{
			KnotenEckig^ eckig = dynamic_cast<KnotenEckig^ >(this->m_dataVertex);
			if (eckig != nullptr){
				eckig->height = double(this->Height);
				eckig->width = double(this->Width);
			}else{
				KnotenRund^ rund = dynamic_cast<KnotenRund^ >(this->m_dataVertex);
				if (rund != nullptr){
					rund->radius = double(this->Height)/2;
				}else{
					throw gcnew Exception("Cast Fehler in DataVertex. Typ Unbekannt.");
				}
			}
		}
	}



}//namespace end
