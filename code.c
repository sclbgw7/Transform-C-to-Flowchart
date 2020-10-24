//Put your code here
//sample
#include <stdio.h>

int main()
{
	int a,sum;sum=0;
	scanf("%d",&a);
	for(int i=1;i<=a;i++)
	{
		if((i>10086&&i<1)||a!=sum)
		{
			continue;
		}
		a+=sum;
	}
	while(sum>a&&(a<0||a>0))
	{
		if(a<0)break;
		else
		{
			a++;
			continue;
		}
		
	}
	printf("%d\n",(sum+1)/2);
	return 0;
}
