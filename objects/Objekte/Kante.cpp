#pragma once
#include "StdAfx.h"
#include "Kante.h"
#include "Knoten.h"
#include "Graph.h"


Kante::Kante( Graph^ graph_init,Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init )
{
	knoten_start=knoten_begin;	
	knoten_start->add_edge(this);
	knoten_end=knoten_ending;
	knoten_end->add_edge(this);
	gerichtet=gerichtet_init;
	shape=shape_init;
	wertung=0;
	owning_graph=graph_init;
}

Kante::~Kante()
{
	delete comment;
	knoten_start->deleted_edge(this);
	if (knoten_start != knoten_end)		//falls Kante=Schleife
	{	
		knoten_end->deleted_edge(this);
	}

	if (owning_graph)
		owning_graph->deleted_edge(this);
}
