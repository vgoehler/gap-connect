#include "StdAfx.h"
#include "AlgorithmusRunDialog.h"


System::Void GAPConnect::AlgorithmusRunDialog::NextButton_Click( System::Object^ sender, System::EventArgs^ e )
{
	if(!dynamic_cast<GAPConnect::Form1^ >(Owner)->ViewGraphDijkstraStep()){//false bei ende des Algorithmus
		this->NextButton->Enabled = false;
	}
	dynamic_cast<GAPConnect::Form1^ >(Owner)->RefreshDrawBox();
}
