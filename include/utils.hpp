#pragma once
#include "base_types.hpp"
#include "cpr/cpr.h"
#include "json/json.h"
#include <Windows.h>
#include <regex>

std::string toString(const std::string &item, bool quoted = false);
std::string toString(const Json::Value &object, bool quoted = true);
std::string format_impl(std::string fmt, std::vector<std::string> parameters);

template <typename T>
inline std::string toString(const T &item, bool quoted = false) {
    std::stringstream ss;
    ss << item;
    return ss.str();
}

template <typename T>
inline std::string toString(const std::vector<T> &iterable,
                            bool quoted = false) {
    if(iterable.size() == 0) { return "[]"; }

    std::stringstream ss;
    ss << "[";
    for(auto &item : iterable) {
        ss << toString(item, quoted) << ",";
    }
    ss.seekp(-1, std::ios::end);
    ss << "]";
    return ss.str();
}

template <typename T, typename Y>
inline std::string toString(const std::map<T, Y> &iterable,
                            bool quoted = false) {
    if(iterable.size() == 0) {
        return "{}";
    }
    std::stringstream ss;
    ss << "{";
    for(auto &item : iterable) {
        ss << toString(item.first, true) << ":"
           << toString(item.second, quoted) << ",";
    }
    ss.seekp(-1, std::ios::end);
    ss << "}";
    return ss.str();
}

template <typename Arg, typename... Args>
inline std::string format_impl(std::string fmt,
                               std::vector<std::string> parameters,
                               Arg &&arg,
                               Args &&... args) {
    parameters.push_back(toString(arg));
    return format_impl(fmt, parameters, std::forward<Args>(args)...);
}

template <typename Arg, typename... Args>
inline std::string format(std::string fmt, Arg &&arg, Args &&... args) {
    std::vector<std::string> parameters;
    return format_impl(fmt, parameters, std::forward<Arg>(arg),
                       std::forward<Args>(args)...);
}