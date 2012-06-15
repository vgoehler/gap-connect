#pragma once
#include "knoten.h"
ref class KnotenRund :
public Knoten
{
	int radius;
public:
	KnotenRund(void);
	KnotenRund(System::String^ string_label);
	~KnotenRund(void);
};

