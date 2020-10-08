//Put your code here
//sample2
#include <stdio.h>

int main()
{
	int a,sum;sum=0;
	scanf("%d",&a);
	for(int i=1;i<=a;i++)
	{
		if(i>10086)
		{
			continue;
		}
		a+=sum;
	}
	while(sum>a)
	{
		if(a<0)break;
		else
		{
			a++;
			continue;
		}
		
	}
	printf("%d\n",sum);
	return 0;
}
