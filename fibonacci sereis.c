#include<stdio.h>
int main()
{
	int t1=0,t2=1,t3,i,number;
	printf("enter the number:");
	scanf("%d",&number);
	printf("\n%d%d",t1,t2);
	for(i=2;i<number;++i)
	{
		t3=t1+t2;
		printf("%d",t3);
		t1=t2;
		t2=t3;
	}
	return 0;
}
