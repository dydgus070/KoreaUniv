#include<stdio.h>
#include<stdlib.h>

typedef struct Red_Black_Tree_Node
{
   Red_Black_Tree_Node * left;
   Red_Black_Tree_Node * right;
   Red_Black_Tree_Node * parent;
   int key;
   char color;

}Node;
typedef struct RBTree
{
   Node * root;
   Node *nil;
   int count;
   int blackcount;
   int blackheight;
   int inst;
   int delt;
   int miss;
}Tree;
Node* CreateNode(Tree* RB,int inputdata)
{
   Node* Newnode=(Node*)malloc(sizeof(Node));
   Newnode->color='R';
   Newnode->key=inputdata;
   Newnode->left=RB->nil;
   Newnode->right=RB->nil;
   Newnode->parent=RB->nil;
   return Newnode;
}
Tree* CreateRBT()
{
   Tree* NewTree = (Tree*)malloc(sizeof(Tree));
   NewTree->count=0;
   NewTree->blackcount=0;
   NewTree->blackheight=0;
   NewTree->delt=0;
   NewTree->inst=0;
   NewTree->miss=0;
   NewTree->nil=(Node*)malloc(sizeof(Node));
   NewTree->nil->left=NewTree->nil;
   NewTree->nil->right=NewTree->nil;
   NewTree->nil->parent=NewTree->nil;
   NewTree->nil->color='B';
   NewTree->nil->key=0;
   NewTree->root=CreateNode(NewTree,0);
   NewTree->root=NewTree->nil;
   NewTree->root->parent=NewTree->nil;
   return NewTree;
}

void RightRotate(Tree* RB, Node*me)
{

   Node * y=me->left;
   me->left=y->right;
   
   if(y->right!=RB->nil)
   {
      y->right->parent=me;
   }

   y->parent=me->parent;
   
   if(me->parent==RB->nil)
   {
      RB->root=y;
   }
   
   else if(me==me->parent->left)
   {
      me->parent->left=y;
   }
   else 
   {
      me->parent->right=y;
   }
   y->right=me;
   me->parent=y;
}

void LeftRotate(Tree* RB, Node*me)
{

   Node * y= me->right;
   
   me->right=y->left;
   
   if(y->left!=RB->nil)
   {
      y->left->parent=me;
   }
   
   y->parent=me->parent;

   if(me->parent==RB->nil)
   {
      RB->root=y;
   }
   
   else if(me==me->parent->left)
   {
      me->parent->left=y;
   }   
   else
   {
         me->parent->right=y;
   }
   y->left=me;
   me->parent=y;
}

int RBinsertFix(Tree* RB, Node * me)
{
   if( me==RB->root || me->parent==RB->root)
   {
      RB->root->color='B';
      return 0;
   }
   
   while(me!=RB->nil&&me!=RB->root&&me->parent->color=='R')   
   {
      if(me->parent==me->parent->parent->left)
      {
         Node * y=me->parent->parent->right;
         if(y->color=='R')
         {
            me->parent->color='B';
            y->color='B';
            me->parent->parent->color='R';
            me=me->parent->parent;
         }
         else 
            { 
               if( me==me->parent->right)
               {
                  me=me->parent;
                  LeftRotate(RB,me);
               }         
            me->parent->color='B';
            me->parent->parent->color='R';
            RightRotate(RB,me->parent->parent);
         }
      }
      else
      {
         Node * y=me->parent->parent->left;
         if(y->color=='R')
         {
            me->parent->color='B';
            y->color='B';
            me->parent->parent->color='R';
            me=me->parent->parent;
         }
         else 
         {
               if( me==me->parent->left)
               {
                  me=me->parent;
                  RightRotate(RB,me);
               }
            me->parent->color='B';
            me->parent->parent->color='R';
            LeftRotate(RB,me->parent->parent);
         }
      }
   }
   RB->root->color='B';
   return 0;
}

int RBinsert(Tree * RB, int inputdat)
{
   Node* a=RB->nil;
   Node* b=RB->root;
   Node* newNode= CreateNode(RB, inputdat);


   if(RB->count==0)         //초기노드
   {
      RB->root=newNode;
      RB->count++;
      return 0;
   }

   while ( b!=RB->nil)         
   {
      a=b;
      if(newNode->key <b->key)
      {
         b=b->left;
      }
      else
      {
         b=b->right;
      }
   }

   newNode->parent=a;

   if( newNode->key<a->key)
   {
      a->left=newNode;
   }
   else
   {
      a->right=newNode;
   }

   newNode->left=RB->nil;
   newNode->right=RB->nil;
   newNode->color='R';

   RBinsertFix(RB, newNode);
   RB->count++;
   return 0;
}

void bst_print(Tree *RB,Node * rt, int level)
{
   if (rt->right != RB->nil)
         bst_print(RB,rt->right, level + 1);
   for(int i = 0; i < level; i++)
         printf("     ");
   printf("%d%c\n\n", rt->key,rt->color);
   
   if (rt->left != RB->nil)
       bst_print(RB,rt->left, level + 1);
}
//DELETE 구현
void RBtransplant(Tree* RB,Node* a,Node*b)
{
   if(a->parent==RB->nil)
      RB->root=b;
   else if(a==a->parent->left)
      a->parent->left=b;
   else
      a->parent->right=b;

   b->parent=a->parent;
}

Node* RBminimum(Tree* RB,Node* x)
{
   while(x->left!=RB->nil)
      x=x->left;
   return x;
}
	
void RBdeletefix(Tree* RB, Node* x) {
   while (x != RB->root && x->color == 'B') {
      if (x == x->parent->left) {
         Node* w = x->parent->right;
         if (w->color == 'R') 
         {
            w->color = 'B';
            x->parent->color = 'R';
            LeftRotate(RB, x->parent);
            w = x->parent->right;
         }
         if (w->left->color =='B' && w->right->color == 'B')
         {
            w->color = 'R';
            x = x->parent;
         }
         else if (w->right->color == 'B') 
         {
            w->left->color = 'B';
            w->color = 'R';
            RightRotate(RB, w);
            w = x->parent->right;
         }
         w->color = x->parent->color;
         x->parent->color = 'B';
         w->right->color = 'B';
         LeftRotate(RB, x->parent);
         x = RB->root;
      }
      else {
         Node* w = x->parent->left;
         if (w->color == 'R') {
            w->color = 'B';
            x->parent->color = 'R';
            LeftRotate(RB, x->parent);
            w = x->parent->left;
         }
         if (w->right->color == 'B' && w->left->color == 'B') {
            w->color = 'R';
            x = x->parent;
         }
         else if (w->left->color == 'B') {
            w->right->color = 'B';
            w->color = 'R';
            LeftRotate(RB, w);
            w = x->parent->left;
         }
         w->color = x->parent->color;
         x->parent->color = 'B';
         w->left->color = 'B';
         RightRotate(RB, x->parent);
         x = RB->root;
      }
   }
   x->color = 'B';
}

void Rbdelete(Tree* RB,Node* z)
{
   Node* x;
   Node* y = z;
   char y_original_color = y->color;
   if (z->left == RB->nil)
   {
      x = z->right;
      RBtransplant(RB,z,z->right);
   }
   else if (z->right == RB->nil)
   {
      x = z->left;
      RBtransplant(RB,z,z->left);
   }
   else {
      y=RBminimum(RB,z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) 
      {
         x->parent = y;
      }
      else
      {
         RBtransplant(RB,y,y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RBtransplant(RB,z,y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }

   if (y_original_color == 'B') 
   {
      RBdeletefix(RB, x); 
   }
   RB->count--;
}

Node* RBsearch(Tree* RB, Node* x, int data)
{
   if(x==RB->nil || x->key==data)
      return x;

   if(data<x->key)
      return RBsearch(RB,x->left,data);
   else
      return RBsearch(RB,x->right,data);
}

void RBblacknode(Tree * RB,Node* x)
{
   if(x==RB->nil)
      return ;
   if(x->color=='B')
      RB->blackcount++;
   RBblacknode(RB,x->left);
   RBblacknode(RB,x->right);
}

int RBblackheight(Tree * RB, Node* x)
{
   int bh=0;
   while (1)
   {
	  if(x->color=='B')
		   bh++;
	   x=x->left;
	   if(x==RB->nil)
		   break;
   }

   return bh;

}
void RBprint_inorder(Tree* RB, Node*x)
{
   if(x==RB->nil)
      return;
   RBprint_inorder(RB,x->left);
   printf("%d",x->key);
   printf(" %c\n",x->color);
   RBprint_inorder(RB,x->right);
}
int RBconvert(Tree* RB, int inputdata)
{
   if(inputdata==0)
   {  
      printf("total = %d\n",RB->count);
	    printf("insert = %d\n",RB->inst);
		printf("delete = %d\n",RB->delt);
		printf("miss = %d\n",RB->miss);

      RBblacknode(RB,RB->root);
      printf("nb = %d\n",RB->blackcount);
	//  RBbheight(RB,RB->root);
	  printf("bh = %d\n",RBblackheight(RB,RB->root));
//	  printf("bh = %d\n",RB->blackheight);
      printf("Inorder Traversal의 결과를 보시려면 아무키나 누르십시오.\n");
      getchar();
      RBprint_inorder(RB,RB->root);
      return 0;
   }
   else if(inputdata>0)
   {
      RBinsert(RB,inputdata);
	  RB->inst++;
   }
   else 
   {
      if(RBsearch(RB,RB->root,(inputdata*(-1)))==RB->nil)
        {
			//printf("There is no %d\n",inputdata*(-1)); 
			RB->miss++;
	  }
	  else 
      {
         Rbdelete(RB,RBsearch(RB,RB->root,(inputdata*(-1))));
		 RB->delt++;
      }
   }
   return 1;   
}

void main()
{
    Tree* test=CreateRBT();
       int data;
	   char fname[50];
       FILE *fp=NULL;
	   printf("filename : ");
	   scanf_s("%s",fname,sizeof(fname));
	   getchar();

       fopen_s(&fp,fname, "r");
      do 
      {
            fscanf_s(fp, "%d", &data);
        }while (RBconvert(test,data)!=0);
        fclose(fp);
   getchar();
}