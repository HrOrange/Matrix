#include "matrix.h"

int main (){
    // Not inversable
    //matrix a({ {-1.0f, 2.0f}, {3.0f, -6.0f} });

    // Inversable
    matrix a({ { 2.0f, -5.0f }, { -1.0f, 3.0f } });
    //matrix b = matrix::inverse(a);
    //matrix a({ { 2.0f, -5.0f, 0.0f }, { -1.0f, 3.0f, 4.0f } });
    matrix b({ { 1.0f }, { -1.0f }, { 1.0f } });
    matrix i({{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});


    matrix test (5, 5);
    test.randomize(-10, 10, 1);
    for(int i = 0; i < test.getCol(); i++) test.set(2, i, 0.0f);

    matrix test2 = matrix::GaussJordanElimination(test);

    test.print();
    test2.print();
    
    return 0;
}