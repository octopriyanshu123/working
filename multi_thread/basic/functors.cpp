#include <iostream>


class test
{
private:
    /* data */
public:
    test(/* args */);
    int operator()(int val){
        std::cout<<"operator  "<<val<<std::endl;
        return val;
    }
    ~test();
};

test::test(/* args */)
{
    std::cout<<"We build the class "<<std::endl;
}

test::~test()
{
}

int main(){
    test t;
    std::cout<<t(9)<<" return from Operator"<<std::endl;

    return 0;
}