// Objekte.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "KnotenRund.h"
#include "KnotenEckig.h"
#include "Kante.h"
#include "Graph.h"
#include "Dijkstra.h"

using namespace Objekte;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//*******test start**********
	{
	System::Diagnostics::Debug::WriteLine("test-main-begin");
	Graph^ graphi=gcnew Graph();
	graphi->create_vertex("A","erster Knoten",1);
	graphi->create_vertex("B","zweiter knoten",2);
	graphi->create_vertex("C","dritter knoten",3);
	graphi->create_vertex("D","vierter knoten",4);
	graphi->create_vertex("D","vierter knoten",5);
	graphi->create_vertex("D","vierter knoten",6);
	graphi->create_vertex("D","vierter knoten",7);
	graphi->create_vertex("D","vierter knoten",8);
	graphi->create_vertex("D","vierter knoten",9);
	graphi->create_vertex("D","vierter knoten",10);
	graphi->create_vertex("D","vierter knoten",11);

	graphi->create_edge(graphi->verticles[0],graphi->verticles[1],2);
	graphi->edges[0]->wertung=1;	
	graphi->create_edge(graphi->verticles[0],graphi->verticles[2],2);
	graphi->edges[1]->wertung=3;
	graphi->create_edge(graphi->verticles[0],graphi->verticles[3],2);
	graphi->edges[2]->wertung=2;
	graphi->create_edge(graphi->verticles[1],graphi->verticles[2],2);
	graphi->edges[3]->wertung=4;
	graphi->create_edge(graphi->verticles[1],graphi->verticles[4],2);
	graphi->edges[4]->wertung=3;
	graphi->create_edge(graphi->verticles[2],graphi->verticles[3],2);
	graphi->edges[5]->wertung=2;
	graphi->create_edge(graphi->verticles[2],graphi->verticles[4],2);
	graphi->edges[6]->wertung=5;
	graphi->create_edge(graphi->verticles[2],graphi->verticles[5],2);
	graphi->edges[7]->wertung=1;
	graphi->create_edge(graphi->verticles[2],graphi->verticles[6],2);
	graphi->edges[8]->wertung=2;
	graphi->create_edge(graphi->verticles[3],graphi->verticles[4],2);
	graphi->edges[9]->wertung=4;
	graphi->create_edge(graphi->verticles[4],graphi->verticles[7],2);
	graphi->edges[10]->wertung=1;
	graphi->create_edge(graphi->verticles[4],graphi->verticles[8],2);
	graphi->edges[11]->wertung=2;
	graphi->create_edge(graphi->verticles[4],graphi->verticles[9],2);
	graphi->edges[12]->wertung=8;
	graphi->create_edge(graphi->verticles[5],graphi->verticles[8],2);
	graphi->edges[13]->wertung=7;
	graphi->create_edge(graphi->verticles[6],graphi->verticles[8],2);
	graphi->edges[14]->wertung=1;
	graphi->create_edge(graphi->verticles[7],graphi->verticles[8],2);
	graphi->edges[15]->wertung=1;
	graphi->create_edge(graphi->verticles[7],graphi->verticles[10],2);
	graphi->edges[16]->wertung=6;
	graphi->create_edge(graphi->verticles[8],graphi->verticles[9],2);
	graphi->edges[17]->wertung=1;
	graphi->create_edge(graphi->verticles[8],graphi->verticles[10],2);
	graphi->edges[18]->wertung=8;
	graphi->create_edge(graphi->verticles[9],graphi->verticles[10],2);
	graphi->edges[19]->wertung=7;

/*
	graphi->write_adjacency_to_file("xtestfile",graphi->convert_graph_to_adjacency());	
	graphi->convert_adjacency_to_graph(graphi->read_file_to_adjacency("xtestfile"));
	graphi->write_adjacency_to_file("xtestfile",graphi->convert_graph_to_adjacency());
	graphi->save_graph("xgraphfile");
	Graph^ graph2 = Graph::load_graph("xgraphfile");
*/
	Dijkstra^ my_diggi =graphi->init_dijkstra(graphi->verticles[0]);
	int i=1;
	while(i >0)
	{
		i=my_diggi->next_step();
	}
	//graphi->edges[0];
	//delete graphi->verticles[1];
	int breakpoint1=0;
	my_diggi;
	/*trim test
	System::Collections::Generic::List<int> listy =gcnew List<int>();
	int x=5;
	int y=6;
	int z=7;
	listy.Add(x);
	listy.Add(y);
	listy.Add(z);
	System::Diagnostics::Debug::WriteLine("list consists of:{0} {1} {2}",listy[0],listy[1],listy[2]);
	listy.Remove(y);
	System::Diagnostics::Debug::WriteLine("list consists of:{0} {1}",listy.Count,listy.Capacity);
	listy.TrimExcess();
	System::Diagnostics::Debug::WriteLine("list consists of:{0} {1}",listy.Count,listy.Capacity);
	*/
//	System::Diagnostics::Debug::WriteLine("comment=comy:{0}",(knot.comment==%comy));

	}
	int breakpoint=0;
	/*

	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());

	*/

	return 0;
}
