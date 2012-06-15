#pragma once
#include <string>
#include "Kommentar.h"
ref class Knoten
{
public:
	int coord_x;
	int coord_y;
protected:
	System::String^ label;
	System::String^ tooltip;
	Kommentar^ com;
public:
	Knoten(void);
	~Knoten(void);
	void set_tooltip(System::String^ string_tooltip);

};

