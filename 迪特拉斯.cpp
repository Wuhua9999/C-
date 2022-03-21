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
	//顶点数  
	int numV;
	//边数  
	int numE;
	//邻接矩阵  
	int **matrix;
public:
	Graph(int numV);
	//建图  
	void createGraph(int numE);
	//析构方法  
	~Graph();
	//迪杰斯特拉算法
	void Dijkstra(int);
	//打印邻接矩阵  
	void printAdjacentMatrix();
	//检查输入  
	bool check(int, int, int);
};
Graph::Graph(int numV)
{
	//对输入的顶点数进行检测
	while (numV <= 0)
	{
		cout << "顶点数有误！重新输入 ";
		cin >> numV;
	}
	this->numV = numV;
	//构建邻接矩阵，并初始化
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
	对输入的边数做检测
	一个numV个顶点的有向图，最多有numV*(numV - 1)条边
	*/
	while (numE < 0 || numE > numV*(numV - 1))
	{
		cout << "边数有问题！重新输入 ";
		cin >> numE;
	}
	this->numE = numE;
	int tail, head, weight, i;
	i = 0;
	cout << "输入每条边的起点(弧尾)、终点(弧头)和权值" << endl;
	while (i < numE)
	{
		cin >> tail >> head >> weight;
		while (!check(tail, head, weight))
		{
			cout << "输入的边不正确！请重新输入 " << endl;
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
迪杰斯特拉算法
求指定顶点vertex到其它顶点的最短路径
不仅要得出最短路径长度，也要得到其序列
*/
void Graph::Dijkstra(int vertex)
{
	int i;
	//最短路径序列中每个顶点的直接前驱
	int *pre = new int[numV];
	for (i = 0; i < numV; i++)
		pre[i] = vertex;
	//顶点vertex到各个顶点的路径长度
	int *Distance = new int[numV];
	//初始化路径长度
	for (i = 0; i < numV; i++)
		Distance[i] = matrix[vertex][i];
	//标记各个顶点最短路径找到与否
	bool *find = new bool[numV];
	memset(find, 0, numV);
	find[vertex] = true;
	int d, v, count;
	count = 1, v = vertex;
	while (count < numV)
	{
		d = INFINITY;
		//确定一个最短距离
		for (i = 0; i < numV; i++)
		{
			if (!find[i] && Distance[i] < d)
			{
				d = Distance[i];
				v = i;
			}
		}
		find[v] = true;
		//更新剩余顶点的前驱和最短距离
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
	//打印最短路径序列和其长度
	stack<int> s;
	for (i = 0; i < numV; i++)
	{
		if (Distance[i] == 0);
		else if (Distance[i] == INFINITY)
			cout << "顶点 " << vertex <<" 到顶点 " << i <<" 无路径！" << endl;
		else
		{
			cout << "顶点 " << vertex << " 到顶点 " << i 
				 << " 最短路径长度是 " << Distance[i] 
				 << " ，其序列是...";
			v = i;
			s.push(v);
			do
			{
				v = pre[v];
				s.push(v);
			} while (v!=vertex);
			//打印最短路径序列
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
//打印邻接矩阵  
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
	cout << "建图..." << endl;
	cout << "输入顶点数 ";
	cin >> numV;
	Graph graph(numV);
	cout << "输入边数 ";
	cin >> numE;
	graph.createGraph(numE);
	cout << endl << "Dijkstra..." << endl;
	for (int i = 0; i < numV; i++)
	graph.Dijkstra(i);
	system("pause");
	return 0;
}
