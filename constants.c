#include <stdio.h>

#define PI 3.1415926535
#define EULER 2.7182818284
#define LAMBDA 1.6
#define GRAVITY 9.81
#define SPEED_OF_LIGHT 299792458
#define PLANCK 6.62607015e-34
#define AVOGADRO 6.02214076e23
#define BOLTZMANN 1.380649e-23

int main() {

    printf("===== IMPORTANT CONSTANTS =====\n\n");

    printf("PI                = %.10f\n", PI);

    printf("Euler Number (e)  = %.10f\n", EULER);

    printf("Lambda            = %.2f\n", LAMBDA);

    printf("Gravity (g)       = %.2f m/s^2\n", GRAVITY);

    printf("Speed of Light    = %d m/s\n", SPEED_OF_LIGHT);

    printf("Planck Constant   = %.15e Js\n", PLANCK);

    printf("Avogadro Number   = %.15e\n", AVOGADRO);

    printf("Boltzmann Constant= %.15e\n", BOLTZMANN);

    return 0;
}

