#pragma once
#include "StdAfx.h"
#include "Knoten.h"


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
		delete[] label;
	if (tooltip)
		delete[] tooltip;
	if (comment)
		comment->~Kommentar();
	//löschen aller anliegenden Kanten:
	if (edges)								//zur Sicherheit (falls array nicht initialisiert)
		if (edges->Count > 0)				//falls array leer
		{	for(int i=edges->Count;i>=0;--i)
				if (edges[i])				//falls kante bereits gelöscht
					edges[i]->~Kante();		//Rückgabe an Graphen wie gestalten?
		}
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

void Knoten::set_comment( Kommentar^ handle_comment )
{
	if (comment)
		comment->~Kommentar();
	comment= handle_comment;
}

void Knoten::add_edge(Kante^ handle_edge)
{
	edges->Add(handle_edge);
}

void Knoten::delete_edge( Kante^ handle_edge )
{
	//todo ?
}
