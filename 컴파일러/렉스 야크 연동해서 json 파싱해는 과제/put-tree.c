/*--------------------------------------------------------------------------
	File-name	: put-tree.c
	Description	: Example of printing parse tree
	Written-by	: Kang, Seung-Shik, 2014/12/10
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX	1024

int N_nodes=0;

typedef struct node {
	int data;

	int nchild;	// number of children
	struct node *down;
	struct node *right;
} NODE, *P_NODE;

// parse tree 출력
void put_tree(NODE *node, int depth)
{
	int i, j;
	NODE *p;

	if (node == NULL) return;

	for (j = 0; j < depth; j++) printf("    ");	// indentation
	printf("| %d (%d)\n", node->data, node->nchild);

	if (node->nchild > 0) {	// daughters
		p = node->down;
		for (i = node->nchild-1; i >= 0; i--) {
			put_tree(p, depth+1);
			if (p == NULL) return;
			p = p->right;
		}
	}
}

// 모든 node에 대한 memory release
void del_tree(NODE *node)
{
	int i, j;
	NODE *p;

	if (node == NULL) return;

	if (node->down) del_tree(node->down);
	if (node->right) del_tree(node->right);

	free(node);
	N_nodes--;
}

// node 한 개 생성 -- memory 할당
NODE *get_newnode()
{
	NODE *node;

	node = (NODE *) malloc(sizeof(NODE));

	node->nchild = (rand() % 4) + 1;
//	node->data = rand() % 100;
	node->down = NULL;
	node->right= NULL;

	N_nodes++;
	return node;
}

// depth n인 sample parse tree 생성 -- child 개수는 random하게 2~5개로...
NODE *build_tree(int n)
{
	int i;
	NODE *node, *n2;

	node = get_newnode();
	node->data = n*1000;	// depth 값을 반영

	if (n-1 > 0) {
		node->down = build_tree(n-1);
		node->down->data += 1;	// 1st child

		n2 = node->down;
		for (i=0; i < node->nchild-1; i++) {
			n2->right = build_tree(n-1);
			n2->right->data += i+2;	// nth child

			n2 = n2->right;
		}
	} else node->nchild = 0;	// terminal node

	return node;
}

main(argc, argv)
int argc; char *argv[];
{
	int depth=4;	// default depth of a tree
	NODE *root;	// root node of a parse tree

	if (argc >= 2 && argv[1][0] == '-')	// C> run.exe -n
		depth = atoi(argv[1]+1);

	srand((unsigned int)time(NULL));
	root = build_tree(depth);	// depth인 sample parse tree 생성
	printf("Total %d nodes are created!\n", N_nodes);

	put_tree(root, 0);	// parse tree 출력
	del_tree(root);	// memory release
	if (N_nodes) printf("Total %d nodes are remaining!\n", N_nodes);

	return 0;
}
/*--------------------------- end of put-tree.c ---------------------------*/
