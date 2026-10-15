# Rezvac File Integrity Monitor (FIM)

A lightweight, educational implementation of a File Integrity Monitor written in C++. This project is designed to demonstrate the fundamental concepts of baseline hashing and continuous monitoring to detect unauthorized file modifications.

## Features
- Baseline Establishment: Calculates an initial checksum of a target file upon startup.
- Automated Monitoring: Periodically checks the file integrity every 2 seconds.
- Violation Alerts: Immediately notifies the user if the current file hash deviates from the baseline.

## Getting Started

### Prerequisites
- A C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)

### Build Instructions
1. Clone the repository
   ```bash
   git clone <repository-url>
   cd rezvac
   ```

2. Build the project
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. Run the monitor
   ```bash
   # On Windows
   ./rezvac_fim.exe
   # On Linux/Mac
   ./rezvac_fim
   ```

## Technical Overview
The monitor uses a basic additive checksum algorithm. It reads the target file byte-by-byte and sums their values. While not cryptographically secure (prone to collisions), it serves as an introduction to the Baseline -> Monitor -> Compare workflow used by professional security tools.

## Disclaimer
This project is for educational purposes only. For production environments, it is strongly recommended to use cryptographic hashes like SHA-256 and OS-level event notifications (such as inotify on Linux or ReadDirectoryChangesW on Windows) instead of polling.
