// Method 1: Using for Loop
// Method 2: Using Formula for the Sum of Nth Term
// Method 3: Using Recursion

//method 1

#include <iostream>
using namespace std;
// int main()
// {
//     int n = 8;
//     int sum =0;
//     for(int i =0;i<= n;i++)
//     {
//          sum = sum +i;
//          //sum =0+1+3+
//     }
//     cout << sum;
//     return 0;
// }

//method2
int main()
{
    int n =8;
    
    int sum = n*(n+1)/2;
    cout<<sum;

}