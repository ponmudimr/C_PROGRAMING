#include <stdio.h>
#include <string.h>
#include "electricity_charge.h"

const char* get_consumer_type_name(ConsumerType type) {
    switch (type) {
        case CONSUMER_DOMESTIC:
            return "Domestic (Residential)";
        case CONSUMER_COMMERCIAL:
            return "Commercial";
        case CONSUMER_INDUSTRIAL:
            return "Industrial";
        case CONSUMER_AGRICULTURAL:
            return "Agricultural";
        default:
            return "Unknown";
    }
}

TariffConfig get_default_tariff(ConsumerType type) {
    TariffConfig config;
    memset(&config, 0, sizeof(TariffConfig));
    config.type = type;

    switch (type) {
        case CONSUMER_DOMESTIC:
            config.fixed_charge = 5.00;
            config.num_slabs = 4;
            config.slabs[0] = (TariffSlab){0, 100, 0.10};
            config.slabs[1] = (TariffSlab){100, 200, 0.15};
            config.slabs[2] = (TariffSlab){200, 500, 0.25};
            config.slabs[3] = (TariffSlab){500, -1, 0.35};
            break;

        case CONSUMER_COMMERCIAL:
            config.fixed_charge = 20.00;
            config.num_slabs = 4;
            config.slabs[0] = (TariffSlab){0, 100, 0.25};
            config.slabs[1] = (TariffSlab){100, 300, 0.35};
            config.slabs[2] = (TariffSlab){300, 1000, 0.45};
            config.slabs[3] = (TariffSlab){1000, -1, 0.55};
            break;

        case CONSUMER_INDUSTRIAL:
            config.fixed_charge = 100.00;
            config.num_slabs = 3;
            config.slabs[0] = (TariffSlab){0, 500, 0.40};
            config.slabs[1] = (TariffSlab){500, 2000, 0.50};
            config.slabs[2] = (TariffSlab){2000, -1, 0.60};
            break;

        case CONSUMER_AGRICULTURAL:
            config.fixed_charge = 2.00;
            config.num_slabs = 2;
            config.slabs[0] = (TariffSlab){0, 500, 0.05};
            config.slabs[1] = (TariffSlab){500, -1, 0.08};
            break;

        default:
            config.num_slabs = 0;
            break;
    }

    return config;
}

int calculate_electricity_bill_custom(double units, const TariffConfig *config, ElectricityBill *bill) {
    if (units < 0 || bill == NULL || config == NULL || config->num_slabs <= 0) {
        return -1;
    }

    memset(bill, 0, sizeof(ElectricityBill));
    bill->units = units;
    bill->type = config->type;
    bill->fixed_charge = config->fixed_charge;

    double remaining_units = units;
    double total_energy_charge = 0.0;
    int active_slabs = 0;

    for (int i = 0; i < config->num_slabs && remaining_units > 0; i++) {
        TariffSlab slab = config->slabs[i];
        double slab_capacity;

        if (slab.max_units < 0) {
            slab_capacity = remaining_units;
        } else {
            slab_capacity = slab.max_units - slab.min_units;
        }

        double units_in_slab = (remaining_units > slab_capacity) ? slab_capacity : remaining_units;
        double slab_amount = units_in_slab * slab.rate_per_unit;

        bill->slabs[i].slab_units = units_in_slab;
        bill->slabs[i].rate = slab.rate_per_unit;
        bill->slabs[i].amount = slab_amount;

        total_energy_charge += slab_amount;
        remaining_units -= units_in_slab;
        active_slabs++;
    }

    bill->num_slabs = active_slabs;
    bill->energy_charge = total_energy_charge;

    bill->gross_amount = bill->energy_charge + bill->fixed_charge;
    bill->fuel_surcharge = bill->units * FUEL_SURCHARGE_PER_UNIT;
    bill->tax_amount = (bill->gross_amount + bill->fuel_surcharge) * TAX_RATE;
    bill->total_amount = bill->gross_amount + bill->fuel_surcharge + bill->tax_amount;
    bill->prompt_discount = bill->total_amount * PROMPT_PAYMENT_DISCOUNT;
    bill->net_payable = bill->total_amount - bill->prompt_discount;

    return 0;
}

int calculate_electricity_bill(double units, ConsumerType type, ElectricityBill *bill) {
    TariffConfig default_config = get_default_tariff(type);
    if (default_config.num_slabs == 0) {
        return -1;
    }
    return calculate_electricity_bill_custom(units, &default_config, bill);
}

void print_electricity_bill(const ElectricityBill *bill) {
    if (bill == NULL) {
        printf("Error: Invalid bill data.\n");
        return;
    }

    printf("\n========================================================\n");
    printf("              ELECTRICITY UTILITY INVOICE               \n");
    printf("========================================================\n");
    printf(" Category        : %s\n", get_consumer_type_name(bill->type));
    printf(" Total Usage     : %.2f kWh\n", bill->units);
    printf("--------------------------------------------------------\n");
    printf(" Energy Charges Breakdown:\n");

    if (bill->num_slabs == 0) {
        printf("   (No consumption charges)\n");
    } else {
        for (int i = 0; i < bill->num_slabs; i++) {
            printf("   Slab %d: %8.2f kWh @ $%5.2f/kWh  =  $%8.2f\n",
                   i + 1,
                   bill->slabs[i].slab_units,
                   bill->slabs[i].rate,
                   bill->slabs[i].amount);
        }
    }

    printf("--------------------------------------------------------\n");
    printf(" Total Energy Charge             : $%8.2f\n", bill->energy_charge);
    printf(" Fixed Monthly Charge            : $%8.2f\n", bill->fixed_charge);
    printf(" Gross Energy Amount             : $%8.2f\n", bill->gross_amount);
    printf(" Fuel Adjustment Surcharge (FAC) : $%8.2f\n", bill->fuel_surcharge);
    printf(" Electricity Tax (%.0f%%)          : $%8.2f\n", TAX_RATE * 100.0, bill->tax_amount);
    printf("--------------------------------------------------------\n");
    printf(" TOTAL AMOUNT DUE                : $%8.2f\n", bill->total_amount);
    printf(" Prompt Payment Discount (%.0f%%)   : -$%7.2f\n", PROMPT_PAYMENT_DISCOUNT * 100.0, bill->prompt_discount);
    printf("--------------------------------------------------------\n");
    printf(" NET AMOUNT PAYABLE ON TIME      : $%8.2f\n", bill->net_payable);
    printf("========================================================\n\n");
}
