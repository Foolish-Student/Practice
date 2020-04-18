//二叉树
#include<stdio.h>
#include<malloc.h>
//定义结构体，数据域和左右指针域
typedef struct tree
{
	char data;
	struct tree* rtree, * ltree;
}tree;
//创建二叉树
void createtree(tree* );
//不管是前序中序还是后序用递归都是最简单，但效率也是最慢的。我们可以用栈代替递归，我们还是用递归因为我还没手写过栈
//前序遍历
void preorder(const tree* );
//中序遍历
void inorder(const tree* );
//后续遍历
void postorder(const tree*);
//还有一种从上往下一行一行遍历   需要用到队列，我也没有手写过队列 就不写了
//树的高度
void hightree(const tree*,int );
int h;//存放高度
//交换各结点的左右子树
void change(tree*);
//那么问题来了  你交换好了谁知道你交换好了？所以还是要输出
void puttree(const tree*);
int main()
{
	//定义一个二叉树根节点
	tree* handtree;
	//动态分配空间
	handtree = (tree*)malloc(sizeof(tree));
	//调用创建二叉树函数之前一定要动态分配空间，不然会报错的
	//先把根结点输入进去，这样方便递归
	printf("请输入根节点:");
	scanf("%c", &handtree->data);
	printf("如果子树为空输入*\n");
	//这里回车符被吃了  也可以用fflush(stdin)清空缓冲区 但是VS好像用不了
	getchar();
	createtree(handtree);
	//前序遍历输出
	printf("前序遍历:");
	preorder(handtree);
	printf("\n");
	//中序遍历输出
	printf("中序遍历:");
	inorder(handtree);
	printf("\n");
	//后续遍历
	printf("后续遍历:");
	postorder(handtree);
	printf("\n");
	//树的高度
	printf("树的高度");
	hightree(handtree, 0);
	printf("%d", h);
	//交换树
	change(handtree);
	//输出交换树
	puttree(handtree);
	return 0;
}
//创建二叉树
void createtree(tree* handtree)
{
	//先找退出条件,结点为*就退出
	if (handtree->data=='*') return;
	//一般是先左后右
	//给左子树分配空间
	handtree->ltree = (tree*)malloc(sizeof(tree));
	printf("输入左子树:");
	scanf("%c", &handtree->ltree->data);
	getchar();
	//递归调用 因为都是同一个步骤重复操作
	createtree(handtree->ltree);
	//如果你的结点为* 那么说明这个空间分配出来就浪费了，就把他释放掉
	if (handtree->ltree->data == '*') {
		free(handtree->ltree);
		handtree->ltree = NULL;
	}
	//右子树同理
	handtree->rtree = (tree*)malloc(sizeof(tree));
	printf("输入右子树:");
	scanf("%c", &handtree->rtree->data);
	getchar();
	createtree(handtree->rtree);
	if (handtree->rtree->data == '*') {
		free(handtree->rtree);
		handtree->rtree = NULL;
	}
}
//前序遍历顺序 头->左->右
void preorder( const tree* handtree) {
	//递归一般的第一件事就是找到出口，当只在于为空的时候就是退出的条件
	if (!handtree) return;
	//思路简单实现也很简单，先输出在递归s
	printf("%c", handtree->data);
	preorder(handtree->ltree);
	preorder(handtree->rtree);
}
//中序遍历思路和前序是一样的 只不过这个顺序是  左->头->右
void inorder( const tree* handtree) {
	if (!handtree) return;
	//注意这里 因为输出顺序不一样  递归的顺序就不一样
	inorder(handtree->ltree);
	printf("%c", handtree->data);
	inorder(handtree->rtree);
}
//后续遍历顺序 左->右->头
void postorder(const tree* handtree) {
	//方法跟上面一样
	if (!handtree) return;
	postorder(handtree->ltree);
	postorder(handtree->rtree);
	printf("%c", handtree->data);
}
//树的高度
void hightree(const tree* handtree , int hight) {
	//定义一个全局变量用来存放高度，以免递归重复刷新初值 
	if (!handtree) {
		h = h > hight ? h : hight;
		return;
	}
	//头遍历 区别就是加了高度
	hightree(handtree->ltree,hight+1);
	hightree(handtree->rtree,hight+1);
}
//交换各结点的左右子树
void change( tree* handtree) {
	//退出条件
	if (!handtree) return;
	//这就是一个非常非常简单的问题了   交换一下值就可以了
	//判断一下左右子树是否都一，如果都有才能交换
	if (handtree->ltree && handtree->rtree) {
		//交换两个数据域
		//这里用到了位运算符    位运算是最快的
		handtree->ltree->data ^= handtree->rtree->data;
		handtree->rtree->data ^= handtree->ltree->data;
		handtree->ltree->data ^= handtree->rtree->data;
	}
	//递归继续寻找    也就是遍历一遍
	change(handtree->ltree);
	change(handtree->rtree);
}
//遍历一遍  这里的遍历和上面不同的是输出了空的结点
void puttree(const tree* handtree) {
	if (!handtree) {
		//空的项用*来代替
		printf("*");
		return;
	}
	printf("%c", handtree->data);
	puttree(handtree->ltree);
	puttree(handtree->rtree);
}