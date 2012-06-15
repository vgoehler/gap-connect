#pragma once
ref class Kommentar
{
	System::String^ label;
	int x;
	int y;
	int hoehe;
	int breite;
public:
	Kommentar(System::String^ string_label,int coord_x,int coord_y);
	~Kommentar(void);
};

