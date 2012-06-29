#pragma once

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	///<summary> Klasse zum Darstellen der Knoten</summary>
	public ref class vertexView : public System::Windows::Forms::Button
	{
	public:
		///<summary> Konstruktor </summary>
		vertexView(System::Windows::Forms::Form^);

		///<summary> Ändert die Art des Knoten.</summary>
		property int kindOf{
			void set(int inValue){
				vertexType = inValue;
				this->changeAppearance();
			}
		}
		property System::Drawing::Point LocationCenter{
			void set(System::Drawing::Point inValue){
				this->Location = System::Drawing::Point(inValue.X - this->Height/2,
														inValue.Y - this->Width/2);
			}
		}

		///<summary> Markiert Knoten visuell und gibt markierungszustand zurück</summary>
		bool markVertex(void);
		///<summary> startet den Dialog zum Konfigurieren des Knotens.</summary>
		void startConfigDialog(void);

	private:
			int vertexType;
			bool isMarked;
			//TODO Ownervariable als Dateninterface
			void InitializeComponent(void);
			///<summary> je nach gewünschter Art des Knotens wird eine andere Darstellungsform gewählt</summary>
			void changeAppearance(void);
			///<summary> Initializiert alle Felder des Dialogs mit passenden Werten aus sich selbst (zu bearbeitender Knoten).</summary>
			void InitializeValues(System::Windows::Forms::Form^);
	};
}