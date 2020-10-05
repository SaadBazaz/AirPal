Report of Data Structures Project
Classes Used:
Vector Class:
We have made a template vector class with a few additional functions. This vector class object is used instead of adjacency list array in the graph class which was static. Now we can add as many cities in the graph as we like.
Date Class:
This class is used for the calculation of date related queries of the user. This class has all the relational functionalities in it. This class object is used in the vertex of the graph which is a city.
CityNode Class:
This is the vertex of the graph class. This has members to store information like Name of City, Date of Travel, Flying time, Landing Time, Transit time, Ticket Price, Total price etc. This class also contain assignment operator overloading.
Graph Class:
This is where the actual graph is made. This has members like Total cities, a vector of type CityNode pointer called Array, another vector of type CityNode pointer called tempallPathGraph which contains the subgraph when the user inputs the source and destination this subgraph is populated, a vector of type string called TotalCitiesStrings which contains the names of the all the cities, another vector of type integer called Prices which contains the hotel charges per day of cities stored in the TotalCitiesStrings in the same order, and name of airline.
Functions of Graph Class:   
1.	CreateGraph(string flights , string hotels)
This function takes the address of the files that needs to be read to populate the main graph. Firstly, the hotels file is opened and read and the vector Prices is filled. Secondly, the flights file is opened and read and the main graph is made here. A line is read from the file and all the information is separately send to another function called AddEgde.
2.	AddEdge(string src , Date date , string flying , string landing , int price , int totaltime  , string airline)
This functions first checks if the source is available or not in the graph if it’s not available then firstly source node is pushed into the vector and then the destination node is attached to this source node head of the linked list. If the source is present it then checks if the destination node is present or not in the linked list if not then it creates a destination node and attaches to the linked list of the source node. In terms of Time Complexity, the checking of the source node in the vector array is linear so it takes O(V) time where V being the number of vertices in the Graph already present. For checking if the destination node is present or not. It checks first if the source is present and then checks if the linked list containing the source node as head contains the destination node which takes O(V + (Edges of that vertex)).
3.	DeleteGraph(Vector<CityNode*> vec)
This function deletes the given graph and also deletes the vector array to free the memory. This function is used in the Destructor of Graph Class.
4.	PrintallPathwithNode(string src , string dest)
This Function Creates the subgraph mentioned in the Graph Class members explanation. This functions calls another function which recursively calls itself and if a path is made from src to dest, it is added to this subgraph. In terms of Time Complexity, it has time complexity of a little over than O(|V|^3). It depends on the total number of edges in the graph as well. 

PQueue Class
This is modified version of priority queue data structure. We used array based implementation. The reason to do so is because we have access to all nodes in advance.
There is no new node created at run time after priority queue is called.
Functions:
1.	PQueue(const int& capacity, Vector<CityNode*> allNodes, Graph& gr)
This constructor receive vector of CityNodes, it’s capacity and a graph. It traverse all nodes and discard those which points to nodes with previous day flights. It also add transit time and costs where it needs to be addes as asked in project statement. At last it sorts all nodes in ascending order according to their flight cost using bubble sort. Overall complexity of this function is O(|N|^2), where N is total number of nodes

2.	Vector<CityNode*> costEffective(const int& N)
As nodes are sorted in ascending order in constructor. This function just return first N nodes, where N is number of nodes the user is asked for.

3.	Vector<CityNode*> priorityAirline(const string& airline, bool& exists)
This function return all routes which uses the specified airline. If routes with that specific airline doesn’t exist, then it’ll return all routes, and ‘exists’ indicate whether routes with specific airline are found or not.

4.	Vector<CityNode*> datePriority(Date date, bool& exists)
datePriority return routes on specific dates asked by user. If no flights were found on that date it’ll return vector of flights one day prior to specified date and one day after specified date.

5.	Vector<CityNode*> transitLocation(const string& cityName, bool& exists)
if user wants to stay on specific city. This function will return all flight’s routes with that specific city.
6.	Vector<CityNode*> minTimePriority( )
Calling this function will sort the list on basis of flight’s total time including transit time. As this function uses bubble sort it’s complexity is O(V), where V is total number of nodes.

7.	Vector<CityNode*> specificTransitTime(const int& min, const int& max, bool& exists)
This function will search the list of all possible flight’s routes which have desired transit time. To minimize the transit time, this function can be used by  passing value 0 and upper max desired value.

8.	Vector<CityNode*> directFlight(bool& exists)
This function will search for direct flights between source and destination. If there is no direct flight then  it’ll return all possible indirect routes. Complexity is O( R ). where R is total routes between source and destination.

9.	Vector<CityNode*> connectingFlight(bool& exists)
Return all indirect flights for given source and destination.Complexity is O( R ). where R is total routes between source and destination.

10.	Vector<CityNode*> costRange(const int& range, bool& exists)
When user wants to search flights in specific cost range, i.e budget flights. This function will return all flights in that range. As this function has to traverse all routes at least once. It’s complexity is O( R ), where R is total number of flight routes.

UI Construction:
Queue Class:
We have made a template queue class with a few additional functions. This queue class object is used for many booking related functions (i.e. tickets will be placed in a list according to a Queue, because the flights will leave in that order).
Trie:
We have constructed a Trie with Spellchecking using the Levenshtein Distance Algorithm (This algorithm is an advanced spellcheck algorithm). The Trie checks the user queries of Source and Distance and is useful in making sure the spellings are correct and accurate.
QT:
QT (pronounced “Cute”) is a library of useful UI-related functions and objects. We have used this library to visualize our work and bring it to life. Within it, however, we have made sure to use all concepts of Data Structures to make the work as efficient and as presentable as possible.

