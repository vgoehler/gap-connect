#pragma once
using namespace System;
[ Serializable ]
public ref class Kommentar
{
private:
	System::String^ label;
public:
	int x;
	int y;
	int height;
	int width;
public:
	Kommentar(System::String^ string_label,int coord_x,int coord_y);
	~Kommentar(void);
	void set_label(System::String^ string_label);	

};

