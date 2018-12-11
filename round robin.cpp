#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cstdlib>
#include<ctime>
using namespace std;
struct node
{
    int pid;
    int ptime;
    struct node *next;
    struct node *prev;
};
static int i=1;
struct node *insert (struct node *head)
{
    int btime;
    node *ptr=head,*temp;
 temp=new node;
 temp->pid=i;
 i++;
 btime=rand()%100;
 temp->ptime=btime;

 if(head==NULL)
 {
  head=temp;
  temp->next=head;
  temp->prev=head;
 }
 else{

  while(ptr->next!=head)
  {
      ptr=ptr->next;
  }
  ptr->next=temp;
  temp->next=head;
  temp->prev=ptr;
  head->prev=temp;
 }
 return head;
};
void display(struct node *start)
{
    cout<<"Pid: \t Ptime:\n";
    struct node *ptr=start;
    while(ptr->next!=start)
    {
        cout<<ptr->pid<<"\t"<<ptr->ptime<<endl;
        ptr=ptr->next;
    }
        cout<<ptr->pid<<"\t"<<ptr->ptime<<endl;
}
struct node *deletion(struct node *head)
{
 node *temp=head;
 if(head==NULL)
 {cout<<"No node in queue"<<endl;
 return head;
 }

 if(head->next==head)
 {
     head=NULL;
 }
 else
{
 node *ptr=head->next;
 ptr->prev=ptr->prev->prev;
 ptr->prev->next=ptr;
 head=ptr;
}
 delete(temp);
 return head;
}
struct node *roundrobin(struct node *head,int a[][2],int *m)
{
    int f=0;
    int totaltime=1500;
    static int c=0;
    int q;
    while(f!=1)
        {

        int x=rand()%20;
        if(x==0 || x==1 )
        {
            f=0;
        }
        else
            {
                q=x;
                f=1;
            }
    }
    node* ptr=head;
    cout<<"The time quantum is : "<<q<<endl;
    int nptime = rand()%10;
    while(ptr!=NULL)
 {
  int t=0,id;

  if(ptr->ptime<=q)
  {
      t=ptr->ptime;
      id=ptr->pid;
      ptr->ptime=0;
      //cout<<ptr->pid<<"\t"<<ptr->ptime<<endl;
      ptr=deletion(ptr);
  }
  else
  {
       ptr->ptime=ptr->ptime-q;
       t=q;
       id=ptr->pid;
       //cout<<ptr->pid<<"\t"<<ptr->ptime<<endl;
       ptr=ptr->next;
  }
  a[c][0]=id;
  if(c>0)
  {
      t+=a[c-1][1];
  }
  a[c][1]=t;
  c++;
  if(t>=totaltime)
      break;
  if(t>=nptime)
  {
      ptr=insert(ptr);
      nptime=rand()%(t+100);
  }
}
*m=c;
 return ptr;
};
int main()
{
    srand(time(NULL));
    int gc[1000][2]={0},m;
    struct node *start=NULL;
    int t=3;

    while(t--)
    {
        start=insert(start);
    }
    display(start);
    start=roundrobin(start,gc,&m);
   // start=deletion(start);

    cout<<"------------ GANT CHART -----------"<<endl<<endl;
for(i=0;i<m;i++)
 {
     cout<<gc[i][0]<<" "<<gc[i][1]<<endl;
 }
    return 0;
}

