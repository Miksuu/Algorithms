#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <string>
#include <iomanip>

class MemoryTools {
public:
    // https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
    static std::string getVirtualMemoryUsageWindowsInMB() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

        double memoryUsageMB = static_cast<double>(virtualMemUsedByMe) / (1024 * 1024);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(5) << memoryUsageMB;
        return stream.str() + "Mb"; // Memory usage in MB as a string
    }
};
