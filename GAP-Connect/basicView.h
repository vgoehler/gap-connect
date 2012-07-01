#pragma once
namespace GAPConnect {
public ref class basicView
{
public:
	basicView(void);
	basicView(System::Windows::Forms::Form^);
	~basicView();

	property System::Drawing::Point Location{
		void set(System::Drawing::Point inValue){
			this->m_location = inValue;
			this->recalcRectangle();
		}
		System::Drawing::Point get(void){
			return(this->m_location);
		}
	}
	property System::Drawing::Size Size{
		void set (System::Drawing::Size inValue){
			this->m_size = inValue;
			this->recalcRectangle();
		}
		System::Drawing::Size get (void){
			return(this->m_size);
		}
	}
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
	property System::Drawing::Rectangle GetBorderRectangle{
		System::Drawing::Rectangle get(void){
			return(this->drawRectangle);
		}
	}
	property System::Drawing::Size MinSize{
		void set (System::Drawing::Size inValue){
			this->m_minsize = inValue;
			this->Height = this->m_size.Height;
			this->Width = this->m_size.Width;
		}
	}
	property System::Drawing::Size MaxSize{
		void set(System::Drawing::Size inValue){
			this->m_maxsize = inValue;
			this->Height = this->m_size.Height;
			this->Width = this->m_size.Width;
		}
	}
protected:
	///<summary> Übergeordnetes Formular </summary>
	System::Windows::Forms::Form^ Parent;
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
};
}
