#pragma once
#include "StdAfx.h"
#include "Knoten.h"
#include "Graph.h"


/*Knoten::Knoten(void)
{	
	label = "";
	coord_x=0;
	coord_y=0;
	edges=gcnew array<Kante^>(0);

}*/

Knoten::~Knoten(void)
{	
	if (label)
	{	delete[] label;
		label=nullptr;		/*als Zeichen der begonnenen destruktion, nötig wegen problemen
							 *innerhalb folgender "for each" schleife; verwendet in delete_edge()	*/
	}
	delete[] tooltip;
	delete comment;
	//**löschen aller anliegenden Kanten:**
	if (edges)								//zur Sicherheit (falls array nicht initialisiert)
		if (edges->Count > 0)				//falls array leer
			for each(Kante^ k in edges )
			{
				delete k;		//Rückgabe an Graphen wie gestalten?
			}
		/*{	for(int i=edges->Count;i>=0;--i)
				if (edges[i])				//falls aus irgendeinem Grund nullptr
					edges[i]->~Kante();		//Rückgabe an Graphen wie gestalten?
		}*/
	edges->Clear();

	if (owning_graph)		//teile erschaffer-graphen mit, dass dieser knoten gelöscht wurde
		owning_graph->deleted_vertex(this);
}

void Knoten::set_tooltip(System::String^ string_tooltip)
{
	if (tooltip)
		delete[] tooltip;
	tooltip=string_tooltip;
}

void Knoten::set_label( System::String^ string_label )
{
	if (label)
		delete[] label;
	label=string_label;
}

/*void Knoten::add_comment( Kommentar^ comment_init )	//siehe deklaration
{
	if (comment)
		delete comment;
	comment= gcnew comment_init;
}*/

void Knoten::add_edge(Kante^ handle_edge)
{
	edges->Add(handle_edge);
}

bool Knoten::deleted_edge( Kante^ handle_edge )
{
	if (label)
	{
		bool b_temp = edges->Remove(handle_edge);
		edges->TrimExcess();
		return b_temp;
	}else
		return 0;
}
