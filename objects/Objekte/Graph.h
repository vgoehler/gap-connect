#pragma once
#include "KnotenEckig.h"
#include "KnotenRund.h"
#include "Kante.h"
ref class Graph
{
public:
	System::Collections::Generic::List<Kante^> ^edges;
	System::Collections::Generic::List<Knoten^> ^verticles;
protected:
	System::String^ label;
public:
	Graph(void);
	~Graph(void);
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init);				//Kante: knoten_begin,knoten_end,gerichtet(-1,0,1,2),shape(NORMAL,STREIFEN,PUNKTE,WELLE)
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init);										//"gerichtet" und/oder "shape" kann weggelassen werden.Dann: gerichtet=0,shape=NORMAL
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending);														
	Knoten^ create_vertex(System::String^ string_label,System::String^ string_tooltip,double radius_init);					//KnotenRund: label,tooltip,radius
	Knoten^ create_vertex(System::String^ string_label,double radius_init);													//KnotenEckig: label,tooltip,height,width (tooltip kann weggelassen werden)
	Knoten^ create_vertex(System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init);
	Knoten^ create_vertex(System::String^ string_label,double height_init,double width_init);								

	void deleted_edge(Kante^ kante_del);
	void deleted_vertex(Knoten^ knoten_del);

	//addcomment-system?

	
};

