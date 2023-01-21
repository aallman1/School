// Copyright [2022] <Andrew Allman>

#ifndef BOOTSEQUENCE_HPP_
#define BOOTSEQUENCE_HPP_

#include<string>
#include<map>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "./Service.hpp"


using std::map;
using boost::posix_time::ptime;


class BootSequence {
 public:
    BootSequence();
    void setInitLine(const int);
    void setEndLine(const int);
    void setBootStampStart(const ptime&);
    void setBootStampComplete(const ptime&);
    void setSuccessful(const bool);
    const bool Successful() const;
    void setServiceMap(map<string, Service>*);
    const map<string, Service>* getServiceMap() const;
    const ptime& getBootStampStart() const;
    const ptime& getBootStampComplete() const;
    const int getInitLine() const;
    const int getEndLine() const;
    ~BootSequence();
 private:
    int _initline;
    int _endline;
    ptime _bootstampstart;
    ptime _bootstampcomplete;
    bool _successfulboot;
    map<string, Service>* _services;
};

#endif  // BOOTSEQUENCE_HPP_

