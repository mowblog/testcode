#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

int getnum_red(int k)
{
 int i;
 int j=k*32;
 for(i=1;j>=0;i++,j++)
  {
   if(i>=32)
    i=1;
   if(j-i<=3)
    break;
   else
    j=j-3;
  }
return (i);
};

int getnum_blue(int f)
{
 int i;
 int j=f*16;
  for(i=1;j>=0;i++,j++)
    {
     if(i>=16)
      i=1;
     if(j-i<=3)
      break;
       else
    j=j-3; 
    }
return (i);
}

int create(int th)
{
 int m;
 int n=th;
 int num;
 int well;
 srand((unsigned)time(NULL));
 well=rand();
    if(n<7)
      {
       well=well*2-1;
       num=getnum_red(well);
      }
     else
      {
       well=well%3+10;
       num=getnum_blue(well-1);
      }
return (num);
}

void main()
{
 int getnum_red(int);
 int getnum_blue(int);
 int num,well;
 int bar;
 char ;
 int a,b;
 int sucess[7];


 for(a=0;a<=6;a++)
  {
   if(a==0)
    sucess[a]==create(well);
   else
    {
      for(b=0;b<a;b++)
      if (sucess[a]==sucess[b])
        sucess[a]=create(well);
    }
  }
  for(a=0;a<=6;a++)
   printf("%d ",sucess[a]);
  getch();
}
