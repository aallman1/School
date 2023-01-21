// Copyright [2022] <Andrew Allman>



#include "./BootSequence.hpp"


BootSequence::BootSequence() {}

void BootSequence::setInitLine(const int initline) { _initline = initline; }

void BootSequence::setEndLine(const int endline) { _endline = endline; }

void BootSequence::setBootStampStart(const ptime& bootstampstart) {
_bootstampstart = bootstampstart; }

void BootSequence::setBootStampComplete(const ptime& bootstampcomplete) {
_bootstampcomplete = bootstampcomplete; }

void BootSequence::setSuccessful(const bool successfulboot) {
_successfulboot = successfulboot; }

void BootSequence::setServiceMap(map<string, Service>* services) {
_services = services; }

const int BootSequence::getInitLine() const { return _initline; }

const int BootSequence::getEndLine() const { return _endline; }

const bool BootSequence::Successful() const { return _successfulboot; }

const ptime& BootSequence::getBootStampStart() const {
return _bootstampstart; }

const ptime& BootSequence::getBootStampComplete() const {
return _bootstampcomplete; }

const map<string, Service>* BootSequence::getServiceMap() const {
return _services; }

BootSequence::~BootSequence() {
if (~_services->empty()) { delete _services; } }







