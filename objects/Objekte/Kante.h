#pragma once
#include "Kommentar.h"
enum KantenFormat{NORMAL,STREIFEN,PUNKTE,WELLE}; //und sonstige ideen - je nach implementierung...

ref class Knoten;
ref class Graph;	/*reine Deklaration von "Knoten" und "Graph" zur verwendung der Knoten-Handle unter
					 *vermeidung von kreuzenden Einbindungen der Header (Knoten.h und Kante.h)
					 */

ref class Kante
{
public:
	int wertung;
	int gerichtet;	/*-1: gerichtet mit Startpunkt 'knoten_end'
					 * 0: ungerichtet
					 * 1: gerichtet mit Startpunkt 'knoten_start'
					 *(2: gerichtet beidseitig??)
					 */
	KantenFormat shape;	//methode f�r redraw bei �nderung?
	Kommentar^ comment;
private:
	Knoten^ knoten_start;
	Knoten^ knoten_end;
	Graph^ owning_graph;			/*achtung! h�lt "Graph" am leben, auch wenn dieser deleted wird, sofern nicht auch alle zugeh�rigen 
								 *kanten freigegeben werden! */

public:
	//m�glicherweise einfachere �berladungsmethode bekannt?
	Kante(Graph^ graph_init,Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init);
	~Kante();
	//change_knoten_start/change_knoten_end n�tig?


};

