#include "StdAfx.h"
#include "KnotenRund.h"


KnotenRund::KnotenRund(void)
{
	radius=10;
	edges=gcnew List<Kante^>();
	comment=gcnew Kommentar();
}

KnotenRund::KnotenRund(Graph^ graph_init,System::String^ string_label,System::String^ string_tooltip,double radius_init)
{	
	label=string_label;
	tooltip=string_tooltip;
	radius=radius_init;
	edges=gcnew List<Kante^>();
	comment=gcnew Kommentar();
	owning_graph=graph_init;
	enabled=true;
}

KnotenRund::~KnotenRund(void)
{
}
