# 🔌 Embedded_Project_Repo (STILL UNDER PROGRESS)

> A structured embedded systems project repository covering foundational communication protocols — **UART, I2C, and SPI** — implemented in **C/C++** from the ground up.

---

## 📖 Overview

This repository is a hands-on embedded systems design project that explores low-level hardware communication protocols used in real-world electronic systems. It is intended as both a learning resource and a practical reference for embedded developers working with microcontrollers and peripherals.

The project covers:
- Serial communication via **UART** (Universal Asynchronous Receiver-Transmitter)
- Multi-device bus communication via **I2C** (Inter-Integrated Circuit)
- High-speed peripheral communication via **SPI** (Serial Peripheral Interface)

---

## 📁 Project Structure

```
Embedded_Project_Repo/
│
├── UART/
│   ├── uart_init.c
│   ├── uart_transmit.c
│   ├── uart_receive.c
│   └── README.md
│
├── I2C/
│   ├── i2c_master.c
│   ├── i2c_slave.c
│   ├── i2c_read_write.c
│   └── README.md
│
├── SPI/
│   ├── spi_master.c
│   ├── spi_slave.c
│   ├── spi_data_transfer.c
│   └── README.md
│
├── include/
│   ├── uart.h
│   ├── i2c.h
│   └── spi.h
│
├── docs/
│   └── protocol_overview.pdf
│
└── README.md
```

---

## 🛠️ Technologies & Tools

| Category        | Details                          |
|----------------|----------------------------------|
| Language        | C / C++                          |
| Protocols       | UART, I2C, SPI                   |
| Build System    | Makefile / CMake                 |
| Debugger        | GDB / OpenOCD                    |
| IDE (optional)  | VS Code, STM32CubeIDE, Keil MDK  |

---

## 🔗 Communication Protocols

### 🔷 UART
- Full-duplex asynchronous serial communication
- Configurable baud rate, data bits, stop bits, and parity
- Suitable for: debug consoles, GPS modules, Bluetooth modules

### 🔷 I2C
- Two-wire synchronous protocol (SDA + SCL)
- Supports multiple masters and slaves on a single bus
- Suitable for: sensors (temperature, humidity, IMU), OLED displays, EEPROMs

### 🔷 SPI
- Four-wire synchronous protocol (MOSI, MISO, SCK, CS)
- High-speed, full-duplex communication
- Suitable for: SD cards, flash memory, ADC/DAC chips, TFT displays

---

## 🚀 Getting Started

### Prerequisites

- A C/C++ compiler (e.g., `arm-none-eabi-gcc` or `avr-gcc`)
- Make or CMake installed
- A compatible microcontroller and programmer/debugger

### Clone the Repository

```bash
git clone https://github.com/vyomeshkumarsingh/Embedded_Project_Repo.git
cd Embedded_Project_Repo
```

### Build

```bash
make all
```

### Flash to Hardware

```bash
# Example using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program output.elf verify reset exit"
```

---

## 📌 Roadmap

- [x] Project structure setup
- [ ] UART driver implementation
- [ ] I2C master/slave driver
- [ ] SPI master/slave driver
- [ ] Integration examples with sensors
- [ ] Unit tests and simulation support

---

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -m 'Add your feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Open a Pull Request

---


---
