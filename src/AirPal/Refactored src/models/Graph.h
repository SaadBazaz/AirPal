#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
#include<cmath>
#include<list>
#include<stack>
#include "Stack.h"
#include<cstring>
#include "Date.h"
using namespace std;

struct CityNode
{
	string CityName;
	Date Date_of_travel;
	string Flying_time;
	string Landing_time;
	int Ticket_price;
	int Total_Time;
	string Name_of_airline;
	int transitTime;
	CityNode* next;
	CityNode() :CityName(""), Date_of_travel(""), Flying_time(""), Landing_time(""), Ticket_price(0),
		Total_Time(0), Name_of_airline(""), transitTime(0), next(0) { }

	void init(const string& cn, Date& dot, const string& ft, const string& lt,
		const string& noa, const int& tp, const int& tt, CityNode* n = NULL) {
		CityName = cn;
		Date_of_travel = dot;
		Flying_time = ft;
		Landing_time = lt;
		Name_of_airline = noa;
		Ticket_price = tp;
		Total_Time = tt;
		transitTime = 0;
		next = n;
	}

	CityNode(string facevalue, Date date, string flying, string landing, int price, int totaltime, string airline) {
		CityName = facevalue;
		Date_of_travel = date;
		Flying_time = flying;
		Landing_time = landing;
		Ticket_price = price;
		Total_Time = totaltime;
		Name_of_airline = airline;
		transitTime = 0;
		next = NULL;
	}

	void DisplayCityInformation() {
		cout << CityName;
		if (CityName.length() >= 8) {
			cout << "\t   ";
		}
		else {
			cout << "\t\t   ";
		}
		cout << Date_of_travel.getStringDate() << "\t\t" << Flying_time
			<< "\t\t" << Landing_time << "\t\t" << Ticket_price << "\t\t" << Name_of_airline;
		if (Name_of_airline.length() <= 5) {
			cout << "\t\t   ";
		}
		else {
			cout << "\t   ";
		}
		cout << Total_Time << " hours" << endl;
	}
	CityNode& operator=(const CityNode& cn) {
		CityName = cn.CityName;
		Date_of_travel = cn.Date_of_travel;
		Flying_time = cn.Flying_time;
		Landing_time = cn.Landing_time;
		Name_of_airline = cn.Name_of_airline;
		Ticket_price = cn.Ticket_price;
		Total_Time = cn.Total_Time;
		transitTime = cn.transitTime;
		next = 0;
		return *this;
	}
	CityNode& operator=(CityNode*& cn) {
		CityName = cn->CityName;
		Date_of_travel = cn->Date_of_travel;
		Flying_time = cn->Flying_time;
		Landing_time = cn->Landing_time;
		Name_of_airline = cn->Name_of_airline;
		Ticket_price = cn->Ticket_price;
		Total_Time = cn->Total_Time;
		transitTime = cn->transitTime;
		next = 0;
		return *this;
	}
	bool operator==(const CityNode& rhs) {
		if (CityName == rhs.CityName) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Graph {
private:
	int TotalCities;
	Vector<CityNode*> Array;
	Vector<CityNode*> tempGraphAllPaths;
	Vector<string> Hotels;
	Vector<string> TotalCityStrings;
	Vector<int> PricesofHotels;
	CityNode* CreateCity(string facevalue, Date date, string flying, string landing, int price,
		int totaltime, string airline) {

		CityNode* temp = new CityNode(facevalue, date, flying, landing, price, totaltime, airline);
		return temp;
	}

public:
	Graph() :TotalCities(0) { }
	~Graph() {
		if (!Array.isEmpty()) {
			DeleteGraph(Array);
			Array.MakeEmpty();
		}
		clearallTempsGraph();
	}

	void clearallTempsGraph() {
		if (!tempGraphAllPaths.isEmpty()) {
			DeleteGraph(tempGraphAllPaths);
			tempGraphAllPaths.MakeEmpty();
		}
	}


	void DeleteGraph(Vector<CityNode*>& vec) {
		if (!vec.isEmpty()) {
			for (int i = 0; i < vec.Size(); i++) {
				if (vec[i] != NULL) {
					CityNode* nodeptr = vec[i];
					CityNode* tempnode = NULL;
					while (nodeptr != NULL) {
						tempnode = nodeptr->next;
						delete nodeptr;
						nodeptr = tempnode;
					}
				}
			}
		}
	}

	void showGraphStructure() {
		CityNode* nodeptr;
		bool temp = false;
		for (int i = 0; i < Array.Size(); i++) {
			if (Array[i] != NULL) {
				temp = true;
			}
		}
		if (!temp) {
			cout << "Empty Graph \n\n";
			return;
		}
		for (int i = 0; i < Array.Size(); i++) {
			if (Array[i] != NULL) {
				cout << Array[i]->CityName << " -> ";
				nodeptr = Array[i]->next;
				while (nodeptr != NULL) {
					cout << nodeptr->CityName;
					if (nodeptr->next != NULL) {
						cout << " , ";
					}
					nodeptr = nodeptr->next;
				}
				cout << endl;
			}
		}
	}

	void addEdge(string src, CityNode dest) {
		bool temp1 = false;
		int index = 0;
		if (CheckifSrcisAvailable(src, index))		// if Src is Already there
		{
			int index1 = 0;
			if (CheckifSrcisAvailable(dest.CityName, index1) == false) {
				Date d(0, 0, 0);
				CityNode* nodeptr = CreateCity(dest.CityName, d, "\0", "\0", 0, 0, "\0");
				Array.push_back(nodeptr);
				TotalCities += 1;
				if (TotalCityStrings.find(dest.CityName) == -1) {
					TotalCityStrings.push_back(dest.CityName);
				}
			}
			CityNode* nodeptr = Array[index];
			CityNode* nodeptrprev = NULL;
			while (nodeptr != NULL) {
				nodeptrprev = nodeptr;
				if (nodeptr->CityName == dest.CityName && nodeptr->Flying_time == dest.Flying_time &&
					nodeptr->Landing_time == dest.Landing_time && nodeptr->Name_of_airline == dest.Name_of_airline
					&& nodeptr->Ticket_price == dest.Ticket_price && nodeptr->Date_of_travel == dest.Date_of_travel
					&& nodeptr->Total_Time == dest.Total_Time) {
					temp1 = 1;
				}
				nodeptr = nodeptr->next;
			}
			if (temp1 == 1)	// if dest is Already there
			{
				//cout << "Edge is Already Created\n\n";
				return;
			}
			else {
				CityNode* nodeptrtemp = CreateCity(dest.CityName, dest.Date_of_travel, dest.Flying_time,
					dest.Landing_time, dest.Ticket_price, dest.Total_Time, dest.Name_of_airline);
				nodeptrprev->next = nodeptrtemp;
				return;
			}
		}
		else       // if Src is Not present
		{
			Date d(0, 0, 0);
			CityNode* nodeptr = CreateCity(src, d, "\0", "\0", 0, 0, "\0");
			Array.push_back(nodeptr);
			TotalCities += 1;
			if (TotalCityStrings.find(src) == -1) {
				TotalCityStrings.push_back(src);
			}
			for (int i = 0; i < Array.Size(); i++) {
				if (Array[i]->CityName == src) {
					Array[i]->next = CreateCity(dest.CityName, dest.Date_of_travel, dest.Flying_time,
						dest.Landing_time, dest.Ticket_price, dest.Total_Time, dest.Name_of_airline);
					return;
				}
			}
		}
	}
	Vector<string> getTotalCityStrings() {
		return TotalCityStrings;
	}
	void getCitiesofSrc(string src, Vector<CityNode>& vec) {
		int index = 0;
		if (CheckifSrcisAvailable(src, index) == false) {
			cout << "There are no Flights From " << src << "\n\n";
			return;
		}
		CityNode* nodeptr = Array[index]->next;
		CityNode temp1;
		while (nodeptr != NULL) {
			temp1 = nodeptr;
			vec.push_back(temp1);
			nodeptr = nodeptr->next;
		}
	}
	void DisplayCitiesFromSrc(string src) {
		Vector<CityNode> veccity;
		getCitiesofSrc(src, veccity);
		if (veccity.isEmpty()) {
			return;
		}
		cout << "Flights from the city of " << src << " : \n\n";
		cout << "City Name \t Travel Date \t  Flying Time \t Landing Time \t  Ticket Price \t\tAirlines \t Total Time \n\n";
		for (int i = 0; i < veccity.Size(); i++) {
			veccity[i].DisplayCityInformation();
		}
	}
	int getTotalCities() {
		return TotalCities;
	}
	Vector<string> getHotels() {
		return Hotels;
	}
	Vector<int> getPrices() {
		return PricesofHotels;
	}
	void CreateGraph(string Flights, string hotels) {
		ifstream ifile(Flights);
		ifstream ifile1(hotels);

		string temp_city_src;
		string temp_city_dest;
		string temp_date;
		string flying;
		string landing;
		int temp_price, temp_time;
		string airline;
		while (ifile1 >> temp_city_src >> temp_price) {
			if (temp_city_src != "" && temp_price != 0) {
				string temptempstring = "";
				for (int i = 0; i < temp_city_src.length(); i++)
				{
					temptempstring += tolower(temp_city_src[i]);
				}
				temptempstring += '\0';
				Hotels.push_back(temptempstring);
				PricesofHotels.push_back(temp_price);
				temp_city_src = "";
				temp_price = 0;
			}
			if (ifile1.eof()) {
				break;
			}
		}
		ifile1.close();
		temp_city_src = "";
		temp_price = 0;
		while (ifile >> temp_city_src >> temp_city_dest >> temp_date >> flying >> landing >> temp_price >> airline)
		{
			/*if (!(ifile >> temp_city_src))
			{
				cout << "Something wrong in temp_city_src \n";
				break;
			}
			if (!(ifile >> temp_city_dest))
			{
				cout << "Something wrong in temp_city_dest \n";
				break;
			}
			if (!(ifile >> temp_date))
			{
				cout << "Something wrong in temp_date \n";
				break;
			}
			if (!(ifile >> flying))
			{
				cout << "Something wrong in flying \n";
				break;
			}
			if (!(ifile >> landing))
			{
				cout << "Something wrong in landing \n";
				break;
			}
			if (!(ifile >> temp_price))
			{
				cout << "Something wrong in temp_price \n";
				break;
			}
			if (!(ifile >> airline))
			{
				cout << "Something wrong in airline \n";
				break;
			}*/
			if (temp_city_src != "" && temp_city_dest != "" && temp_date != "" && flying != "" &&
				landing != "" && temp_price != 0 && airline != "") {
				stringstream geek(flying);
				stringstream geek1(landing);
				int starting_time, ending_time;
				geek >> starting_time;
				geek1 >> ending_time;
				if (starting_time > ending_time) {
					ending_time += 24;
				}
				temp_time = ending_time - starting_time;
				Date d(temp_date);
				string temptempstring = "";
				for (int i = 0; i < temp_city_src.length(); i++)
				{
					temptempstring += tolower(temp_city_src[i]);
				}
				temptempstring += '\0';
				string temptempstring1 = "";
				for (int i = 0; i < temp_city_dest.length(); i++)
				{
					temptempstring1 += tolower(temp_city_dest[i]);
				}
				temptempstring1 += '\0';
				CityNode dest(temptempstring1, d, flying, landing, temp_price, temp_time, airline);
				addEdge(temptempstring, dest);
				temp_city_dest = "";
				temp_city_src = "";
				temp_date = "";
				temp_price = 0;
				flying = "";
				landing = "";
				airline = "";
			}
			if (ifile.eof()) {
				break;
			}
		}
		ifile.close();
	}
	bool CheckifSrcisAvailable(string src, int& index) {
		for (int i = 0; i < Array.Size(); i++) {
			if (Array[i] != NULL && Array[i]->CityName == src) {
				index = i;
				return true;
			}
		}
		return false;
	}
	int indexof(const string& index) {
		for (int i = 0; i < TotalCities; i++) {
			if (Array[i]->CityName == index) {
				return i;
			}
		}
	}
	//int weightof(const int& index, const CityNode* nd)
	//{
	//	CityNode* curr = Array[index];
	//	Vector<int> vec;
	//	while (curr)
	//	{
	//		if (curr->CityName == nd->CityName)
	//		{
	//			vec.push_back(curr->Ticket_price);
	//		}
	//		curr = curr->next;
	//	}
	//	return vec.findMin();
	//}
	//int minDistance(const vector<int>& distance, const vector<bool>& S) const
	//{
	//	int minindex = 0;
	//	for (int i = 1; i < TotalCities; i++)
	//	{
	//		if ((distance[i] < distance[minindex]) && S[i] == false)
	//		{
	//			minindex = i;
	//		}
	//	}
	//	return minindex;
	//}
	//
	//void Dijkstra(const string& source, const string& dest) {
	//	vector<string> Vertex(TotalCities);
	//	Vector<CityNode> Parent(TotalCities);
	//	stack<CityNode> path;
	//	vector<bool> S(TotalCities);
	//	vector<int> distance(TotalCities);
	//	//stack<string> path;
	//	int counter = 0;
	//	Date d(0, 0, 0);
	//	CityNode tmpNode("\0", d, "\0", "\0", 0, 0, "\0");
	//	CityNode* curr;
	//	for (int i = 0; i < TotalCities; i++)
	//	{
	//		Vertex[i] = Array[i]->CityName;
	//		//Parent[i].init("\0","\0","\0","\0","\0",0,0);
	//		Parent.push_back(tmpNode);
	//		distance[i] = INT_MAX;
	//		S[i] = 0;
	//	}
	//	distance[TotalCityStrings.find(source)] = 0;
	//	counter++;
	//	while (counter <= TotalCities) {
	//		int u = minDistance(distance, S);
	//		S[u] = 1;
	//		if (Vertex[u] == dest)break;
	//		curr = Array[u];
	//		while (curr) {
	//			if (distance[u] + weightof(u, curr) < distance[TotalCityStrings.find(curr->CityName)])
	//			{
	//				distance[TotalCityStrings.find(curr->CityName)] = distance[u] + weightof(u, curr);
	//				tmpNode.init(curr->CityName, curr->Date_of_travel, curr->Flying_time, curr->Landing_time,
	//					curr->Name_of_airline, curr->Ticket_price, curr->Total_Time);
	//				Parent[TotalCityStrings.find(curr->CityName)] = tmpNode;
	//			}
	//			curr = curr->next;
	//		}
	//		counter++;
	//	}
	//	cout << "\nTotal Cost: " << distance[TotalCityStrings.find(dest)] << endl;
	//	
	//	/*path.push(Parent[indexof(dest)]);
	//	string dst = dest;
	//	do
	//	{
	//		tmpNode = Parent[indexof(dst)];
	//		path.push(tmpNode);
	//		dst = tmpNode.CityName;
	//	} while (path.top().CityName != source);
	//	cout << endl;
	//	while (!path.empty())
	//	{
	//		cout << path.top().CityName << " -> ";
	//		path.pop();
	//	}
	//	cout << "NULL\n";*/
	//}

	// Prints all paths from 's' to 'd' 
	void printAllPathsWithNode(string src, string dest) {
		Date d(0, 0, 0);
		string temptempstring = "";
		for (int i = 0; i < src.length(); i++)
		{
			temptempstring += tolower(src[i]);
		}
		temptempstring += '\0';
		CityNode src1(temptempstring, d, "\0", "\0", 0, 0, "\0");
		temptempstring = "";
		for (int i = 0; i < dest.length(); i++)
		{
			temptempstring += tolower(dest[i]);
		}
		temptempstring += '\0';
		CityNode dest1(temptempstring, d, "\0", "\0", 0, 0, "\0");
		// Mark all the vertices as not visited 
		bool* visited = new bool[TotalCities];

		// Create an array to store paths 
		CityNode* path = new CityNode[TotalCities];
		int path_index = 0; // Initialize path[] as empty 

		// Initialize all vertices as not visited 
		for (int i = 0; i < TotalCities; i++)
			visited[i] = false;
		// Call the recursive helper function to print all paths 
		printAllPathsUtil(src1, dest1, visited, path, path_index);
		delete[] visited;
		delete[] path;
	}

	// A recursive function to print all paths from 'u' to 'd'. 
	// visited[] keeps track of vertices in current path. 
	// path[] stores actual vertices and path_index is current 
	// index in path[] 
	void printAllPathsUtil(CityNode u, CityNode d, bool visited[], CityNode path[], int& path_index) {
		// Mark the current node and store it in path[] 
		visited[TotalCityStrings.find(u.CityName)] = true;
		path[path_index] = u;
		path_index++;

		// If current vertex is same as destination, then print 
		// current path[] 
		if (u == d) {
			bool timetravel = 0;
			for (int i = 1; i < path_index; i++) {
				if (path[i - 1].Date_of_travel > path[i].Date_of_travel) {
					timetravel = 1;
				}
			}
			if (!timetravel)
				AddEdgeinTempAllPathGraph(tempGraphAllPaths, path_index, path);
		}
		else // If current vertex is not destination 
		{
			// Recur for all the vertices adjacent to current vertex 
			CityNode* nodeptr = Array[TotalCityStrings.find(u.CityName)];
			while (nodeptr) {
				if (!visited[TotalCityStrings.find(nodeptr->CityName)]) {
					CityNode tempnode;
					tempnode.init(nodeptr->CityName, nodeptr->Date_of_travel, nodeptr->Flying_time, nodeptr->Landing_time,
						nodeptr->Name_of_airline, nodeptr->Ticket_price, nodeptr->Total_Time);
					printAllPathsUtil(tempnode, d, visited, path, path_index);
				}
				nodeptr = nodeptr->next;
			}
		}

		// Remove current vertex from path[] and mark it as unvisited 
		path_index--;
		visited[TotalCityStrings.find(u.CityName)] = false;
	}
	void DisplaytempAllPathGraph() {
		CityNode* nodeptr;
		for (int i = 0; i < tempGraphAllPaths.Size(); i++) {
			//cout << tempGraphAllPaths[i]->CityName << " -> ";
			tempGraphAllPaths[i]->DisplayCityInformation();
			nodeptr = tempGraphAllPaths[i]->next;
			while (nodeptr) {
				/*cout << nodeptr->CityName;
				if (nodeptr->next != NULL)
				{
					cout << " -> ";
				}*/
				nodeptr->DisplayCityInformation();
				nodeptr = nodeptr->next;
			}
			cout << endl;
		}
	}
	Vector<CityNode*> gettempallPathGraph() {
		return tempGraphAllPaths;
	}
	void AddEdgeinTempAllPathGraph(Vector<CityNode*>& vec, int path_index, CityNode path[]) {
		bool temp = false, temp1 = false;
		if (vec.isEmpty()) {
			CityNode* nodeptr = CreateCity(path[0].CityName, path[0].Date_of_travel, path[0].Flying_time, path[0].Landing_time, path[0].Ticket_price, path[0].Total_Time % 24, path[0].Name_of_airline);
			vec.push_back(nodeptr);
			CityNode* tempnode = vec[0];
			int sumofcost = 0;
			int sumofTime = 0;
			int i = 1;
			while (i < path_index) {
				tempnode->next = CreateCity(path[i].CityName, path[i].Date_of_travel, path[i].Flying_time, path[i].Landing_time, path[i].Ticket_price, path[i].Total_Time % 24, path[i].Name_of_airline);
				i++;
				sumofcost += tempnode->next->Ticket_price;
				sumofTime += tempnode->next->Total_Time;
				tempnode = tempnode->next;
			}
			vec[0]->Ticket_price = sumofcost;
			vec[0]->Total_Time = sumofTime;
			return;
		}
		else {
			CityNode* nodeptr = CreateCity(path[0].CityName, path[0].Date_of_travel, path[0].Flying_time, path[0].Landing_time, path[0].Ticket_price, path[0].Total_Time % 24, path[0].Name_of_airline);
			vec.push_back(nodeptr);
			CityNode* tempnode = vec[vec.Size() - 1];
			int i = 1;
			int sumofCost = 0;
			int sumofTime = 0;
			while (i < path_index) {
				tempnode->next = CreateCity(path[i].CityName, path[i].Date_of_travel, path[i].Flying_time, path[i].Landing_time, path[i].Ticket_price, path[i].Total_Time % 24, path[i].Name_of_airline);
				i++;
				sumofCost += tempnode->next->Ticket_price;
				sumofTime += tempnode->next->Total_Time;
				tempnode = tempnode->next;
			}
			vec[vec.Size() - 1]->Ticket_price = sumofCost;
			vec[vec.Size() - 1]->Total_Time = sumofTime;
			return;
		}
	}
};

class PQueue {
	int cap, size;
	Vector<CityNode*> arr;
public:
	PQueue(const int& capacity, Vector<CityNode*> allNodes, Graph& gr) :cap(capacity), size(0) {
		//arr = allNodes;
		CityNode* curr, *prev;
		bool timetravel = 0;

		for (int i = 0; i < allNodes.Size(); i++) {
			timetravel = 0;
			curr = allNodes[i]->next;
			prev = curr;
			curr = curr->next;
			while (curr) {
				//Parsing time here
				stringstream objpr0(prev->Flying_time);
				stringstream objpr1(prev->Landing_time);
				stringstream objcrf(curr->Flying_time);
				int prf, prl, crf;
				objpr0 >> prf;
				objpr1 >> prl;
				objcrf >> crf;
				if (prev->Date_of_travel == curr->Date_of_travel) {
					if ((prl >= crf) || (prf > prl)) {
						timetravel = 1;
						break;
					}
					if (abs(crf - prl) > 12) {
						allNodes[i]->Ticket_price += gr.getPrices()[gr.getHotels().find(prev->CityName)];
						allNodes[i]->Total_Time += abs(crf - prl);
						allNodes[i]->transitTime += abs(crf - prl);
					}
					else {
						allNodes[i]->Total_Time += abs(crf - prl);
						allNodes[i]->transitTime += abs(crf - prl);
					}
				}
				else if ((curr->Date_of_travel.getDay() - prev->Date_of_travel.getDay()) == 1) {
					if (prl < prf) {
						allNodes[i]->Total_Time += (crf - prl);
						allNodes[i]->transitTime += (crf - prl);
						if (crf - prl > 12) {
							allNodes[i]->Ticket_price += (((crf - prl) / 24) * gr.getPrices()[gr.getHotels().find(prev->CityName)]);
						}
					}
					else {
						int formula = 24 - prl + crf;
						allNodes[i]->Total_Time += formula;
						allNodes[i]->transitTime += formula;

						if (formula > 12) {
							allNodes[i]->Ticket_price += (((formula) / 24) * gr.getPrices()[gr.getHotels().find(prev->CityName)]);
						}
					}
				}
				else if (prev->Date_of_travel < curr->Date_of_travel) {
					if (prf < prl) {
						int formula = 24 - prl;
						formula += (curr->Date_of_travel.getDay() - (prev->Date_of_travel.getDay() + 1)) * 24;
						formula += crf;
						allNodes[i]->Total_Time += formula;
						allNodes[i]->transitTime += formula;

						if (formula > 12) {
							allNodes[i]->Ticket_price += (((formula) / 24) * gr.getPrices()[gr.getHotels().find(prev->CityName)]);
						}
					}
					else {
						int formula = 24 - prl;
						int tmpdt = prev->Date_of_travel.getDay() + 1;
						if (curr->Date_of_travel.getDay() - tmpdt == 1) {
							formula += crf;
						}
						else {
							tmpdt += 1;
							formula += (curr->Date_of_travel.getDay() - tmpdt) * 24;
							formula += crf;
						}
						allNodes[i]->Total_Time += formula;
						allNodes[i]->transitTime += formula;

						if (formula > 12) {
							allNodes[i]->Ticket_price += (((formula) / 24) * gr.getPrices()[gr.getHotels().find(prev->CityName)]);
						}
					}
				}
				prev = curr;
				curr = curr->next;
			}
			if (!timetravel) {
				arr.push_back(allNodes[i]);
				size++;
			}
		}
		for (int i = 0; i < size - 1; i++) {
			for (int j = i; j < size; j++) {
				if (arr[i]->Ticket_price > arr[j]->Ticket_price) {
					auto tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}
	int Size()const { return size; }

	Vector<CityNode*> costEffective(const int& howmany) {
		Vector<CityNode*> tmp;
		for (int j = 0; j < size && j < howmany; j++) {
			tmp.push_back(arr[j]);
		}
		return tmp;
	}
	void costEffective(Vector<CityNode*>& allnodes, const int& howmany) {
		CityNode* tmp;
		for (int i = 0; i < size - 1; i++) {
			for (int j = i; j < size; j++) {
				if (arr[i]->Ticket_price > arr[j]->Ticket_price) {
					tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}
	Vector<CityNode*> priorityAirline(const string& airline, bool& exists) {
		Vector<CityNode*> tmp;
		bool istrue;
		CityNode* curr;
		for (int j = 0; j < size; j++) {
			curr = arr[j]->next;
			istrue = 0;
			while (curr) {
				if (curr->Name_of_airline == airline) {
					istrue = 1;
					break;
				}
				curr = curr->next;
			}
			if (istrue)
				tmp.push_back(arr[j]);
		}
		if (tmp.Size() == 0) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> datePriority(Date date, bool& exists) {
		Vector<CityNode*> tmp;
		for (int i = 0; i < size; i++) {
			if (arr[i]->next->Date_of_travel == date)
				tmp.push_back(arr[i]);
		}
		date++;
		for (int i = 0; i < size; i++) {
			if (arr[i]->next->Date_of_travel == date)
				tmp.push_back(arr[i]);
		}
		date--;
		date--;
		for (int i = 0; i < size; i++) {
			if (arr[i]->next->Date_of_travel == date)
				tmp.push_back(arr[i]);
		}
		if (tmp.Size() == 0) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> transitLocation(const string& cityName, bool& exists) {
		Vector<CityNode*> tmp;
		bool istrue;
		CityNode* curr;
		for (int j = 0; j < size; j++) {
			curr = arr[j]->next;
			istrue = 0;
			while (curr) {
				if (curr->CityName == cityName) {
					istrue = 1;
					break;
				}
				curr = curr->next;
			}
			if (istrue)
				tmp.push_back(arr[j]);
		}
		if (tmp.Size() == 0) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> minTimePriority() {
		Vector<CityNode*> tmp = arr;
		CityNode* curr;
		for (int i = 0; i < size - 1; i++) {
			for (int j = i; j < size; j++) {
				if (tmp[i]->Total_Time > tmp[j]->Total_Time) {
					curr = tmp[i];
					tmp[i] = tmp[j];
					tmp[j] = curr;
				}
			}
		}
		arr = tmp;
		size = tmp.Size();
		return tmp;
	}
	Vector<CityNode*> specificTransitTime(const int& min, const int& max, bool& exists) {
		Vector<CityNode*> tmp;
		CityNode* curr;
		for (int i = 0; i < size; i++) {
			if (arr[i]->transitTime >= min && arr[i]->transitTime <= max) {
				tmp.push_back(arr[i]);
			}
		}
		if (!tmp.Size()) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> directFlight(bool& exists) {
		Vector<CityNode*> tmp;
		CityNode* curr;
		for (int i = 0; i < size; i++) {
			if (!arr[i]->next->next) {
				tmp.push_back(arr[i]);
			}
		}
		if (!tmp.Size()) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> connectingFlight(bool& exists) {
		Vector<CityNode*> tmp;
		CityNode* curr;
		for (int i = 0; i < size; i++) {
			if (arr[i]->next->next) {
				tmp.push_back(arr[i]);
			}
		}
		if (!tmp.Size()) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}
	Vector<CityNode*> costRange(const int& range, bool& exists) {
		Vector<CityNode*> tmp;
		CityNode* curr;
		for (int i = 0; i < size; i++) {
			if (arr[i]->Ticket_price <= range) {
				tmp.push_back(arr[i]);
			}
		}
		if (!tmp.Size()) {
			exists = 1;
			return arr;
		}
		arr = tmp;
		size = tmp.Size();
		exists = 0;
		return tmp;
	}

};
//int main()
//{
//	Graph zg;
//	g.CreateGraph("Flights.txt", "HotelCharges_perday.txt");
//
//	string src = "Islamabad";
//	string dest = "Paris";
//	g.printAllPathsWithNode(src, dest);
//	///*Vector<CityNode*> veccities = g.gettempallPathGraph();
//	//cout << "Size : " << veccities.Size() << endl;*/
//	//g.DisplaytempAllPathGraph();
//	PQueue pq(g.gettempallPathGraph().Size(), g.gettempallPathGraph(), g);
//	Vector<CityNode*> tmp = pq.costEffective(100);
//	Date dt(3, 12, 2019);
//	bool changed = 0;
//	/*tmp = pq.timePriority(dt);
//
//	tmp = pq.priorityAirline("ANA");
//	cout << "-----------------------------\n";*/
//	tmp = pq.priorityAirline("ANA", changed);
//
//	tmp = pq.datePriority(dt, changed);
//	CityNode* curr;
//	for (int i = 0; i < tmp.Size(); i++) {
//		cout << tmp[i]->transitTime << "\n";
//		tmp[i]->DisplayCityInformation();
//		curr = tmp[i]->next;
//		while (curr) {
//			curr->DisplayCityInformation();
//			curr = curr->next;
//		}
//		cout << endl;
//	}
//
//}