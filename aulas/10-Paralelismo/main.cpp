#include <iostream>
#include <stdio.h>
#include <omp.h>

double leibniz_pi(int n) {
    int i;
    double sign = 1.0;
    double sum = 0.0;
    for (i = 0; i < n; i++) {
        sum += sign / (2 * i + 1);
        sign = -sign;
    }
    return 4.0 * sum;
}

int main() {
    int n;
    double pi;
    n = 1000000000;

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    pi = leibniz_pi(n);

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    std::cout << pi << std::endl;
    std::cout << "total time: " << exec_time << std::endl;
    return 0;
}