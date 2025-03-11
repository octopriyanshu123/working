#include <iostream>

template <typename T>
T add(T a, T b){
    return a+b;
}


template <typename T>
class Box {
private:
    T content;
public:
    void setContent(T value) {
        content = value;
    }
    T getContent() {
        return content;
    }
};




int main(int argc, char** argv){
    std::cout<<add(2,3)<<std::endl;
    std::cout<<add(4.4,3.4);


    Box<int> intBox;
intBox.setContent(42);

Box<std::string> strBox;
strBox.setContent("Hello");

    return 0;
}