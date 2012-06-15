// Objekte.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "KnotenRund.h"
#include "KnotenEckig.h"
#include "Kante.h"

using namespace Objekte;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//*******test start**********
	System::Diagnostics::Debug::WriteLine("test-main-begin");
	KnotenEckig knot("hans");
	KnotenRund knor("hasi");
	knot.width=20;
	knot.set_tooltip("freak");
	Kommentar comy("das ist ein kommentar",10,5);
	knot.set_comment(%comy);
	if (knot.comment==nullptr)
		System::Diagnostics::Debug::WriteLine("comment=comy");
	else
		System::Diagnostics::Debug::WriteLine("comment!=comy");
	Kante kanti(%knot,%knor,1,PUNKTE);
	
	knot.~KnotenEckig();
	
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());



	return 0;
}
