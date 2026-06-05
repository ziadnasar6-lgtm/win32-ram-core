
#define _WIN32_WINNT 0x0601

#include <iostream>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <limits>
#include <Psapi.h>
#include <TlHelp32.h>
#include <string>

using namespace std;

// ANSI Color Codes for Styling
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[35m";
const string MAGENTA = "\033[36m";

namespace zoz
{
    // Feature 1: Global System RAM Diagnostics
    void memoryGlobalInformation()
    {
        MEMORYSTATUSEX memoryInfo;
        memoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memoryInfo);

        DWORDLONG allRam = memoryInfo.ullTotalPhys / (1024 * 1024 * 1024);
        DWORDLONG freeRam = memoryInfo.ullAvailPhys / (1024 * 1024 * 1024);
        DWORDLONG totalVirtual = memoryInfo.ullTotalPageFile / (1024 * 1024 * 1024);
        DWORDLONG freeVirtual = memoryInfo.ullAvailPageFile / (1024 * 1024 * 1024);
        DWORDLONG usageRam = memoryInfo.dwMemoryLoad;

        cout << BOLD << MAGENTA;
        cout << "==============================================" << endl;
        cout << "=          The Information About Ram         =" << endl;
        cout << "==============================================" << endl;
        cout << RESET << endl;
        cout << BOLD << GREEN;

        cout << "Total Physical RAM : " << allRam << " GB " << endl;
        cout << "Current RAM Load   : " << usageRam << " % " << endl;
        cout << "Free Physical RAM  : " << freeRam << " GB " << endl;
        cout << "Total Virtual Ram  : " << totalVirtual << " GB " << endl;
        cout << "Free Virtual Ram   : " << freeVirtual << " GB " << endl;
        cout << RESET << endl;
    }

    // Feature 2: Deep Inspect a Specific Process
    void memForeachProcess(DWORD pid)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

        if (hProcess == NULL)
        {
            cout << BOLD << RED << "❌ Invalid process or INVALID PID [" << pid << "] !!!! " << RESET << endl;
            return;
        }

        PROCESS_MEMORY_COUNTERS_EX infounique;
        infounique.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

        if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS *)&infounique, sizeof(infounique)))
        {
            SIZE_T usedRam = infounique.WorkingSetSize / (1024 * 1024);
            SIZE_T usedRamMax = infounique.PeakWorkingSetSize / (1024 * 1024);
            SIZE_T privateRam = infounique.PrivateUsage / (1024 * 1024);
            DWORD ramfauels = infounique.PageFaultCount;

            cout << BOLD << BLUE << endl;
            cout << "========================================================" << endl;
            cout << "=             The DETAILS About Ram PROCESS            =" << endl;
            cout << "========================================================" << endl;
            cout << RESET << BOLD << CYAN << endl;

            cout << "Working Set (RAM Used) : " << usedRam << " MB " << endl;
            cout << "Peak Working Set Size  : " << usedRamMax << " MB" << endl;
            cout << "Private Memory Usage   : " << privateRam << " MB " << endl;
            cout << "Page Fault Count       : " << ramfauels << " times" << endl;
            cout << RESET << endl;
        }
        else
        {
            cout << BOLD << RED << "❌ Could not get memory info for PID " << pid << RESET << endl;
        }
        CloseHandle(hProcess);
    }
};

namespace nassar
{
    // Feature 3: Real-Time Stream UI (Per Second)
    void showMemoryPerSecond()
    {
        MEMORYSTATUSEX secondMemory;
        secondMemory.dwLength = sizeof(MEMORYSTATUSEX);

        system("cls");
        cout << BOLD << YELLOW << "=== Real-Time RAM Monitor (Press Ctrl+C to stop) ===" << RESET << endl;

        while (true)
        {
            GlobalMemoryStatusEx(&secondMemory);
            DWORDLONG usedmemory = secondMemory.dwMemoryLoad;

            COORD pos = {0, 3}; // Fixed layout position
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            cout << YELLOW << "=================================" << endl;
            cout << "=  RAM Load: " << BOLD << RED << usedmemory << " %" << RESET << YELLOW << "                =" << endl;
            cout << "=================================" << RESET << endl;

            Sleep(1000); // Refreshes every 1 second
        }
    }

    // Feature 4: Side-by-Side Process Memory Benchmarking
    void compareTwoPids(DWORD pid_one, DWORD pid_two)
    {
        HANDLE process_1 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid_one);
        HANDLE process_2 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid_two);

        if (process_1 == NULL || process_2 == NULL)
        {
            cout << BOLD << RED << "❌ One or both PIDs are invalid/inaccessible!" << RESET << endl;
            if (process_1) CloseHandle(process_1);
            if (process_2) CloseHandle(process_2);
            return;
        }

        PROCESS_MEMORY_COUNTERS_EX one = { sizeof(PROCESS_MEMORY_COUNTERS_EX) };
        PROCESS_MEMORY_COUNTERS_EX two = { sizeof(PROCESS_MEMORY_COUNTERS_EX) };

        GetProcessMemoryInfo(process_1, (PROCESS_MEMORY_COUNTERS *)&one, sizeof(one));
        GetProcessMemoryInfo(process_2, (PROCESS_MEMORY_COUNTERS *)&two, sizeof(two));

        SIZE_T used_one = one.WorkingSetSize / (1024 * 1024);
        SIZE_T private_one = one.PrivateUsage / (1024 * 1024);
        
        SIZE_T used_two = two.WorkingSetSize / (1024 * 1024);
        SIZE_T private_two = two.PrivateUsage / (1024 * 1024);

        cout << BOLD << BLUE << "\n=======================================================" << endl;
        cout << "=             PROCESS PERFORMANCE BENCHMARK           =" << endl;
        cout << "=======================================================" << RESET << endl;

        if (private_one > private_two)
        {
            cout << BOLD << RED << "⚠️  ALERT: PID [" << pid_one << "] consumes MORE Private RAM than PID [" << pid_two << "] by " << (private_one - private_two) << " MB!\n" << RESET;
        }
        else if (private_two > private_one)
        {
            cout << BOLD << RED << "⚠️  ALERT: PID [" << pid_two << "] consumes MORE Private RAM than PID [" << pid_one << "] by " << (private_two - private_one) << " MB!\n" << RESET;
        }
        else
        {
            cout << BOLD << GREEN << "⚖️ Both processes are utilizing identical memory block sizes!\n" << RESET;
        }

        cout << BOLD << CYAN << "\n[Metrics for PID " << pid_one << "]:" << RESET << "\n -> RAM Used: " << used_one << " MB | Private Allocation: " << private_one << " MB | Faults: " << one.PageFaultCount << endl;
        cout << BOLD << MAGENTA << "[Metrics for PID " << pid_two << "]:" << RESET << "\n -> RAM Used: " << used_two << " MB | Private Allocation: " << private_two << " MB | Faults: " << two.PageFaultCount << endl;

        CloseHandle(process_1);
        CloseHandle(process_2);
    }

    // Feature 5: Real-Time Active Memory Guardian Engine
    void protectRam(DWORD pidPlus)
    {
        cout << BOLD << BLUE << "\n==================================" << endl;
        cout << "=  Enter Max Guard Limit (in MB): =" << endl;
        cout << "==================================" << RESET << endl;
        SIZE_T mg;
        cin >> mg;

        cout << BOLD << MAGENTA << "\n=========================================" << endl;
        cout << "=      Enter Guard Duration (Minutes):  =" << endl;
        cout << "=========================================" << RESET << endl;
        int minute;
        cin >> minute;

        PROCESS_MEMORY_COUNTERS_EX memInfoPlus = { sizeof(PROCESS_MEMORY_COUNTERS_EX) };

        system("cls");
        cout << BOLD << GREEN << "🛡️ Memory Guardian Engine Active for PID [" << pidPlus << "]..." << RESET << endl;

        for (int i = 0; i < (minute * 60); i++)
        {
            HANDLE hprocessPlus = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pidPlus);

            if (hprocessPlus != NULL)
            {
                if (GetProcessMemoryInfo(hprocessPlus, (PROCESS_MEMORY_COUNTERS *)&memInfoPlus, sizeof(memInfoPlus)))
                {
                    SIZE_T privateMemory = memInfoPlus.PrivateUsage / (1024 * 1024);

                    COORD posPlus = {0, 3};
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posPlus);

                    if (privateMemory > mg)
                    {
                        cout << BOLD << RED;
                        cout << "========================================================" << endl;
                        cout << "=       ⚠️ WARNING: THRESHOLD MEMORY LIMIT EXCEEDED !! =" << endl;
                        cout << "========================================================" << endl;
                        cout << "=  Current Private Usage: " << privateMemory << " MB / Limit: " << mg << " MB" << endl;
                        cout << "========================================================" << RESET << endl;
                    }
                    else
                    {
                        cout << BOLD << GREEN;
                        cout << "========================================================" << endl;
                        cout << "=            Status: SECURE (Under Active Guard)       =" << endl;
                        cout << "========================================================" << endl;
                        cout << "=  Current Private Usage: " << privateMemory << " MB / Limit: " << mg << " MB" << endl;
                        cout << "========================================================" << RESET << endl;
                    }
                }
                CloseHandle(hprocessPlus);
            }
            else
            {
                cout << BOLD << RED << "\n[-] 🛑 Process terminated, crashed or closed. Guardian shutting down!" << RESET << endl;
                return;
            }
            Sleep(1000); // Evaluates resource layouts every 1 second
        }
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    cout << endl << endl;
    cout << BOLD << MAGENTA;
    cout << "👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾" << endl;
    cout << "👾               WELCOME TO MY RAM UTILITY SYSTEM          👾" << endl;
    cout << "👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾 👾" << endl;
    cout << RESET << endl << endl;

    cout << BOLD << GREEN;
    cout << "1. Check Global System RAM Metrics" << endl;
    cout << "2. Inspect a Specific Process (Detailed Audit)" << endl;
    cout << "3. Show Live Global Memory Stream UI (Per Second)" << endl;
    cout << "4. Compare Memory Footprints Between Two Processes" << endl;
    cout << "5. Deploy an Active Memory Guardian Threshold on a Process" << endl;
    cout << RESET << endl;

    cout << "✨ Select a pipeline operation (1-5): ✨" << endl;
    int num;
    while (!(cin >> num) || num <= 0 || num > 5)
    {
        cout << "❌ Invalid Choice! Enter a valid index number (1-5): " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    DWORD pid, pid2;

    switch (num)
    {
    case 1:
        zoz::memoryGlobalInformation();
        break;
    case 2:
        cout << "✨ Enter Target PID: ✨" << endl;
        cin >> pid;
        zoz::memForeachProcess(pid);
        break;
    case 3:
        nassar::showMemoryPerSecond();
        break;
    case 4:
        cout << "✨ Enter First PID: ✨" << endl;
        cin >> pid;
        cout << "✨ Enter Second PID: ✨" << endl;
        cin >> pid2;
        nassar::compareTwoPids(pid, pid2);
        break;
    case 5:
        cout << "✨ Enter Target PID to Guard: ✨" << endl;
        cin >> pid;
        nassar::protectRam(pid);
        break;
    }

    cout << endl;
    system("pause");
    return 0;
}
