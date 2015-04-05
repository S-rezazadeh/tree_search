/*
This is simple version of application. Many of OOP concpts , exceptions ,  copy constructors , abstraction , List Nodes are removed :)
*/


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class BFSQueue;
class UCSQueue;

class Node
{
	friend class BFSQueue;
	friend class UCSQueue;
public:
	Node()
	{

	}
	int getDepth()
	{
		return depth;
	}
	int getG()
	{
		return g;
	}
	Node * getNext()
	{
		return next;
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

		}
	}


private:
	Node * start;

};


class Tree
{
public:
	Tree()
	{

	}

private:
	Node * root;
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

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			cout << graph[i][j] << "\t";
		}
		cout << endl;
	}


	cin.get();
	return 0;
}