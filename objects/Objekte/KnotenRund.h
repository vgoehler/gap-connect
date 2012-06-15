#pragma once
#include "knoten.h"
ref class KnotenRund :
public Knoten
{
public:
	double radius;
public:
	KnotenRund(void);
	KnotenRund(System::String^ string_label);
	~KnotenRund(void);
};

