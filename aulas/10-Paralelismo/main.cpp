#include <iostream>
#include <stdio.h>

double leibniz_pi(int n) {
    double i;
    double sign = 1.0;
    double sum = 0.0;
    for (i = 0.0; i < n; i++) {
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