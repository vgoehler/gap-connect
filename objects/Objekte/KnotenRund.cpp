#include "StdAfx.h"
#include "KnotenRund.h"


KnotenRund::KnotenRund(void)
{
}

KnotenRund::KnotenRund(System::String^ string_label)
{	label=string_label;
	radius=10;
	coord_x=0;
	coord_y=0;
}

KnotenRund::~KnotenRund(void)
{
}
