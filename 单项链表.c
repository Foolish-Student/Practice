/*
单项链表有两种插入方法，一种是头插法，一种是尾插法。
我个人比较喜欢尾插法，因为尾插法的顺序和输入的顺序是一样的
所以今天写的是尾插法
*/
#include<stdio.h>
#include<malloc.h>
#include<string.h>
//定义一个结构体
struct NUM{
	char a[100];
	struct NUM* next;
};
//输入成员函数
void setlist(struct NUM*);
//输出函数
void showlist(struct NUM*);
//查找函数
void findlist(struct NUM*, const char*);
//插入
void insertlist(struct NUM*, const char*,const int);
//删除
void deletelist(struct NUM*, const int);
//释放
void freelist(struct NUM*);
int main()
{
	//定义一个头指针,给他赋值为空
	struct NUM* ptr_head = NULL;
	//给头分配一块内存
	ptr_head = (struct NUM*)malloc(sizeof(struct NUM));
	printf("插入一组元素(0000结束):");	
	setlist(ptr_head);
	int choice;
	for (;;) {
		printf("\n****************************************\n");
		printf("1.查找\n");
		printf("2.插入\n");
		printf("3.删除\n");
		printf("4.输出\n");
		printf("5.退出\n");
		printf("输入序号即可\n");
		printf("\n****************************************\n");
		scanf("%d", &choice);//选择
		//根据 选择做出相应的步骤
		if (choice == 1) {
			printf("输入查找的字符：");
			char t[20];
			scanf("%s", t);
			findlist(ptr_head, t);
		}
		else if (choice == 2) {
			printf("输入插入的位置和字符（第一个为位置为1）");
			char t[20];
			int n;
			scanf("%d%s", &n, t);
			insertlist(ptr_head, t, n);
		}
		else if (choice == 3) {
			printf("输入要删除的位置（第一个位置为1）");
			int n;
			scanf("%d", &n);
			deletelist(ptr_head, n);
		}
		else if (choice == 4) {
			showlist(ptr_head);
		}
		else if (choice == 5) {
			freelist(ptr_head);
			break;
		}
		else {
			printf("输入错误\n");
		}
	}
	return 0;
}
//写入函数
void setlist(struct NUM* ptr_head) {
	//定义一个头指针、尾指针和临时指针
	struct NUM* ptr_end, * ptr_temp;//*ptr_head;
	//把头的地址给尾，这样尾移动的时候头还在
	ptr_end = ptr_head;
	//循环录入
	do {
		//动态分配一块空间
		ptr_temp = (struct NUM*)malloc(sizeof(struct NUM));
		//输入一个数
		scanf("%s", &ptr_temp->a);
		//设置一个推出点  输入0000的时候就退出
		if (!strcmp(ptr_temp->a, "0000")) {
			//释放刚刚分配的空间后退出循环
			free(ptr_temp);
			break;
		}
		//将尾巴结构体指针指向tpr_temp
		ptr_end->next = ptr_temp;
		//让尾巴等于tpr_temp，这样刚刚录入的就变成了最后一个，头还不变，这样就链起来了
		ptr_end = ptr_temp;
	} while (1);
	//将尾巴的地址复制空
	ptr_end->next = NULL;
	//return ptr_head;
}
//输出
void showlist(struct NUM* ptr_out) {
	//使用do while循环输出我觉得是最好的
	do{
		//指针往后走
		ptr_out = ptr_out->next;
		//输出，以一个制表符隔开
		printf("%s\t", ptr_out->a);
	} while (ptr_out->next);//直到遇见空指针就退出，是输出完了在推出，所以用do while
	printf("\n");
}
//查找
void findlist(struct NUM* ptr_find, const char* s) {
	int len = 0;//记录位置
	do {
		//位置每次+1
		len++;
		//一直往后走
		ptr_find = ptr_find->next;
		//判断，输出后退出
		if (!strcmp(ptr_find->a, s)) {
			printf("字符%s位于队列中第%d位\n", s, len);
			return;
		}
	} while (ptr_find->next);//判断是否为空
	//如果没有找到
	printf("没有找到\n");
}
//插入
void insertlist(struct NUM* ptr_insert, const char* insert,const int add) {
	//先判断是否越界
	int len=0;
	struct NUM* ptr_temp=ptr_insert;
	//遍历一遍得到长度
	do {
		ptr_temp = ptr_temp->next;
		len++;
	} while (ptr_temp->next);
	//看一下是否越界
	if (add > len+1 || add <= 0) {
		printf("越界！！！\n");
	}
	else {
		//没有越界就 插入,遍历找到位置
		len = add-1;
		while (len--) ptr_insert = ptr_insert->next;
		//分配一块空间
		ptr_temp = NULL;
		ptr_temp = (struct NUM*)malloc(sizeof(struct NUM));
		//赋值
		strcpy(ptr_temp->a, insert);
		//链上去
		ptr_temp->next = ptr_insert->next;
		ptr_insert->next = ptr_temp;
		printf("插入成功！！！\n");
	}
}
//删除
void deletelist(struct NUM* ptr_delete, const int add) {
	//先判断是否越界
	int len = 0;
	struct NUM* ptr_temp = ptr_delete;
	//遍历一遍得到长度
	do {
		ptr_temp = ptr_temp->next;
		len++;
	} while (ptr_temp->next);
	//看一下是否越界
	if (add > len  || add <= 0) {
		printf("越界！！！\n");
	}
	else {
		//先遍历一遍找到位置
		len = add - 1;
		while (len--) ptr_delete = ptr_delete->next;
		//把要删除的内存用一个指针存起来一会好释放
		ptr_temp = ptr_delete->next;
		//链一下
		ptr_delete->next = ptr_delete->next->next;
		//释放空间
		free(ptr_temp);
		printf("删除成功！！！\n");
	}
}
//释放
void freelist(struct NUM* ptr_head) {
	//结束的时候把空间都释放掉
	//需要一个临时指针来帮助
	struct NUM* ptr_temp ;
	do {
		//记录前一个往后移动
		ptr_temp = ptr_head;
		ptr_head = ptr_head->next;
		//释放前一个
		free(ptr_temp);
	} while (ptr_head->next);//遇到NULL结束
	//释放最后一个
	free(ptr_head);
}