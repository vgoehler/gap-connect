#pragma once
namespace GAPConnect {
public ref class drawTools
{
public:
	drawTools(void);
	System::Drawing::Pen^ m_edge;
	System::Drawing::Pen^ m_vertexMarked;
	System::Drawing::Font^ m_drawFont;
	System::Drawing::SolidBrush^ m_vertexFill;
};}//namespace