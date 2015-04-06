/*
This is simple version of application. Many of OOP concpts , exceptions ,  copy constructors , abstraction , List Nodes , inline functions , multi goals in tree are removed :)
*/


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class BFSQueue;
class UCSQueue;
class LinkedList;

class Node
{
	friend class BFSQueue;
	friend class UCSQueue;
	friend class LinkedList;
public:
	Node()
	{

	}
	Node(int _id ,char _state, int _depth, int _cost, Node * _parent)
	{
		id = _id;
		state = _state;
		depth = _depth;
		g = _cost;
		parent = _parent;
	}
	int getId()
	{
		return id;
	}
	char getState()
	{
		return state;
	}
	int getDepth()
	{
		return depth;
	}
	int getG()
	{
		return g;
	}
	Node * getParent()
	{
		return parent;
	}
	Node * getNext()
	{
		return next;
	}

	void setId(int val)
	{
		id = val;
	}
	void setDepth(int val)
	{
		depth = val;
	}
	void setG(int val)
	{
		g = val;
	}
	void setNext(Node * val)
	{
		next = val;
	}


private:
	int id;
	char state;
	int depth;
	int g;
	Node * parent;
	Node * next;
};

class BFSQueue
{
public:
	BFSQueue()
	{
		start = NULL;
	}
	bool isEmpty()
	{
		if (start == NULL)
			return true;
		return false;
	}
	Node remove()
	{
		if (isEmpty())
		{
			cout << "Error";
		}

		Node result = *start;

		Node * temp = start;
		start = temp->getNext();
		delete temp;

		return result;

	}
	void insert(Node val)
	{
		if (isEmpty() || val.getDepth() < start->getDepth())
		{
			Node * temp = start;
			start = new Node;
			start->next = temp;
			start->depth = val.depth;
			start->g = val.g;
			start->parent = val.parent;
			start->state = val.state;
			start->id = val.getId();
		}
		else
		{
			Node * p = start;
			while (p->next != NULL && p->next->getDepth() < val.getDepth())
				p = p->next;

			Node * temp = p->next;

			p->next = new Node;
			p = p->next;
			p->next = temp;
			p->depth = val.depth;
			p->g = val.g;
			p->parent = val.parent;
			p->state = val.state;
			p->id = val.id;

		}
	}



private:
	Node * start;

};


class UCSQueue
{
public:
	UCSQueue()
	{
		start = NULL;
	}
	bool isEmpty()
	{
		if (start == NULL)
			return true;
		return false;
	}
	Node remove()
	{
		if (isEmpty())
		{
			cout << "Error";
		}

		Node result = *start;

		Node * temp = start;
		start = temp->getNext();
		delete temp;

		return result;

	}
	void insert(Node val)
	{
		if (isEmpty() || val.getG() < start->getG())
		{
			Node * temp = start;
			start = new Node;
			start->next = temp;
			start->depth = val.depth;
			start->g = val.g;
			start->parent = val.parent;
			start->state = val.state;
			start->id = val.id;
		}
		else
		{
			Node * p = start;
			while (p->next != NULL && p->next->getDepth() < val.getDepth())
				p = p->next;

			Node * temp = p->next;

			p->next = new Node;
			p = p->next;
			p->next = temp;
			p->depth = val.depth;
			p->g = val.g;
			p->parent = val.parent;
			p->state = val.state;
			p->id = val.getId();

		}
	}


private:
	Node * start;

};



class LinkedList
{
public:
	LinkedList()
	{
		start = NULL;
		last = NULL;
	}

	bool isEmpty()
	{
		if (start == NULL)
			return true;
		return false;
	}

	Node * getLast()
	{
		return last;
	}

	Node * getStart()
	{
		return start;
	}


	Node * addToEnd(Node val)
	{
		if (isEmpty())
		{
			Node * temp = start;
			start = new Node;
			start->next = temp;
			start->depth = val.depth;
			start->g = val.g;
			start->parent = val.parent;
			start->state = val.state;

			last = start;
			return last;
		}
		last->next = new Node;
		last = last->next;
		last->depth = val.depth;
		last->g = val.g;
		last->parent = val.parent;
		last->state = val.state;
		last->next = NULL;
		return last;

	}


private:
	Node * start;
	Node * last;

};


class Tree
{
public:
	Tree(int ** g, char * _states , int n , int initState, int _goal)
	{
		matrix = new int *[n];
		states = new char[n];
		for (int i = 0; i < n; i++)
		{
			states[i] = _states[i];
			matrix[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = g[i][j];
			}//for j
		}




		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << g[i][j] << "  ";
			}
			cout << endl;
		}


		root = makeNode(initState,states[initState], 0, 0, NULL);
		goal = _goal;
		len = n;

	}
	Node getRoot()
	{
		return root;
	}

	int ** getMatrix()
	{
		return matrix;
	}

	LinkedList getExpandList()
	{
		return expandList;
	}



	bool isGoal(Node node)
	{
		if(node.getId() == goal)
			return true;
		return false;
	}

	bool BFS()
	{
		bfsFringe = BFSQueue();
		expandList = LinkedList();

		bfsFringe.insert(root);

		Node temp;
		while (!bfsFringe.isEmpty())
		{
			temp = bfsFringe.remove();
			if (isGoal(temp))
			{
				expandList.addToEnd(temp);

				return true;
			}
			bfsExpand(temp);
		}
		return false;

	}

	void bfsExpand(Node node)
	{
		//cout << "Expanded " << node.getState()<<"["<<node.getId()<<"]" << "\n";
		Node * prnt = expandList.addToEnd(node);
		Node temp;
		int cost;
		for (int i = 0; i<len; i++)
		{
			cost = matrix[node.getId()][i];
			//cout << "cost " << node.getState() << " -> " << states[i]<<"["<<i<<"]" << " = " << cost << endl;
			if (cost != 0)
			{
				temp = makeNode(i, states[i], cost + node.getG(), node.getDepth() + 1, prnt);
				bfsFringe.insert(temp);
			}//if != 0
		}//for i
	}


private:
	Node root;
	int ** matrix;
	char * states;
	int len;
	BFSQueue bfsFringe;
	UCSQueue ucsFringe;
	LinkedList expandList;
	int goal;
	Node makeNode(int id , char state, int cost, int depth, Node * parent)
	{
		Node result(id , state, depth, cost, parent);
		return result;
	}


};

int** getData(int &count)
{
	ifstream inp("data.txt");
	string value;
	string line;
	count = 0;

	while (getline(inp, line))
		count++;

	int ** graph = new int *[count];
	int i = 0, j;
	ifstream file("data.txt");
	while (getline(file, line))
	{
		graph[i] = new int[count];
		j = 0;
		stringstream ss(line);
		while (getline(ss, value, ','))
		{
			graph[i][j++] = atoi(value.c_str());
		}
		i++;
	}

	return graph;

}


int main()
{
	int count;
	int **graph = getData(count);

	char * states = new char[count];
	char a = 'a';

	for (int i = 0; i < count; i++)
	{
		cout << "Enter a char for state [" << i << "]: ";
		//cin >> states[i];
		states[i] = a++;
		cout << states[i] << endl;
	}
	int init;
	cout << "Enter Init state number: ";
	cin >> init;

	int goal;
	cout << "Enter goal state number: ";
	cin >> goal;

	Tree t(graph, states, count, init, goal);
	t.BFS();

	Node * exp = t.getExpandList().getStart();
	cout << "BFS Expand List:\n";
	
	while (exp != NULL)
	{
		cout << exp->getState();
		exp = exp->getNext();
		cout << " -> ";
	}

	cout << "\nBFS Solution List:\n";
	exp = t.getExpandList().getLast();
	while (exp != NULL)
	{
		cout << exp->getState();
		exp = exp->getParent();
		cout << " <- ";
	}



	cin.ignore();
	cin.get();
	return 0;
}