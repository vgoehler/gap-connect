#include "StdAfx.h"
#include "KnotenEckig.h"


KnotenEckig::KnotenEckig(void)
{
	height=10;
	width=15;
	edges=gcnew List<Kante^>();
}

KnotenEckig::KnotenEckig(Graph^ graph_init,System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init)
{	
	label=string_label;
	tooltip=string_tooltip;
	height=height_init;
	width=width_init;
	edges=gcnew List<Kante^>();
	owning_graph=graph_init;
}

KnotenEckig::~KnotenEckig(void)
{
}


