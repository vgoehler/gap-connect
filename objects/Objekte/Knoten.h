#pragma once
#include <string>
#include "Kommentar.h"
#include "Kante.h"

using namespace System::Collections::Generic;
ref class Knoten
{
public:
	int coord_x;
	int coord_y;
		Kommentar^ comment;//protected !?
		System::Collections::Generic::List<Kante^> ^edges;//protected !?
protected:
	System::String^ label;
	System::String^ tooltip;


public:
	//Knoten(void);   //abstrakte klasse
	~Knoten(void);
	/*set_label/set_tooltip möglicherweise in 1 methode umschreiben, die eine verkürzte version von "tooltip" in "label" schreibt
	 *dann aber auch Anderung der höhe-breite veränderbarkeit [siehe KnotenEckig/KnotenRund]:
	 *-Setze hoehe/breite auf private und erstelle methode, die bei änderung der selben auch das label verkürtzt
	 */
	void set_tooltip(System::String^ string_tooltip);
	void set_label(System::String^ string_label);
	void set_comment(Kommentar^ handle_comment);
	void add_edge(Kante^ handle_edge);
	void delete_edge(Kante^ handle_edge);
	
};

