#include "StdAfx.h"
#include "drawTools.h"

namespace GAPConnect {
drawTools::drawTools(void)
{
	this->m_edge = gcnew System::Drawing::Pen(System::Drawing::Color::Maroon, 2);
	this->m_edgeMarked = gcnew System::Drawing::Pen(System::Drawing::Color::SpringGreen, 4);
	this->m_edgeDeactivated = gcnew System::Drawing::Pen(System::Drawing::Color::LightGray, 1);
	this->m_edgeHilfslinie = gcnew System::Drawing::Pen(System::Drawing::Brushes::Orange, 1);
	this->m_vertexMarked = gcnew System::Drawing::Pen(System::Drawing::Color::Gold, 3);
	this->m_drawFont = gcnew System::Drawing::Font( "Arial",8 );
	this->m_vertexFill = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
	this->m_vertexDeactivated = gcnew System::Drawing::SolidBrush(System::Drawing::Color::LightGray);
}
}//namespace