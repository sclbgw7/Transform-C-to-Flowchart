//Put your code here
//sample
#include <stdio.h>

int main()
{
	int a,b,c;
	scanf("%d%d",&a,&b,&c);
	if(a>b)
	  while(b>0)
	  {
		  b--;/*sui bian xie de*/
		  c+=b;
	  }
	printf("%d\n",c);
	return 0;
}
