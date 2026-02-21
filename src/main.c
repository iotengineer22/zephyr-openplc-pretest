/* Zephyr main.c template */
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "iec_std_lib.h" // Include path to lib folder

// Functions defined in Config0.c
extern void config_init__(void);
extern void config_run__(unsigned long tick);
extern unsigned long long common_ticktime__; // Cycle time defined in Config0.c (ns)
extern void glueVars(void);
extern void updateTime(void);

// Variables defined in LOCATED_VARIABLES.h (extern declaration if necessary)
// Mapping based on POUS.c definition:
// X001 -> __IX0_6
// X002 -> __IX0_7
// Y001 -> __QX0_2
extern IEC_BOOL *__IX0_6;
extern IEC_BOOL *__IX0_7;
extern IEC_BOOL *__QX0_2;

// Get GPIO specs from devicetree
static const struct gpio_dt_spec x001 = GPIO_DT_SPEC_GET(DT_ALIAS(plcin1), gpios);
static const struct gpio_dt_spec x002 = GPIO_DT_SPEC_GET(DT_ALIAS(plcin2), gpios);
static const struct gpio_dt_spec y001 = GPIO_DT_SPEC_GET(DT_ALIAS(plcout1), gpios);

int main(void) {
    config_init__(); // Initialization
    glueVars();      // Initialize variable pointers

    // Set cycle time to 1us (1000ns) / 10us (10000ns). Overwrite Config0.c default value.
    common_ticktime__ = 10000;

    unsigned long tick = 0;
    uint32_t start_cyc, end_cyc, scan_time_ns;
    uint32_t prev_start_cyc = 0;
    uint32_t actual_cycle_ns = 0;
    int64_t next_log_time = k_uptime_get();

    // GPIO initialization
    if (!gpio_is_ready_dt(&x001) || !gpio_is_ready_dt(&x002) || !gpio_is_ready_dt(&y001)) {
        printk("Error: GPIO devices not ready\n");
        return 0;
    }

    gpio_pin_configure_dt(&x001, GPIO_INPUT);
    gpio_pin_configure_dt(&x002, GPIO_INPUT);
    gpio_pin_configure_dt(&y001, GPIO_OUTPUT);

    while (1) {
        start_cyc = k_cycle_get_32();
        if (tick > 0) {
            actual_cycle_ns = k_cyc_to_ns_floor32(start_cyc - prev_start_cyc);
        }
        prev_start_cyc = start_cyc;

        // 1. Input: Copy Zephyr GPIO -> PLC variables (__IX0_0 etc.)
        *__IX0_6 = gpio_pin_get_dt(&x001); // X001
        *__IX0_7 = gpio_pin_get_dt(&x002); // X002
        
        // 2. Execute logic
        config_run__(tick++);
        
        // 3. Output: Copy PLC variables (__QX0_0 etc.) -> Zephyr GPIO
        gpio_pin_set_dt(&y001, *__QX0_2); // Y001

        // Update PLC internal time (Required for timers like TON to work)
        updateTime();

        end_cyc = k_cycle_get_32();
        scan_time_ns = k_cyc_to_ns_floor32(end_cyc - start_cyc);

        // For operation check: Output log every 0.1s (100ms)
        int64_t now = k_uptime_get();
        if (now >= next_log_time) {
            printk("PLC Cycle Tick: %lu, Scan Time: %u ns, Cycle Time: %u ns, In(X1,X2): %d %d, Out(Y1): %d\n",
                   tick, scan_time_ns, actual_cycle_ns, *__IX0_6, *__IX0_7, *__QX0_2);
            next_log_time = now + 100;
        }

        // Busy wait until the configured cycle time (common_ticktime__)
        // k_sleep can only wait in system tick units (usually 100us-1ms),
        // so busy wait is required for short duration control like 1us.
        while (k_cyc_to_ns_floor32(k_cycle_get_32() - start_cyc) < common_ticktime__) {
            // Spin loop
        }
    }
    return 0;
}

