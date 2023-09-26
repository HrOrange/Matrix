#include "matrix.h"

int main (){
    // Not inversable
    //matrix a({ {-1.0f, 2.0f}, {3.0f, -6.0f} });

    // Inversable
    //matrix t({{1.0f, 2.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}});
    matrix t({{1.0f, 2.0f, 1.0f, -9.0f}, {1.0f, -3.0f, 3.0f, 7.0f}, {0.0f, 0.0f, 1.0f, 8.0f}});
    t.print();
    matrix t2 = matrix::GaussJordanEliminationReduced(t, false);
    t2.print();

    return 0;
    //g++ main.cpp matrix.h -o bin/main.exe
}