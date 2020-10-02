#include<stdio.h>

//for kruskal
typedef struct
{
    int w;
    int v1;
    int v2;
} EDGE;

//for prim
typedef struct
{
    int fromedgeweight;//the cost spending to arrive the vertex
    int from;
    int visit;
} pVERTEX;

//for dijkstra
typedef struct
{
    int distance;//distance from source
    int from;
    int visit;
} dVERTEX;

void PushMinHeap(EDGE heap[],int *nedge,EDGE newedge)
{
    int parent,child,tmp;
    child=++(*nedge);
    parent=child/2;
    heap[child]=newedge;
    while(heap[parent].w>heap[child].w && child!=1)
    {
        tmp=heap[parent].w;heap[parent].w=heap[child].w;heap[child].w=tmp;
        tmp=heap[parent].v1;heap[parent].v1=heap[child].v1;heap[child].v1=tmp;
        tmp=heap[parent].v2;heap[parent].v2=heap[child].v2;heap[child].v2=tmp;
        child=parent;
        parent/=2;
    }
}

void PopMinHeap(EDGE heap[],int *nedge)
{
    int parent,minchild,tmp;
    parent=1;
    heap[parent].w=heap[*nedge].w;
    heap[parent].v1=heap[*nedge].v1;
    heap[parent].v2=heap[*nedge].v2;
    (*nedge)--;
    //adjust
    if(heap[parent*2].w<heap[parent*2+1].w)
        minchild=parent*2;
    else
        minchild=parent*2+1;
    while(heap[parent].w>heap[minchild].w && parent<=(*nedge) && minchild!=-1)
    {
        tmp=heap[parent].w;heap[parent].w=heap[minchild].w;heap[minchild].w=tmp;
        tmp=heap[parent].v1;heap[parent].v1=heap[minchild].v1;heap[minchild].v1=tmp;
        tmp=heap[parent].v2;heap[parent].v2=heap[minchild].v2;heap[minchild].v2=tmp;
        //update parent
        parent=minchild;
        //determine new parent's minchild
        if((parent*2+1)<=(*nedge))//2 child
        {
            if(heap[parent*2].w<heap[parent*2+1].w)
                minchild=parent*2;
            else
                minchild=parent*2+1;
        }
        else if(parent*2==(*nedge))//1 child
            minchild=parent*2;
        else
            minchild=-1;
    }
}

//find vertex's root and speed up the finding process
int CollapsingFind(int vertex,int subset[])
{
    int root,trail,lead;
    //find vertex's root
    for(root=vertex;subset[root]>=0;root=subset[root]);
    //collapsing
    for(trail=vertex;trail!=root;trail=lead)
    {
        lead=subset[trail];//next who will be collapsing is trail's parent
        subset[trail]=root;//let trail's parent be root
    }
    return root;
}

//union subset1 with root1 and subset2 with root2
void WeightedUnion(int root1,int root2,int subset[])
{
    int tmp;
    tmp=subset[root1]+subset[root2];
    if(subset[root1]>subset[root2])//subset1's n(child) < subset2's n(child)
    {
        subset[root1]=root2;//subset 1's root change to subset2's root
        subset[root2]=tmp;//update subset2's n(child)
    }
    else
    {
        subset[root2]=root1;
        subset[root1]=tmp;
    }
    
    
}

void kruskal()
{
    FILE *fin;
    fin=fopen("input1.txt","r");
    
    int n,i,j;
    fscanf(fin,"%d",&n);
    //read graph by adjacency matrix and build min heap to store edge
    int G[n+1][n+1],nedge;
    EDGE heap[n*(n-1)],newedge;
    nedge=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            fscanf(fin,"%d",&G[i][j]);
            if(i<j && G[i][j]!=0)//i<j because symmetric triangle
            {
                newedge.v1=i;
                newedge.v2=j;
                newedge.w=G[i][j];
                
                PushMinHeap(heap,&nedge,newedge);
            }
        }
    //initial n trees,which means n subsets
    int subset[n+1];
    //initially every subsets has one vertex and the vertex is root(<0)
    for(i=1;i<=n;i++)
        subset[i]=-1;
    
    //kruskal
    EDGE edge;
    int root1,root2,nMST,sum;
    nMST=1;sum=0;
    //pop min heap until heap is empty
    printf("The output is\n");
    while(nedge>0)
    {
        //pick min edge and adjust min heap
        edge=heap[1];
        PopMinHeap(heap,&nedge);
        //if v1 and v2 are under same subset(by check each subset's root is same or not),continue
        root1=CollapsingFind(edge.v1,subset);
        root2=CollapsingFind(edge.v2,subset);
        //because v1 and v2 are in the same subset which means that they have been connected through other edge,union them wil cause cycle
        if(root1==root2)
            continue;
        //else union v1's subset and v2's subset
        WeightedUnion(root1,root2,subset);
        printf("Edge %d:<%d %d> cost:%d\n",nMST,edge.v1,edge.v2,edge.w);
        sum+=edge.w;
        nMST++;
    }
    printf("Minimum cost = %d\n",sum);
    fclose(fin);
}

void prim()
{
    FILE *fin;
    fin=fopen("input2.txt","r");
    
    int source,n,i,j,mincost,mincostvertex,nedge,sum,oo=2147483646;
    fscanf(fin,"%d",&n);
    //read graph by adjacency matrix
    int G[n+1][n+1];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            fscanf(fin,"%d",&G[i][j]);
    //set initial current min cost,from what vertex to itself,and visit
    pVERTEX v[n+1];
    for(i=1;i<=n;i++)
    {
        v[i].fromedgeweight=oo;
        v[i].from=-1;
        v[i].visit=0;
    }
    //prim
    fscanf(fin,"%d",&source);
    v[source].fromedgeweight=0;
    nedge=0;
    sum=0;
    printf("The output is\n");
    for(i=1;i<=n;i++)
    {
        //find the vertex which spends min edge cost to itself
        mincost=oo;
        for(j=1;j<=n;j++)
        {
            if(v[j].fromedgeweight<mincost && !v[j].visit)
            {
                mincost=v[j].fromedgeweight;
                mincostvertex=j;
            }
        }
        v[mincostvertex].visit=1;
        sum+=v[mincostvertex].fromedgeweight;
        
        //print
        if(mincostvertex!=source)
            printf("Edge %d:<%d %d> cost:%d\n",nedge,v[mincostvertex].from,mincostvertex,v[mincostvertex].fromedgeweight);
        
        //update the current cost from mincostvertex to v[j] which adjacency to mincostvertex
        for(j=1;j<=n;j++)
        {
            //find v[j] which is "adjacency" to mincostvertex and have not visit
            if(!v[j].visit && G[mincostvertex][j])
            {
                //update
                if(G[mincostvertex][j]<v[j].fromedgeweight)
                {
                    v[j].from=mincostvertex;
                    v[j].fromedgeweight=G[mincostvertex][j];
                }
            }
        }
        nedge++;
    }
    printf("Minimum cost=%d\n",sum);
    fclose(fin);
}

void dijkstra()
{
    FILE *fin;
    fin=fopen("input3.txt","r");
    
    int n,i,j,start,end,oo=2147483646,mindistance,mindistancevertex;
    fscanf(fin,"%d",&n);
    //read graph by adjacency matrix
    int G[n+1][n+1];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            fscanf(fin,"%d",&G[i][j]);
    //enter start and end
    printf("Enter two vertices <start end>:");
    scanf("%d%d",&start,&end);
    //set initial distance from source,from vertex,visit
    dVERTEX v[n+1];
    for(i=1;i<=n;i++)
    {
        v[i].from=-1;
        v[i].distance=oo;
        v[i].visit=0;
        if(G[start][i])
            v[i].distance=G[start][i];
    }
    v[start].distance=0;
    
    //dijkstra
    for(i=1;i<=n;i++)
    {
        //find min distance's vertex
        mindistance=oo;
        for(j=1;j<=n;j++)
        {
            if(!v[j].visit && v[j].distance<mindistance)
            {
                mindistance=v[j].distance;
                mindistancevertex=j;
            }
        }
        v[mindistancevertex].visit=1;
        
        /*printf("%d,%d\n",mindistancevertex,v[mindistancevertex].distance);
         printf("distance:");
         for(j=1;j<=n;j++)
         printf("%d\t",v[j].distance);
         printf("\n");*/
        
        
        //update the distance from mindistancevertex to v[j] which adjacency to mincostvertex
        for(j=1;j<=n;j++)
        {
            if(!v[j].visit && G[mindistancevertex][j])
            {
                if(v[mindistancevertex].distance+G[mindistancevertex][j]<v[j].distance)
                {
                    v[j].distance=v[mindistancevertex].distance+G[mindistancevertex][j];
                    v[j].from=mindistancevertex;
                }
            }
        }
    }
    printf("The cost from %d to %d is : ",start,end);
    if(v[end].distance!=oo)
        printf("%d\n",v[end].distance);
    else
        printf("-1\n");
}

int main()
{
    int option;
    printf("(1)Kruskal\n");
    printf("(2)Prim\n");
    printf("(3)Dijkstra\n");
    scanf("%d",&option);
    if(option==1)
        kruskal();
    else if(option==2)
        prim();
    else if(option==3)
        dijkstra();
    return 0;
}
