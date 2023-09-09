#include "matrix.h"

int main (){
    // Not inversable
    //matrix a({ {-1.0f, 2.0f}, {3.0f, -6.0f} });

    // Inversable
    matrix a({ { 2.0f, -5.0f }, { -1.0f, 3.0f } });
    matrix c = matrix::inverse(a);
    a.print();
    c.print();

    std::cout << "trace of a: " << matrix::trace(a) << std::endl;
    /*
    {
        {3, 5},
        {1, 2}
    }
    */
    return 0;
}