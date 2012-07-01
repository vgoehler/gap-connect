#include "StdAfx.h"
#include "basicView.h"


namespace GAPConnect {
basicView::basicView(System::Windows::Forms::Form^ inParent):Parent(inParent)
{
		this->Size = System::Drawing::Size(25,25);
		this->m_minsize = System::Drawing::Size(0,0);
		this->m_maxsize = System::Drawing::Size(0,0);
}

basicView::basicView( void )
{

}

basicView::~basicView()
{

}

void basicView::recalcRectangle( void )
{
	this->drawRectangle = System::Drawing::Rectangle(m_location, m_size);
}

}