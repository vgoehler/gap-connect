#pragma once

namespace GAPConnect {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	///<summary> Klasse zum Darstellen der Knoten</summary>
	public ref class vertexView :
	public basicView
	{
	public:
		///<summary> Konstruktor </summary>
		vertexView(System::Windows::Forms::Form^);

		///<summary> Ändert die Art des Knoten.</summary>
		property int kindOf{
			void set(int inValue){
				vertexType = inValue;
				this->refreshParent();
			}
		}
		property System::Drawing::Point LocationCenter{
			void set(System::Drawing::Point inValue){
				this->Location = System::Drawing::Point(inValue.X - this->Size.Height/2,
														inValue.Y - this->Size.Width/2);
			}
		}
		property System::String^ Text{
			void set (System::String^ inValue){
				this->m_text = inValue;
			}
			System::String^ get (void){
				return(this->m_text);
			}
		}
		property System::String^ Kommentar{
			void set (System::String^ inValue){
				this->m_kommentar = inValue;
			}
			System::String^ get (void){
				return(this->m_kommentar);
			}
		}
		///<summary> Markiert Knoten visuell und gibt markierungszustand zurück</summary>
		bool markVertex(void);
		///<summary> startet den Dialog zum Konfigurieren des Knotens.</summary>
		void startConfigDialog(void);
		///<summary> je nach gewünschter Art des Knotens wird eine andere Darstellungsform gewählt</summary>
		void paintVertex(System::Windows::Forms::PaintEventArgs^ e);

	private:
			///<summary> Typ des Knotens 0 - Rund; 1 - Eckig </summary>
			int vertexType;
			///<summary> Zeigt an ob der Knoten ausgewählt ist </summary>
			bool isMarked;
			///<summary> Beschriftung des Elements</summary>
			String^ m_text;
			///<summary> Font des Textes </summary>
			System::Drawing::Font^ textFont;
			///<summary> Kommentartext </summary>
			String^ m_kommentar;
			//TODO Ownervariable als Dateninterface
			///<summary> Initializiert alle Felder des Dialogs mit passenden Werten aus sich selbst (zu bearbeitender Knoten).</summary>
			void InitializeValues(System::Windows::Forms::Form^);
			///<summary> Refresh des Parent wird angefordert. </summary>
			void refreshParent(void);
	};
}