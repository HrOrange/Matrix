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


    matrix t2 ({ { 1.0f, 0.0f, 3.0f, 1.0f }, { 2.0f, 0.0f, 1.0f, -1.0f }, { 3.0f, 0.0f, 4.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 2.0f }});
    float t3 = matrix::determinant(t2);
    std::cout << "Determinant: " << t3 << std::endl;

    /*
    matrix t2 ({ { 3.0f, 9.0f}, { 4.0f, 8.0f }});
    t2.print();
    matrix t3 = matrix::copy(t2);
    t3.set(0, 0, 1.0f);
    t3.set(0, 1, 3.0f);

    matrix t4 = matrix::copy(t2);
    t4.set(1, 0, 2.0f);
    t4.set(1, 1, 4.0f);

    std::cout << matrix::determinant2x2(t2) << std::endl;
    std::cout << matrix::determinant2x2(t3) << std::endl;
    std::cout << matrix::determinant2x2(t4) << std::endl;
    */

    return 0;
}