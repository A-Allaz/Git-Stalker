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
    filesystem::path root_dir = filesystem::path("/home/") / user;

    filesystem::create_directories(root_dir / ".gitstalker_logs");

    return(ofstream(root_dir.string() + "/" + ".gitstalker_logs/" + build_log_timestamp() + ".log"));
}

void log(string message){
    cerr << "[" << build_log_timestamp() << "] " << message << endl;
}

#endif