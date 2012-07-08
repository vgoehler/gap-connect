#pragma once
#include <string>
#include "Kommentar.h"
#include "Kante.h"
using namespace System;
[Serializable]
ref class Graph;

using namespace System::Collections::Generic;
[Serializable]
public ref class Knoten
{
public:
	System::Drawing::Point coords;
	Kommentar^ comment;
	System::Collections::Generic::List<Kante^> ^edges;
	System::String^ label;
	System::String^ tooltip;
protected:
	Graph^ owning_graph;			/*achtung! hält "Graph" am leben, auch wenn dieser deleted wird, sofern nicht auch alle zugehörigen 
									 *Knoten freigegeben werden! */

public:
	//Knoten(void);   //abstrakte klasse
	~Knoten(void);
	/*set_label/set_tooltip möglicherweise in 1 methode umschreiben, die eine verkürzte version von "tooltip" in "label" schreibt
	 *dann aber auch Anderung der höhe-breite veränderbarkeit [siehe KnotenEckig/KnotenRund]:
	 *-Setze hoehe/breite auf private und erstelle methode, die bei änderung der selben auch das label verkürtzt
	 */
	void set_tooltip(System::String^ string_tooltip);
	void set_label(System::String^ string_label);
//	void add_comment(Kommentar^ comment_init);  //im moment nicht nötig
	void add_edge(Kante^ handle_edge);
	bool deleted_edge(Kante^ handle_edge); //wird nur von Kante aufgerufen - manueller Aufruf nicht empfohlen
	
};

