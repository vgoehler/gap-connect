#include "StdAfx.h"
#include "KnotenEckig.h"


KnotenEckig::KnotenEckig(void)
{
	height=10;
	width=15;
	coord_x=0;
	coord_y=0;
	edges=gcnew List<Kante^>(0);
}

KnotenEckig::KnotenEckig(System::String^ string_label)
{	
	label=string_label;
	height=10;
	width=15;
	coord_x=0;
	coord_y=0;
	edges=gcnew List<Kante^>(0);
}

KnotenEckig::~KnotenEckig(void)
{
}


