#include "StdAfx.h"
#include "KnotenRund.h"


KnotenRund::KnotenRund(void)
{
	radius=10;
	edges=gcnew List<Kante^>();
}

KnotenRund::KnotenRund(Graph^ graph_init,System::String^ string_label,System::String^ string_tooltip,double radius_init)
{	
	label=string_label;
	tooltip=string_tooltip;
	radius=radius_init;
	edges=gcnew List<Kante^>();
	owning_graph=graph_init;
}

KnotenRund::~KnotenRund(void)
{
}
