// Copyright [2022] <Andrew Allman>

#include "./Service.hpp"


Service::Service(): _servicename("undefined"), _initline(-1),
_endline(-1), _elapsed(-1), _successful(false) {}

Service::Service(const string& servicename,
const int initline, const int endline,
const int elapsed, const bool successful):
_initline(initline),
_endline(endline),
_elapsed(elapsed),
_successful(successful) {}

void Service::setName(const string& servicename) {
_servicename = servicename; }

void Service::setInitLine(const int initline) {
_initline =  initline; }

void Service::setEndLine(const int endline) {
_endline = endline; }

void Service::setElapsed(const int elapsed) {
_elapsed = elapsed; }

void Service::setSuccessful(const bool successful) {
_successful = successful; }

const string& Service::getName() const {
return _servicename; }

const int Service::getInitLine() const {
return _initline; }

const int Service::getEndLine() const {
return _endline; }

const int Service::getElapsed() const {
return _elapsed; }

const bool Service::getSuccessful() const {
return _successful; }
