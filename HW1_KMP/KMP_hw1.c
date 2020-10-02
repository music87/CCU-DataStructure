#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    int index,sum;
    char name[201];
}DATA;

void myread(char finalstring[])
{
    FILE *fp=NULL;
    char line[501];
    int i,n,j,tmp;
    unsigned long  len;
    DATA data[200];
    
    fp=fopen("data.csv","r");
    i=0;
    while(fgets(line,500,fp)!=NULL)
    {
        //read new data start
        char *start;
        start=strtok(line,",");
        strcpy(data[i].name,start);
        printf("===the name : %s\n",data[i].name);
        
        start=strtok(NULL,"\n\r");
        data[i].index=atoi(start);
        printf("===the index : %d\n",data[i].index);
        //read new data end
        
        //combine and print finalstring start
        len=strlen(finalstring);
        for(j=0;j<len;j++)
            finalstring[j]=0;
        n=i+1;//total i+1 datas（i count from 0）to combine finalstring
        data[0].sum=0;//determine the location of copy
        for(j=1;j<n;j++)
            data[j].sum=data[j-1].sum+data[j-1].index;
        
        for(j=0;j<n-1;j++)//start to copy,here copy pre-string
        {
            strncat(finalstring,data[j].name,data[j+1].sum-data[j].sum);
            finalstring[strlen(finalstring)]='\0';
        }
        strcat(finalstring,data[j].name);
        
        for(j=n-2;j>=0;j--)//continue to copy，here copy remaining-part of string
        {
            tmp=data[j+1].sum-data[j].sum;
            strcat(finalstring,&data[j].name[tmp]);
        }
        printf("finalstring : %s\n",finalstring);
        //combine and print finalstring end
        
        i++;
    }
    fclose(fp);
}

void mywrite(char finalstring[])
{
    int leave,i,j,n,tmp;
    unsigned long len;
    char line[501];
    DATA data[200];
    printf("Please input the date.If you don't want to input anything else,please input -1.\n");
    i=0;
    while(1)
    {
        //write new data start
        printf("===the name : ");
        fgets(line,500,stdin);
        line[strlen(line)-1]='\0';
        
        leave=atoi(line);//determine whether the user do or do not want to type in anything else
        if(leave==-1)//user finishes inputing data,leave
            return;
        
        strcpy(data[i].name,line);
        
        printf("===the index : ");
        scanf("%d",&data[i].index);getchar();
        //write new data end
        
        //combine and print finalstring start
        len=strlen(finalstring);
        for(j=0;j<len;j++)
            finalstring[j]=0;
        n=i+1;//total i+1 datas（i count from 0）to combine finalstring
        data[0].sum=0;//determine the location of copy
        for(j=1;j<n;j++)
            data[j].sum=data[j-1].sum+data[j-1].index;
        
        for(j=0;j<n-1;j++)//start to copy,here copy pre-string
        {
            strncat(finalstring,data[j].name,data[j+1].sum-data[j].sum);
            finalstring[strlen(finalstring)]='\0';
        }
        strcat(finalstring,data[j].name);
        
        for(j=n-2;j>=0;j--)//continue to copy，here copy remaining-part of string
        {
            tmp=data[j+1].sum-data[j].sum;
            strcat(finalstring,&data[j].name[tmp]);
        }
        printf("finalstring : %s\n",finalstring);
        //combine and print finalstring end
        
        i++;
    }
    
}


void fail(char pattern[],int fail[],unsigned long len)
{
    int i,j;
    
    fail[0]=-1;
    //i means where it's test in "pattern" now . in order to find fail[i]
    for(i=1;i<len;i++)
    {
        j=fail[i-1];
        //we have known pat[i-1]==pat[fail[i-1]],pat[fail[i-1]]==pat[fail[fail[i-1]],...
        /*pat[i] v.s. pat[fail[j-1]+1],if not equal,then
         pat[i] v.s. pat[fail[fail[j-1]]+1],if not equal,then
         pat[i] v.s. pat[fail[fail[fail[j-1]]]+1],if not equal,then
         ......*/
        while(pattern[i]!=pattern[j+1] && j>=0)
            j=fail[j];
        
        if(pattern[i]==pattern[j+1])
            j=j+1;
        else
            j=-1;
        fail[i]=j;
    }
}


void KMP(char string[],char pattern[],int fail[])
{
    int i,j;
    unsigned long len;
    len=strlen(string);
    char tmp[len];
    len=strlen(string);
    for(i=0,j=0;i<len;)//i means where it's test in "pattern" now .in order to find where pattern and string are equal
    {
        if(pattern[j]==string[i])/*try pat[j+1] v.s. str[i+1]*/
        {
            i++;j++;
            if(j==strlen(pattern))//match
            {
                //printf("locate between %d and %d\n",i-j,i-1);
                strncpy(tmp,string,i-j);tmp[i-j]='\0';//copy pre-string
                strcat(tmp,&string[i]);//copy remaining-part of string
                strcpy(string,tmp);//pop
                i=i-j;j=0;//the pattern have been pop,so you have to re-adjust the location of index
                //printf("string=%s\n",string);
                break;//only pop the first matching
            }
        }
        else
        {
            if(j==0)/*step by step,try pat[j==0] v.s. str[i+1]*/
                i++;
            else
            {
                /*KMP,
                 we have known that pat[j]!=str[i] && j!=0
                 try pat[fail[j-1]+1] v.s. str[i]
                 next time entry here will try pat[fail[fail[j-1]]+1] v.s. str[i]
                 next^2 time entry here will try pat[fail[fail[fail[j-1]]]+1] v.s. str[i]
                 ......
                 */
                j=fail[j-1]+1;//j is set to -1+1=0 at least
            }
        }
    }
    printf("the output is : %s\n",string);
}

int main()
{
    int num,i;
    char string[1001],pattern[1001];
    while(1)
    {
        printf("What do you want to do?Please input the number.\n");
        printf("(1)Read data from a file.\n");
        printf("(2)Write new data\n");
        printf("(3)Use KMP to pop data\n");
        printf("(0)Exit\n");
        scanf("%d",&num);getchar();
        
        if(num==1)//Read data from a file(set string)
        {
            printf("=================================\n");
            myread(string);
            printf("=================================\n");
        }
        
        else if(num==2)//Write new data(set string)
        {
            printf("=================================\n");
            mywrite(string);
            printf("=================================\n");
        }
        
        else if(num==3)//Use KMP to pop data
        {
            printf("input pop name : \n");
            fgets(pattern,1000,stdin);
            pattern[strlen(pattern)-1]='\0';
            printf("input pop name is : %s\n",pattern);
            
            //set pattern's lps start
            unsigned long len;
            len=strlen(pattern);
            int lps[len];
            fail(pattern,lps,len);
            printf("lps={");
            for(i=0;i<len-1;i++)
                printf("%d,",lps[i]+1);
            printf("%d}\n",lps[i]+1);
            //set pattern's lps end
            
            KMP(string,pattern,lps);
        }
        else if(num==0) break;
    }
    return 0;
}
