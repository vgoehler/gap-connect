#include "StdAfx.h"
#include "basicView.h"


namespace GAPConnect {
basicView::basicView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools):Parent(inParent), m_drawTools(inDrawTools), m_marked(false), m_enable(true)
{
		this->Size = System::Drawing::Size(25,25);
		this->m_minsize = System::Drawing::Size(0,0);
		this->m_maxsize = System::Drawing::Size(0,0);
}

basicView::basicView( void ):Parent(nullptr), m_drawTools(nullptr), m_marked(false), m_enable(true)
{

}

basicView::~basicView()
{

}

void basicView::recalcRectangle( void )
{
	this->drawRectangle = System::Drawing::Rectangle(m_location, m_size);
}

bool basicView::Mark( void )
{
	this->IsMarked = !this->IsMarked;
	return (this->IsMarked);
}

bool basicView::Enable( void )
{
	this->IsEnabled = !this->IsEnabled;
	return (this->IsEnabled);
}

void basicView::refreshParent( void )
{
	dynamic_cast<GAPConnect::Form1^ >(this->Parent)->Refresh();
}

bool basicView::Contains( System::Drawing::Point& pkt )
{
	return(this->GetBorderRectangle.Contains(pkt));
}

}//namespace