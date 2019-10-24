#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
	char val;
	struct Node *left;
	struct Node *right;
}	Node;

typedef struct ReturnType {
	Node * root;	// 创建好树的根节点
	int	used;		// 创建树过程中用掉的值个数
}	ReturnType;

// A B D F # # # # C # E # G # #
// CreateTree 函数需要返回两个值
// 1. Node *	根结点
// 2. int		使用了多少值
ReturnType createTree(char preorder[], int size) {
	char rootValue = preorder[0];
	if (rootValue == '#') {
		ReturnType returnValue;
		returnValue.root = NULL;
		returnValue.used = 1;
		return returnValue;
	}

	Node * root = (Node *)malloc(sizeof(Node));
	root->val = rootValue;

	ReturnType left = createTree(preorder + 1, size - 1);
	// left.root;	创建好的左子树的根结点
	// left.used;	创建左子树过程中使用掉的值个数
	ReturnType right = createTree(preorder + 1 + left.used,
		size - 1 - left.used);

	root->left = left.root;
	root->right = right.root;

	ReturnType returnValue;
	returnValue.root = root;
	returnValue.used = 1 + left.used + right.used;

	return returnValue;
}

char * array;
int size;

void preorder(Node *root) {
	if (root == NULL) {
		return;
	}

	// 根
	size += sprintf(array + size, "(%c", root->val);
	if (root->left == NULL && root->right != NULL) {
		size += sprintf(array + size, "()");
		preorder(root->right);
	}
	else if (root->left == NULL && root->right == NULL) {

	}
	else if (root->left != NULL && root->right == NULL) {
		preorder(root->left);
	}
	else {
		preorder(root->left);
		preorder(root->right);
	}

	size += sprintf(array + size, ")");
}

char * tree2str(Node *root) {
	array = (char *)malloc(sizeof(char)* 10000);
	size = 0;

	preorder(root);
	array[size - 1] = '\0';
	return array + 1;
}

void test() {
	char * preorder = "ABDF####C#E#G##";
	int size = strlen(preorder);

	ReturnType r = createTree(preorder, size);

	printf("成功\n");

	char * p = tree2str(r.root);
	printf("%s\n", p);
}

int main(){
	system("pause");
	test();
}