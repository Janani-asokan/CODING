//Method 1 : Using Brute Force
//Method 2 : Using Ternary Operator
//Method 3 : Using Bitwise Operators


#include <iostream>
using namespace std;
/* int main ()
{
    int number;
    cout << "Enter a number:"; cin >> number;
 
    //checking whether the number is even or odd
    if (number % 2 == 0)
        cout << number << " : Even";
    else
        cout << number << " : Odd";
        
    return 0;
}
 */
//ternary operator

/* int main()
{
int a = 7;
//int number;
//cout << "Enter a number:"; cin >> number;
//Ternary Operator Syntax
//( Condition ) ? ( if True : Action ) : ( if False : Action ) ;
a%2==0? cout<<"even":cout<<"odd";
} */


 bool iseven(int a)
    {
        return (!(a & 1));
    }
int main()
{int num ;
    cout<<"enter num"; cin>>num;
   if(iseven(num))
   {
    cout<<"even";
   }
   else{
    cout<<"odd9";
   }
   
}