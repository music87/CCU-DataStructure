#include<stdio.h>
#include<stdlib.h>

typedef struct tree *treepointer;
struct tree
{
    int data;
    treepointer lchild;
    treepointer rchild;
};

treepointer insert(treepointer currentroot,int newdata)
{
    if(currentroot==NULL)//insert
    {
        treepointer tmp;
        tmp=(treepointer)malloc(sizeof(struct tree));
        tmp->rchild=NULL;
        tmp->lchild=NULL;
        tmp->data=newdata;
        currentroot=tmp;
        printf("Number %d is inserted.\n",newdata);
    }
    else if(newdata>(currentroot->data))//go to right subtree
        currentroot->rchild=insert(currentroot->rchild,newdata);
    else if(newdata<(currentroot->data))//go to left subtree
        currentroot->lchild=insert(currentroot->lchild,newdata);
    else if(newdata==(currentroot->data))//already exist
        printf("Error.Number %d exists.\n",newdata);
    return currentroot;
}


treepointer delete(treepointer currentroot,int dedata,int havedeleted)
{
    treepointer tmp;
    if(currentroot==NULL)//case1:not found
        printf("Number not found.\n");
    else if(dedata<(currentroot->data))//go to left subtree
        currentroot->lchild=delete(currentroot->lchild,dedata,havedeleted);
    else if(dedata>(currentroot->data))//go to right subtree
        currentroot->rchild=delete(currentroot->rchild,dedata,havedeleted);
    else//start to delete
    {
        //case2:no child
        if(currentroot->lchild==NULL && currentroot->rchild==NULL)
        {
            free(currentroot);
            currentroot=NULL;//for return NULL to pre currentroot's lchild/rchild
            if(havedeleted==0)
            {
                printf("Number %d is deleted.\n",dedata);
                havedeleted=1;
            }
        }
        //case3:1child
        else if(currentroot->lchild==NULL && currentroot->rchild)
        {
            tmp=currentroot;
            currentroot=currentroot->rchild;
            free(tmp);
            if(havedeleted==0)
            {
                printf("Number %d is deleted.\n",dedata);
                havedeleted=1;
            }
        }
        else if(currentroot->rchild==NULL && currentroot->lchild)
        {
            tmp=currentroot;
            currentroot=currentroot->lchild;
            free(tmp);
            if(havedeleted==0)
            {
                printf("Number %d is deleted.\n",dedata);
                havedeleted=1;
            }
        }
        //case 4:2child
        else if(currentroot->rchild && currentroot->lchild)
        {
            //find min in the right subtree
            tmp=currentroot->rchild;
            while(tmp->lchild)
                tmp=tmp->lchild;
            currentroot->data=tmp->data;//copy data
            //be care:tmp may not be a leaf node so can't just use "free(tmp)"
            if(havedeleted==0)
            {
                printf("Number %d is deleted.\n",dedata);
                havedeleted=1;
            }
            currentroot->rchild=delete(currentroot->rchild,tmp->data,havedeleted);
        }
    }
    return currentroot;
    
}

void search(treepointer currentroot,int sdata)
{
    while(1)
    {
        if(currentroot==NULL)
        {
            printf("SORRY. Number not found.\n");
            break;
        }
        if(sdata==(currentroot->data))
        {
            printf("BINGO! Number is found.\n");
            break;
        }
        if(sdata>(currentroot->data))//go to right subtree
            currentroot=currentroot->rchild;
        else if(sdata<(currentroot->data))//go to left subtree
            currentroot=currentroot->lchild;
        
    }
}

void Infixprint(treepointer current)
{
    if(current)
    {
        Infixprint(current->lchild);
        printf("%d ",current->data);
        Infixprint(current->rchild);
    }
}

void Levelprint(treepointer root)
{
    treepointer cirq[1000];
    int front,rear;
    front=rear=-1;
    if(root)
        cirq[++rear]=root;
    while(front!=rear)
    {
        //pop and top
        front=(front+1)%1000;
        printf("%d ",cirq[front]->data);
        //push
        if(cirq[front]->lchild)
        {
            rear=(rear+1)%1000;
            cirq[rear]=cirq[front]->lchild;
        }
        if(cirq[front]->rchild)
        {
            rear=(rear+1)%1000;
            cirq[rear]=cirq[front]->rchild;
        }
    }
}

void BTS()
{
    char x;
    treepointer root;
    root=NULL;
    while(1)
    {
        printf("(I)nsert a number.\n");
        printf("(D)elete a number.\n");
        printf("(S)earch a number.\n");
        printf("(P)rint Infix & Level order\n");
        printf("(R)eturn.\n");
        scanf("%c",&x);getchar();
        if(x=='I' || x=='i')//Insert
        {
            int newdata;
            printf("Enter a number.\n");
            scanf("%d",&newdata);getchar();
            root=insert(root,newdata);
        }
        else if(x=='D' || x=='d')//Delete
        {
            int deletedata,havedeleted;
            havedeleted=0;
            printf("Enter a number to delete.\n");
            scanf("%d",&deletedata);getchar();
            root=delete(root,deletedata,havedeleted);
        }
        else if(x=='S' || x=='s')//Search
        {
            int searchdata;
            printf("Enter the Element to search.\n");
            scanf("%d",&searchdata);getchar();
            search(root,searchdata);
        }
        else if(x=='P' || x=='p')//Print infix & level order
        {
            printf("The tree in infix order : ");
            Infixprint(root);
            printf("\nThe tree in level order : ");
            Levelprint(root);printf("\n");
        }
        else if(x=='R')
            break;
    }
    return;
}
//=========================================================
treepointer Tinsert(treepointer currentroot,int newdata)
{
    if(currentroot==NULL)//insert
    {
        treepointer tmp;
        tmp=(treepointer)malloc(sizeof(struct tree));
        tmp->rchild=NULL;
        tmp->lchild=NULL;
        tmp->data=newdata;
        currentroot=tmp;
    }
    else if(newdata>(currentroot->data))//go to right subtree
        currentroot->rchild=Tinsert(currentroot->rchild,newdata);
    else if(newdata<(currentroot->data))//go to left subtree
        currentroot->lchild=Tinsert(currentroot->lchild,newdata);
    return currentroot;
}

treepointer ALC(treepointer currentroot,int a,int b)
{
    if(a>currentroot->data && b>currentroot->data)
        currentroot=ALC(currentroot->rchild,a,b);
    else if(a<currentroot->data && b<currentroot->data)
        currentroot=ALC(currentroot->lchild,a,b);
    //if a/b->data<currentroot->data && b/a->data>currentroot->data
    //=>currentroot is the nearest ancestor
    return currentroot;
}

void treasurehunter()
{
    FILE *fin;
    int key,treasure,bomb,x,array[1000],n,i,havedeleted,stack[1000],top;
    treepointer root,currentroot,alc;
    root=NULL;
    //load file
    printf("Please input the map file: example.txt\n");
    fin=fopen("exmap.txt","r");
    //fout=fopen("","w");
    if(fin!=NULL) printf("Load file success.\n");
    else printf("Fail to load file.\n");
    //set key,treasure and bomb
    printf("Please input the key location : ");
    scanf("%d",&key);getchar();
    printf("Please input the treasure location : ");
    scanf("%d",&treasure);getchar();
    printf("Please input the bomb number (0~9) : ");
    scanf("%d",&bomb);getchar();
    
    //read map
    n=0;
    while(fscanf(fin,"%d",&x)!=EOF)
    {
        root=Tinsert(root,x);
        array[n++]=x;
    }
    //bomb
    for(i=0;i<n;i++)
    {
        if((array[i]/10)==bomb || (array[i]%10==bomb))
        {
            havedeleted=0;
            root=delete(root,array[i],havedeleted);
        }
    }
    
    //findkey function : root -> key(not include)
    //root to key(not include)
    alc=ALC(root,key,treasure);
    printf("Adventurer successfully found the treasure.\n");
    printf("Shortest path to find the treasure:\n");
    currentroot=root;
    while(key!=currentroot->data)
    {
        printf("%d->",currentroot->data);
        if(key>currentroot->data)//go to right subtree
            currentroot=currentroot->rchild;
        else if(key<currentroot->data)//go to left subtree
            currentroot=currentroot->lchild;
    }
    
    //findtreasure function : key(include) -> (alc) -> treasure
    //if key==alc && treas==alc impossible
    //if key==alc && treas!=alc
    //if key!=alc && treas==alc
    //if key!=alc && treas!=alc
    
    //key to alc
    if(key==alc->data)//key == alc , include key==alc
        printf("%d->",alc->data);
    else// key != alc , include key , not include alc
    {
        top=-1;
        currentroot=alc;
        while(key!=currentroot->data)
        {
            if(key>currentroot->data)//go to right subtree
                currentroot=currentroot->rchild;
            else if(key<currentroot->data)//go to left subtree
                currentroot=currentroot->lchild;
            stack[++top]=currentroot->data;
        }
        while(top!=-1)
        {
            printf("%d->",stack[top]);
            top--;
        }
    }
    
    //alc to treasure
    if(treasure==alc->data) //treasure==alc , include treasure==alc
        printf("%d\n",alc->data);
    else if(alc->data!=key)//treasure!=alc , include alc , include treasure
    {
        currentroot=alc;
        while(treasure!=currentroot->data)
        {
            printf("%d->",currentroot->data);
            if(treasure>currentroot->data)//go to right subtree
                currentroot=currentroot->rchild;
            else if(treasure<currentroot->data)//go to left subtree
                currentroot=currentroot->lchild;
        }
        printf("%d\n",currentroot->data);
    }
    else//treasure!=alc , not include alc , include treasure
    {
        currentroot=alc;
        while(treasure!=currentroot->data)
        {
            if(treasure>currentroot->data)//go to right subtree
                currentroot=currentroot->rchild;
            else if(treasure<currentroot->data)//go to left subtree
                currentroot=currentroot->lchild;
            if(currentroot->data!=treasure)
                printf("%d->",currentroot->data);
        }
        printf("%d\n",currentroot->data);
    }
    fclose(fin);
}

int main()
{
    int x;
    while(1)
    {
        printf("(1)Binary Search Tree.\n");
        printf("(2)Treasure Hunter.\n");
        printf("(3)Exit.\n");
        scanf("%d",&x);getchar();
        if(x==1)//BTS
            BTS();
        else if(x==2)//Treasure Hunter
            treasurehunter();
        else if(x==3)
            break;
    }
    return 0;
}
