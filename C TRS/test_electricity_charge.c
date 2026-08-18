#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "electricity_charge.h"

#define EPSILON 0.001

static int double_equals(double a, double b) {
    return fabs(a - b) < EPSILON;
}

void test_domestic_bill_calculation(void) {
    ElectricityBill bill;

    // Test 0 units
    assert(calculate_electricity_bill(0, CONSUMER_DOMESTIC, &bill) == 0);
    assert(double_equals(bill.units, 0.0));
    assert(double_equals(bill.energy_charge, 0.0));
    assert(double_equals(bill.fixed_charge, 5.00));
    assert(double_equals(bill.gross_amount, 5.00));

    // Test 100 units (Slab 1 only)
    assert(calculate_electricity_bill(100, CONSUMER_DOMESTIC, &bill) == 0);
    assert(double_equals(bill.units, 100.0));
    assert(double_equals(bill.energy_charge, 10.00)); // 100 * 0.10
    assert(double_equals(bill.fixed_charge, 5.00));
    assert(double_equals(bill.fuel_surcharge, 15.00)); // 100 * 0.15
    assert(double_equals(bill.gross_amount, 15.00));   // 10.00 + 5.00
    // Tax = (15.00 + 15.00) * 0.05 = 1.50
    assert(double_equals(bill.tax_amount, 1.50));
    assert(double_equals(bill.total_amount, 31.50));   // 15 + 15 + 1.50

    // Test 250 units (Slabs 1, 2, 3)
    // Slab 1: 100 * 0.10 = 10.00
    // Slab 2: 100 * 0.15 = 15.00
    // Slab 3:  50 * 0.25 = 12.50
    // Total energy = 37.50
    assert(calculate_electricity_bill(250, CONSUMER_DOMESTIC, &bill) == 0);
    assert(double_equals(bill.energy_charge, 37.50));
    assert(bill.num_slabs == 3);

    printf("  [PASS] test_domestic_bill_calculation\n");
}

void test_commercial_bill_calculation(void) {
    ElectricityBill bill;

    // 400 units
    // Slab 1: 100 * 0.25 = 25.00
    // Slab 2: 200 * 0.35 = 70.00
    // Slab 3: 100 * 0.45 = 45.00
    // Total energy = 140.00
    assert(calculate_electricity_bill(400, CONSUMER_COMMERCIAL, &bill) == 0);
    assert(double_equals(bill.energy_charge, 140.00));
    assert(double_equals(bill.fixed_charge, 20.00));
    assert(bill.num_slabs == 3);

    printf("  [PASS] test_commercial_bill_calculation\n");
}

void test_industrial_bill_calculation(void) {
    ElectricityBill bill;

    // 2500 units
    // Slab 1: 500 * 0.40 = 200.00
    // Slab 2: 1500 * 0.50 = 750.00
    // Slab 3: 500 * 0.60 = 300.00
    // Total energy = 1250.00
    assert(calculate_electricity_bill(2500, CONSUMER_INDUSTRIAL, &bill) == 0);
    assert(double_equals(bill.energy_charge, 1250.00));
    assert(double_equals(bill.fixed_charge, 100.00));
    assert(bill.num_slabs == 3);

    printf("  [PASS] test_industrial_bill_calculation\n");
}

void test_agricultural_bill_calculation(void) {
    ElectricityBill bill;

    // 600 units
    // Slab 1: 500 * 0.05 = 25.00
    // Slab 2: 100 * 0.08 = 8.00
    // Total energy = 33.00
    assert(calculate_electricity_bill(600, CONSUMER_AGRICULTURAL, &bill) == 0);
    assert(double_equals(bill.energy_charge, 33.00));
    assert(double_equals(bill.fixed_charge, 2.00));
    assert(bill.num_slabs == 2);

    printf("  [PASS] test_agricultural_bill_calculation\n");
}

void test_custom_tariff(void) {
    TariffConfig config;
    assert(create_custom_tariff(&config, CONSUMER_DOMESTIC, 10.00) == 0);
    assert(add_tariff_slab(&config, 0, 100, 0.20) == 0);
    assert(add_tariff_slab(&config, 100, -1, 0.40) == 0);

    assert(validate_tariff_config(&config) == 1);

    ElectricityBill bill;
    assert(calculate_electricity_bill_custom(150, &config, &bill) == 0);
    // 100 * 0.20 + 50 * 0.40 = 20 + 20 = 40 energy charge
    assert(double_equals(bill.energy_charge, 40.00));
    assert(double_equals(bill.fixed_charge, 10.00));

    printf("  [PASS] test_custom_tariff\n");
}

void test_invalid_inputs(void) {
    ElectricityBill bill;

    // Negative units
    assert(calculate_electricity_bill(-10, CONSUMER_DOMESTIC, &bill) == -1);

    // NULL bill pointer
    assert(calculate_electricity_bill(100, CONSUMER_DOMESTIC, NULL) == -1);

    // Invalid consumer type
    assert(calculate_electricity_bill(100, (ConsumerType)999, &bill) == -1);

    // Invalid tariff config
    TariffConfig invalid_config;
    create_custom_tariff(&invalid_config, CONSUMER_DOMESTIC, -5.0); // negative fixed charge
    assert(validate_tariff_config(&invalid_config) == 0);
    assert(calculate_electricity_bill_custom(100, &invalid_config, &bill) == -1);

    printf("  [PASS] test_invalid_inputs\n");
}

int main(void) {
    printf("=== Running Electricity Charge Unit Tests ===\n");
    test_domestic_bill_calculation();
    test_commercial_bill_calculation();
    test_industrial_bill_calculation();
    test_agricultural_bill_calculation();
    test_custom_tariff();
    test_invalid_inputs();
    printf("All electricity charge tests passed successfully!\n");
    return 0;
}
