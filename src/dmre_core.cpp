#include <iostream>
#include <string>
#include <fstream>

enum class SystemContext { IDLE, MULTITASKING, HEAVY_GAMING_OR_LOAD };

class DynamicMemoryRegulator {
private:
    SystemContext currentContext;
    const std::string swappinessPath = "/proc/sys/vm/swappiness";

    void updateKernelSwappiness(int value) {
        std::ofstream swappinessFile(swappinessPath);
        if (swappinessFile.is_open()) {
            swappinessFile << value;
            swappinessFile.close();
        }
    }

public:
    DynamicMemoryRegulator() : currentContext(SystemContext::IDLE) {}
    void monitorRuntimeContext(const std::string& activePackage, float cpuLoad, int availableRAM) {
        if (activePackage == "com.tencent.ig" || cpuLoad > 85.0) {
            currentContext = SystemContext::HEAVY_GAMING_OR_LOAD;
            updateKernelSwappiness(0);
        } else if (availableRAM < 2048) {
            currentContext = SystemContext::MULTITASKING;
            updateKernelSwappiness(60);
        }
    }
};
