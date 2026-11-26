#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

extern int verbose;

string build_log_timestamp();

ofstream init_logfile();

fs::path get_latest_log_file();

void log(string message);

void clean_logs();

void print_logs(fs::path latest_logs);

#endif