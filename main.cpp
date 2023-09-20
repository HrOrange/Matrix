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


    matrix t2 ({ { 3.0f, 1.0f }, { 6.0f, 10.0f }});
    t2.print();
    float t3 = matrix::determinant(t2);
    std::cout << "Determinant: " << t3 << std::endl;
    //3 * 6 - 1 * 10 = 8


    matrix t4 ({ { 10000.048914891f, 1.0f, 0.99999938f }, { 6.0f, 0.0f, 10.0f }, { 1902.010f, 0.0f, 10.0f }});
    t4.print(1);
    t4.print(2);
    t4.print(3);
    
    return 0;
}