// Objekte.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "KnotenRund.h"
#include "KnotenEckig.h"
#include "Kante.h"
#include "Graph.h"

using namespace Objekte;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//*******test start**********
	{
	System::Diagnostics::Debug::WriteLine("test-main-begin");
	Graph^ graphi=gcnew Graph();
	graphi->create_vertex("A","erster Knoten",10.4);
	graphi->create_vertex("B","zweiter knoten",20,30);
	graphi->create_edge(graphi->verticles[0],graphi->verticles[1],2,STREIFEN);
	graphi->edges[0];
	delete graphi->verticles[1];
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
