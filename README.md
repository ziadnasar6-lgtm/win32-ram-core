# 🖥️ Win32 Native Memory Guardian & Systems Architecture Utility

A high-performance system monitoring and security auditing command-line engine built natively in **C++** utilizing core **Windows Core APIs (Win32)**. This utility interfaces directly with the kernel to extract global memory states, benchmark isolated applications, handle side-by-side performance footprints, and deploy an active threshold monitor (**Memory Guardian Engine**) over target tasks.

Featuring a fully customized UI rendered directly via advanced custom ANSI styling maps.

---

## 🚀 Architectural Pipelines & Core Features

* **Pipeline 1: Global Architectural Mapping:** Real-time structural validation of System Physical RAM load states, address pools, allocation spaces, and Virtual memory limits.
* **Pipeline 2: Deep Process Memory Auditing:** Deep-dive memory inspection using isolated target PIDs to unpack structural stats: Active Working Set, Peak Allocation footprint, and structural internal Private Allocations.
* **Pipeline 3: Streaming Performance Engine:** Live asynchronous system interface running continuous refresh timers to log global RAM consumption spikes per second.
* **Pipeline 4: Binary Benchmarking Matrix:** Comparative side-by-side analysis mapping two distinct operational processes to evaluate allocation deltas, memory overhead spikes, and cache validation properties.
* **Pipeline 5: Active Memory Guardian Threshold:** Security runtime guard that watches targeted runtime environments, monitors active allocations, and fires system threshold alerts immediately upon boundary violation.

---

## 🛠️ Kernel API Hooking Strategies Used

This project directly hooks and evaluates state changes within the Windows Subsystem Kernel using:
1. `GlobalMemoryStatusEx` + `MEMORYSTATUSEX`: Hooks active memory management registries to poll immediate metrics regarding system physical bounds.
2. `OpenProcess` (`PROCESS_QUERY_INFORMATION` | `PROCESS_VM_READ`): Injects customized security permission descriptors over structural target handlers safely.
3. `GetProcessMemoryInfo` + `PROCESS_MEMORY_COUNTERS_EX`: Tracks high-fidelity internal layout properties:
   * **Working Set Size:** Real-time RAM space mapped for the physical scope execution.
   * **Private Usage:** Dedicated block properties allocated specifically for the context space (essential for analyzing leakage variables).
   * **Page Fault Count:** Internal operational faults indicating mapping lookups tracking to the secondary disk store.

---

## 📁 Code Domains Structure: Namespaces

The system enforces isolation of logical components through clean modular architecture configurations:

### 🔷 `zoz::` Logic Core
* `memoryGlobalInformation()`: Gathers global storage configurations, processes limits, and outputs standard scalable units (Gigabytes).
* `memForeachProcess(DWORD pid)`: Inspects system tasks with functional exception-handling protocols mapping inaccessible or restricted descriptors.

### 🔷 `nassar::` System Management Hub
* `showMemoryPerSecond()`: Fires low-overhead terminal UI tracking using strategic console cursor mapping `SetConsoleCursorPosition`.
* `compareTwoPids(DWORD pid_one, DWORD pid_two)`: Quantifies spatial layout changes and highlights relative allocation deltas ($Memory_{Target1} - Memory_{Target2}$).
* `protectRam(DWORD pidPlus)`: The core runtime engine providing structural watchpoints to capture malicious heap growths or algorithmic infinite loops.

---

## 📦 Building and Deployment Specifications

### Setup Prerequisite Requirements
* **Platform OS Target:** Microsoft Windows 7 / 8 / 10 / 11 Desktop Subsystem.
* **Build Stack:** Native MSVC Toolchain or MinGW (GCC Base) runtime configuration setup.

### Direct Build Command Link Execution
```bash
g++ -O3 main.cpp -o MemoryGuardian -lpsapi
