#ifndef ELECTRICITY_CHARGE_H
#define ELECTRICITY_CHARGE_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SLABS 5
#define TAX_RATE 0.05            // 5% electricity tax
#define FUEL_SURCHARGE_PER_UNIT 0.15 // $0.15 per kWh fuel surcharge
#define PROMPT_PAYMENT_DISCOUNT 0.02 // 2% discount for prompt payment

typedef enum {
    CONSUMER_DOMESTIC = 1,
    CONSUMER_COMMERCIAL,
    CONSUMER_INDUSTRIAL,
    CONSUMER_AGRICULTURAL
} ConsumerType;

typedef struct {
    double min_units;
    double max_units; // -1 for infinity (upper slab)
    double rate_per_unit;
} TariffSlab;

typedef struct {
    ConsumerType type;
    TariffSlab slabs[MAX_SLABS];
    int num_slabs;
    double fixed_charge;
} TariffConfig;

typedef struct {
    double slab_units;
    double rate;
    double amount;
} SlabDetail;

typedef struct {
    double units;
    ConsumerType type;
    SlabDetail slabs[MAX_SLABS];
    int num_slabs;
    double energy_charge;
    double fixed_charge;
    double gross_amount;
    double tax_amount;
    double fuel_surcharge;
    double total_amount;
    double prompt_discount;
    double net_payable;
} ElectricityBill;

/**
 * Get default tariff configuration for a given consumer type.
 */
TariffConfig get_default_tariff(ConsumerType type);

/**
 * Calculate electricity bill using default tariff configurations.
 * Returns 0 on success, -1 if inputs are invalid.
 */
int calculate_electricity_bill(double units, ConsumerType type, ElectricityBill *bill);

/**
 * Calculate electricity bill using a custom tariff configuration.
 * Returns 0 on success, -1 if inputs are invalid.
 */
int calculate_electricity_bill_custom(double units, const TariffConfig *config, ElectricityBill *bill);

/**
 * Print detailed itemized electricity bill to standard output.
 */
void print_electricity_bill(const ElectricityBill *bill);

/**
 * Get human-readable string representation of consumer type.
 */
const char* get_consumer_type_name(ConsumerType type);

/**
 * Create a new empty custom tariff structure.
 */
int create_custom_tariff(TariffConfig *config, ConsumerType type, double fixed_charge);

/**
 * Add a tariff slab to a custom tariff configuration.
 * Returns 0 on success, -1 if maximum slabs reached or invalid parameters.
 */
int add_tariff_slab(TariffConfig *config, double min_units, double max_units, double rate_per_unit);

/**
 * Validate consistency and validity of a tariff configuration.
 * Returns 1 if valid, 0 if invalid.
 */
int validate_tariff_config(const TariffConfig *config);

#ifdef __cplusplus
}
#endif

#endif // ELECTRICITY_CHARGE_H
