#pragma once
#include "Kommentar.h"
enum KantenFormat{NORMAL,DISABLED,STREIFEN,PUNKTE,WELLE}; //und sonstige ideen - je nach implementierung...
using namespace System;

ref class Knoten;
ref class Graph;	/*reine Deklaration von "Knoten" und "Graph" zur verwendung der Knoten-Handle unter
					 *vermeidung von kreuzenden Einbindungen der Header (Knoten.h und Kante.h)
					 */
[Serializable]
public ref class Kante
{
public:
	System::String^ string_wertung;
	int gerichtet;	/*(-1: gerichtet mit Startpunkt 'knoten_end'?? wenn ja dann adjazenz-funktion prüfen)
					 * 0: ungerichtet
					 * 1: gerichtet mit Startpunkt 'knoten_start'
					 *(2: gerichtet beidseitig??) [wenn nicht ändere "convert_from_adjacency"]
					 */
	KantenFormat shape;	//methode für redraw bei änderung?
	Kommentar^ comment;
private:
	Knoten^ knoten_start;
	Knoten^ knoten_end;
	Graph^ owning_graph;		/*achtung! hält "Graph" am leben, auch wenn dieser deleted wird, sofern nicht auch alle zugehörigen 
								 *kanten freigegeben werden! */

public:
	//möglicherweise einfachere überladungsmethode bekannt?
	Kante(Graph^ graph_init,Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init);
	~Kante();
	property int wertung{
		void set(int wert){
			//delete[] string_wertung;
			string_wertung=wert.ToString();	
		}
		int get(void){
			int wert;
			if(int::TryParse(string_wertung,wert))
				return wert;
			else 
				return 0;
		}
	}
	Knoten^ get_knoten_start();
	Knoten^ get_knoten_end();
	Knoten^ find_other_vertex(Knoten^ edge_origin);
	//change_knoten_start/change_knoten_end nötig?

};

