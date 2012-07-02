#include "StdAfx.h"
#include "drawTools.h"

namespace GAPConnect {
drawTools::drawTools(void)
{
	this->m_edge = gcnew System::Drawing::Pen(System::Drawing::Color::Maroon, 2);
	this->m_vertexMarked = gcnew System::Drawing::Pen(System::Drawing::Color::Gold, 3);
	this->m_drawFont = gcnew System::Drawing::Font( "Arial",8 );
	this->m_vertexFill = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
}
}//namespace