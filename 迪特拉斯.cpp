#include<iostream>  
#include<iomanip>
#include<stack>
using namespace std;
#define MAXWEIGHT 100
#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY 1000
class Graph
{
private:
	//������  
	int numV;
	//����  
	int numE;
	//�ڽӾ���  
	int **matrix;
public:
	Graph(int numV);
	//��ͼ  
	void createGraph(int numE);
	//��������  
	~Graph();
	//�Ͻ�˹�����㷨
	void Dijkstra(int);
	//��ӡ�ڽӾ���  
	void printAdjacentMatrix();
	//�������  
	bool check(int, int, int);
};
Graph::Graph(int numV)
{
	//������Ķ��������м��
	while (numV <= 0)
	{
		cout << "������������������ ";
		cin >> numV;
	}
	this->numV = numV;
	//�����ڽӾ��󣬲���ʼ��
	matrix = new int*[numV];
	int i, j;
	for (i = 0; i < numV; i++)
		matrix[i] = new int[numV];
	for (i = 0; i < numV; i++)
	for (j = 0; j < numV; j++)
	{
		if (i == j)
			matrix[i][i] = 0;
		else
			matrix[i][j] = INFINITY;
	}
}
void Graph::createGraph(int numE)
{
	/*
	������ı��������
	һ��numV�����������ͼ�������numV*(numV - 1)����
	*/
	while (numE < 0 || numE > numV*(numV - 1))
	{
		cout << "���������⣡�������� ";
		cin >> numE;
	}
	this->numE = numE;
	int tail, head, weight, i;
	i = 0;
	cout << "����ÿ���ߵ����(��β)���յ�(��ͷ)��Ȩֵ" << endl;
	while (i < numE)
	{
		cin >> tail >> head >> weight;
		while (!check(tail, head, weight))
		{
			cout << "����ı߲���ȷ������������ " << endl;
			cin >> tail >> head >> weight;
		}
		matrix[tail][head] = weight;
		i++;
	}
}
Graph::~Graph()
{
	int i;
	for (i = 0; i < numV; i++)
		delete[] matrix[i];
	delete[]matrix;
}
/*
�Ͻ�˹�����㷨
��ָ������vertex��������������·��
����Ҫ�ó����·�����ȣ�ҲҪ�õ�������
*/
void Graph::Dijkstra(int vertex)
{
	int i;
	//���·��������ÿ�������ֱ��ǰ��
	int *pre = new int[numV];
	for (i = 0; i < numV; i++)
		pre[i] = vertex;
	//����vertex�����������·������
	int *Distance = new int[numV];
	//��ʼ��·������
	for (i = 0; i < numV; i++)
		Distance[i] = matrix[vertex][i];
	//��Ǹ����������·���ҵ����
	bool *find = new bool[numV];
	memset(find, 0, numV);
	find[vertex] = true;
	int d, v, count;
	count = 1, v = vertex;
	while (count < numV)
	{
		d = INFINITY;
		//ȷ��һ����̾���
		for (i = 0; i < numV; i++)
		{
			if (!find[i] && Distance[i] < d)
			{
				d = Distance[i];
				v = i;
			}
		}
		find[v] = true;
		//����ʣ�ඥ���ǰ������̾���
		for (i = 0; i < numV; i++)
		{
			if (!find[i])
			{
				d = Distance[v] + matrix[v][i];
				if (d < Distance[i])
				{
					pre[i] = v;
					Distance[i] = d;
				}
			}
		}
		count++;
	}
	//��ӡ���·�����к��䳤��
	stack<int> s;
	for (i = 0; i < numV; i++)
	{
		if (Distance[i] == 0);
		else if (Distance[i] == INFINITY)
			cout << "���� " << vertex <<" ������ " << i <<" ��·����" << endl;
		else
		{
			cout << "���� " << vertex << " ������ " << i 
				 << " ���·�������� " << Distance[i] 
				 << " ����������...";
			v = i;
			s.push(v);
			do
			{
				v = pre[v];
				s.push(v);
			} while (v!=vertex);
			//��ӡ���·������
			while (!s.empty())
			{
				cout << setw(3) << s.top();
				s.pop();
			}
			cout << endl;
		}
	}
	cout << endl;
	delete[]find;
	delete[]pre;
	delete[]Distance;
}
//��ӡ�ڽӾ���  
void Graph::printAdjacentMatrix()
{
	int i, j;
	cout.setf(ios::left);
	cout << setw(7) << " ";
	for (i = 0; i < numV; i++)
		cout << setw(7) << i;
	cout << endl;
	for (i = 0; i < numV; i++)
	{
		cout << setw(7) << i;
		for (j = 0; j < numV; j++)
			cout << setw(7) << matrix[i][j];
		cout << endl;
	}
}
bool Graph::check(int tail, int head, int weight)
{
	if (tail < 0 || tail >= numV || head < 0 || head >= numV
		|| weight <= 0 || weight >= MAXWEIGHT)
		return false;
	return true;
}
int main()
{
	int numV, numE;
	cout << "��ͼ..." << endl;
	cout << "���붥���� ";
	cin >> numV;
	Graph graph(numV);
	cout << "������� ";
	cin >> numE;
	graph.createGraph(numE);
	cout << endl << "Dijkstra..." << endl;
	for (int i = 0; i < numV; i++)
	graph.Dijkstra(i);
	system("pause");
	return 0;
}
