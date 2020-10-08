//Put your code here
//sample1:zhan zhuan xiang chu fa
#include <stdio.h>

int main()
{
	int a , b , temp ;
	scanf("%d%d",&a,&b);
	if (a < b) swap(a,b);

	while (b != 0) {
		temp = a % b;
		a = b;
		b = temp;
	}
	printf("%d\n",a);
	return 0;
}
