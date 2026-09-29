#pragma once
#include <string>
#include <vector>

struct ProcessInfo {
    int pid;
    std::string name;
    long memoryUsageKB;
};

class ProcessMonitor {
public:
    // Сканирует /proc и возвращает процессы, превышающие лимит памяти
    static std::vector<ProcessInfo> GetMemoryHogs(long limitKB);
    static void TerminateProcess(int pid);
};
