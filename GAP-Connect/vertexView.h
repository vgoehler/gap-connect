#pragma once

///<summary> Klasse zum Darstellen der Knoten</summary>
public ref class vertexView : public System::Windows::Forms::Button
{
public:
	vertexView(void);

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

private:
		int vertexType;
		void InitializeComponent(void);
		void changeAppearance(void);

};

