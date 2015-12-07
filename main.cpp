#include <iostream>
#include "chess.h"
#include <stdexcept>

int queens = 0;

auto in = [](int x, int y){
    if(x >= N or y >= N) 
        throw std::range_error("function in(int,int), limit exceeded!");
    
    return std::make_pair(x,y);
};

auto print = [](){
    std::string matrix = operations::getMatrixString();
    std::cout<<matrix<<std::endl;
};

auto NextQueen = [](){
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(operations::can_put( in(i,j) )){
                operations::put( in(i,j) );
                queens++;
            }
        }
    }
};

int main()
{
    operations::put( in(X,Y) );
    
    NextQueen();
    
    print();
    
    return 0;
}

