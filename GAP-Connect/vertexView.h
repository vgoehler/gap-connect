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
		///<summary> Konstruktor mit �bergabe eines Knotens </summary>
		vertexView(System::Windows::Forms::Form^, GAPConnect::drawTools^, Graph^ parentDataGraph, Knoten^ inKnoten);
		///<summary> Destruktor </summary>
		~vertexView();

		///<summary> �ndert die Art des Knoten.</summary>
		property int TypeofVertex{
			void set(int inValue){
				if (this->m_vertexType != inValue){
					this->m_vertexType = inValue;
					//TODO einen auf den anderen Type umwandeln
				}
			}
			int get (void){
				return(this->m_vertexType);
			}
		}
		///<summary> Gibt die Mitte des Knotens zur�ck, bzw. zentriert den Knoten auf einer �bergebenen Position</summary>
		property System::Drawing::Point LocationCenter{
			void set(System::Drawing::Point inValue){
				this->Location = System::Drawing::Point(inValue.X - this->Width/2,
														inValue.Y - this->Height/2);
				this->m_dataVertex->coords = this->Location;
			}
			System::Drawing::Point get(void){
				return(Point(this->Location.X + this->Width /2, this->Location.Y + this->Height /2));
			}
		}
		///<summary> startet den Dialog zum Konfigurieren des Knotens.</summary>
		virtual void startConfigDialog(bool refreshAfterDialog) override;
		///<summary> je nach gew�nschter Art des Knotens wird eine andere Darstellungsform gew�hlt</summary>
		void drawVertex(System::Windows::Forms::PaintEventArgs^ e);
		///<summary> Aktivierungszustand des Elements kann gesetzt werden bzw. abgefragt. �berschrieben.</summary>
		property bool IsEnabled{
			virtual void set(bool inValue) override{
				basicView::IsEnabled = inValue;
				if (inValue){
					this->m_vertexSolidBrush = this->m_drawTools->m_vertexFill;
				}else{
					this->m_vertexSolidBrush = this->m_drawTools->m_vertexDeactivated;
				}
				if (this->DataVertex != nullptr)
				{
					this->DataVertex->enabled = inValue;
				}
			}
		}
		///<summary> gibt Dockpunkt an sich selbst zur�ck spezifisch zum �bergebenen Winkel </summary>
		System::Drawing::Point  getDockPoint(double angle);
		///<summary> Gibt Daten Knoten zur�ck </summary>
		property Knoten^ DataVertex{
			Knoten^ get( void ){
				return(this->m_dataVertex);
			}
		}
		property Int32 Height{
			virtual void set(Int32 inValue) override{
				this->basicView::Height = inValue;
				this->updateDataVertex();
			}
		}
		property Int32 Width{
			virtual void set(Int32 inValue) override{
				this->basicView::Width = inValue;
				this->updateDataVertex();
			}
		}
		///<summary> Eintrag f�r die Beschriftung </summary>
		property System::String^ Text{
				void set (System::String^ inValue){
					this->m_dataVertex->label = inValue;
				}
				System::String^ get (void){
					return(this->m_dataVertex->label);
				}
			}
		///<summary> Eintrag f�r den Kommentar </summary>
		property System::String^ Kommentar{
				void set (System::String^ inValue){
					this->m_dataVertex->comment->label = inValue;
				}
				System::String^ get (void){
					return(this->m_dataVertex->comment->label);
				}
			}
		///<summary> Location aus den Daten neu Laden im Falle das ein Algorithmus auf Datenebene die ge�ndert hat. </summary>
		void updateLocationFromDataVertex(void);

	private:
			///<summary> Typ des Knotens 0 - Rund; 1 - Eckig </summary>
			int m_vertexType;
			///<summary> Datenknoten </summary>
			Knoten^ m_dataVertex;
			///<summary> Initializiert alle Felder des Dialogs mit passenden Werten aus sich selbst (zu bearbeitender Knoten).</summary>
			void InitializeDialogValues(System::Windows::Forms::Form^);
			///<summary> Setzt die Werte des Knoten aus dem Konfigdialog heraus</summary>
			void SetDialogValues(System::Windows::Forms::Form^);
			///<summary> Skaliert den Knoten auf die Gr��e des Textes. </summary>
			void ScaleVertex(void);
			///<summary> Farbe mit der der Knoten gezeichnet wird. </summary>
			System::Drawing::SolidBrush^ m_vertexSolidBrush;
			///<summary> setzt je nach Eckig oder Rund die Gr��e im data</summary>
			void updateDataVertex( void );
	};
}