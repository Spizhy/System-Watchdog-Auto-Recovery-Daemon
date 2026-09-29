#include "ProcessMonitor.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <csignal>
#include <sstream>

namespace fs = std::filesystem;

std::vector<ProcessInfo> ProcessMonitor::GetMemoryHogs(long limitKB) {
    std::vector<ProcessInfo> hogs;

    // В Linux информация о процессах хранится в /proc
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (!entry.is_directory()) continue;
        
        std::string dirName = entry.path().filename().string();
        // Проверяем, является ли имя папки числом (PID)
        if (dirName.find_first_not_of("0123456789") != std::string::npos) continue;

        int pid = std::stoi(dirName);
        std::string statusPath = entry.path().string() + "/status";
        
        std::ifstream statusFile(statusPath);
        if (!statusFile.is_open()) continue;

        std::string line;
        std::string name;
        long vmrss = 0;

        while (std::getline(statusFile, line)) {
            if (line.rfind("Name:", 0) == 0) {
                std::istringstream iss(line);
                std::string key;
                iss >> key >> name;
            } else if (line.rfind("VmRSS:", 0) == 0) {
                std::istringstream iss(line);
                std::string key, unit;
                iss >> key >> vmrss >> unit;
            }
        }

        if (vmrss > limitKB) {
            hogs.push_back({pid, name, vmrss});
        }
    }
    return hogs;
}

void ProcessMonitor::TerminateProcess(int pid) {
    std::cout << "[Watchdog] Sending SIGTERM to PID " << pid << "\n";
    kill(pid, SIGTERM); // Мягкое завершение процесса
}
