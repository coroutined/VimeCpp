#include "utils.hpp"

std::string toString(const std::string &item, bool quoted) {
    return quoted && item != "null" ? "\"" + item + "\"" : item;
}

std::string toString(const Json::Value &object, bool quoted) {
    std::stringstream ss;
    switch(object.type()) {
        case Json::objectValue:
            ss << "{";
            for(std::string &key : object.getMemberNames()) {
                ss << toString(key, true) << ":" << toString(object[key], quoted);
                ss << ",";
            }
            ss.seekp(-1, std::ios::end);
            ss << "}";
            break;
        case Json::arrayValue:
            ss << "[";
            for(auto &item : object) {
                ss << toString(item, quoted) << ",";
            }
            ss.seekp(-1, std::ios::end);
            ss << "]";
            break;
        case Json::stringValue:
            ss << toString(object.asString(), quoted);
            break;
        case Json::booleanValue:
        case Json::intValue:
        case Json::nullValue:
        case Json::realValue:
        case Json::uintValue:
            ss << object;
            break;
    }
    return ss.str();
}

std::string format_impl(std::string fmt, std::vector<std::string> parameters) {
    std::string result;
    std::smatch match;
    while(std::regex_search(fmt, match, std::regex(R"((\{)(\d)(\}))"))) {
        uint index = std::stoi(match[2].str());
        result += match.prefix().str() + parameters[index];
        fmt = match.suffix().str();
    }
    return result + fmt;
}