#include <stdio.h>
#include <stdlib.h>
int opcount = 0;
int *sieve(int a)
{
    int *arr = (int *)calloc(sizeof(int), a + 1);
    arr[0] = arr[1] = -1;
    for (int i = 2; i < a + 1; ++i)
    {
        if(arr[i] == 0)
        {
            for (int j = i * 2; j < a + 1; j += i)
            {
                 opcount++;

                arr[j] = -1;
            }
        }
    }
    printf("The opcount is : %d\n",opcount);
    return arr;
}
int count(int a, int b){
    int ans = 0;
    while(b % a == 0 && b != 0){
        ans += 1;
        b /= a;
    }
    return ans;
}
int power(int a, int b){
    int ans = 1;
    for(; b > 0; --b){
        ans *= a;
    }
    return ans;
}
int gcd(int a, int b)
{
    int *a_arr = sieve(a);
    int ans = 1;
    for (int i = 2; i < a + 1; ++i)
    {
        if (a_arr[i] == 0 && a % i == 0 && b % i == 0)
        {
            int c_a = count(i, a);
            int c_b = count(i, b);
            int c = c_a >= c_b ? c_b : c_a;
            ans *= power(i, c);
        }
    }
    return ans;
}
void main()
{
    printf("enter a and b\n");
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", gcd(a, b));
}
