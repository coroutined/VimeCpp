#pragma once
#include <utility>


enum RequestStatus {
	PARSE_ERROR_CODE = -4, // Non-API status code - JSON parse error
	UNEXPECTED_ERROR = -3,
	INTERNAL_SERVER_ERROR = -2,
	NO_METHOD_ERROR = -1,
	SUCCESS_CODE = 0,
	INCORRECT_TOKEN = 1,
	RATE_LIMIT_REACHED = 2,
	ARGUMENT_ERROR = 3,
	METHOD_DISABLED = 4,
	RESOURCE_NOT_EXIST = 10, // 10+ status code, depends on method
};

template<class T>
using VimeResponse = std::pair<T, RequestStatus>;
using ulonglong = unsigned long long;
using ushort = unsigned short;
using ulong = unsigned long;
using uint = unsigned int;