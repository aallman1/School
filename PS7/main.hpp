// Copyright [2022] <Andrew Allman>

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<numeric>
#include<locale>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/regex.hpp>

#include "./BootSequence.hpp"

using std::vector;
using std::string;
using std::stoi;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using boost::posix_time::time_facet;
using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::regex;
using boost::smatch;

std::map<string, Service>* parseServicesLines(
    const vector<std::pair<string, int>> init_lines,
    const vector<pair<string, int>> end_lines, bool successful_boot);

const int generateBootSequences(std::ifstream&, vector<BootSequence*>&);
void generateLogs(const int line_count,
const vector<BootSequence*>&, const string& fp);

const regex INIT_BOOT_RS("\\(log\\.c\\.[0-9]+\\) server started");
const regex COMP_BOOT_RS(
    "AbstractConnector:Started SelectChannelConnector@0\\.0\\.0\\.0:9080");

const regex INIT_SERVICE_RS("Starting Service\\.  [a-zA-Z]+ [0-9]*\\.[0-9]+");
const regex COMP_SERVICE_RS("Service started successfully.");
const regex DATE_FRM_RS("[0-9]{4}-[0-9]{2}-[0-9]{2}");
const regex TIME_FRM_RS("[0-9]{2}:[0-9]{2}:[0-9]{2}(\\.[0-9]{1,3})?");
const regex ALPHA_STRING("[a-zA-Z]+");
const regex MS_FRM_NUMBER_RS("\\([0-9]+");

const size_t SERVICE_INITLINE_SPLIT_INDEX = 19;
const size_t SERVICE_ENDLINE_SPLIT_INDEX = 31;

const time_facet* T_FACET(new time_facet("%Y-%m-%d %H:%M:%S"));

const std::vector<string> SERVICES = {
    "Logging", "DatabaseInitialize", "MessagingService",
    "HealthMonitorService", "Persistence", "ConfigurationService",
    "LandingPadService", "PortConfigurationService", "CacheService",
    "ThemingService", "StagingService", "DeviceIOService", "BellService",
    "GateService", "ReaderDataService", "BiometricService",
    "StateManager", "OfflineSmartviewService", "AVFeedbackService",
    "DatabaseThreads", "SoftLoadService", "WATCHDOG",
    "ProtocolService", "DiagnosticsService"
};

#endif  // MAIN_HPP_
