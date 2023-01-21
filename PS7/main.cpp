// Copyright [2022] <Andrew Allman>



#include "./main.hpp"



int main(int argc, char* argv[]) {
    string log_filename = argv[1];
    std::ifstream logfile(log_filename);
    log_filename.substr(log_filename.find("/") + 1);
    std::vector<BootSequence*> Sequences;
    int lines = generateBootSequences(logfile, Sequences);
    generateLogs(lines, Sequences,
        log_filename.substr(log_filename.find("/") + 1));
    for (auto& boot_sequence : Sequences) {
        delete boot_sequence;
    }
}

void generateLogs(const int line_count,
const vector<BootSequence*>& Sequences,
const string& filename) {
    std::ofstream boot_log;
    vector<string> exception_cases;
    boot_log.open("reports/" + filename + ".rpt");
    boot_log.imbue(std::locale(cout.getloc(), T_FACET));

    int completed = std::accumulate(Sequences.begin(), Sequences.end(), 0,
    [](int sum, const BootSequence* itr)
    {return sum + static_cast<int>(itr->Successful());});

    boot_log << "Device Boot Report\n" << endl;
    boot_log << "InTouch log file: " + filename << endl;
    boot_log << "Lines Scanned: " << line_count << endl;

    boot_log << "Device boot count: initiated = "
    << Sequences.size()
    << ", Completed: "
    << completed
    << "\n"
    << endl;

    for (auto& boot_sequence : Sequences) {
        boot_log << "=== Device boot ===" << endl;
        if (boot_sequence->Successful()) {
            boot_log << boot_sequence->getInitLine()
            << "(" + filename + "): "
            << boot_sequence->getBootStampStart()
            << " Boot Start"
            << endl;

            boot_log << boot_sequence->getEndLine()
            << "(" + filename + "): "
            << boot_sequence->getBootStampComplete()
            << " Boot Completed"
            << endl;

            boot_log << "\tBoot Time: " << (
                boot_sequence->getBootStampComplete() -
                boot_sequence->getBootStampStart()).total_milliseconds()
            << " ms"
            << "\n"
            << endl;

            boot_log << "Services" << endl;

            auto service_map_ptr = boot_sequence->getServiceMap();
            for (auto& service : SERVICES) {
                if ((*service_map_ptr).find(service)
                != (*service_map_ptr).end()) {
                    boot_log << "\t" + service + "\n";

                    if ((*service_map_ptr).at(service).getEndLine() == -1) {
                        boot_log << "\t\tStart: "
                        << "Not Started"
                        << "(" + filename + ")"
                        << endl;
                    } else {
                        boot_log << "\t\tStart: "
                        << (*service_map_ptr).at(service).getInitLine()
                        << "(" + filename + ")"
                        << endl;
                    }

                    if ((*service_map_ptr).at(service).getEndLine() == -1) {
                    boot_log << "\t\tCompleted: "
                    << "Not Completed"
                    << "(" + filename + ")"
                    << endl
                    << "\t\tElapsed Time: \n"
                    << endl;
                    exception_cases.push_back(service);
                    } else {
                    boot_log << "\t\tCompleted: "
                        << (*service_map_ptr).at(service).getEndLine()
                        << "(" + filename + ")"
                        << endl
                        << "\t\tElapsed Time: "
                        << (*service_map_ptr).at(service).getElapsed()
                        << " ms\n"
                        << endl;
                    }
                } else {
                    exception_cases.push_back(service);
                }
            }
            if (!exception_cases.empty()) {
                boot_log << "\t*** Services not successfully started: ";
                for (auto str_itr = exception_cases.begin();
                    str_itr != exception_cases.end() - 1; ++str_itr) {
                        boot_log << *str_itr << ", ";
                }
            boot_log << exception_cases[exception_cases.size() - 1]
            << "\n"
            << endl;
            exception_cases.clear();
            }
        } else {
            boot_log << boot_sequence->getInitLine()
            << "(" + filename + "): "
            << boot_sequence->getBootStampStart()
            << " Boot Start"
            << endl
            << "**** Incomplete boot ****\n"
            << endl;

            boot_log << "Services" << endl;

            for (auto& service : SERVICES) {
                boot_log << "\t" + service + "\n"
                << "\t\tStart: Not started"
                << "(" + filename + ")"
                << endl
                << "\t\tCompleted: Not completed"
                << "(" + filename + ")"
                << endl
                << "\t\tElapsed Time:"
                << endl;
            }

            boot_log << "\n\t*** Services not successfully started: ";

            for (auto str_itr = SERVICES.begin();
            str_itr != SERVICES.end() - 1; ++str_itr) {
                boot_log << *str_itr << ", ";
            }
            boot_log << SERVICES[SERVICES.size() - 1]
            << "\n"
            << endl;
        }
    }
    boot_log.close();
}

const int generateBootSequences(std::ifstream& logfile,
vector<BootSequence*>& Sequences) {
    bool first_pass = true, boot_complete = false;
    int line_count = 0, bt_init_line = -1, bt_end_line = -1;
    time_duration starttime, endtime;
    date start_date;
    smatch rs_match;
    std::string t_line;

    std::vector<std::pair<std::string, int>>
    service_init_lines,
    service_end_lines;

    while (!logfile.eof()) {
        line_count++;

        std::getline(logfile, t_line);

        if (regex_search(t_line, INIT_BOOT_RS)) {
            if (!first_pass) {
                if (boot_complete) {
                    Sequences.push_back(new BootSequence);
                    Sequences[Sequences.size() - 1]->
                    setServiceMap(parseServicesLines(
                        service_init_lines, service_end_lines, true));
                    Sequences[Sequences.size() - 1]->
                    setBootStampStart(ptime(start_date, starttime));
                    Sequences[Sequences.size() - 1]->
                    setBootStampComplete(ptime(start_date, endtime));
                    Sequences[Sequences.size() - 1]->
                    setInitLine(bt_init_line);
                    Sequences[Sequences.size() - 1]->
                    setEndLine(bt_end_line);
                    Sequences[Sequences.size() - 1]->
                    setSuccessful(true);
                    service_init_lines.clear();
                    service_end_lines.clear();
                    boot_complete = false;
                } else {
                    Sequences.push_back(new BootSequence);
                    Sequences[Sequences.size() - 1]->
                    setServiceMap(parseServicesLines(
                        service_init_lines, service_end_lines, false));
                    Sequences[Sequences.size() - 1]->
                    setBootStampStart(ptime(start_date, starttime));
                    Sequences[Sequences.size() - 1]->
                    setInitLine(bt_init_line);
                    Sequences[Sequences.size() - 1]->
                    setSuccessful(false);
                    service_init_lines.clear();
                    service_end_lines.clear();
                }

            } else { first_pass = false; }

            bt_init_line = line_count;

            if (regex_search(t_line, rs_match, DATE_FRM_RS)) {
                start_date = date(from_simple_string(rs_match.str()));
            }

            if (regex_search(t_line, rs_match, TIME_FRM_RS)) {
                starttime = time_duration(
                    std::stoi(rs_match.str().substr(0, 2)),
                    std::stoi(rs_match.str().substr(3, 2)),
                    std::stoi(rs_match.str().substr(6, 2)), 0);
            }
        }

        if (regex_search(t_line, COMP_BOOT_RS) && !first_pass) {
            if (regex_search(t_line, rs_match, TIME_FRM_RS)) {
                endtime = time_duration(
                    std::stoi(rs_match.str().substr(0, 2)),
                    std::stoi(rs_match.str().substr(3, 2)),
                    std::stoi(rs_match.str().substr(6, 2)), 0);
                boot_complete = true;
                bt_end_line = line_count;
            }
        }

        if (regex_search(t_line, INIT_SERVICE_RS) && !first_pass) {
            service_init_lines.push_back(
                std::pair<string, int>(t_line, line_count));
        }

        if (regex_search(t_line, COMP_SERVICE_RS) && !first_pass) {
            service_end_lines.push_back(
                std::pair<string, int>(t_line, line_count));
        }
    }

    if (!service_init_lines.empty() && boot_complete) {
        Sequences.push_back(new BootSequence);
        Sequences[Sequences.size() - 1]->
        setServiceMap(parseServicesLines(
            service_init_lines, service_end_lines, true));
        Sequences[Sequences.size() - 1]->
        setBootStampStart(ptime(start_date, starttime));
        Sequences[Sequences.size() - 1]->
        setBootStampComplete(ptime(start_date, endtime));
        Sequences[Sequences.size() - 1]->
        setInitLine(bt_init_line);
        Sequences[Sequences.size() - 1]->
        setEndLine(bt_end_line);
        Sequences[Sequences.size() - 1]->
        setSuccessful(true);
        service_init_lines.clear();
        service_end_lines.clear();
    } else if (!service_init_lines.empty()) {
        Sequences.push_back(new BootSequence);
        Sequences[Sequences.size() - 1]->
        setServiceMap(parseServicesLines(
            service_init_lines, service_end_lines, false));
        Sequences[Sequences.size() - 1]->
        setBootStampStart(ptime(start_date, starttime));
        Sequences[Sequences.size() - 1]->
        setInitLine(bt_init_line);
        Sequences[Sequences.size() - 1]->
        setSuccessful(false);
        service_init_lines.clear();
        service_end_lines.clear();
    }
    return t_line == "" ? --line_count : line_count;
}

std::map<std::string, Service>* parseServicesLines(
const vector<std::pair<std::string, int>> init_lines,
const vector<std::pair<std::string, int>> end_lines, bool successful_boot) {
    smatch rs_match;
    std::map<std::string, Service>* service_map =
        new std::map<std::string, Service>;

    if (successful_boot) {
        for (auto& line : init_lines) {
            string temp_split = line.first.substr(SERVICE_INITLINE_SPLIT_INDEX);
            if (regex_search(temp_split, rs_match, ALPHA_STRING)) {
                (*service_map)[rs_match.str()].setName(rs_match.str());
                (*service_map)[rs_match.str()].setInitLine(line.second);
                (*service_map)[rs_match.str()].setSuccessful(true);
            }
        }

        for (auto& line : end_lines) {
            string temp_split = line.first.substr(SERVICE_ENDLINE_SPLIT_INDEX);
            if (regex_search(temp_split, rs_match, ALPHA_STRING)) {
                string tServiceName(rs_match.str());
                (*service_map)[tServiceName].setEndLine(line.second);
                if (regex_search(temp_split, rs_match, MS_FRM_NUMBER_RS)) {
                    (*service_map)[tServiceName].setElapsed(
                        stoi(rs_match.str().substr(1)));
                }
            }
        }
    } else {
        for (auto& service : SERVICES) {
            (*service_map)[service] = Service();
            (*service_map)[service].setSuccessful(false);
        }
    }
    return service_map;
}



