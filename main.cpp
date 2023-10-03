#include "matrix.h"

int main (){
    
    // Inversable
    matrix t1({{2, -7}, {-1, 4}});
    matrix t2({{1, -2}, {0, -1}});
    matrix t3({{4, 7}, {1, 2}});
    
    matrix t4 = matrix::multiply(t1, t2);
    matrix t5 = matrix::multiply(t4, t3);

    t5.print();

    return 0;
}