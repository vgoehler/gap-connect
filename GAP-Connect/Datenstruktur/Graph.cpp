#include "StdAfx.h"
#include "Graph.h"
#include "Dijkstra.h"
#define PI 3.14159265

Graph::Graph(void)
{
	label="noname";
	edges=gcnew List<Kante^>();
	verticles=gcnew List<Knoten^>();
}

Graph::Graph(System::String^ string_label)
{
	label=string_label;
	edges=gcnew List<Kante^>();
	verticles=gcnew List<Knoten^>();
}

Graph::~Graph(void)
{
	if (label)
	{	delete[] label;
		label=nullptr;		
	}			/*als Zeichen der begonnenen destruktion, nötig wegen problemen
				 *innerhalb folgender "for each" schleife; verwendet in delete_edge()
				 *sowie delete_vertex*/
	if (edges)								//zur Sicherheit (falls array nicht initialisiert)
	{	
			int c_edges	= edges->Count;
			if (c_edges > 0)				
				for (int i=c_edges-1;i>=0;i--)
					delete edges[i];
		edges->Clear();
		delete edges;
		edges=nullptr;
	}
	if (verticles)							//zur Sicherheit (falls array nicht initialisiert)
	{	
		int c_verticles	= verticles->Count;
		if (c_verticles > 0)				
			for (int i=c_verticles-1;i>=0;i--)
				delete verticles[i];
		verticles->Clear();
		delete verticles;
		verticles=nullptr;
	}
}


Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init,KantenFormat shape_init )
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,gerichtet_init,shape_init);
	edges->Add(edge_new);
	return edge_new;
}
Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending,int gerichtet_init )
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,gerichtet_init,NORMAL);
	edges->Add(edge_new);
	return edge_new;
}
Kante^ Graph::create_edge( Knoten^ knoten_begin,Knoten^ knoten_ending)
{
	Kante^ edge_new = gcnew Kante(this,knoten_begin,knoten_ending,0,NORMAL);
	edges->Add(edge_new);
	return edge_new;
}


Knoten^ Graph::create_vertex( System::String^ string_label,System::String^ string_tooltip,double radius_init)
{
	KnotenRund^ vertex_new = gcnew KnotenRund(this,string_label,string_tooltip,radius_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,double radius_init )
{
	KnotenRund^ vertex_new = gcnew KnotenRund(this,string_label,nullptr,radius_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,System::String^ string_tooltip,double height_init,double width_init )
{
	KnotenEckig^ vertex_new = gcnew KnotenEckig(this,string_label,string_tooltip,height_init,width_init);
	verticles->Add(vertex_new);
	return vertex_new;
}
Knoten^ Graph::create_vertex( System::String^ string_label,double height_init,double width_init )
{
	KnotenEckig^ vertex_new = gcnew KnotenEckig(this,string_label,nullptr,height_init,width_init);
	verticles->Add(vertex_new);
	return vertex_new;
}


void Graph::deleted_edge( Kante^ kante_del )
{
	if (label)
	{
		if (edges)
			edges->Remove(kante_del);
	}
}

void Graph::deleted_vertex( Knoten^ knoten_del )
{
	if (label)
	{
		if (verticles)
			verticles->Remove(knoten_del);
	}
}

array<int,2>^ Graph::convert_graph_to_adjacency()
{
	if(verticles==nullptr)
		return nullptr;			//kein Knotenarray initialisiert -> keine Adjazenzmatrix möglich
	verticles->TrimExcess();
	if (edges)
		edges->TrimExcess();
	int c_verticles=verticles->Count;
	if (c_verticles==0)			//keine Knoten vorhanden -> keine Adjazenzmatrix möglich
		return nullptr;
	//Adjazenzmatrix der größe NxN; N=anzahl Knoten.
	array<int,2>^ array_adj = gcnew array<int,2>(c_verticles,c_verticles);
	//initialisieren:
	for (int i=0;i < c_verticles;i++)
	{
		for (int j=0;j < c_verticles;j++)
		{
			array_adj[i,j]=0;
		}
	}
	int v1=0,v2=0; //vertex-index
	for each(Kante^ ka in edges)
	{
		v1 = verticles->IndexOf(ka->get_knoten_start());
		v2 = verticles->IndexOf(ka->get_knoten_end());
		array_adj[v1,v2]=1;			//hinrichtung immer
		if (ka->gerichtet == 0 || ka->gerichtet==2)
			array_adj[v2,v1]=1;		//rückrichtung nur bei ungerichteter kante
	}
	
	return array_adj;
}

void Graph::convert_adjacency_to_graph(array<int,2>^ array_adj)
{
	if (array_adj==nullptr)
		return;
	{//löschen von Kanten und Knoten um neuen Graphen zu erstellen
		if (edges)								
		{	
			int c_edges	= edges->Count;
			if (c_edges > 0)				
				for (int i=c_edges-1;i>=0;i--)
					delete edges[i];
		edges->Clear();
		}
		if (verticles)							
		{	
			int c_verticles	= verticles->Count;
			if (c_verticles > 0)				
				for (int i=c_verticles-1;i>=0;i--)
					delete verticles[i];
		verticles->Clear();
		}
	}
	if (verticles == nullptr)		//falls nicht mehr/noch nicht vorhanden
		verticles=gcnew List<Knoten^>();
	if (edges == nullptr)
		edges=gcnew List<Kante^>();

	int N_array_adj =array_adj->GetLength(0);	// "N" as in NxN matrix
	for (int i=0;i<N_array_adj;i++)
	{
		create_vertex("",10);
	}
	//obere rechte Dreiecksmatrix
	for (int i=0;i < N_array_adj;i++)
	{
		for (int j=N_array_adj-1;j > i;j--)
		{
			if(array_adj[i,j]==1)
			{	if (array_adj[j,i]==1)
					create_edge(verticles[i],verticles[j],0);	//wenn beidseitig vorhanden dann 1 doppelseitige kante
				else
					create_edge(verticles[i],verticles[j],1);
			}
		}
	}
	//
	for (int j=0;j < N_array_adj;j++)
	{
		for (int i=N_array_adj-1;i>=j;i--)
		{
			if(array_adj[i,j]==1)
			{	
				if(i==j)
					create_edge(verticles[i],verticles[i],0);//Schleifen	
				else
					if (array_adj[j,i]!=1)//doppelseitige bereits erschaffen
						create_edge(verticles[i],verticles[j],1);
			}
		}
	}

}

void Graph::write_adjacency_to_file( System::String^ string_fileName,array<int,2>^ array_adj )
{
	System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(string_fileName);
	int N_array_adj =array_adj->GetLength(0);
	if(N_array_adj>0)
	{	if(N_array_adj==1)
			sw->Write("{0}",array_adj[0,0]);
		else
		{
			for (int i=0; i<N_array_adj;i++)
			{
				for (int j=0;j<N_array_adj-1;j++)
				{
					sw->Write("{0},",array_adj[i,j]);
				}
				sw->WriteLine("{0}",array_adj[i,N_array_adj-1]);	//springt danach zu nächster zeile
			}
		}
	}
	sw->Close();
}

array<int,2>^ Graph::read_file_to_adjacency( System::String^ string_fileName )
{
	array<int,2>^ array_adj;
	System::String^ string_line;

	try 
	{
		System::IO::StreamReader^ sr = System::IO::File::OpenText(string_fileName);
		if((string_line = sr->ReadLine()) == nullptr)//wenn Datei leer, return NULL
		{	
			sr->Close();
			return nullptr;
		}
		int N=(string_line->Length +1)/2;
		array_adj = gcnew array<int,2>(N,N);

		for(int j=0;j<N;j++)			//schreibe erste zeile in Matrix
			if (string_line[2*j]==49)
				array_adj[0,j]=1;
			else
			{
				if (string_line[2*j]==48)
					array_adj[0,j]=0;
				else
				{
					sr->Close();
					return nullptr;
				}
			}
		int i = 1;						//beginn des counters bei 2.Zeile
		while ((string_line = sr->ReadLine()) != nullptr) 
		{
			for(int j=0;j<N;j++)
				if (string_line[2*j]==49)
					array_adj[i,j]=1;
				else
				{
					if (string_line[2*j]==48)
						array_adj[i,j]=0;
					else
					{
						sr->Close();
						return nullptr;
					}
				}
			i++;
			if (i>N)
			{
				sr->Close();
				return nullptr;		//keine NxN matrix in Datei
			}
		}
		if(i<N)
		{	sr->Close();
			return nullptr;			//keine NxN matrix in Datei
		}
		sr->Close();
	}
	catch (System::Exception^ e)
	{
		//error reading/finding file
		return nullptr;
	}

	return array_adj;
}

bool Graph::save_graph(System::String ^string_fileName )
{	
	try
	{
		// create new memory stream
		System::IO::MemoryStream ^_MemoryStream = gcnew System::IO::MemoryStream();

		// create new BinaryFormatter
		System::Runtime::Serialization::Formatters::Binary::BinaryFormatter ^_BinaryFormatter = gcnew System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();

		// Serializes an object, or graph of connected objects, to the given stream.
		_BinaryFormatter->Serialize(_MemoryStream, this);

		// convert stream to byte array
		array<System::Byte> ^_ByteArray = _MemoryStream->ToArray();

		// Open file for reading
		System::IO::FileStream ^_FileStream = gcnew System::IO::FileStream(string_fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);

		// Writes a block of bytes to this stream using data from a byte array.
		_FileStream->Write(_ByteArray, 0, _ByteArray->Length);

		// close file stream
		_FileStream->Close();

		// cleanup
		_MemoryStream->Close();
		delete _MemoryStream;
		_MemoryStream = nullptr;
		_ByteArray = nullptr;

		return true;
	}
	catch (System::Exception ^e)
	{
		// Error
		//Console::WriteLine("Exception caught in process: {0}", e->ToString());
	}

	// Error occured, return null
	return false;
}

Graph^ Graph::load_graph(System::String ^string_fileName)
{
	try
	{
		// Open file for reading
		System::IO::FileStream ^_FileStream = gcnew System::IO::FileStream(string_fileName, System::IO::FileMode::Open, System::IO::FileAccess::Read);

		// attach filestream to binary reader
		System::IO::BinaryReader ^_BinaryReader = gcnew System::IO::BinaryReader(_FileStream);

		// get total byte length of the file
		System::IO::FileInfo ^_FileInfo = gcnew System::IO::FileInfo(string_fileName);
		System::Int64 _TotalBytes = _FileInfo->Length;

		// read entire file into buffer
		array<System::Byte> ^_ByteArray = _BinaryReader->ReadBytes(safe_cast<Int32>(_TotalBytes));

		// close file reader and do some cleanup
		_FileStream->Close();
		delete _FileStream;
		_FileStream = nullptr;
		_BinaryReader->Close();

		// convert byte array to memory stream
		System::IO::MemoryStream ^_MemoryStream = gcnew System::IO::MemoryStream(_ByteArray);

		// create new BinaryFormatter
		System::Runtime::Serialization::Formatters::Binary::BinaryFormatter ^_BinaryFormatter = gcnew System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();

		// set memory stream position to starting point
		_MemoryStream->Position = 0;

		// Deserializes a stream into an object graph and return as a object.
		return safe_cast<Graph^>(_BinaryFormatter->Deserialize(_MemoryStream));
	}
	catch (Exception ^_Exception)
	{
		// Error
		Console::WriteLine("Exception caught in process: {0}", _Exception->ToString());
	}

	// Error occured, return null
	return nullptr;
}

Dijkstra^ Graph::init_dijkstra(Knoten ^knoten_start)
{
	return gcnew Dijkstra(knoten_start);
}

int Graph::optimize(int n,bool verticles_placed)
{
	int v_count=verticles->Count;
	if(!verticles_placed)
		throw_points_around(1,v_count);

	System::Collections::Generic::List<System::Drawing::Point> ^positions=gcnew List<System::Drawing::Point>();
	for(int i=0;i<v_count;i++)
	{
		positions->Add(verticles[i]->coords);
	}
	


	int crossing_counter=-1;
	int n_counter=n;
	for(n_counter;n_counter>0;n_counter--)
	{
		//Rectangle creation
		System::Collections::Generic::List<System::Drawing::Rectangle> ^rectangles=gcnew List<System::Drawing::Rectangle>();
		for each(Kante^ ka in edges)
		{
			int x1 = ka->get_knoten_start()->coords.X;
			int y1 = ka->get_knoten_start()->coords.Y;
			int x2 = ka->get_knoten_end()->coords.X;
			int y2 = ka->get_knoten_end()->coords.Y;
			if(x1<x2)
				if(y1<y2)
					rectangles->Add(System::Drawing::Rectangle(x1,y1,x2-x1,y2-y1));
				else
					rectangles->Add(System::Drawing::Rectangle(x1,y2,x2-x1,y1-y2));
			else
				if(y1<y2)
					rectangles->Add(System::Drawing::Rectangle(x2,y1,x1-x2,y2-y1));
				else
					rectangles->Add(System::Drawing::Rectangle(x2,y2,x1-x2,y1-y2));
		}//*for end*
		int temp_crossing_counter=0;
		int count= rectangles->Count;
		int y=0;
		for (int i=0; i<count;i++)
		{	
			for (int j=count-1; j>i;j--)
			{	
				if (crossing(rectangles[i],rectangles[j],edges[i],edges[j]))
					temp_crossing_counter++;
			}
		}
		delete rectangles;
		//wenn weniger kreuzungen vorhanden, knotenpositionen speichern (außer beim ersten mal) und kreuzungs-zahl merken
		if (temp_crossing_counter<crossing_counter && crossing_counter!=-1)
		{	crossing_counter=temp_crossing_counter;
			for(int i=0;i<v_count;i++)
				positions[i] = verticles[i]->coords;
		}
		else
			if(crossing_counter==-1)
				crossing_counter=temp_crossing_counter;
		if(crossing_counter==0 || n_counter<=0)
			break;	//abbruch bei 0 kreuzungen oder n==0;

		//eigentlicher random-algoritmus:
		if(n_counter < n/2)
			throw_points_around(2,v_count);
		else
			throw_points_around(1,v_count);

	}//*algorithm end*
	//setzen der Knoten-koordinaten auf bestes ergebnis
	for(int i=0;i<v_count;i++)
		verticles[i]->coords = positions[i];
	return crossing_counter;
}

bool Graph::crossing(System::Drawing::Rectangle rec1,System::Drawing::Rectangle rec2,Kante^ ka1,Kante^ ka2)
{
	//Kontrollrechtecke müssen sich überschneiden
	int rec1_orig_height=rec1.Height;
	int rec1_orig_width=rec1.Width;
	int rec2_orig_height=rec2.Height;
	int rec2_orig_width=rec2.Width;

	rec1.X--;
	rec1.Y--;
	rec1.Height+=2;
	rec1.Width+=2;
	rec2.X--;
	rec2.Y--;
	rec2.Height+=2;
	rec2.Width+=2;
	if (rec1.IntersectsWith(rec2))
	{
		if ((ka1->get_knoten_start() == ka2->get_knoten_start() && ka1->get_knoten_end() == ka2->get_knoten_end() || ka1->get_knoten_start() == ka2->get_knoten_end() && ka1->get_knoten_end() == ka2->get_knoten_start()))
		{	//Doppelkante, Falsch zurückgeben, da diese durch Knotenverschiebung nicht behoben wird
			return(false);
		}else 
			if (ka1->get_knoten_start() == ka2->get_knoten_start() || ka1->get_knoten_start() == ka2->get_knoten_end() || ka1->get_knoten_end() == ka2->get_knoten_start() || ka1->get_knoten_end() == ka2->get_knoten_end())
			{
				//wenn startpunkt oder endpunkt gleich, dann kann es keine crossings geben, lediglich inclusionen wenn ein rechteck im anderen ist
				if (rec1.Contains(rec2) || rec2.Contains(rec1))
				{
					if(rec1_orig_height>0 && rec2_orig_height>0)
						if(rec1_orig_height*rec2_orig_width/rec2_orig_height == rec1_orig_width)
							return(true);
						else
							return (false);
					else
						if(rec1_orig_height==0 && rec2_orig_height==0)
							return(true);
						else
							return(false);
				}
				return(false);
			}
		//Geradengleichung aufstellen
		System::Drawing::PointF rv1 = System::Drawing::PointF(float((ka1->get_knoten_end()->coords.X)-(ka1->get_knoten_start()->coords.X)),float((ka1->get_knoten_end()->coords.Y)-(ka1->get_knoten_start()->coords.Y)));
		System::Drawing::PointF rv2 = System::Drawing::PointF(float((ka2->get_knoten_end()->coords.X)-(ka2->get_knoten_start()->coords.X)),float((ka2->get_knoten_end()->coords.Y)-(ka2->get_knoten_start()->coords.Y)));
		//wenn Richtungsvektor linear abhängig zu einander dann Parallel; keine Fallunterscheidung, einfach rechnen lassen, findet in dem fall keinen schnittpunkt
		System::Drawing::PointF ov1 = System::Drawing::PointF(float(ka1->get_knoten_start()->coords.X),float(ka1->get_knoten_start()->coords.Y));
		System::Drawing::PointF ov2 = System::Drawing::PointF(float(ka2->get_knoten_start()->coords.X),float(ka2->get_knoten_start()->coords.Y));
		//Umgestelltes Gleichungssystem ov1 + faktor1 * rv1 = ov2 + faktor2 * rv2
		float faktor2 = (rv1.Y * (ov1.X-ov2.X) + rv1.X * (ov2.Y - ov1.Y)) / (rv1.Y * rv2.X - rv1.X * rv2.Y);
		float faktor1 = (ov2.Y - ov1.Y + faktor2*rv2.Y)/rv1.Y;
		
		if(rv1.Y == 0)//vorläufig
			return (true);
		//Schnittpunkt
		System::Drawing::Point schnittpunkt = System::Drawing::Point(int(ceil(ov1.X+faktor1*rv1.X)), int(ceil(ov1.Y+faktor1*rv1.Y)));
		if (rec1.Contains(schnittpunkt))
		{
			return(true);
		}
	}
	return(false);

}

void Graph::throw_points_around(int modi,int v_count)
{
	int x_start=300;
	int y_start=300;
	int possible_places=(int)(v_count*2.3);
	int count = verticles->Count;
	int max_edges1=0;
	int max_edges2=0;
	int max_edges_index1=0;
	int max_edges_index2=0;
	double my_random;
	Random ^ rnd = gcnew Random;	

	System::Collections::Generic::List<int>^ point_placement = gcnew System::Collections::Generic::List<int>(count);
	for(int i =0; i<count;i++)
	{
		//suche nach hochgradigen knoten
		if (verticles[i]->edges->Count > max_edges1)
		{	max_edges1=verticles[i]->edges->Count;
			max_edges_index1=i;
		}
		else
			if(verticles[i]->edges->Count > max_edges2)
			{	max_edges2=verticles[i]->edges->Count;
				max_edges_index2=i;
			}

		my_random=rnd->Next(0,possible_places-1);
		if (!(point_placement->Contains((int)my_random)))
		{
			point_placement->Add((int)my_random);
		}
		else
			i--;
	}
	//höchsten grad in mitte setzen oder 2.höchsten
	int mid_index=0;
	if(modi==1)
		mid_index=max_edges_index1;
	else if(modi==2)
		mid_index=max_edges_index2;

	bool my_switch=true;
	for(int i=0;i<count;i++)
	{
		if (i==mid_index)
		{
			verticles[i]->coords.X =x_start;
			verticles[i]->coords.Y =y_start;
		}
		else
		{	
			if(verticles[i]->edges->Count <= 1)	//knoten mit nur einer kante/isolierter knoten
			{	my_random=point_placement[i]*2*PI/possible_places;
				verticles[i]->coords.X =(int)((System::Math::Sin(my_random))*40+x_start);
				verticles[i]->coords.Y =(int)((System::Math::Cos(my_random))*40+y_start);
			}else
				if(my_switch)
				{
					my_switch=false;
					my_random=point_placement[i]*2*PI/possible_places;
					verticles[i]->coords.X =(int)((System::Math::Sin(my_random))*100+x_start);
					verticles[i]->coords.Y =(int)((System::Math::Cos(my_random))*100+y_start);
				}
				else
				{
					my_switch=true;
					my_random=point_placement[i]*2*PI/possible_places;
					verticles[i]->coords.X =(int)((System::Math::Sin(my_random))*200+x_start);
					verticles[i]->coords.Y =(int)((System::Math::Cos(my_random))*200+y_start);
				}
		}
	}

	delete rnd;
}

