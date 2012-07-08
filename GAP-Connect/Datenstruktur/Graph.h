#pragma once
#include "KnotenEckig.h"
#include "KnotenRund.h"
#include "Kante.h"
using namespace System;
ref class Dijkstra;
[Serializable]
public ref class Graph
{
public:
	System::Collections::Generic::List<Kante^> ^edges;
	System::Collections::Generic::List<Knoten^> ^verticles;
protected:
	System::String^ label;
public:
	Graph(void);
	Graph(System::String^ string_label);
	property System::String^ name{
		void set(System::String^ string_label){
			label=string_label;
		}
		System::String^ get(void){
			return label;
		}
	}
	~Graph(void);
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init);				//Kante: knoten_begin,knoten_end,gerichtet(-1,0,1,2),shape(NORMAL,STREIFEN,PUNKTE,WELLE)
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init);										//"gerichtet" und/oder "shape" kann weggelassen werden.Dann: gerichtet=0,shape=NORMAL
	Kante^ create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending);														
	Knoten^ create_vertex(System::String^ string_label,System::String^ string_tooltip,double radius_init);					//KnotenRund: label,tooltip,radius
	Knoten^ create_vertex(System::String^ string_label,double radius_init);													//KnotenEckig: label,tooltip,height,width (tooltip kann jeweils weggelassen werden)
	Knoten^ create_vertex(System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init);
	Knoten^ create_vertex(System::String^ string_label,double height_init,double width_init);								

	void deleted_edge(Kante^ kante_del);
	void deleted_vertex(Knoten^ knoten_del);

	array<int,2>^ convert_graph_to_adjacency();	//zurückgegebenes array wieder löschen nach verwendung!
	void convert_adjacency_to_graph(array<int,2>^ array_adj);	//erstellt immer gerichteten Graphen
	void write_adjacency_to_file(System::String^ string_fileName,array<int,2>^ array_adj);
	array<int,2>^ read_file_to_adjacency(System::String^ string_fileName);
	bool save_graph(System::String ^string_fileName );
	static Graph^ load_graph(System::String ^string_fileName);
	static Dijkstra^ init_dijkstra(Knoten ^knoten_start);

	int optimize();

	
};

