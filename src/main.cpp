#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

size_t get_file_checksum(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "[!] Error: Unable to open file at path: " << filePath << std::endl;
        return 0;
    }

    size_t checksum = 0;
    char byte;
    while (file.get(byte)) {
        checksum += static_cast<unsigned char>(byte);
    }

    file.close();
    return checksum;
}

int main() {
    //config
    const std::string targetFile = "protected/text.txt";
    const int checkIntervalSeconds = 2;

    std::cout << "===========================================" << std::endl;
    std::cout << "   Simple File Integrity Monitor v1.0      " << std::endl;
    std::cout << "===========================================" << std::endl;

    //initialize baseline
    std::cout << "[*] Initializing baseline for: " << targetFile << std::endl;
    size_t baselineHash = get_file_checksum(targetFile);

    if (baselineHash == 0) {
        std::cerr << "[!] Critical error establishing baseline. Check if file exists." << std::endl;
        return 1;
    }

    std::cout << "[+] Baseline established. Hash: " << baselineHash << std::endl;
    std::cout << "[*] Monitoring started. Interval: " << checkIntervalSeconds << "s" << std::endl;
    std::cout << "[*] Press Ctrl+C to terminate program." << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    try {
        while (true) {
            //checking file integrity
            size_t currentHash = get_file_checksum(targetFile);

            if (currentHash != baselineHash) {
                std::cout << "\n[ALERT] INTEGRITY VIOLATION DETECTED!" << std::endl;
                std::cout << "  -> Expected: " << baselineHash << std::endl;
                std::cout << "  -> Actual:   " << currentHash << std::endl;
                std::cout << "[*] Monitoring halted due to change." << std::endl;
                break;
            }

            //Use a small delay to prevent high CPU usage
            std::this_thread::sleep_for(std::chrono::seconds(checkIntervalSeconds));
        }
    } catch (const std::exception& e) {
        std::cerr << "[!] An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
