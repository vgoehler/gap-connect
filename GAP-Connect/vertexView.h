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
		vertexView(System::Windows::Forms::Form^, GAPConnect::drawTools^, Graph^ parentDataGraph);
		///<summary> Destruktor </summary>
		~vertexView();

		///<summary> Ändert die Art des Knoten.</summary>
		property int TypeofVertex{
			void set(int inValue){
				this->m_vertexType = inValue;
			}
			int get (void){
				return(this->m_vertexType);
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
		virtual void startConfigDialog(bool refreshAfterDialog) override;
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
		///<summary> gibt Dockpunkt an sich selbst zurück spezifisch zum Übergebenen Winkel </summary>
		System::Drawing::Point  getDockPoint(double angle);
		///<summary> Gibt Daten Knoten zurück </summary>
		property Knoten^ DataVertex{
			Knoten^ get( void ){
				return(this->m_dataVertex);
			}
		}

	private:
			///<summary> Typ des Knotens 0 - Rund; 1 - Eckig </summary>
			int m_vertexType;
			///<summary> Datenknoten </summary>
			Knoten^ m_dataVertex;
			///<summary> Initializiert alle Felder des Dialogs mit passenden Werten aus sich selbst (zu bearbeitender Knoten).</summary>
			void InitializeDialogValues(System::Windows::Forms::Form^);
			///<summary> Setzt die Werte des Knoten aus dem Konfigdialog heraus</summary>
			void SetDialogValues(System::Windows::Forms::Form^);
			///<summary> Skaliert den Knoten auf die Größe des Textes. </summary>
			void ScaleVertex(void);
			///<summary> Farbe mit der der Knoten gezeichnet wird. </summary>
			System::Drawing::SolidBrush^ m_vertexSolidBrush;
	};
}