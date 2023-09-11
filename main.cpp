#include "matrix.h"

int main (){
    // Not inversable
    //matrix a({ {-1.0f, 2.0f}, {3.0f, -6.0f} });

    // Inversable
    //matrix a({ { 2.0f, -5.0f }, { -1.0f, 3.0f } });
    //matrix b = matrix::inverse(a);
    matrix a({ { 2.0f, -5.0f, 0.0f }, { -1.0f, 3.0f, 4.0f } });
    matrix b({ { 1.0f }, { -1.0f }, { 1.0f } });
    a.print();
    b.print();

    matrix c = matrix::multiply(a, b);
    c.print();
    return 0;
}