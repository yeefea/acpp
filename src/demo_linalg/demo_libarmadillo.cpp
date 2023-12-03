#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void example_matrix()
{
    mat A(5, 5, fill::randu);
    double x = A(1, 2);

    mat B = A + A;
    mat C = A * B;
    mat D = A % B;

    cx_mat X(A, B);

    B.zeros();
    B.set_size(10, 10);
    B.ones(5, 6);

    B.print("B:");

    mat::fixed<5, 6> F;

    double aux_mem[24];
    mat H(&aux_mem[0], 4, 6, false); // use auxiliary memory
}

void example()
{
    mat A(4, 5, fill::randu);
    mat B(4, 5, fill::randu);

    cout << A * B.t() << endl;
}
int main()
{
    example();
    example_matrix();
    return 0;
}