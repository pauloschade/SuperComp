#include <omp.h>
#include <stdio.h>
#include <iostream>

double leibniz_pi(int n) {
    int i;
    int sign = 1;
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += sign * 4 / (2 * i + 1);
        sign = -sign;
    }
    return sum;
}

int main() {
    int n;
    double pi;
    n = 1000000000;
    pi = leibniz_pi(n);
    std::cout << pi << std::endl;
    return 0;
}