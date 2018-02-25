#include<stdio.h>
#include<stdlib.h>
struct TreeNode{
	int val;
	struct TreeNode * left;
	struct TreeNode * right;
};

struct Tree{
	struct TreeNode * root;
};
void sum(struct TreeNode * cur,int * res);
void treeAdd(struct Tree * tree,int n);
void treePrintNode(struct TreeNode * cur);
void treePrint(struct Tree * tree);
struct TreeNode * search(struct TreeNode * cur,int n);
void treeAddRec(struct TreeNode ** cur,int n);
int sumrec(struct TreeNode * cur,int res);
int SUM(struct TreeNode * cur);
void reverse(struct TreeNode * cur);
int count_sheet(struct TreeNode * cur);
struct TreeNode * treeAdd_no_Add(int x,struct TreeNode * cur);

int main(){
	struct Tree tree;
	struct TreeNode * mem=NULL;
	FILE * f;
	char fname[]="test.txt";
	int n,res=0,s=0,k;
	tree.root = NULL;
	f=fopen(fname,"r");
	/* while(fscanf(f,"%d",&n)==1){
		treeAdd(&tree,n);
	} */
	while(fscanf(f,"%d",&n)==1){
		tree.root=treeAdd_no_Add(n,tree.root);
	}
	treePrint(&tree);
	if(mem!=NULL){printf("%d\n",mem->val);}
	printf("\n");
	treeAddRec(&tree.root,6);
	treePrint(&tree);
	k=SUM(tree.root);
	printf("Сумма: %d\n",k);
	printf("\n");
	s=count_sheet(tree.root);
	printf("Количество листьев: %d\n",s);
	reverse(tree.root);
	treePrint(&tree);
}

//если элемент больше предыдущего, то он записывается вправо, иначе влево
void treeAdd(struct Tree * tree,int n){
	struct TreeNode * cur = tree->root;
	struct TreeNode ** curAddr = &tree->root;
	struct TreeNode * node = malloc(sizeof(struct TreeNode));
	node->left = NULL;
	node->right = NULL;
	node->val = n;
	while(cur!=NULL){
		if(cur->val<n){
			//right
			curAddr=&cur->right;
			cur=cur->right;
		}
		else{
			//left
			curAddr=&cur->left;
			cur=cur->left;
		}
	}
	*curAddr=node;
}

//рекусивное добавление
void treeAddRec(struct TreeNode ** cur,int n){
	if(*cur!=NULL){
		if((*cur)->val<n){
			treeAddRec(&((*cur)->right),n);
		}
		else{
			treeAddRec(&((*cur)->left),n);
		}
	}
	else{
		(*cur)=malloc(sizeof(struct TreeNode));
		(*cur)->val=n;
		(*cur)->right=NULL;
		(*cur)->left=NULL;
	}
}

//рекусивное добавление без указателей
struct TreeNode * treeAdd_no_Add(int x,struct TreeNode * cur){
	if(cur==NULL){
		cur=malloc(sizeof(struct TreeNode));
		cur->val=x;
		cur->left=NULL;
		cur->right=NULL;
	}
	else{
		if(x>cur->val){
			cur->right=treeAdd_no_Add(x,cur->right);
		}
		else{
			cur->left=treeAdd_no_Add(x,cur->left);
		}
	}
	return cur;
}

void treePrintNode(struct TreeNode * cur){
	if(cur==NULL){
		return;
	}
	treePrintNode(cur->left);
	printf("%d\n",cur->val);
	treePrintNode(cur->right);
	return;
}

void treePrint(struct Tree * tree){
	treePrintNode(tree->root);
}

//сумма
void sum(struct TreeNode * cur,int * res){
	if(cur==NULL){
		return;
	}
	sum(cur->left,res);
	*res=*res+cur->val;
	sum(cur->right,res);
	return;
}

int sumrec(struct TreeNode * cur,int res){
	if(cur==NULL){
		return res;
	}
	res=sumrec(cur->left,res);
	res=res+cur->val;
	res=sumrec(cur->right,res);
	return res;
}

int SUM(struct TreeNode * cur){
	int al,ar;
	if(cur==NULL){
		return 0;
	}
	al=SUM(cur->left);
	ar=SUM(cur->right);
	return al+ar+cur->val;
}

//поиск
struct TreeNode * search(struct TreeNode * cur,int n){
	struct TreeNode * tmp;
	tmp=cur;
	if(tmp==NULL){
		return NULL;
	}
	while((tmp!=NULL)&&(n!=tmp->val)){
		if(n>tmp->val){
			tmp=tmp->right;
		}
		else if(n<tmp->val){
			tmp=tmp->left;
		}
	}
	return tmp;
}

//перенаправление указателей
void reverse(struct TreeNode * cur){
	struct TreeNode * tmp;
	if(cur==NULL){
		return;
	}
	reverse(cur->left);
	reverse(cur->right);
	tmp=cur->right;
	cur->right=cur->left;
	cur->left=tmp;
}

//количество листьев
int count_sheet(struct TreeNode * cur){
	int count=0;
	if(cur==NULL){
		return 0;
	}
	if((cur->left==NULL)&&(cur->right==NULL)){return 1;}
	count=count+count_sheet(cur->left);
	count=count+count_sheet(cur->right);
	return count;
}