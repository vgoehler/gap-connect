#pragma once
#include "Graph.h"
public ref class Dijkstra
{
public:
	System::Collections::Generic::List<Knoten^> ^verticles_target;
	System::Collections::Generic::List<Knoten^> ^verticles_predecessor;
	System::Collections::Generic::List<Kante^> ^edges;
	System::Collections::Generic::List<int> ^int_finished;
	System::Collections::Generic::List<int> ^int_distance;
	System::Collections::Generic::List<int> ^int_outdated;
/************************************************************************
	Die drei array verticles_target,verticles_predecessor und int_distance
	sind gemeinsam auszulesen. Wenn man am index i in verticles_target[i]
	schaut, findet man einen endknoten, bei int_distance[i] den entsprechenden
	gesamt-weg bis dahin und bei verticles_predecessor[i] den vorgänger.
!!	bei einem Mehrfachauftreten eines Knotens innerhalb des verticles_target-
	arrays gilt nur der zuletzt eingetragene mitsamt seinen entsprechenden daten.
	Man sollte die arrays also von hinten nach vorn lesen und bei wiederholtem 
	auftreten eines knotens den 2. und folgende ignorieren.

	Nach vollständig ausgeführtem Algorithmus(!) kann auch cut_outdated verwendet
	werden, um Mehrfachauftreten von knoten zu verhindern. Ein anwenden der
	cut_outdated Methode zwischen schritten des algorithmus ist zwar möglich,
	verfälscht aber im Moment noch oftmals die folgenden Schritte.
*************************************************************************/

	Dijkstra(Knoten ^knoten_start);
	~Dijkstra(); //!!!!!!
	int find_IndexOf(Knoten ^knoten_search);	//durchsuchen des arrays von hinten nach vorn
	Knoten^ next_step();  //giebt zuletzt verwendeten Knoten wieder, wenn weitere schritte möglich; giebt nllptr wieder, wenn algorithmus komplett.
	void cut_outdated (); //nur verwendbar, nachdem der algorithmus vollständig angewandt wurde; entfernt überflüssige doppelwege

};

