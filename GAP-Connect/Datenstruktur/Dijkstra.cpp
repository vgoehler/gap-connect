#include "StdAfx.h"
#include "Dijkstra.h"


Dijkstra::Dijkstra(Knoten ^knoten_start)
{
	verticles_target=gcnew List<Knoten^>();
	verticles_predecessor=gcnew List<Knoten^>();
	edges=gcnew List<Kante^>();
	int_distance=gcnew List<int>();
	int_finished=gcnew List<int>();
	int_outdated=gcnew List<int>();
	verticles_target->Add(knoten_start);
	verticles_predecessor->Add(knoten_start);
	int_distance->Add(0);
}

Dijkstra::~Dijkstra()
{
	delete int_finished;
	delete int_distance;
	delete int_outdated;
	delete verticles_predecessor;
	delete verticles_target;
	delete edges;
	int_finished=nullptr;
	int_distance=nullptr;
	int_outdated=nullptr;
	verticles_predecessor=nullptr;
	verticles_target=nullptr;
	edges=nullptr;
}

int Dijkstra::find_IndexOf( Knoten ^knoten_search )
{
	if(verticles_target->Count>0)
		for (int i=(verticles_target->Count)-1;i >=0 ;i--)
			if (knoten_search==verticles_target[i])
			{	
				return i;
			}
	return -1;
}

Knoten^ Dijkstra::next_step()
{
	//suche nach kleinstem bereits aufgenommenen weg
	int for_max=int_distance->Count;
	int int_distance_min=2147483647; //max
	int i_current_position=-1;
	for (int i=0;i<for_max;i++)
	{
		if (!(int_finished->Contains(i)) && int_distance_min>int_distance[i])
		{	//wenn knoten noch nicht bearbeitet und distanz kleiner als bis jetzt aufgenommen
			int_distance_min=int_distance[i];
			i_current_position=i;
		}
	}
	// i_of_distance ist jetzt stelle im array mit geringster distanz
	if (i_current_position==-1)
		return nullptr;
		
	
	Knoten ^knoten_current=verticles_target[i_current_position];
	//
	for_max=(knoten_current->edges)->Count;
	for(int i=0;i<for_max;i++)
	{
		int wertung_current=0;
		Knoten^ knoten_target=(knoten_current->edges[i]->find_other_vertex(knoten_current));
		if(knoten_target!=knoten_current && knoten_target != verticles_predecessor[i_current_position])
		//darf keine schleife sein und nicht dem weg zurück zum vorgänger entsprechen
		{
			//wenn Wertung der aktuell bearbeiteten Kante <0, dann wird sie als 0 angesehn.
			//sowie durch wertung-Property bedingt: wenn Wertung nicht in zahl umwandelbar ebenfalls Wertung=0.
			if((knoten_current->edges[i]->wertung)>=0)
				wertung_current=knoten_current->edges[i]->wertung;
			if (verticles_target->Contains(knoten_target))
			{
				int index_target=find_IndexOf(knoten_target);
				if (index_target==-1)
					return nullptr;
				if ((int_distance[i_current_position]+wertung_current) < int_distance[index_target])
				//wenn Weg(momentaner knoten + neue kante) < alter Weg zu neuem knoten
				{	
					int_finished->Add(index_target);//makre alten weg als bereits abgearbeitet, damit später kein leerlauf entsteht
					int_outdated->Add(index_target);//marke alten weg als outdated 
					verticles_target->Add(knoten_target);
					verticles_predecessor->Add(knoten_current);
					edges->Add(knoten_current->edges[i]);
					int_distance->Add((int_distance[i_current_position]+wertung_current));
				}
				//ansonsten wird nichts getan
			}
			else
			{
				verticles_target->Add(knoten_target);
				verticles_predecessor->Add(knoten_current);
				edges->Add(knoten_current->edges[i]);
				int_distance->Add((int_distance[i_current_position]+wertung_current));
			}
		}	
	}//*end for* (alle kanten des knotens abgearbeitet)
	int_finished->Add(i_current_position);
	//return nullptr wenn alle knoten bearbeitet
	if (int_finished->Count >= verticles_target->Count)
		return nullptr;
	else
		return knoten_current;
}

void Dijkstra::cut_outdated()
{
	int_outdated->Sort();
	if(int_outdated->Count>0)
		for(int i=(int_outdated->Count)-1; i>=0;i--)
		{
			verticles_target->RemoveAt(int_outdated[i]);
			verticles_predecessor->RemoveAt(int_outdated[i]);
			edges->RemoveAt(int_outdated[i]);
			int_distance->RemoveAt(int_outdated[i]);
			int_outdated->RemoveAt(i);
		}
}
