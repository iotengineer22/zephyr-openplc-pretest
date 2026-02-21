# Zephyr RTOS + OpenPLC (Pre-test Version)

This is a pre-test version of OpenPLC adapted from the OpenPLC v3 program to run on Zephyr RTOS.
Original OpenPLC v3: https://github.com/thiagoralves/OpenPLC_v3

## ⚠️ Disclaimer
This project is a **pre-test version**. It has not been thoroughly tested, so please use with caution.

## License
GPL (General Public License)

## Tested Hardware
Build and operation have been confirmed on the following boards:

*   Raspberry Pi 4B
*   Raspberry Pi Pico 2 W
*   Nordic nRF54L15-DK

## Demo Description
This is a simple **self-holding circuit (latching circuit)** demo using ladder logic.

*   **X001**: Start Button (Normally Open / NO contact)
*   **X002**: Stop Button (Normally Closed / NC contact treated, or logical negation)
*   **M001**: Internal Auxiliary Relay (for latching)
*   **Y001**: Output

### Execution Flow
The program executes in the following order:

1.  `config_run__()` is called from the `main()` loop in `src/main.c`.
2.  `RES0_run__()` is called from `config_run__()` in `src/core/Config0.c`.
3.  `MAIN_body__()` (in `src/core/POUS.c`) is called from `RES0_run__()` in `src/core/Res0.c`, and the logic is executed.

## Build Instructions

### Raspberry Pi 4B
```bash
west build -p always -b rpi_4b
```

### Raspberry Pi Pico 2 W
```bash
west build -p -b rpi_pico2/rp2350a/m33/w
```

### Nordic nRF54L15-DK
Please build using nRF Connect (VS Code extension, etc.).

## GPIO Configuration
Please check the `.overlay` files in the `boards/` directory for GPIO assignments for each board.

## Test Video
(Paste video links here)