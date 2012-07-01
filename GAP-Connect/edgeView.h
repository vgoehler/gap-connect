#pragma once

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

///<summary> Klasse zur Darstellung der Knoten </summary>
public ref class edgeView :
public System::Windows::Forms::Control
{
public:
	edgeView(System::Windows::Forms::Form^ , System::Windows::Forms::Button^ ,System::Windows::Forms::Button^ , int);

private:
	void InitializeComponent(void);
	System::Windows::Forms::Button^ startVertex;
	System::Windows::Forms::Button^ endVertex;
	System::Drawing::Point createLocation( void );
	System::Drawing::Size createSize( void );
	System::Void drawEdge_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
	int lineMode;
};

}