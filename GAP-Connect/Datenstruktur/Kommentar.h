#pragma once
using namespace System;
[ Serializable ]
public ref class Kommentar
{
private:
	System::String^ string_label;
public:
	Kommentar(System::String^ string_label);
	Kommentar(void);
	~Kommentar(void);
	property System::String^ label{
		void set(System::String^ l){
			if(string_label)
				delete[] string_label;
			string_label=l;
		}
		System::String^ get(void){
			return string_label;
		}
	}
};

