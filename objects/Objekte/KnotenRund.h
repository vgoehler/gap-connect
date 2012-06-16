#pragma once
#include "knoten.h"
ref class KnotenRund :
public Knoten
{
public:
	double radius;
public:
	KnotenRund(void);
	KnotenRund(Graph^ graph_init,System::String^ string_label,System::String^ string_tooltip,double radius_init);
	~KnotenRund(void);
};

