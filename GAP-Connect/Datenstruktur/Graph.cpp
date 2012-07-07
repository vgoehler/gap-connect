#include "StdAfx.h"
#include "Graph.h"
#include "Dijkstra.h"

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
		create_vertex("",10,10);
	}
	for (int i=0;i < N_array_adj;i++)
	{
		for (int j=0;j < N_array_adj;j++)
		{
			if(array_adj[i,j]==49)
			{	if (array_adj[j,i]==49)
					create_edge(verticles[i],verticles[j],2);	//wenn beidseitig vorhanden dann 1 doppelseitige kante
				else
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

		for(int j=0;j<N;j++)							//schreibe erste zeile in Matrix
			array_adj[0,j]=string_line[2*j];
		int i = 1;									//beginn des counters bei 2.Zeile
		while ((string_line = sr->ReadLine()) != nullptr) 
		{
			for(int j=0;j<N;j++)
				array_adj[i,j]=string_line[2*j];
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

