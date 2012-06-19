#include "StdAfx.h"
#include "drawingarea.h"


System::Void GAPConnect::drawingarea::drawingarea_FormClosing( System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e )
{
	if (!(this->isClosing)){
		if (this->isChanged){
			//TODO SavePrompt Dialog
			if ( MessageBox::Show( L"Es sind Änderungen vorhanden. Wollen Sie das Schließen abbrechen?", L"Änderungen!", MessageBoxButtons::YesNo , MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes ){
				//User will schließen abbrechen
				e->Cancel = true;
			}
		}else{
			//keine Änderungen
			(dynamic_cast<GAPConnect::Form1^>(this->Owner))->doOnDrawingAreaClose(this);

		}
	}
}
