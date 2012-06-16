#pragma once
#include "StdAfx.h"
#include "Kommentar.h"


Kommentar::Kommentar(System::String^ string_label,int coord_x,int coord_y)
{
	label=string_label;
	x=coord_x;
	y=coord_y;
	height=10;
	width=10;
}

Kommentar::~Kommentar(void)
{	
	if(label)
		delete[] label;
}

void Kommentar::set_label( System::String^ string_label )
{
	delete[] label;
	label=string_label;
}

