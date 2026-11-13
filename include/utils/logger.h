#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <iostream>

using namespace std;

extern int verbose;

string build_log_timestamp();

ofstream init_logfile();

void log(string message);

void clean_logs();

#endif