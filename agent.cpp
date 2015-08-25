#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<functional>
using namespace std;
queue<int> path;
stack<int> spath;

class Graph{
public:
	string name;
	int index;
	bool operator<(const Graph &p) const;
	int parent;
	int cost;
	int level;

};
bool Graph::operator<(const Graph & p)const
{
//	cout <<endl<< this->name <<" "<< this->cost << ">" << p.name <<"  "<< p.cost << endl;
	if (this->cost > p.cost)
		return true;
	else if (this->cost < p.cost)
		return false;
	else if (this->name.compare(p.name) > 0)
		return true;
	else
		return false;
}
struct dfsprio : public std::binary_function<Graph, Graph, bool>
{
	bool operator()(const Graph lhs, const Graph rhs) const
	{
		if (lhs.level < rhs.level)
		{
			return true;
		}
		else if (lhs.level > rhs.level)
		{
			return false;
		}
		else
		{
			/*if (lhs.cost > rhs.cost)
				return true;
			else if (lhs.cost < rhs.cost)
				return false;
			else*/
			if (lhs.name.compare(rhs.name) > 0)
				return true;
			else
				return false;
		}
	}
};
struct bfsprio : public std::binary_function<Graph, Graph, bool>
{
	bool operator()(const Graph lhs, const Graph rhs) const
	{
		if (lhs.level > rhs.level)
		{
			return true;
		}
		else if (lhs.level < rhs.level)
		{
			return false;
		}
		else
		{
			/*if (lhs.cost > rhs.cost)
				return true;
			else if (lhs.cost < rhs.cost)
				return false;
			else*/ 
			if (lhs.name.compare(rhs.name) > 0)
				return true;
			else
				return false;
		}
	}
};
void updatedfs(priority_queue<Graph, std::vector<Graph>, dfsprio> *pque,Graph Nodes)
{
	priority_queue<Graph, std::vector<Graph>, dfsprio> tempque;
	while (!pque->empty())
	{
		Graph temp = pque->top();
		tempque.push(pque->top());
		pque->pop();
	}
	while (!tempque.empty())
	{
		if (tempque.top().index == Nodes.index)
		{
			Graph temp = tempque.top();
			temp.cost = Nodes.cost;
			temp.parent = Nodes.parent;
			temp.level = Nodes.level;
			pque->push(temp);
			tempque.pop();
		}
		else
		{
			Graph temp = tempque.top();
			pque->push(tempque.top());
			tempque.pop();
		}
	}
}
void updatebfs(priority_queue<Graph, std::vector<Graph>, bfsprio> *pque, Graph Nodes)
{
	priority_queue<Graph, std::vector<Graph>, bfsprio> tempque;
	while (!pque->empty())
	{
		Graph temp = pque->top();
		tempque.push(pque->top());
		pque->pop();
	}
	while (!tempque.empty())
	{
		if (tempque.top().index == Nodes.index)
		{
			Graph temp = tempque.top();
			temp.cost = Nodes.cost;
			temp.parent = Nodes.parent;
			temp.level = Nodes.level;
			pque->push(temp);
			tempque.pop();
		}
		else
		{
			Graph temp = tempque.top();
			pque->push(tempque.top());
			tempque.pop();
		}
	}
}
void updateucs(priority_queue<Graph> *pque, Graph Nodes)
{
	priority_queue<Graph, std::vector<Graph>, bfsprio> tempque;
	while (!pque->empty())
	{
		Graph temp = pque->top();
		tempque.push(pque->top());
		pque->pop();
	}
	while (!tempque.empty())
	{
		if (tempque.top().index == Nodes.index)
		{
			Graph temp = tempque.top();
			temp.cost = Nodes.cost;
			temp.parent = Nodes.parent;
			temp.level = Nodes.level;
			pque->push(temp);
			tempque.pop();
		}
		else
		{
			Graph temp = tempque.top();
			pque->push(tempque.top());
			tempque.pop();
		}
	}
}
void path_finder(int source, int destination, Graph * Nodes)
{
	int ptr = destination;
	while(ptr != source)
	{
		spath.push(ptr);
		ptr = Nodes[ptr].parent;
	}
	spath.push(ptr);
}
void inputOrder(Graph *Nodes, int node_count, vector<vector<int> > vec, vector<vector<int> > &ovec)
{
	priority_queue<Graph> names;
	for (int i = 0; i < node_count; i++)
		names.push(Nodes[i]);
	for (int i = 0; i < node_count; i++)
	{
//		cout << names.top().name << names.top().index<< endl;
		copy(vec[names.top().index].begin(), vec[names.top().index].end(), ovec[i].begin());
		names.pop();
	}

}
void display(int node_count, Graph * Nodes, vector<vector<int> > ovec)
{
	std::ofstream out("output.txt");
		/*for (int i = 0; i < node_count; i++)
		{

		for (int j = 0; j < node_count; j++)
		{
		out << a[i][j]<<"\t";
		}
		out << endl;
		}

		for (int i = 0; i < node_count; i++)
		out << i << " -> " << Nodes[i].name << endl;*/
		out << Nodes[path.front()].name;
		path.pop();
		while (!path.empty())
		{
			out << "-" << Nodes[path.front()].name;
			path.pop();
		}
		out << std::endl;
		/*Display shortes path*/
		out << Nodes[spath.top()].name;

		int cost = Nodes[spath.top()].cost;
		spath.pop();
		while (!spath.empty())
		{
			out << "-" << Nodes[spath.top()].name;
			cost = Nodes[spath.top()].cost;
			spath.pop();
		}
		out << endl << cost;
	out.close();
}
void displayerr(int node_count, Graph * Nodes, vector<vector<int> > ovec)
{
	std::ofstream out("output.txt");
	/*for (int i = 0; i < node_count; i++)
	{

	for (int j = 0; j < node_count; j++)
	{
	out << a[i][j]<<"\t";
	}
	out << endl;
	}

	for (int i = 0; i < node_count; i++)
	out << i << " -> " << Nodes[i].name << endl;*/
	out << Nodes[path.front()].name;
	path.pop();
	while (!path.empty())
	{
		out << "-" << Nodes[path.front()].name;
		path.pop();
	}
	out << std::endl;
	out << "NoPathAvailable";
	out.close();
}
bool bfs(int source, int destination, int node_count, Graph *Nodes, vector<vector<int> > ovec)
{
	vector<bool> visited(node_count,false);
	vector<bool> frontier(node_count, false);
	priority_queue<Graph, std::vector<Graph>, bfsprio> pque;
	Nodes[source].cost = 0;
	Nodes[source].level = 0;
	visited[source] = true;
	pque.push(Nodes[source]);
	while (!pque.empty())
	{
		int v = pque.top().index;
		pque.pop();
		frontier[v] = false;
		path.push(v);
		if (v == destination)
			return true;
		for (int i = 0; i < node_count; i++)
		{
			if (ovec[v][i] != 0)
			{
				if (visited[i] && frontier[i] && Nodes[i].level > (Nodes[v].level + 1))
				{
					Nodes[i].parent = v;
					Nodes[i].cost = Nodes[v].cost + ovec[v][i];
					Nodes[i].level = Nodes[v].level + 1;
					updatebfs(&pque, Nodes[i]);
				}
				else if (!visited[i])
				{
					visited[i] = true;
					frontier[i] = true;
					Nodes[i].parent = v;
					Nodes[i].cost = Nodes[v].cost + ovec[v][i];
					Nodes[i].level = Nodes[v].level + 1;
					pque.push(Nodes[i]);
				}
			}
		}
	}
	return false;
}
bool dfs(int source, int destination, int node_count, Graph * Nodes, vector<vector<int> > ovec)
{
	vector<bool> visited(node_count, false);
	vector<bool> frontier(node_count, false);
	priority_queue<Graph, std::vector<Graph>, dfsprio> pque;
	Nodes[source].cost = 0;
	Nodes[source].level = 0;
	frontier[source] = true;
	visited[source] = true;
	pque.push(Nodes[source]);
	while (!pque.empty()) 
	{
		int v = pque.top().index;
		pque.pop();
		frontier[v] = false;
		path.push(v);
		if (v == destination)
			return true;
		for (int i = 0; i < node_count; i++)
		{
			if (ovec[v][i] != 0)
			{
				if (visited[i] && frontier[i] && Nodes[i].level > (Nodes[v].level + 1))
				{
					Nodes[i].parent = v;
					Nodes[i].cost = Nodes[v].cost + ovec[v][i];
					Nodes[i].level = Nodes[v].level + 1;
					updatedfs(&pque,Nodes[i]);
				}
				else if (!visited[i])
				{
					Nodes[i].parent = v;
					Nodes[i].cost = Nodes[v].cost + ovec[v][i];
					Nodes[i].level = Nodes[v].level + 1;
					visited[i] = true;
					frontier[i] = true;
					pque.push(Nodes[i]);
				}
			}
		}
	}
	return false;
}
bool uniform_cost_search(int source,int destination,int node_count,Graph *Nodes,vector<vector<int> > ovec)
{
	vector<bool> visited(node_count, false);
	vector<bool> frontier(node_count, false);
	priority_queue<Graph> pque;
	pque.push(Nodes[source]);
	frontier[source] = true;
	visited[source] = true;
	while (!pque.empty())
	{
		Graph tnode = pque.top();
		pque.pop();
		path.push(tnode.index);
		frontier[tnode.index] = false;
		if (tnode.index == destination)
			return true;
		visited[tnode.index] = true;
		for (int i = 0; i < node_count; i++)
		{
			if (ovec[tnode.index][i] && !visited[i])
			{
				int tcost = Nodes[tnode.index].cost+ovec[tnode.index][i];
				if (!frontier[i])
				{
					frontier[i] = true;
					Nodes[i].cost = tcost;
					Nodes[i].parent = tnode.index;
					pque.push(Nodes[i]);
				}
				else if (tcost < Nodes[i].cost)
				{
					Nodes[i].cost = tcost;
					Nodes[i].parent = tnode.index;
					updateucs(&pque,Nodes[i]);
				}
			}
		}
	}
	return false;
}
void source_destination(int *sint, int *dint, int node_count,Graph *Nodes,string source,string destination)
{
	for (int i = 0; i < node_count; i++)
	{

		if (!source.compare(Nodes[i].name))
			*sint = i;
		else if (!destination.compare(Nodes[i].name))
			*dint = i;
	}
}
int main(int argc, char const * argv[])
{ 
	int task,node_count,sint=-1,dint=-1;
	std::string source, destination,temp;
	std::ifstream in("input.txt");

	in >> task;
	in >> source;
	in >> destination;
	in >> node_count;
	Graph *Nodes = new Graph[node_count];
	for (int i = 0; i< node_count; i++)
	{
		in >> temp;
		Nodes[i].name = temp;
		Nodes[i].index = i;
		Nodes[i].cost = 0;
		Nodes[i].parent = NULL;
	}
	vector<vector<int> > vec ( node_count, vector<int>(node_count) ) ;
	vector<vector<int> > ovec(node_count, vector<int>(node_count));
	for (int i = 0; i < node_count; i++)
		for(int j = 0; j < node_count;j++)
		{
		in >> vec[i][j];
		}
	 source_destination(&sint,&dint,node_count,Nodes,source,destination);

	 if (source == destination)
	 {
		 std::ofstream out("output.txt");
		 out << Nodes[sint].name<<endl;
		 out << Nodes[sint].name<<endl;
		 out << Nodes[sint].cost;
		 out.close();
		 return 0;
	 }
	 bool result;
	 switch (task)
	 {
	 case 1:
		 result = bfs(sint, dint, node_count, Nodes, vec);
		 break;
	 case 2:
		 result = dfs(sint, dint, node_count, Nodes, vec);
		 break;
	 case 3:
		 result = uniform_cost_search(sint, dint, node_count, Nodes, vec);
		 break;
	 default:
		 break;
	 }
	 if (result)
	 {
		 path_finder(sint, dint, Nodes);
		 display(node_count, Nodes, vec);
	 }
	  else
	 {
		 displayerr(node_count, Nodes, vec);
//		 out << "NoPathAvailable";
	 }
	 in.close();
	return 0;
}
