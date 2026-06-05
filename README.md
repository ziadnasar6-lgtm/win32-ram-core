# 🖥️ Windows RAM Monitor & Task Manager Custom Utility

A lightweight, high-performance command-line utility built in **C++** utilizing the native **Windows API (Win32)** to monitor system memory internals, audit individual process layouts, and perform granular comparisons between running applications.

Designed with a stylized ANSI-colored terminal layout featuring a tailored dark cyber theme.

---

## 🚀 Key Features

* **Global RAM Auditing:** Real-time diagnostics of Total, Available, Used, and Free physical memory extracted natively via structural platform states.
* **Granular Process Tracking:** Deep-dive inspection of any active application using its Process ID (PID) to inspect its precise memory footprint.
* **Process vs Process Analytics:** Comparative performance analysis engine that highlights memory hogs and evaluates memory leaks or high page fault frequencies side-by-side.
* **UTF-8 Support:** Native console emoji mapping using Windows code-page layers to ensure custom visual assets display perfectly.

---

## 🛠️ Deep Dive: Windows API Internals Used

This project bypasses generic wrappers to interact directly with the Windows Subsystem Kernel using:
1. `GlobalMemoryStatusEx`: Populates the `MEMORYSTATUSEX` structure to gather high-precision structural allocation data of both global physical and virtual memory addresses.
2. `OpenProcess`: Opens a local process object with `PROCESS_QUERY_INFORMATION` and `PROCESS_VM_READ` security access rights.
3. `GetProcessMemoryInfo`: Injects and handles data across `PROCESS_MEMORY_COUNTERS_EX` to extract:
   * **Working Set Size:** The current physical memory pages mapped into the RAM pool.
   * **Private Usage:** Dedicated memory strictly allocated for the selected process context (critical for detecting memory leaks).
   * **Page Fault Count:** Total structural overhead occurrences requiring disk virtual memory indexing.

---

## 📊 Code Architecture: Namespaces Matrix

The project separates functional logical domains into highly specialized internal modules:

### 1. `zoz::` Domain
* `all_info_about_system()`: Parses, scales, and prints global system hardware metrics converted seamlessly from bytes into Gigabytes (GB).
* `mem_for_one_process(DWORD pid)`: Evaluates standalone runtime targets, safely tracking invalid resource queries or closed handles.

### 2. `nassar::` Domain
* `show_ram_usage()`: Initializes a system-loop refresh system to display persistent performance updates.
* `compar_two_pid(DWORD pid_one, DWORD pid_two)`: Evaluates absolute usage deltas ($Used_1 - Used_2$) and prints isolated, context-aware alert frames based on performance priority.

---

## 📦 Compilation & Setup

### Prerequisites
* Operating System: **Windows** 7 / 8 / 10 / 11.
* Compiler: Any standard **MSVC** or **MinGW** C++ compiler supporting standard library mapping.

### Build via Command Line (MinGW Example)
```bash
g++ -O3 main.cpp -o RamMonitor -lpsapi
