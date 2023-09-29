//#include "matrix.h"
#include "frac.h"

int main (){
    
    // Inversable
    //matrix t({{3.0f, 1.0f, 2.0f, 4.0f}, {8.0f, 5.0f, -1.0f, 2.0f}, {7.0f, 3.0f, 2.0f, 6.0f}, {-3.0f, -1.0f, 6.0f, 4.0f}});
    //t.print();
    //matrix t2 = matrix::GaussJordanEliminationReduced(t, true);
    //t2.print();

    frac t1(2.47f);
    frac t2(3.30f);
    
    t1.print();
    std::cout << std::endl;
    
    t2.print();
    std::cout << std::endl;

    frac t3 = frac::add(t1, t2);
    t3.print();
    t3.reduce();

    return 0;
}