#pragma once
#include "knoten.h"
ref class KnotenEckig :
public Knoten
{
	int height;
	int width;
public:
	KnotenEckig(void);
	KnotenEckig(System::String^ string_label);
	~KnotenEckig(void);
};

