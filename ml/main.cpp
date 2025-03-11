#include <iostream>
int main(){
    float x[4] = {2, 4, 6, 8};
    float y[4] = {3, 7, 5, 10};
    float sunx = 0;
    float suny = 0;
    float sunxsqr2 = 0;
    float sunxy = 0;

    for (int i = 0; i < 4; i++) {
        sunx += x[i];
        suny += y[i];
        sunxsqr2 += x[i] * x[i];
        sunxy += x[i] * y[i];  
    }

    float b = (4 * sunxy - sunx * suny) / (4 * sunxsqr2 - sunx * sunx);
    float c = (suny * sunxsqr2 - sunx * sunxy) / (4 * sunxsqr2 - sunx * sunx);  

    std::cout << "b: " << b << " c: " << c << std::endl;
    return 0;
}
