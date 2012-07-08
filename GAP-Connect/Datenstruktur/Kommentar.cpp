#pragma once
#include "StdAfx.h"
#include "Kommentar.h"


Kommentar::Kommentar(System::String^ str_label,int coord_x,int coord_y)
{
	string_label=str_label;
}

Kommentar::Kommentar( void )
{
	string_label="";
}

Kommentar::~Kommentar(void)
{	
	if(label)
		delete[] label;
}
