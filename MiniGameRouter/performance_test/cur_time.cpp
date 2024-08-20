#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>

// 将时间戳转换为字符串，保留毫秒级精度
std::string timestampToString(std::chrono::milliseconds timestamp) {
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timestamp);
    auto milliseconds = timestamp - std::chrono::duration_cast<std::chrono::milliseconds>(seconds);

    std::time_t time = seconds.count();
    std::tm tm;
    localtime_r(&time, &tm);  // 使用线程安全的 localtime_r

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    return oss.str();
}

// 将字符串转换为时间戳，保留毫秒级精度
std::chrono::milliseconds stringToTimestamp(const std::string& timeString) {
    std::tm tm = {};
    std::istringstream iss(timeString.substr(0, 19));
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

    std::time_t time = std::mktime(&tm);
    int milliseconds = 0;
    try {
        milliseconds = std::stoi(timeString.substr(20, 3));
    } catch (const std::exception& e) {
        std::cerr << "Error parsing milliseconds: " << e.what() << std::endl;
    }

    auto duration = std::chrono::seconds(time) + std::chrono::milliseconds(milliseconds);
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

int main() {
    // 打开文件进行写入
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();
    auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    // 将时间戳转换为字符串
    std::string timeString = timestampToString(currentTimestamp);
    outFile << "Time String: " << timeString << std::endl;

    // 将字符串转换为时间戳
    auto newTimestamp = stringToTimestamp(timeString);
    outFile << "New Timestamp (ms): " << newTimestamp.count() << std::endl;

    // 关闭文件
    outFile.close();

    return 0;
}