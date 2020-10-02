#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node *nodepointer;//a pointer to node
struct node{
    nodepointer llink;//struct allow including a "pointer" to itself
    nodepointer rlink;
    char data[101];
};
//>___<->node<->"newnode"<->___<->___<->headnode<-
void addnode(nodepointer node,nodepointer newnode)
{
    newnode->llink=node;
    newnode->rlink=node->rlink;
    (node->rlink)->llink=newnode;
    node->rlink=newnode;
}

//>___<->node<->"deathrow"<->___<->___<->headnode<-
void deletenode(nodepointer deathrow)
{
    deathrow->llink->rlink=deathrow->rlink;
    deathrow->rlink->llink=deathrow->llink;
    free(deathrow);
}

int readfile(nodepointer node)//add newnode after node(node<->newnode)
{
    printf("Start read data from a file\n");
    FILE *fptr;
    int n;
    char line[101];
    fptr=fopen("data.txt","r");
    n=0;
    while(fgets(line,100,fptr)!=NULL)
    {
        line[strlen(line)-1]='\0';
        nodepointer newnode=(nodepointer)malloc(sizeof(struct node));//cannot put outside the while,because you need new memory_location to connect itself to the old memory_location
        strcpy(newnode->data,line);
        addnode(node,newnode);
        printf("%s is appended\n",newnode->data);
        node=newnode;//move node to newnode's place
        n++;
    }
    node=node->rlink->rlink;//last node's next is headnode,headnode's next is the first node that have true value
    printf("the list datas are : \n");
    printf("[");
    for(;(node->data[0])!='\0';node=node->rlink)
    {
        printf("%s",node->data);
        if((node->rlink->data[0])!='\0')
            printf(",");
        else
            printf("]\n");
    }
    fclose(fptr);
    return n;
}

int writedata(nodepointer node)//add newnode after node(node<->newnode)
{
    int n,i;
    printf("how many nodes do you want to append?\n");
    scanf("%d",&n);getchar();
    for(i=0;i<n;i++)
    {
        nodepointer newnode=(nodepointer) malloc(sizeof(struct node));
        fgets(newnode->data,100,stdin);
        newnode->data[strlen(newnode->data)-1]='\0';
        printf("%s is appended\n",newnode->data);
        addnode(node,newnode);
        node=newnode;
    }
    node=node->rlink->rlink;//last node's next is headnode,headnode's next is the first node that have true value
    printf("the list datas are : \n");
    printf("[");
    for(;(node->data[0])!='\0';node=node->rlink)
    {
        printf("%s",node->data);
        if((node->rlink->data[0])!='\0')
            printf(",");
        else
            printf("]\n");
    }
    return n;
    
}

void RussianRoulette(int direction,int k,nodepointer headnode,int n)
{
    nodepointer deathrow,temp;
    int i;
    
    /*printf("0,headnode,%p\n",headnode);
     for(node=(headnode->rlink),i=1;(node->data[0])!='\0';node=(node->rlink),i++)
     printf("%d,%s,%p\n",i,node->data,node);*/
    //bug:if only one node
    //bug:deathrow=headnode+2*direction; because the location of headnode and the locations of all the deathrow isn't connect continuously; on the other hand,the locations of all the deathrow is connect continuously
    if(direction>0)
        deathrow=headnode->rlink->rlink;
    else if(direction<0)
        deathrow=headnode->llink;
    while(1)
    {
        //termination condition
        if((deathrow->rlink)==headnode && (deathrow->llink)==headnode)
        {
            printf("the last data is : %s\n",deathrow->data);
            break;
        }
        printf("list length is : %d\n",n--);
        
        //decide deathrow's location
        if(direction>0)
        {
            for(i=0;i<k;i++)
            {
                if((deathrow->rlink)==headnode)
                    deathrow=deathrow->rlink->rlink;
                else
                    deathrow=deathrow->rlink;
            }
            if((deathrow->rlink)==headnode)
                temp=deathrow->rlink->rlink;
            else
                temp=deathrow->rlink;
        }
        else if(direction<0)
        {
            for(i=0;i<k;i++)
            {
                if((deathrow->llink)==headnode)
                    deathrow=deathrow->llink->llink;
                else
                    deathrow=deathrow->llink;
            }
            if((deathrow->llink)==headnode)
                temp=deathrow->llink->llink;
            else
                temp=deathrow->llink;
        }
        printf("the data is popped : %s\n",deathrow->data);
        deletenode(deathrow);
        //set next initial deathrow,because the original deathrow has been free
        deathrow=temp;
    }
    
}

int main()
{
    int input,direction,k,n;
    while(1)
    {
        nodepointer headnode=(nodepointer) malloc(sizeof(struct node));
        headnode->llink=headnode;
        headnode->rlink=headnode;
        headnode->data[0]='\0';
        printf("What do you want to do?\n");
        printf("(1)Read data from a file\n");
        printf("(2)Append new nodes\n");
        printf("(0)Exit\n");
        scanf("%d",&input);getchar();
        if(input==1)
            n=readfile(headnode);//deliver the location which is pointed by the headnode(rather than the headnode's location,&headnode),that is,change the location's contents rather than the headnode's
        else if(input==2)
            n=writedata(headnode);
        else if(input==0)
            return 0;
        
        printf("choose direction\n");
        printf("(1)right\n");
        printf("(2)left\n");
        scanf("%d",&direction);getchar();
        if(direction==1)//right's direction = 1
            printf("the direction is : right\n");
        else if(direction==2)
        {
            printf("the direction is : left\n");
            direction=direction-3;//left's direction = 2-3 = -1
        }
        printf("Input skip number\n");
        scanf("%d",&k);getchar();
        printf("the skip number is : %d\n",k);
        RussianRoulette(direction,k,headnode,n);
        free(headnode);
    }
}
