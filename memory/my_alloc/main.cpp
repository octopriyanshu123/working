#include <stdio.h>
#include <stdlib.h>
#include <iostream>
        
int main() {
    for (int i=0;i<10;i++){
         int* ptr = (int *)malloc(50000);
         std::cout<<ptr<<std::endl;
    }   
}       

