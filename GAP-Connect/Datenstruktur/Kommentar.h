#pragma once
using namespace System;
[ Serializable ]
public ref class Kommentar
{
private:
	System::String^ string_label;
public:
	Kommentar(System::String^ string_label,int coord_x,int coord_y);
	~Kommentar(void);
	property System::String^ label{
		void set(System::String^ l){
			delete[] string_label;
			string_label=l;
		}
		System::String^ get(void){
			return string_label;
		}
	}
};

