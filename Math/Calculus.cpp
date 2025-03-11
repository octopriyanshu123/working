#include <iostream>
using namespace std;
int a, x, n, derivative;
int main ()
{
cout<< "Hello. I am a computer program. I can calculate the derivative of an expression using power rule.";
cout<< "\nPlease type the values of a and n for use like the ex.:";
cout<< "\ny=ax^n";
cin.get ();
cout<< "a=?\n";
cin>> a;
cout<< "x=?\n";
cin>> x;
cout<< "n=?\n";
cin>> n;
derivative=a*n*(x^(n-1));

cout<< "dy/dx=" << derivative;
return 0;
}