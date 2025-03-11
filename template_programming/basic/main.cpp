
#include <iostream>
using namespace std;


template <typename int> void Print(int x){
   std::cout<<"Int"<<std::endl;
}

template <typename T> void Print(T x){
    std::cout<<x<<std::endl;
}
int main()
{
    Print(1.1);
    int x = 0;
    Print(x);

    return 0;
}