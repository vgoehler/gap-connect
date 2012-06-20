#include "StdAfx.h"
#include "Graph.h"


Graph::Graph(void)
{
	label="noname";
	edges=gcnew List<Kante^>();
	verticles=gcnew List<Knoten^>();
}

Graph::~Graph(void)
{
	if (label)
	{	delete[] label;
		label=nullptr;		
	}			/*als Zeichen der begonnenen destruktion, nötig wegen problemen
				 *innerhalb folgender "for each" schleife; verwendet in delete_edge()
				 *sowie delete_vertex*/
	if (edges)								//zur Sicherheit (falls array nicht initialisiert)
	{	if (edges->Count > 0)				//falls array leer
			for each(Kante^ ka in edges )
			{
				delete ka;
			}
		edges->Clear();
	}
	if (verticles)							//zur Sicherheit (falls array nicht initialisiert)
	{	if (verticles->Count > 0)				//falls array leer
			for each(Knoten^ kn in verticles )
			{
				delete kn;
			}
		verticles->Clear();
	}
}


Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init )
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,gerichtet_init,shape_init);
	edges->Add(edge_new);
	return edge_new;
}
Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init )
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,gerichtet_init,NORMAL);
	edges->Add(edge_new);
	return edge_new;
}
Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending)
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,0,NORMAL);
	edges->Add(edge_new);
	return edge_new;
}


Knoten^ Graph::create_vertex( System::String^ string_label,System::String^ string_tooltip,double radius_init)
{
	KnotenRund^ vertex_new = gcnew KnotenRund(this,string_label,string_tooltip,radius_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,double radius_init )
{
	KnotenRund^ vertex_new = gcnew KnotenRund(this,string_label,nullptr,radius_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init )
{
	KnotenEckig^ vertex_new = gcnew KnotenEckig(this,string_label,string_tooltip,height_init,width_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,double height_init,double width_init )
{
	KnotenEckig^ vertex_new = gcnew KnotenEckig(this,string_label,nullptr,height_init,width_init);
	verticles->Add(vertex_new);
	return vertex_new;
}


void Graph::deleted_edge( Kante^ kante_del )
{
	if (label)
	{
		if (edges)
			edges->Remove(kante_del);
	}
}

void Graph::deleted_vertex( Knoten^ knoten_del )
{
	if (label)
	{
		if (verticles)
			verticles->Remove(knoten_del);
	}
}

array<int,2>^ Graph::convert_to_adjacency()
{
	edges->TrimExcess();
	verticles->TrimExcess();
	int c_verticles=verticles->Count;
	//Adjazenzmatrix der größe NxN; N=anzahl Knoten.
	array<int,2>^ array_adj = gcnew array<int,2>(c_verticles,c_verticles);
	//initialisieren:
	for (int i=0;i < c_verticles;i++)
	{
		for (int j=0;j < c_verticles;j++)
		{
			array_adj[i,j]=0;
		}
	}
	int v1=0,v2=0; //vertex-index
	for each(Kante^ ka in edges)
	{
		v1 = verticles->IndexOf(ka->get_knoten_start());
		v2 = verticles->IndexOf(ka->get_knoten_end());
		array_adj[v1,v2]=1;			//hinrichtung immer
		if (ka->gerichtet == 0 || ka->gerichtet==2)
			array_adj[v2,v1]=1;		//rückrichtung nur bei ungerichteter kante
	}
	
	return array_adj;
}

bool Graph::convert_from_adjacency()
{
	//return 0 wenn ...ähm...?
	return 0;
}
