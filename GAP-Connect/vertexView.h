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
		vertexView(System::Windows::Forms::Form^, GAPConnect::drawTools^);

		///<summary> Ändert die Art des Knoten.</summary>
		property int kindOf{
			void set(int inValue){
				vertexType = inValue;
			}
		}
		///<summary> Gibt die Mitte des Knotens zurück, bzw. zentriert den Knoten auf einer Übergebenen Position</summary>
		property System::Drawing::Point LocationCenter{
			void set(System::Drawing::Point inValue){
				this->Location = System::Drawing::Point(inValue.X - this->Width/2,
														inValue.Y - this->Height/2);
			}
			System::Drawing::Point get(void){
				return(Point(this->Location.X + this->Width /2, this->Location.Y + this->Height /2));
			}
		}
		///<summary> startet den Dialog zum Konfigurieren des Knotens.</summary>
		void startConfigDialog(void);
		///<summary> je nach gewünschter Art des Knotens wird eine andere Darstellungsform gewählt</summary>
		void paintVertex(System::Windows::Forms::PaintEventArgs^ e);
		///<summary> Aktivierungszustand des Elements kann gesetzt werden bzw. abgefragt. Überschrieben.</summary>
		property bool IsEnabled{
			bool get( void ){
				return(basicView::IsEnabled);
			}
			void set(bool inValue){
				basicView::IsEnabled = inValue;
				if (inValue){
					this->m_vertexSolidBrush = this->m_drawTools->m_vertexFill;
				}else{
					this->m_vertexSolidBrush = this->m_drawTools->m_vertexDeactivated;
				}
			}
		}

	private:
			///<summary> Typ des Knotens 0 - Rund; 1 - Eckig </summary>
			int vertexType;
			//TODO Ownervariable als Dateninterface
			///<summary> Initializiert alle Felder des Dialogs mit passenden Werten aus sich selbst (zu bearbeitender Knoten).</summary>
			void InitializeValues(System::Windows::Forms::Form^);
			///<summary> Setzt die Werte des Knoten aus dem Konfigdialog heraus</summary>
			void SetValues(System::Windows::Forms::Form^);
			///<summary> Skaliert den Knoten auf die Größe des Textes. </summary>
			void ScaleVertex(void);
			///<summary> Farbe mit der der Knoten gezeichnet wird. </summary>
			System::Drawing::SolidBrush^ m_vertexSolidBrush;
	};
}