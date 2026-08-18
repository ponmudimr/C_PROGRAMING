#include <stdio.h>
#include <stdlib.h>
#include "electricity_charge.h"

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void print_tariff_rates(void) {
    printf("\n========================================================\n");
    printf("                CURRENT TARIFF RATE CARDS               \n");
    printf("========================================================\n");
    for (int type = CONSUMER_DOMESTIC; type <= CONSUMER_AGRICULTURAL; type++) {
        TariffConfig config = get_default_tariff((ConsumerType)type);
        printf("\n [%d] Category: %s\n", type, get_consumer_type_name((ConsumerType)type));
        printf("     Fixed Monthly Charge: $%.2f\n", config.fixed_charge);
        printf("     Slab Rates:\n");
        for (int i = 0; i < config.num_slabs; i++) {
            if (config.slabs[i].max_units < 0) {
                printf("       Slab %d: Above %.0f kWh     -> $%.2f / kWh\n",
                       i + 1, config.slabs[i].min_units, config.slabs[i].rate_per_unit);
            } else {
                printf("       Slab %d: %.0f - %.0f kWh    -> $%.2f / kWh\n",
                       i + 1, config.slabs[i].min_units, config.slabs[i].max_units, config.slabs[i].rate_per_unit);
            }
        }
    }
    printf("========================================================\n\n");
}

static void calculate_interactive_bill(void) {
    int category_choice;
    double units;

    printf("\n--- Calculate Electricity Bill ---\n");
    printf("Select Consumer Category:\n");
    printf("  1. Domestic (Residential)\n");
    printf("  2. Commercial\n");
    printf("  3. Industrial\n");
    printf("  4. Agricultural\n");
    printf("Enter choice (1-4): ");

    if (scanf("%d", &category_choice) != 1 || category_choice < 1 || category_choice > 4) {
        printf("Invalid category selection!\n");
        clear_input_buffer();
        return;
    }

    printf("Enter total electricity consumption (kWh / Units): ");
    if (scanf("%lf", &units) != 1 || units < 0) {
        printf("Invalid unit input! Units must be a non-negative number.\n");
        clear_input_buffer();
        return;
    }

    ElectricityBill bill;
    if (calculate_electricity_bill(units, (ConsumerType)category_choice, &bill) == 0) {
        print_electricity_bill(&bill);
    } else {
        printf("Failed to calculate electricity bill.\n");
    }
}

static void run_quick_estimate_matrix(void) {
    double sample_units[] = {100.0, 250.0, 500.0, 1000.0, 2500.0};
    int num_samples = sizeof(sample_units) / sizeof(sample_units[0]);

    printf("\n=========================================================================\n");
    printf("                 QUICK ESTIMATE MATRIX ACROSS CATEGORIES                 \n");
    printf("=========================================================================\n");
    printf(" %-12s | %-12s | %-12s | %-12s | %-12s\n", "Units (kWh)", "Domestic", "Commercial", "Industrial", "Agricultural");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < num_samples; i++) {
        double u = sample_units[i];
        ElectricityBill b_dom, b_com, b_ind, b_agr;

        calculate_electricity_bill(u, CONSUMER_DOMESTIC, &b_dom);
        calculate_electricity_bill(u, CONSUMER_COMMERCIAL, &b_com);
        calculate_electricity_bill(u, CONSUMER_INDUSTRIAL, &b_ind);
        calculate_electricity_bill(u, CONSUMER_AGRICULTURAL, &b_agr);

        printf(" %-12.0f | $%11.2f | $%11.2f | $%11.2f | $%11.2f\n",
               u, b_dom.total_amount, b_com.total_amount, b_ind.total_amount, b_agr.total_amount);
    }
    printf("=========================================================================\n\n");
}

int main(void) {
    int choice;

    while (1) {
        printf("\n===========================================\n");
        printf("    ELECTRICITY CHARGE CALCULATOR SYSTEM   \n");
        printf("===========================================\n");
        printf(" 1. Calculate Electricity Bill\n");
        printf(" 2. View Tariff Rate Cards\n");
        printf(" 3. View Quick Estimate Matrix\n");
        printf(" 4. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                calculate_interactive_bill();
                break;
            case 2:
                print_tariff_rates();
                break;
            case 3:
                run_quick_estimate_matrix();
                break;
            case 4:
                printf("Thank you for using Electricity Charge Calculator. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please select from options 1-4.\n");
                break;
        }
    }

    return 0;
}
