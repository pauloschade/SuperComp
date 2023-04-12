#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

double leibniz_pi(int n) {
    int i;
    double sign = 1.0;
    double pi_sum = 0.0;
    #pragma omp parallel for reduction(+:pi_sum)
    for (i = 0; i < n; i++) {
        pi_sum += pow(-1, i) / (2 * i + 1);
    }
    return 4.0 * pi_sum;
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