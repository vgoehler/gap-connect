#pragma once
namespace GAPConnect {
public ref class basicView
{
public:
	basicView(void);
	basicView(System::Windows::Forms::Form^);
	~basicView();

	///<summary> Schreib und Liest die Position des Elements</summary>
	property System::Drawing::Point Location{
		void set(System::Drawing::Point inValue){
			this->m_location = inValue;
			this->recalcRectangle();
		}
		System::Drawing::Point get(void){
			return(this->m_location);
		}
	}
	///<summary> Schreibt und Liest die Größe des Elements</summary>
	property System::Drawing::Size Size{
		void set (System::Drawing::Size inValue){
			this->m_size = inValue;
			this->recalcRectangle();
		}
		System::Drawing::Size get (void){
			return(this->m_size);
		}
	}
	///<summary> Gibt Höhe des Elemnts zurück und Schreibt dieselbe</summary>
	property Int32 Height{
		void set (Int32 inValue){
			if (inValue > this->m_maxsize.Height && this->m_maxsize.Height != 0){
				inValue = this->m_maxsize.Height;
			}else if (inValue < this->m_minsize.Height){
				inValue = this->m_minsize.Height;
			}
			this->Size = System::Drawing::Size(this->m_size.Width, inValue);
		}
		Int32 get (void){
			return(this->m_size.Height);
		}
	}
	///<summary> Gibt Breite des Elements zurück und Schreibt dieselbe</summary>
	property Int32 Width{
		void set (Int32 inValue){
			if (inValue > this->m_maxsize.Width && this->m_maxsize.Width != 0){
				inValue = this->m_maxsize.Width;
			}else if (inValue < this->m_minsize.Width){
				inValue = this->m_minsize.Width;
			}
			this->Size = System::Drawing::Size(inValue, this->m_size.Height);
		}
		Int32 get (void){
			return(this->m_size.Width);
		}
	}
	///<summary> Gibt das Rechteck-Objekt des Elements zurück</summary>
	property System::Drawing::Rectangle GetBorderRectangle{
		System::Drawing::Rectangle get(void){
			return(this->drawRectangle);
		}
	}
	///<summary> Schreibt Minimal Größe</summary>
	property System::Drawing::Size MinSize{
		void set (System::Drawing::Size inValue){
			this->m_minsize = inValue;
			this->Height = this->m_size.Height;
			this->Width = this->m_size.Width;
		}
	}
	///<summary> Schreibt Maximal Größe </summary>
	property System::Drawing::Size MaxSize{
		void set(System::Drawing::Size inValue){
			this->m_maxsize = inValue;
			this->Height = this->m_size.Height;
			this->Width = this->m_size.Width;
		}
	}
	///<summary> Markiert Element und gibt Status zurück. Funktioniert als Toggle. </summary>
	bool Mark( void );
	///<summary> Markiert das Element, bzw. gibt MarkierungsStatus zurück.</summary>
	property bool IsMarked{
		void set(bool inValue){
			this->m_marked = inValue;
		}
		bool get( void ){
			return(this->m_marked);
		}
	}
	///<summary> Ändert den Aktivierungsstatus des Elements als Toggle. </summary>
	bool Enable( void );
	///<summary> Aktivierungszustand des Elements kann gesetzt werden bzw. abgefragt. </summary>
	property bool IsEnabled{
		bool get( void ){
			return(this->m_enable);
		}
		void set(bool inValue){
			this->m_enable = inValue;
		}
	}
	///<summary> Eintrag für die Wichtung </summary>
	property System::String^ Text{
			void set (System::String^ inValue){
				this->m_text = inValue;
			}
			System::String^ get (void){
				return(this->m_text);
			}
		}
	///<summary> Eintrag für den Kommentar </summary>
	property System::String^ Kommentar{
			void set (System::String^ inValue){
				this->m_kommentar = inValue;
			}
			System::String^ get (void){
				return(this->m_kommentar);
			}
		}
	///<summary> Gibt Wahr/Falsch zurück wenn Punkt im Kontrollrechteck liegt </summary>
	bool Contains (System::Drawing::Point& pkt);

protected:
	///<summary> Übergeordnetes Formular </summary>
	System::Windows::Forms::Form^ Parent;
	///<summary> Zeichentools</summary>
	GAPConnect::drawTools^ m_drawTools;
	///<summary> Refresh des Parent wird angefordert. </summary>
	void refreshParent(void);
private:
	///<summary> Variable für die Location des Knotens </summary>
	System::Drawing::Point m_location;
	///<summary> Variable enthält Größe des Knotens </summary>
	System::Drawing::Size m_size;
	///<summary> Minimale Größe </summary>
	System::Drawing::Size m_minsize;
	///<summary> Maximale Größe </summary>
	System::Drawing::Size m_maxsize;
	///<summary> enthält das Rechteck welches den Knoten umgibt </summary>
	System::Drawing::Rectangle drawRectangle;
	///<summary> Rechteck wird neu berechnet. Kommt bei neuer Location und neuer Size vor </summary>
	void recalcRectangle(void);
	///<summary> Markiert ob Element Aktiviert oder Deaktiviert ist. </summary>
	bool m_enable;
	///<summary> Markiert ob Element Ausgewählt wurde. </summary>
	bool m_marked;
	///<summary> Text </summary>
	String^ m_text;
	///<summary> Kommentar </summary>
	String^ m_kommentar;
};
}
