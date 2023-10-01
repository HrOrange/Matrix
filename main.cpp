#include "matrix.h"

int main (){
    
    // Inversable
    matrix t({{3.0f, 1.0f, 2.0f, 4.0f}, {8.0f, 3.45f, -1.0f, 2.0f}, {7.0f, 3.0f, 2.0f, 6.0f}, {-3.0f, -1.0f, 6.0f, 4.0f}});
    t.print();
    t.reduce();
    t.print();
    //matrix t2 = matrix::GaussJordanEliminationReduced(t, true);
    //t2.print();
    
    return 0;
}