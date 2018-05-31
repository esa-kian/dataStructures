
/*
اجرای پیمایش اول سطح گراف 
برنامه زیر برای چاپ پیمایش اول سطح از راس مبدا میباشد
*/ 
#include<iostream>
#include <list>

using namespace std;

// این کلاس نشان دهنده یک گراف جهت دار با استفاده از نمایش لیست مجاورت است 
class Graph
{
	int V; 
	list<int> *adj;    // اشاره گر به یک آرایه شامل لیست مجاورت
public:
	Graph(int V);  // سازنده
	void addEdge(int v, int w); // تابع افزودن یال به گراف
	void BFS(int s);  //چاپ پیمایش اول سطح از مبدا s
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // افزودن راس w به لیست
}

void Graph::BFS(int s)
{
	// علامت گذاری تمام رئوس به عنوان دیدار نکرده
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// ایجاد یک صف برای پیمایش اول سطح
	list<int> queue;

	// علامت گذاری گره جاری به عنوان بازدید کرده و در نوبت قراردادن آن
	visited[s] = true;
	queue.push_back(s);

	//  برای دریافت تمام راسهای مجاور یک راس استفاده خواهد شد'i'
	list<int>::iterator i;

	while (!queue.empty())
	{
		// کاهش یک راس از صف و چاپ آن
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		// دریافت تمام راس های مجاور راس s و کاهش آنها از صف
		// اگر راس مجاوری بازدید نشده بود درآخر بازدید شود
		// سپس آنرا به صف اضافه میکنیم
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

// تابع اصلی برای تست متد های کلاس گراف
int main()
{
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
	g.BFS(2);

	return 0;
}
 
