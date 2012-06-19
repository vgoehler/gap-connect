#include "StdAfx.h"
#include "menu.h"


System::Void GAPConnect::menu::dockingToolStripMenuItem_CheckedChanged( System::Object^ sender, System::EventArgs^ e )
{
	GAPConnect::Form1^ master = dynamic_cast<GAPConnect::Form1^>(this->Owner);
	//checked geändert!
	if (this->Docked == true){
		//Modus Docked
		master->DebugText = L"Docked";
		//alte Freekoordinaten speichern (im array)
		master->saveWindowPositions();
	}else{
		//Freier Modus
		master->DebugText = L"Free";
	}
	master->setWindowLayout();
}
