// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 7 finding shade 
//  create a graph based on input 
//   create a function to traverse 
//   the graph in a "dfs like" manner 
//   output path found in graph 
#include <iostream>
#include <string>
#include <unordered_map> // making graph 
#include <list> // build adjancy list 
#include <stack> // output path 

//struct definition 
struct vertexType{
	std::string destination;
	int length;
};

//----FUNCTION DEFINITIONS----
//dfs ( start node , end node , stamina , adjacency list, visited , predecessor )
bool dfs(std::string, std::string, int , std::unordered_map<std::string, std::list<vertexType>>,
		std::unordered_map<std::string, bool>, std::unordered_map<std::string, std::string>&);
//buildAdj ( adjList )
void buildAdj(std::unordered_map<std::string, std::list<vertexType>>  &);
//showPath ( start node , end node, predecessor )
void showPath(std::string, std::string, std::unordered_map<std::string, std::string> );


int main()
{
	//get start node, end node, and stamina
	std::string start, end;
	int stamina; 
	std::cin >> start;
	std::cin >> end;
	std::cin >> stamina;
	//make maps for graph 
	std::unordered_map<std::string, std::list<vertexType> > adjList;
	std::unordered_map<std::string, std::string> predecessor; 
	std::unordered_map<std::string, bool> visited;
	//build adjacency list 
	buildAdj(adjList);
	// if else for if dfs finds a path 
	if(dfs(start, end, stamina, adjList, visited, predecessor))
		{std::cout << "Time to cool off!\n";showPath(start,end,predecessor);}
	else 
		std::cout << "This is going to be a long summer...\n";
	return 0;
}


//**returns true if valid stamina path found**
bool dfs(std::string curr, std::string end, int stamina, std::unordered_map<std::string, std::list<vertexType> > adjList,
		std::unordered_map<std::string, bool> visited, std::unordered_map<std::string, std::string> & predecessor)
{
	visited[curr] = true;
	if(curr == end && stamina > 0)
		return true;//valid path found 
	for(auto daisy = adjList[curr].begin(); daisy != adjList[curr].end(); ++daisy)
		if(!visited[daisy->destination] && (stamina - daisy->length > 0)) //second condtion narrows our search
		{
			stamina -= daisy->length; 
			predecessor[daisy->destination] = curr; 
			if (dfs(daisy->destination, end, stamina, adjList, visited, predecessor))
				return true;
			stamina += daisy->length;
		}
	return false;
}

//builds adjacency list from input 
void buildAdj(std::unordered_map<std::string, std::list<vertexType>> & adjList)
{
	std::string temp; 
	int count = 0;
	std::string from, to;
	int distance;
	while(std::cin >> temp)
	{
		count++;
		if(count == 1)
			from = temp;
		if(count == 2)
			to = temp;
		if(count == 3)
		{
			distance = stoi(temp);
			adjList[from].push_back({to, distance});
			count = 0;
		}
	}
	return;
}

//using predecessor array output path from start node to end node 
void showPath(std::string s , std::string e,std::unordered_map<std::string, std::string> graph)
{
	std::stack<std::string> path;
	std::string node = e;
	while(node != s)
	{
		path.push(node);
		node = graph[node];
	}
	path.push(node);
	std::cout << "Path: ";
	while(!path.empty())
	{
		std::cout << path.top() << " ";
		path.pop();
	}
	std::cout << std::endl;
	return;
}