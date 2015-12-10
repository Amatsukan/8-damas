#ifndef CHESS
#define CHESS

#include <array>
#include <utility> 
#include <algorithm>

#include "definitions.h"

template <class T, size_t ROW, size_t COL>
using Matrix = std::array<std::array<T, COL>, ROW>;


static Matrix<bool, N, N> chessTable;


namespace attack{
    auto main_diagonal= [](std::pair<int,int> location){
        bool result = true;
        
        for(int i = location.first, j = location.second; i < N and j < N; i++, j++){
            if(!(i == location.first and j == location.second))
                result = result and !chessTable[i][j];
        }
        for(int i = location.first, j = location.second; i >= 0 and j >= 0; i--, j--){
            if(!(i == location.first and j == location.second))
                result = result and !chessTable[i][j];
        }
        
        return result;
    };
    
    auto secondary_diagonal= [](std::pair<int,int> location){
        bool result = true;
        
        for(int i = location.first, j = location.second; i < N and j >= 0; i++, j--){
            if(!(i == location.first and j == location.second))
                result = result and !chessTable[i][j];
        }
        for(int i = location.first, j = location.second; i >= 0 and j < N; i--, j++){
            if(!(i == location.first and j == location.second))
                result = result and !chessTable[i][j];
        }
        
        return result;
    };
    
    auto horizontal= [](std::pair<int,int> location){
        bool result = true;
        for(int i = 0; i<N; i++){
            if(i != location.second)
                result = result and !chessTable[location.first][i];
        }
        
        return result;
    };
    
    auto vertical= [](std::pair<int,int> location){
        bool result = true;
        for(int i = 0; i<N; i++){
            if(i != location.first)
                result = result and !chessTable[i][location.second];
        }
        
        return result;
    };
};

namespace operations{
    namespace {
        static int put_total = 0;
    }

    auto total() {
        return put_total;
    }

    auto put(const std::pair<int,int>& location) {
        ++put_total;
        chessTable[location.first][location.second] = true;
        return put_total;
    }

    auto remove(const std::pair<int,int>& location) {
        --put_total;
        chessTable[location.first][location.second] = false;
        return put_total;
    }

    auto can_put = [](std::pair<int,int> location){
        
        bool hori      = attack::horizontal(location);
        bool vert      = attack::vertical(location);
        bool sec_diag  = attack::secondary_diagonal(location);
        bool main_diag = attack::main_diagonal(location);
        
        return hori and vert and sec_diag and main_diag;
    };
    
    auto initMatriz = [] () {
        std::for_each(chessTable.begin(), chessTable.end(),
            [](std::array<bool, N> elem){
                std::for_each(elem.begin(), elem.end(), 
                    [](bool pos){ 
                        pos = false;
                    });
            });
    };
    
    auto getMatrixString = [] () {
        std::string s;
        
        std::for_each(chessTable.begin(), chessTable.end(),
            [&s](std::array<bool, N> elem){
                std::for_each(elem.begin(), elem.end(), 
                    [&s](bool pos){ 
                        s += '[';
                        s += " \0 Q"+(pos*3);
                        s += ']';
                    });
                s += '\n';
            });
            
        return s;
    };
}

#endif