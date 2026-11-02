# ADC UART Monitoring

![MCU](https://img.shields.io/badge/MCU-STM32F407VG-03234B?logo=stmicroelectronics&logoColor=white)
![Language](https://img.shields.io/badge/C-bare--metal-A8B9CC?logo=c&logoColor=white)
![Drivers](https://img.shields.io/badge/HAL-none%20(CMSIS%20only)-orange)
![Build](https://img.shields.io/badge/build-arm--none--eabi--gcc-blue)

Reads an analog voltage with **ADC1** and streams the raw value and the voltage in millivolts to a PC over **USART2**. Written at register level on an STM32F407 Discovery board (CMSIS only, no HAL), with `printf` retargeted to the UART.

## Features

- ADC1 on channel 1 (PA1) in **continuous conversion** mode, 12-bit
- Conversion to millivolts: `mV = raw × 3300 / 4095`
- `printf` output through `__io_putchar` → USART2 TX
- 115200 baud, one line roughly every 100 ms

## Hardware

| Part | Notes |
|---|---|
| STM32F407G-DISC1 | Default 16 MHz HSI clock |
| Analog source | Potentiometer, LDR divider, sensor output (0–3.3 V) |
| USB–TTL serial adapter | 115200 baud, 8N1 |

### Wiring

| Signal | STM32 pin | Connects to |
|---|---|---|
| ADC1_IN1 (analog) | PA1 | Potentiometer wiper / sensor output |
| USART2_TX (AF7) | PA2 | USB–TTL RX |
| GND | GND | Adapter and analog source ground |

```mermaid
flowchart LR
    POT[Potentiometer] -- "0-3.3 V (PA1)" --> ADC[ADC1] --> CPU[STM32F407] -- "USART2 115200 (PA2)" --> PC[PC terminal]
```

Output format:

```
ADC: <0-4095> | Voltage: <mV> mV
```

## Build and flash

Requires the [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) (`arm-none-eabi-gcc`) and GNU Make.

```bash
make            # -> build/ADC_UART_Monitoring.elf / .bin
make flash      # uses st-flash (stlink tools)
```

Or flash the `.elf` with STM32CubeProgrammer / STM32CubeIDE.

## Known limitations

- The 100 ms delay between lines is a busy-wait loop, so the rate is approximate.

---

### 🇹🇷 Türkçe özet

STM32F407 Discovery üzerinde, HAL kullanmadan register düzeyinde yazılmış ADC okuma örneği. ADC1 kanal 1 (PA1) sürekli dönüşüm modunda okunuyor, değer milivolta çevrilip `printf` ile USART2 (PA2, 115200) üzerinden terminale basılıyor.
