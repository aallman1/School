// Copyright [2022] <Andrew Allman>

#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include<string>

using std::string;

class Service {
 public:
    Service();
    Service(const string&, const int, const int, const int, const bool);
    void setName(const string&);
    void setInitLine(const int);
    void setEndLine(const int);
    void setElapsed(const int);
    void setSuccessful(const bool);
    const string& getName() const;
    const int getInitLine() const;
    const int getEndLine() const;
    const int getElapsed() const;
    const bool getSuccessful() const;
 private:
    string _servicename;
    int _initline;
    int _endline;
    int _elapsed;
    bool _successful;
};

#endif  // SERVICE_HPP_
