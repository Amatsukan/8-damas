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

auto count = 0u;

auto fill(int j = 0) {
    ++count;
    if (j == N) return operations::total();

    for (auto i = 0u; i < N; ++i) {
        if (operations::can_put(in(j, i))) {
            operations::put(in(j, i));

            if (fill(j + 1) == N) {
                return N;
            } else {
                operations::remove(in(j, i));
            }
        }
    }

    return operations::total();
}

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
    //operations::put( in(X,Y) );

    //NextQueen();
    fill();

    print();

    std::cout << std::endl << count << std::endl;

    return 0;
}

