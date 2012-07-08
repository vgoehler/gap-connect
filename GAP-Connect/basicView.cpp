#include "StdAfx.h"
#include "basicView.h"


namespace GAPConnect {
basicView::basicView(System::Windows::Forms::Form^ inParent, GAPConnect::drawTools^ inDrawTools, Graph^ parentDataGraph):Parent(inParent), m_drawTools(inDrawTools), m_marked(false), m_enable(true), m_dataGraph(parentDataGraph)
{
		this->Size = System::Drawing::Size(25,25);
		this->m_minsize = System::Drawing::Size(4,4);//damit wir irgendwas klickbares haben
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
	//wenn breite oder höhe gleich der minsize sind, muss die location um minsize/2 versetzt werden
	Int32 x = this->m_location.X;
	Int32 y = this->m_location.Y;
	x -= (this->Width == this->m_minsize.Width) ? m_minsize.Width /2 : 0;
	y -= (this->Height == this->m_minsize.Height) ? m_minsize.Height /2 : 0;
	this->drawRectangle = System::Drawing::Rectangle(Point(x,y), m_size);
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
	dynamic_cast<GAPConnect::Form1^ >(this->Parent)->RefreshDrawBox();
}

bool basicView::Contains( System::Drawing::Point& pkt )
{
	return(this->GetBorderRectangle.Contains(pkt));
}

}//namespace