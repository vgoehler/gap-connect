#include "StdAfx.h"
#include "Kante.h"


Kante::Kante( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,Format shape_init )
{
	knoten_start=knoten_begin;	
	knoten_end=knoten_ending;
	gerichtet=gerichtet_init;
	shape=shape_init;
}

Kante::Kante( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init )
{
	knoten_start=knoten_begin;
	knoten_end=knoten_ending;
	gerichtet=gerichtet_init;
}

Kante::Kante( Knoten^ knoten_begin,Knoten^ knoten_ending )
{
	knoten_start=knoten_begin;
	knoten_end=knoten_ending;
}

Kante::~Kante()
{
	if (comment)
		comment->~Kommentar();

}
