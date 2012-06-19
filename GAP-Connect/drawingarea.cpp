#include "StdAfx.h"
#include "drawingarea.h"


System::Void GAPConnect::drawingarea::drawingarea_FormClosing( System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e )
{
	if (!(this->isClosing)){
		if (this->isChanged){
			//TODO SavePrompt Dialog
			if ( MessageBox::Show( L"Es sind �nderungen vorhanden. Wollen Sie das Schlie�en abbrechen?", L"�nderungen!", MessageBoxButtons::YesNo , MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes ){
				//User will schlie�en abbrechen
				e->Cancel = true;
			}
		}else{
			//keine �nderungen
			(dynamic_cast<GAPConnect::Form1^>(this->Owner))->doOnDrawingAreaClose(this);

		}
	}
}
