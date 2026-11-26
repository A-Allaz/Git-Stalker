#ifndef __LOGGER_CPP__
#define __LOGGER_CPP__

#include <utils/logger.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int verbose = 0;

string build_log_timestamp(){
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto milliseconds = duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const std::time_t time = system_clock::to_time_t(now);

    std::ostringstream result;
    result << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S") << '_' << std::setfill('0') << std::setw(3) << milliseconds.count();

    return result.str();
}

ofstream init_logfile(){
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home/") / user;

    fs::create_directories(root_dir / ".gitstalker/gitstalker_logs");

    return(ofstream(root_dir.string() + "/" + ".gitstalker/gitstalker_logs/" + build_log_timestamp() + ".log"));
}

fs::path get_latest_log_file(){
    fs::path latest = "";
    fs::file_time_type latest_time = fs::file_time_type::min();
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home/") / user;

    for (const auto& entry : fs::directory_iterator(root_dir / ".gitstalker/gitstalker_logs")) {
        if (!entry.is_regular_file() || entry.path().extension() != ".log")
            continue;

        const auto modified = entry.last_write_time();
        if (modified > latest_time) {
            latest = entry.path();
            latest_time = modified;
        }
    }

    return latest;
}

void log(string message){
    cerr << "[" << build_log_timestamp() << "] " << message << endl;
}

void clean_logs(){
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home/") / user;

    fs::remove_all(root_dir / ".gitstalker/gitstalker_logs");
}

void print_logs(fs::path latest_logs){
    if (latest_logs.empty())
        return;

    std::ifstream log_line(latest_logs);
    if (!log_line) {
        std::cerr << "Could not open log file " << latest_logs << '\n';
        return;
    }

    std::string line;
    while (std::getline(log_line, line)) {
        const char* color = "\033[37m"; // White

        if (line.find("[ERROR]") != std::string::npos)
            color = "\033[31m"; // Red
        else if (line.find("[WARNING]") != std::string::npos)
            color = "\033[35m"; // Magenta (purple)

        std::cout << color << line << "\033[0m" << endl;
    }
}

void dump_logs(fs::path log_file){
    if (log_file.empty())
        return;

    std::ifstream log_line(log_file);
    if (!log_line) {
        std::cerr << "Could not open log file " << log_file << '\n';
        return;
    }

    std::string line;
    while (std::getline(log_line, line)) {

        if (line.find("[ERROR]") != std::string::npos)
            std::cout << "\033[31m" << line << "\033[0m" << endl;
        else if (line.find("[WARNING]") != std::string::npos)
            std::cout << "\033[35m" << line << "\033[0m" << endl;
    }
}

#endif