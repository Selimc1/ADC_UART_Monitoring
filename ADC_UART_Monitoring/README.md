# ADC UART Monitoring

![STM32](https://img.shields.io/badge/Microcontroller-STM32F407VG-blue)
![Architecture](https://img.shields.io/badge/Architecture-Bare%20Metal-orange)

## 📌 Project Overview
This project is a bare-metal implementation designed to read analog signals and transmit them to a computer via a serial interface. It demonstrates how to configure and utilize the Analog-to-Digital Converter (ADC) alongside the Universal Asynchronous Receiver-Transmitter (UART) without relying on high-level libraries like HAL. This is highly useful for real-time sensor monitoring, debugging, or logging data to a PC terminal (such as PuTTY) or a custom web dashboard.

## 🚀 Key Features
- **Bare-Metal Register Access:** Direct manipulation of STM32 registers (RCC, ADC1, USART2) for maximum efficiency and minimum footprint.
- **ADC Sampling:** Continuous or polled conversion of analog voltage levels (e.g., from a potentiometer or analog sensor).
- **UART Serial Communication:** Configured for 115200 baud rate, transmitting numeric ADC values as formatted strings (using custom `printf` retargeting or byte-by-byte transmission).
- **TTL Converter Compatibility:** Designed to interface seamlessly with standard USB-to-TTL modules (like CP2102 or CH340).

## 🛠️ Hardware Requirements
- **STM32F407G-DISC1** Development Board (or similar STM32F4 series).
- **USB-to-TTL Serial Converter** (Connected to USART2 pins).
- **Analog Source** (Potentiometer, LDR, etc.).

## ⚙️ How It Works
1. **Clock Configuration:** Enables the AHB1 and APB1/APB2 clocks for GPIO, ADC, and USART peripherals.
2. **ADC Initialization:** Sets up ADC1 with appropriate prescalers and resolution (12-bit default).
3. **UART Initialization:** Sets up USART2 for 115200-8-N-1 asynchronous communication.
4. **Main Loop:** The microcontroller constantly triggers an ADC read, converts the 12-bit digital value into a human-readable string, and pushes it out through the USART2 TX register.

## 💻 Getting Started
To use this project, simply clone the repository, open the folder using **STM32CubeIDE**, and build the project. Connect your ST-LINK to flash the microcontroller, and connect your TTL converter to the designated USART TX/RX pins to view the data stream.
