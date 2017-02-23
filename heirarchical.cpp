#include<iostream>
#include<sys/time.h>
const int size=15;
using namespace std;

struct node
{
	char name;
    unsigned dist[size];
    unsigned from[size];
    unsigned region;
}rt[size];
/*
void quick(int l,int u,int *temp,int *s)
{
   	int p,i,j,t;
   	if(l<u)
   	{
   		p=temp[l];
   		i=l;
   		j=u;
    	while(i<j)
   		{
    		while(temp[i]<=p && i<j )
				i++;
      		while(temp[j]>p && i<=j )
	  			j--;
      		if(i<=j)
      		{	
			  	t=temp[i];
				temp[i]=temp[j];
				temp[j]=t;
				t=s[i];
				s[i]=s[j];
				s[j]=t;
			}
  		}				
		t=temp[j];
		temp[j]=temp[l];
		temp[l]=t;
		t=s[j];
		s[j]=s[l];
		s[l]=t;
  		quick(l,j-1,temp,s);
  		quick(j+1,u,temp,s); 
 	}
}
*/
void sort(int a[], int s[], int n)
{
	int i, j, temp[size], t;
	for(i=0; i<n; i++)
		temp[i]=a[i];
	for(i=0; i<n; i++)
		for(j=i+1; j<n; j++)
			if(temp[i]>temp[j])
			{
				t=temp[i];
				temp[i]=temp[j];
				temp[j]=t;
				t=s[i];
				s[i]=s[j];
				s[j]=t;	
			}
}

int main()
{
	struct timeval tv1,tv2;
	unsigned least=65535;
	int i, j, k, l, r[size], n=12, conn[size], temp[size], regi=0, sorted[size], flag=0, count;
	int costmat[12][12]={{0,1,1,65535,65535,65535,65535,65535,65535,65535,65535,65535},
							{1,0,1,1,65535,65535,65535,65535,65535,65535,65535,65535},
							{1,1,0,65535,65535,65535,65535,65535,65535,65535,65535,1},
							{65535,1,65535,0,1,1,65535,65535,65535,65535,65535,65535},
							{65535,65535,65535,1,0,65535,1,65535,65535,65535,65535,65535},
							{65535,65535,65535,1,65535,0,1,65535,65535,65535,65535,65535},
							{65535,65535,65535,65535,1,1,0,1,65535,65535,65535,65535},
							{65535,65535,65535,65535,65535,65535,1,0,1,1,65535,65535},
							{65535,65535,65535,65535,65535,65535,65535,1,0,65535,65535,1},
							{65535,65535,65535,65535,65535,65535,65535,1,65535,0,1,65535},
							{65535,65535,65535,65535,65535,65535,65535,65535,65535,1,0,1},
							{65535,65535,1,65535,65535,65535,65535,65535,1,65535,1,0},
						};
	char x='A';
	
	/*cout<<"Enter the number of nodes: ";
	cin>>n;
	for(i=0; i<n; i++)
	{
		cout<<"Assign a character to node "<<i+1<<" :\t";
		cin>>rt[i].name;
		rt[i].dist[i]=0;
		rt[i].region=0;
	}
	cout<<"\nEnter the cost matrix :\n";*/
	
	gettimeofday(&tv1,NULL);
	for(i=0; i<n; i++)
	{
		rt[i].name=x++;
		rt[i].dist[i]=0;
		rt[i].region=0;
	}
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		{
            rt[i].dist[j]=costmat[i][j];	//initialise the distance equal to cost matrix
            rt[i].from[j]=j;
		}

	for(i=0; i<n; i++)
		for(conn[i]=0, j=0; j<n; j++)
			if(rt[i].dist[j]==1)
				conn[i]++;
	
	for(i=0; i<n; i++)
	{
		temp[i]=conn[i];
	}
	
	for(i=0; i<n; i++)
		sorted[i]=i;
	
	//quick(0,n,temp,sorted);
	sort(conn,sorted,n);
	
	for(i=0; i<n ;i++)						//Assigning region to the nodes
	{
		if(rt[sorted[i]].region==0)
		{
			for(flag=0, j=0; j<n; j++)
			{
				if(rt[sorted[i]].dist[j]==1 && rt[j].region!=0)
				{
					flag=1;
					break;	
				}
			}
			if(flag==1)
					rt[sorted[i]].region=rt[j].region;
			else
			{
				rt[sorted[i]].region=++regi;
				for(j=0; j<n; j++)
					if(rt[sorted[i]].dist[j]==1)
							rt[j].region=regi;
			}	
		}
	}
	
	do
    {
        count=0;
        for(i=0;i<n;i++)		//We choose arbitary vertex k and we calculate the direct distance from
        	for(j=0;j<n;j++)	//the node i to k using the cost matrix and add the distance from k to node j
        		for(k=0;k<n;k++)
		            if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j])
		            {			//We calculate the minimum distance
		                rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
		                rt[i].from[j]=k;
		                count++;
		            }
    }while(count!=0);
	
   for(i=0;i<n;i++)
    {
        cout<<"\n\n For node "<<rt[i].name<<endl;
        for(j=0;j<n ;j++)
        {
        	if( rt[i].region==rt[j].region)
            	cout<<"\t\nTo node "<<rt[j].name<<" via "<<rt[rt[i].from[j]].name<<" Distance is "<<rt[i].dist[j];
        }
        for(l=1; l<=regi; l++)
        {
        	if(rt[i].region!=l)
        	{
        		for(least=65535, j=0; j<n; j++)
        		{
        			if(rt[j].region==l)
        			{
        				if(rt[i].dist[j]<least)
        				{
        					least=rt[i].dist[j];
        					r[l]=rt[i].from[j];
						}
					}
				}
				cout<<"\t\nTo region "<<l<<" via "<<rt[r[l]].name<<" Distance is "<<least;
			}
		}
    }
    gettimeofday(&tv2,NULL);
    cout<<endl<<tv2.tv_usec<<endl<<tv1.tv_usec;
	cout<<"\nTotal time taken : "<<(double)(tv2.tv_usec-tv1.tv_usec);
	return 0;
}
