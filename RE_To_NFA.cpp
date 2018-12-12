#include<stdio.h>
#include<string.h>

int main()
{
	char reg[20];
	int q[20][3],i,j,len,a,b;
	int tmp[20],k,count,add[20];
	
	for(a=0;a<20;a++)
	{
		for(b=0;b<3;b++)
		{
			q[a][b]=0;
		}
	}
	printf("Regular expression: \n");

	scanf("%s",reg);
	len=strlen(reg);
	i=0; //Ki tu trong chuoi
	j=0; //Trang thai
	k=0;
	count=0;
	//Ham xu ly bieu thuc chinh quy 
	while(i<len)
	{
		if(reg[i]=='a' && reg[i+1] !='*')
		{
			q[j][0]=j+1;
			j++;
		}
		
		if(reg[i]=='b' && reg[i+1] !='*')
		{
			q[j][1]=j+1;
			j++;
		}
		
		if(reg[i]=='e' && reg[i+1] !='*')
		{
			q[j][2]=j+1;
			j++;
		}
		
		if(reg[i]=='+')
		{
			tmp[k] = j;						
			add[k] = j+1;			
			k++;
			count++;
			j++;	
		}
		
		if(reg[i]=='a' && reg[i+1]=='*')
		{
				q[j][2]=j+1;
				j++;
				q[j][0]=j+1;
				j++;
				q[j][2]=j-1;
		}
		
		if(reg[i]=='b' && reg[i+1]=='*')
		{
				q[j][2]=j+1;
				j++;
				q[j][1]=j+1;
				j++;
				q[j][2]=j-1;
		}
		i++;
	}
	
	for (k=0;k<count;k++)
	{
		q[tmp[k]][2] = j;
	}
	
	printf ("NFA: \n");
	
	printf ("Q = {");
	for (i=0;i<j;i++) printf ("q%d, ",i);
	printf ("q%d }\n",j);
	
	printf ("A = {a,b}\n");
	
	printf ("Start state: q0 \n");
	
	printf ("Finish State: q%d \n ", j);
	
	printf("Transition function: \n");
	for(i=0;i<=j;i++)
	{
		if(q[i][0]!=0)
			printf("\n f[q%d,a]-->q%d",i,q[i][0]);
		if(q[i][1]!=0)
			printf("\n f[q%d,b]-->q%d",i,q[i][1]);
		if (count !=0)
		{
		if(i==0)
		{
			printf("\n f[q%d,e]-->",i);
			for (k = 0;k<count;k++)
			{
				printf("q%d ",add[k]);
				if ( k != count - 1) printf("& ");
			}
		}
		else
		{
			if(q[i][2]!=0)
			{
				printf("\n f[q%d,e]-->q%d",i,q[i][2]);
			}
		}
		}
		else
		{
			if(q[i][2]!=0)
				printf("\n f[q%d,e]-->q%d",i,q[i][2]);
		}
	}
	printf("\n");
}
