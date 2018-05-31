//اجرای الگوریتم پرایم
#include <stdio.h>
#include <limits.h>
#include <iostream>
using namespace std;

// تعداد راس ها در گراف
#define V 5

// یک تابع کاربردی برای پیدا کردن کمترین مقدار راس ها

int minKey(int key[], bool mstSet[])
{
	// مقداردهی اولیه مقدار حداقل
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
	if (mstSet[v] == false && key[v] < min)
		min = key[v], min_index = v;

	return min_index;
}

// تابعی کاربردی برای چاپ MST ساخته شده ذخیره شده در parent[]
void printMST(int parent[], int n, int graph[V][V])
{
	printf("Edge   Weight\n");
	for (int i = 1; i < V; i++)
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

//تابعی برای ساخت و چاپ MST برای یک گراف نشان داده شده با استفاده از نمایش ماتریس مجارت

void primMST(int graph[V][V])
{
	int parent[V]; // آرایه ای برای ذخیره سازی MSTساخته شده 
	int key[V];   // مقادیر کلید برای انتخاب سبکترین یال در کاهش استفاده میشود
	bool mstSet[V];  // برای نشان دادن مجموعه ای از رئوس که هنوز در MST گنجانده نشده

	// مقداردهی تمام کلید ها به عنوان یک مقدار خیلی بزرگ
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;     // ساخت این کلید باعث میشود این راس به عنوان اولین راس برداشته شود
	parent[0] = -1; // اولین گره همیشه ریشه است
//MST به تعداد V  خواهد شد 
	for (int count = 0; count < V - 1; count++)
	{
		// حداقل راس کلیدی از مجموعه ای از رئوس را انتخاب کنید
		// هنوز در MST گنجانده نشده
		int u = minKey(key, mstSet);

		// افزودن راس انتخاب شده به مجموعه MST
		mstSet[u] = true;

		/* به روز رسانی مقدار های کلیدی
		و شاخص والد رئوس را مجاور از رأس برداشت.
		تنها کسانی که رئوس را که هنوز در MST گنجانده نشده در نظر بگیرید
		*/
		for (int v = 0; v < V; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
		if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
			parent[v] = u, key[v] = graph[u][v];
	}

	// چاپ سازنده MST
	printMST(parent, V, graph);
}


int main()
{
	/* اجازه بدهید به ما نمودار زیر را ایجاد کنیم
	2    3
	(0)--(1)--(2)
	|   / \   |
	6| 8/   \5 |7
	| /     \ |
	(3)-------(4)
	9          */
	int graph[V][V] = { { 0, 2, 0, 6, 0 },
	{ 2, 0, 3, 8, 5 },
	{ 0, 3, 0, 0, 7 },
	{ 6, 8, 0, 0, 9 },
	{ 0, 5, 7, 9, 0 },
	};

	// چاپ راه حل
	primMST(graph);
	cin.get();
	return 0;
}
 
