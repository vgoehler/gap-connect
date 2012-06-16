#pragma once
#include "knoten.h"
ref class KnotenEckig :
public Knoten
{
public:
	double height;
	double width;
public:
	KnotenEckig(void);
	KnotenEckig(Graph^ graph_init,System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init);
	~KnotenEckig(void);

};

