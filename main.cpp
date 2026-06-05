#define _WIN32_WINNT 0x0601

#include <iostream>
#include <string>
#include <windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <iomanip>

using namespace std;

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

    void all_info_about_system()
    {
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(MEMORYSTATUSEX);

        GlobalMemoryStatusEx(&mem_info);

        DWORDLONG all = mem_info.ullTotalPhys / (1024 * 1024 * 1024);
        DWORDLONG avlible = mem_info.ullAvailPhys / (1024 * 1024 * 1024);
        DWORDLONG mem_free = all - avlible;
        DWORDLONG percnt = mem_info.dwMemoryLoad;

        cout << BOLD << MAGENTA;
        cout << "=====================================" << endl;
        cout << "=       ALL RAM : " << all << " GB             =" << endl;
        cout << "=====================================" << endl;
        cout << endl;
        cout << "=====================================" << endl;
        cout << "=    AVALIBLE RAM : " << avlible << " GB           =" << endl;
        cout << "=====================================" << endl;
        cout << endl;
        cout << "=====================================" << endl;
        cout << "=       USAGE RAM : " << percnt << " %            =" << endl;
        cout << "=====================================" << endl;
        cout << endl;
        cout << "=====================================" << endl;
        cout << "=       FREE RAM : " << mem_free << " GB            =" << endl;
        cout << "=====================================" << endl;
        cout << endl;
        cout << RESET;
    }

    void mem_for_one_process(DWORD pid)
    {

        HANDLE h_proces = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

        if (h_proces == NULL)
        {
            cout << BOLD << RED;
            cout << "ERROR ERROR !!! INVALID PROCESS FOR PID " << pid << " !! " << endl;
            cout << endl;
            cout << RESET;
            return;
        }

        PROCESS_MEMORY_COUNTERS_EX mem_for_one_process;
        mem_for_one_process.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

        if (GetProcessMemoryInfo(h_proces, (PROCESS_MEMORY_COUNTERS *)&mem_for_one_process, sizeof(mem_for_one_process)))
        {

            SIZE_T mem_one_programm = mem_for_one_process.WorkingSetSize / (1024 * 1024);
            SIZE_T max_mem_used = mem_for_one_process.PeakWorkingSetSize / (1024 * 1024);
            SIZE_T private_usage = mem_for_one_process.PrivateUsage / (1024 * 1024);
            DWORD max_faulet = mem_for_one_process.PageFaultCount;

            cout << BOLD << BLUE;
            cout << "===========================================" << endl;
            cout << "=     INFORMATION ABOUT YOUR PROGRAMM     =" << endl;
            cout << "===========================================" << endl;
            cout << RESET;
            cout << endl;

            cout << RED;
            cout << "THE RAM :  " << mem_one_programm << " MB " << endl;
            cout << "PRIVATE USAGE : " << private_usage << " MB " << endl;
            cout << "THE MAX FAUELT : " << max_faulet << " time " << endl;
            cout << "MAX RAM USED : " << max_mem_used << " MB " << endl;
            cout << RESET;
        }
        else
        {
            cout << BOLD << RED;
            cout << "ERROR ERROR !!! INVALID PROCESS FOR PID " << pid << " !! " << endl;
            cout << endl;
            cout << RESET;
            return;
        }
    }

};

namespace nassar
{

    void show_ram_usage()
    {

        cout << BLUE;
        MEMORYSTATUSEX zoz;
        zoz.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&zoz);

        while (true)
        {
            system("cls");
            COORD pos = {10, 10};

            // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            cout << "=========================" << endl;
            cout << "=                      " << 50 << "=" << endl;
            cout << "=========================" << endl;
            Sleep(5000);
        }
        cout << RESET;
    }
    void compar_two_pid(DWORD pid_one, DWORD pid_two)
    {
        HANDLE process_1 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid_one);
        HANDLE process_2 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid_two);

        if (process_1 == NULL)
        {
        }
        else if (process_2 == NULL)
        {
            cout << "INVALID PROCESS FOR PID " << pid_one << " ERROR !!! " << endl;
        }
        PROCESS_MEMORY_COUNTERS_EX one;
        one.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
        ;
        //?===============================  one ===========================================

        GetProcessMemoryInfo(process_1, (PROCESS_MEMORY_COUNTERS *)&one, sizeof(one));

        DWORDLONG used = one.WorkingSetSize / (1024 * 1024);
        DWORD max_fault = one.PageFaultCount;
        DWORDLONG private_useing = one.PrivateUsage / (1024 * 1024);

        PROCESS_MEMORY_COUNTERS_EX two;
        two.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

        //?===============================  two ===========================================

        GetProcessMemoryInfo(process_2, (PROCESS_MEMORY_COUNTERS *)&two, sizeof(two));

        DWORDLONG used_two = two.WorkingSetSize / (1024 * 1024);
        DWORD max_fault_two = two.PageFaultCount;
        DWORDLONG private_useing_two = two.PrivateUsage / (1024 * 1024);

        if (used > used_two)
        {
            cout << BLUE;
            cout << "===============================================" << endl;
            cout << "=       InFormation about Process One         =" << endl;
            cout << "===============================================" << endl;
            cout << RESET;
            cout << RED;
            cout << "======================================" << endl;
            cout << "=             DANGER DANGER !!!      =" << endl;
            cout << "======================================" << endl;
            cout << RESET;
            cout << BOLD << RED;

            cout << "Process ONE  take ram grater than process two " << used - used_two << " MB  " << endl;
            cout << "The usage (Process one ) with pid  : " << pid_one << " : " << used << endl;
            cout << "private useing is : " << private_useing << " MB ";
            cout << "The MAX Fauelt : " << max_fault << " Times " << endl;
            cout << RESET;
        }

        else if (used_two > used)
        {
            cout << BLUE;
            cout << "===============================================" << endl;
            cout << "=       InFormation about Process Two         =" << endl;
            cout << "===============================================" << endl;
            cout << RESET;
            cout << RED;
            cout << "======================================" << endl;
            cout << "=             DANGER DANGER !!!      =" << endl;
            cout << "======================================" << endl;
            cout << RESET;
            cout << BOLD << RED;
            cout << "Process ONE  take ram grater than process two " << used_two - used << " MB  " << endl;
            cout << "The usage (Process two ) with pid  : " << pid_two << " : " << used_two << endl;
            cout << "private useing is : " << private_useing_two << " MB ";
            cout << "The MAX Fauelt : " << max_fault_two << " Times " << endl;
            cout << RESET;
        }

        else if (used == used_two)
        {
            cout << CYAN;
            cout << "TWO PROCESSS ARE EQUAL " << endl;
            cout << RESET;
            cout << BOLD << MAGENTA;
            cout << "===============================================" << endl;
            cout << "=       InFormation about Process One         =" << endl;
            cout << "===============================================" << endl;

            cout << "The usage (Process one ) with pid  : " << pid_one << " : " << used << endl;
            cout << "private useing is : " << private_useing << " MB ";
            cout << "The MAX Fauelt : " << max_fault << " Times " << endl;
            cout << RESET;
            cout << endl;

            cout << BLUE;
            cout << "===============================================" << endl;
            cout << "=       InFormation about Process Two         =" << endl;
            cout << "===============================================" << endl;
            cout << RESET;
            cout << BOLD << RED;
            cout << "The usage (Process two ) with pid  : " << pid_two << " : " << used_two << endl;
            cout << "private useing is : " << private_useing_two << " MB ";
            cout << "The MAX Fauelt : " << max_fault_two << " Times " << endl;
            cout << RESET;
        }
    }

};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    cout << BOLD << GREEN;
    cout << endl
         << endl;
    cout << "\t\t\t\t\t===================================================" << endl;
    cout << "\t\t\t\t\t=           WELCOME TO MY RAM SYSTEM              =" << endl;
    cout << "\t\t\t\t\t===================================================" << endl;
    cout << RESET;
    cout << endl
         << endl;
    // zoz::all_info_about_system();

    nassar::show_ram_usage();
    cout << endl
         << endl;
    return 0;
}
