// Objekte.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "KnotenRund.h"
#include "KnotenEckig.h"

using namespace Objekte;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//*******test start**********
	KnotenEckig knoten1("hans");
	System::Diagnostics::Debug::WriteLine("test-main");
	knoten1.~KnotenEckig();

	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());



	return 0;
}
