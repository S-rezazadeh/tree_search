#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
public:
	Node()
	{

	}



private:
	char state;
	int depth;
	int g;
	Node * parent;
	Node * next;
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