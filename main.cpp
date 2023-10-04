#include "matrix.h"

int main (){
    
    // Inversable
    matrix t1({{-2, 1, -1, 0}, {5, 2, 7, 0}, {3, 0, 3, 0}});

    t1.print();
    matrix t2 = matrix::GaussJordanEliminationReduced(t1,true);
    t2.print();

    return 0;
}