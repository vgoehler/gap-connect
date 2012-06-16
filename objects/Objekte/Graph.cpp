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
