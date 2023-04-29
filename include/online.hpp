#pragma once
#include <map>
#include "json/json.h"
#include "base_types.hpp"
#include "user.hpp"
#include "utils.hpp"


struct Online {
	ushort							total;
	std::map<std::string, ushort>	separated;

	Online() = default;
	Online(const Online &rval) = default;
	Online(const Json::Value &object);
	Online(Online &&old) noexcept;

	Online &operator=(const Online &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Online &rval);

	std::string toString() const;
};

struct Stream {
	std::string						title;
	std::string						owner;
	ushort							viewers;
	std::string						url;
	uint							duration;
	std::string						platform;
	User							user;

	Stream() = default;
	Stream(const Stream &rval) = default;
	Stream(const Json::Value &object);
	Stream(Stream &&old) noexcept;

	Stream &operator=(const Stream &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Stream &rval);

	std::string toString() const;
};

struct OnlineStaff {
	User							user;
	UserSession						online;

	OnlineStaff() = default;
	OnlineStaff(const OnlineStaff &rval) = default;
	OnlineStaff(const Json::Value &object);
	OnlineStaff(OnlineStaff &&old) noexcept;

	OnlineStaff &operator=(const OnlineStaff &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const OnlineStaff &rval);

	std::string toString() const;
};
