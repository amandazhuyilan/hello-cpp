#include <iostream>
int Max(int x,int y){
    return x > y ? x : y;
}
float Max(float x, float y){
    return x > y ? x : y ;
}

int main(){
    float result = Max(8.1f, 6) ;
    std::cout << result ;
    return 0 ;
}
