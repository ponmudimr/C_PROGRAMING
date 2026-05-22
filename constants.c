#include <stdio.h>

#define PI 3.1415926535
#define TAU 6.2831853071
#define EULER 2.7182818284
#define GOLDEN_RATIO 1.6180339887
#define SQRT2 1.4142135623
#define LN2 0.6931471805

#define GRAVITY 9.81
#define SPEED_OF_LIGHT 299792458
#define SPEED_OF_SOUND 343

#define PLANCK 6.62607015e-34
#define REDUCED_PLANCK 1.054571817e-34

#define AVOGADRO 6.02214076e23
#define BOLTZMANN 1.380649e-23
#define GAS_CONSTANT 8.314462618

#define ELECTRON_CHARGE 1.602176634e-19
#define ELECTRON_MASS 9.10938356e-31
#define PROTON_MASS 1.67262192369e-27
#define NEUTRON_MASS 1.67492749804e-27

#define VACUUM_PERMITTIVITY 8.854187817e-12
#define VACUUM_PERMEABILITY 1.25663706212e-6
#define COULOMB_CONSTANT 8.9875517923e9

#define STEFAN_BOLTZMANN 5.670374419e-8
#define FARADAY 96485.33212

#define EARTH_RADIUS 6371000
#define EARTH_MASS 5.972e24
#define EARTH_GRAVITY 9.80665

#define SUN_MASS 1.989e30
#define SUN_RADIUS 6.9634e8

#define ATM_PRESSURE 101325
#define ROOM_TEMPERATURE 298.15

#define BYTE_BITS 8
#define KB 1024
#define MB 1048576
#define GB 1073741824

#define CPU_CLOCK 3.5e9

#define COPPER_RESISTIVITY 1.68e-8
#define SILICON_DENSITY 2330

#define WATER_BOILING 100
#define WATER_FREEZING 0

#define ABSOLUTE_ZERO -273.15

int main() {

    printf("=========== MATHEMATICAL CONSTANTS ==========\n\n");

    printf("PI                         = %.10f\n", PI);
    printf("TAU                        = %.10f\n", TAU);
    printf("Euler Number               = %.10f\n", EULER);
    printf("Golden Ratio               = %.10f\n", GOLDEN_RATIO);
    printf("Square Root of 2           = %.10f\n", SQRT2);
    printf("Natural Log of 2           = %.10f\n", LN2);

    printf("\n=========== PHYSICS CONSTANTS ===============\n\n");

    printf("Gravity                    = %.2f m/s^2\n", GRAVITY);
    printf("Speed of Light             = %d m/s\n", SPEED_OF_LIGHT);
    printf("Speed of Sound             = %d m/s\n", SPEED_OF_SOUND);

    printf("Planck Constant            = %.15e\n", PLANCK);
    printf("Reduced Planck Constant    = %.15e\n", REDUCED_PLANCK);

    printf("Boltzmann Constant         = %.15e\n", BOLTZMANN);
    printf("Gas Constant               = %.10f\n", GAS_CONSTANT);

    printf("\n=========== ATOMIC CONSTANTS ================\n\n");

    printf("Electron Charge            = %.15e C\n", ELECTRON_CHARGE);
    printf("Electron Mass              = %.15e kg\n", ELECTRON_MASS);
    printf("Proton Mass                = %.15e kg\n", PROTON_MASS);
    printf("Neutron Mass               = %.15e kg\n", NEUTRON_MASS);

    printf("Avogadro Number            = %.15e\n", AVOGADRO);

    printf("\n=========== ELECTRICAL CONSTANTS ============\n\n");

    printf("Vacuum Permittivity        = %.15e\n", VACUUM_PERMITTIVITY);
    printf("Vacuum Permeability        = %.15e\n", VACUUM_PERMEABILITY);
    printf("Coulomb Constant           = %.10e\n", COULOMB_CONSTANT);
    printf("Faraday Constant           = %.10f\n", FARADAY);

    printf("\n=========== ASTRONOMY CONSTANTS =============\n\n");

    printf("Earth Radius               = %d meters\n", EARTH_RADIUS);
    printf("Earth Mass                 = %.5e kg\n", EARTH_MASS);
    printf("Earth Gravity              = %.5f\n", EARTH_GRAVITY);

    printf("Sun Mass                   = %.5e kg\n", SUN_MASS);
    printf("Sun Radius                 = %.5e meters\n", SUN_RADIUS);

    printf("\n=========== ENVIRONMENTAL ===================\n\n");

    printf("Atmospheric Pressure       = %d Pa\n", ATM_PRESSURE);
    printf("Room Temperature           = %.2f Kelvin\n", ROOM_TEMPERATURE);

    printf("Water Boiling Point        = %d C\n", WATER_BOILING);
    printf("Water Freezing Point       = %d C\n", WATER_FREEZING);

    printf("Absolute Zero              = %.2f C\n", ABSOLUTE_ZERO);

    printf("\n=========== COMPUTER CONSTANTS ==============\n\n");

    printf("Bits in One Byte           = %d\n", BYTE_BITS);
    printf("Kilobyte                   = %d Bytes\n", KB);
    printf("Megabyte                   = %d Bytes\n", MB);
    printf("Gigabyte                   = %d Bytes\n", GB);

    printf("CPU Clock Example          = %.2e Hz\n", CPU_CLOCK);

    printf("\n=========== MATERIAL CONSTANTS ==============\n\n");

    printf("Copper Resistivity         = %.15e\n", COPPER_RESISTIVITY);
    printf("Silicon Density            = %d kg/m^3\n", SILICON_DENSITY);

    return 0;
}
