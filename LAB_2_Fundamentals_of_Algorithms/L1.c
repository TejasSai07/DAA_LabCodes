#include<stdio.h>
int GreCD(int a, int b ){
	int opcount = 0;

	int gcd = 1;
	int small = a < b ? a : b;

	for(int i = small; i>=2;i--) {
		opcount++;
		if(a%i==0 && b%i==0){
			gcd = i;
			return gcd;
		}
		}
	printf("OpCount is : %d \n",opcount);
	return gcd;
}


void main(){
	int a,b;

	printf("Enter Value of A : \n");
	scanf("%d",&a);
	printf("Enter Value of B : \n");
	scanf("%d",&b);

	int GCD;

	GCD = GreCD(a,b);

	printf("GCD is : %d \n",GCD);
	
}
