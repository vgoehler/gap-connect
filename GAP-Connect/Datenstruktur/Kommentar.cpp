#pragma once
#include "StdAfx.h"
#include "Kommentar.h"


Kommentar::Kommentar(System::String^ string_label,int coord_x,int coord_y)
{
	label=string_label;
}

Kommentar::~Kommentar(void)
{	
	if(label)
		delete[] label;
}
