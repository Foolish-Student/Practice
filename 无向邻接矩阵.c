//无向图的邻接矩阵
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//创建一个结构体，用来存放结点和边
typedef struct plan {
	char vertax[100];		 //用来存放顶点
	int vertaxcon;			 //用来存放顶点的个数
	int arccon;				 //用来存放边的个数
	int array[100][100];	 //矩阵用来存放结点和边的关系
}plan;
void creat(plan*);				 //用来创建图
int find(plan*, int);			 //用来查找位置
void show(plan*);				 //输出邻接矩阵
int main()
{
	plan *picture;			 //创建一个结构体指针
	picture = (plan*)malloc(sizeof(plan));		//动态分配内存
	creat(picture);
	return 0;
}
//实现图
void creat(plan* picture) 
{
	//先输入结点个数和边
	printf("请输入结点的个数:");
	scanf("%d", &picture->vertaxcon);
	printf("请输入边的条数:");
	scanf("%d", &picture->arccon);
	//录入顶点
	for (int i = 0; i < picture->vertaxcon; i++)
	{
		getchar();				//吃一下回车符
		printf("顶点：");
		scanf("%c", &picture->vertax[i]);
	}
	//初始化邻接矩阵
	memset(picture->array, 0, sizeof(picture->array));
	printf("请输入顶点和邻结点的关系，构造邻接矩阵\n");
	//依次输入顶点和临界点
	char a, b;
	for (int i = 0; i < picture->arccon; i++)
	{
		printf("顶点：");
		getchar();
		scanf("%c", &a);
		getchar();
		printf("连结点：");
		scanf("%c", &b);
		//来寻找脚标 好来建立矩阵
		int x = find(picture, a);
		int y = find(picture, b);
		//也存在没用找到的情况，来判断一下
		if (x == -1 || y == -1) {
			printf("输入错误，请重新输入\n");
			i--;
			continue;					//如果其中一个不满足就跳过这次循环
		}
		else {
			//满足的话就把矩阵赋值
			picture->array[x][y] = 1;
			picture->array[y][x] = 1;
		}
	}
	//都输入完了 输出即可
	show(picture);
}
int find(plan* picture, char num)
{
	int x = 0;
	//遍历一遍来找到位置
	while (x < picture->vertaxcon)
	{
		//如果相等就直接退出
		if (num == picture->vertax[x])
		{
			break;
		}
		x++;
	}
	//如果找到了就返回脚标，如果没用找到就返回一个不可能的数，这里设置为-1
	return x < picture->vertaxcon ? x : -1;
}
//输出矩阵
void show(plan* picture) {
	printf("\n*****************\n");
	printf("    邻接举证\n");
	//遍历输出一遍即可
	printf("%5c", ' ');
	for (int i = 0; i < picture->vertaxcon; i++)
	{
		printf("%-5c", picture->vertax[i]);
	}
	printf("\n");
	for (int i = 0; i < picture->vertaxcon; i++)
	{
		printf("%-5c", picture->vertax[i]);
		for (int j = 0; j < picture->vertaxcon; j++)
		{
			printf("%-5d", picture->array[i][j]);
		}
		printf("\n");
	}
}