#pragma once
#include "StdAfx.h"
#include "Knoten.h"


Knoten::Knoten(void)
{	label = "";
	coord_x=0;
	coord_y=0;

}

Knoten::~Knoten(void)
{	
	if (label)
		delete[] label;
	if (tooltip)
		delete[] tooltip;
	if (com)
		com->~Kommentar();

}

void Knoten::set_tooltip(System::String^ string_tooltip)
{
	tooltip=string_tooltip;
}
