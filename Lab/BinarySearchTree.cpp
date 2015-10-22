#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)return 0;
    return getSize(node->left)+getSize(node->right)+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode *temp;
    int d=0;
    temp=root;
    if(node==0)return -1;
    while(1)
    {
        if(temp==0)return -1;
        if(temp->item==node->item)return d;
        d++;
        if(node->item<temp->item) temp=temp->left;
        else temp=temp->right;
    }
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode *temp;
    int d=0;
    temp=root;
    while(1)
    {
        if(temp==0)return -1;
        if(temp->item==item)return d;
        d++;
        if(item<temp->item) temp=temp->left;
        else temp=temp->right;
    }
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    if (node==0) return FALSE_VALUE;
    if(node->item==item)
    {
        if(node->left==0 && node->right==0)
        {
            free(node);
            root=0;
            return TRUE_VALUE;
        }
        if(node->left==0 node->right!=0)
        {
            root=node->right;
            free(node);
            return TRUE_VALUE;
        }
        if(node->left!=0 node->right==0)
        {
            root=node->left;
            free(node);
            return TRUE_VALUE;
        }
        if()


    }

}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    while(temp->left!=0)
    {
        temp=temp->left;
    }
    return temp->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    while(temp->right!=0)
    {
        temp=temp->right;
    }
    return temp->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    //int n=0;
    int l,r;
    if(node==0)return 0;
    if(node->item>=leftBound && node->item<=rightBound)
    {
        //n++;
        l=rangeSearch(node->left,leftBound,node->item);
        r=rangeSearch(node->right,node->item,rightBound);
        return l+r+1;
    }
    else if(node->item>rightBound)
    {
        l=rangeSearch(node->left,leftBound,rightBound);
        return l;
    }
    else if(node->item<leftBound)
    {
        r=rangeSearch(node->right,leftBound,rightBound);
        return r;
    }

}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            printf("%d\n",getSize(root));
        }
        else if(ch==8)
        {
            int i;
            scanf("%d",&i);
            printf("%d\n",calcDepth(i));
        }
        else if(ch==9)
        {

        }
        else if(ch==10)
        {
            printf("%d\n",getMinItem());
        }
        else if(ch==11)
        {
            printf("%d\n",getMaxItem());
        }
        else if(ch==12)
        {
            int l,r;
            scanf("%d",&l);
            scanf("%d",&r);
            printf("%d\n",rangeSearch(root,l,r));
        }
        else if(ch==6)
        {
            break;
        }
    }

}
