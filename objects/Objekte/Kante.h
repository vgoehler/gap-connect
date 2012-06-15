#pragma once
#include "Kommentar.h"
enum Format{STREIFEN,PUNKTE,WELLE}; //und sonstige ideen - je nach implementierung...

ref class Knoten;	/*reine Deklaration von "Knoten" zur verwendung der Knoten-Handle unter
					 *vermeidung von kreuzenden Einbindungen der Header (Knoten.h und Kante.h)
					 */

ref class Kante
{
public:
	int gerichtet;	/*-1: gerichtet mit Startpunkt 'knoten_end'
					 * 0: ungerichtet
					 * 1: gerichtet mit Startpunkt 'knoten_start'
					 *(2: gerichtet beidseitig??)
					 */
	Format shape;	//methode für redraw bei änderung?
private:
	Knoten^ knoten_start;
	Knoten^ knoten_end;
	Kommentar^ comment;

public:
	//sehr warscheinlich einfachere überladungsmethode bekannt?
	Kante(Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,Format shape_init);
	Kante(Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init);
	Kante(Knoten^ knoten_begin,Knoten^ knoten_ending);
	~Kante();
	//change_knoten_start/change_knoten_end nötig?


};

