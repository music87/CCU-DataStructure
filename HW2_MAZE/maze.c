#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int row;
    int col;
}POSITION;

void setmaze(int maze[17][17],int Amark[17][17],int Bmark[17][17])
{
    FILE *fptr;
    fptr=fopen("maze.txt","r");
    int i,j;
    char tmp;
    for(i=1;i<=15;i++)
    {
        maze[0][0]=maze[0][16]=maze[16][0]=maze[16][16]=1;
        maze[0][i]=maze[i][0]=maze[i][16]=maze[16][i]=1;
        Amark[0][0]=Amark[0][16]=Amark[16][0]=Amark[16][16]=Amark[0][i]=Amark[i][0]=Amark[i][16]=Amark[16][i]=0;
        Bmark[0][0]=Bmark[0][16]=Bmark[16][0]=Bmark[16][16]=Bmark[0][i]=Bmark[i][0]=Bmark[i][16]=Bmark[16][i]=0;
        for(j=1;j<=15;j++)
        {
            Amark[i][j]=Bmark[i][j]=0;
            fscanf(fptr,"%c",&tmp);
            if(tmp=='\n')fscanf(fptr,"%c",&tmp);
            if(tmp=='1')maze[i][j]=1;
            else if(tmp=='0')maze[i][j]=0;
        }
    }
    fclose(fptr);
}

void pop(POSITION stack[],POSITION *now,int *top)//deliver top's value to now
{
    (*now).row=stack[(*top)].row;
    (*now).col=stack[(*top)].col;
}

void push(POSITION stack[],POSITION now,int *top)//add now into the stack
{
    (*top)++;
    stack[(*top)].row=now.row;
    stack[(*top)].col=now.col;
}

void tryAdirection(int direction,POSITION now,POSITION *next)
{
    (*next).row=now.row;
    (*next).col=now.col;
    
    if(direction==1)//right
        (*next).col=now.col+1;
    else if (direction==2)//down
        (*next).row=now.row+1;
    else if (direction==3)//up
        (*next).row=now.row-1;
    else if (direction==4)//left
        (*next).col=now.col-1;
}

void tryBdirection(int direction,POSITION now,POSITION *next)
{
    (*next).row=now.row;
    (*next).col=now.col;
    
    if(direction==1)//left
        (*next).col=now.col-1;
    else if (direction==2)//up
        (*next).row=now.row-1;
    else if (direction==3)//down
        (*next).row=now.row+1;
    else if (direction==4)//right
        (*next).col=now.col+1;
}

int main()
{
    int maze[17][17],found,direction;
    int Amark[17][17],Bmark[17][17],Atop,Btop;
    POSITION Astack[257],Bstack[257];
    POSITION Anow,Bnow,Anext,Bnext;
    FILE *fptr;
    fptr=fopen("result.txt","w");
    
    setmaze(maze,Amark,Bmark);
    
    //initial
    found=0;
    
    Atop=0;//A start at (1,1)
    Astack[0].row=Astack[0].col=1;
    Amark[1][1]=1;
    
    Btop=0;//B start at (15,15)
    Bstack[0].row=Bstack[0].col=15;
    Bmark[15][15]=1;
    
    
    //---if "either" have not arrive the export(try) and stack is not empty
    while(Atop>-1 && Btop>-1 && !found)
    {
        pop(Astack,&Anow,&Atop);
        pop(Bstack,&Bnow,&Btop);
        //printf("ratA(%d,%d)\n",Anow.row-1,Anow.col-1);
        //printf("ratB(%d,%d)\n",Bnow.row-1,Bnow.col-1);
        fprintf(fptr,"ratA(%d,%d)\n",Anow.row-1,Anow.col-1);
        fprintf(fptr,"ratB(%d,%d)\n",Bnow.row-1,Bnow.col-1);
        
        //---if "either" have arrive the export(find the path) or stack is empty(no path) , end the program
        if((Anow.row==15 && Anow.col==15) || (Bnow.row==1 && Bnow.col==1))
        {
            found=1;
            break;
        }
        
        //determine A's next step start
        //try four direction(A)
        for(direction=1;direction<=4;direction++)
        {
            tryAdirection(direction,Anow,&Anext);//see where is the next
            //test this direction is ok or not（unvisited and not out of boundary)
            if(!maze[Anext.row][Anext.col] && !Amark[Anext.row][Anext.col])
            {
                //if ok , "push" in the stack and "mark" the position
                push(Astack,Anext,&Atop);
                Amark[Anext.row][Anext.col]=1;
                break;
            }
        }
        //if not and complete trying four direction , "pop" out the stack to go previous position)
        if(direction>4)
        {
            pop(Astack,&Anow,&Atop);
            Atop--;
        }
        //determine A's next step end
        
        //determine B's next step start
        //try four direction(B)
        for(direction=1;direction<=4;direction++)
        {
            tryBdirection(direction,Bnow,&Bnext);
            //test this direction is ok or not（unvisited and not out of boundary)
            if(!maze[Bnext.row][Bnext.col] && !Bmark[Bnext.row][Bnext.col])
            {
                //if ok , "push" in the stack and "mark" the position
                push(Bstack,Bnext,&Btop);
                Bmark[Bnext.row][Bnext.col]=1;
                break;
            }
        }
        //if not and complete trying four direction , "pop" out the stack to go previous position)
        if(direction>4)
        {
            pop(Bstack,&Bnow,&Btop);
            Btop--;
        }
        //determine B's next step end
        
    }
    if(!found) fprintf(fptr,"no path found\n");
    else fprintf(fptr,"the path is found and listed completely above\n");
    fclose(fptr);
    return 0;
}
