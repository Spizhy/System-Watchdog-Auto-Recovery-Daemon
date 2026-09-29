# System Watchdog & Auto-Recovery Daemon

## Overview
A lightweight, high-performance system daemon written in modern C++ (C++20). This tool automates server reliability by continuously monitoring running processes for memory leaks or CPU spikes. If a process exceeds its allocated resource limits for a sustained period, the watchdog automatically terminates the rogue process, initiates a recovery script, and logs the event.

## Key Features
- **Low Overhead:** Written in native C++ with minimal dependencies, ensuring the monitor itself consumes negligible resources.
- **Configurable Thresholds:** Users can define soft and hard limits for CPU and RAM usage per process via a simple configuration file.
- **Graceful Termination:** Attempts a safe shutdown (SIGTERM) before forcing a kill (SIGKILL).
- **Auto-Recovery:** Capable of executing shell commands to restart critical services automatically.
- **Cross-Platform Potential:** Core logic is isolated, currently optimized for POSIX-compliant systems (Linux/macOS) with hooks available for Windows API expansion.

## Tech Stack
- **Language:** C++20
- **Build System:** CMake
- **Testing:** Google Test (GTest)

## Build Instructions
1. Ensure you have `cmake` and a C++20 compatible compiler installed (GCC/Clang).
2. Clone the repository and navigate to the root directory.
3. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
