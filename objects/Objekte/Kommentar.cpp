#pragma once
#include "StdAfx.h"
#include "Kommentar.h"


Kommentar::Kommentar(System::String^ string_label,int coord_x,int coord_y)
{
	label=string_label;
	x=coord_x;
	y=coord_y;
	hoehe=10;
	breite=10;
}

Kommentar::~Kommentar(void)
{	if(label)
		delete[] label;
}

