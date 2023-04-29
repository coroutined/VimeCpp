#pragma once
#include <iostream>
#include "json/json.h"
#include "base_types.hpp"
#include "user.hpp"
#include "utils.hpp"


struct LeaderboardInfo {
	std::string						type;
	std::string						description;
	ushort							maxSize;
	std::vector<std::string>		sort;

	LeaderboardInfo() = default;
	LeaderboardInfo(const LeaderboardInfo &rval) = default;
	LeaderboardInfo(const Json::Value &object);
	LeaderboardInfo(LeaderboardInfo &&old) noexcept;

	LeaderboardInfo &operator=(const LeaderboardInfo &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const LeaderboardInfo &rval);

	std::string toString() const;
};

struct LeaderboardMeta {
	std::string						type;
	std::string						sort;
	ushort							offset;
	ushort							size;
	ushort							maxSize;

	LeaderboardMeta() = default;
	LeaderboardMeta(const LeaderboardMeta &rval) = default;
	LeaderboardMeta(const Json::Value &object);
	LeaderboardMeta(LeaderboardMeta &&old) noexcept;

	LeaderboardMeta &operator=(const LeaderboardMeta &old) = default;
	friend std::ostream &operator<<(std::ostream &os, const LeaderboardMeta &rval);

	std::string toString() const;
};

struct Leaderboard {
	LeaderboardMeta					leaderboard;
	Json::Value						records;

	Leaderboard() = default;
	Leaderboard(const Leaderboard &rval) = default;
	Leaderboard(const Json::Value &object);
	Leaderboard(Leaderboard &&old) noexcept;

	Leaderboard &operator=(const Leaderboard &old) = default;
	friend std::ostream &operator<<(std::ostream &os, const Leaderboard &rval);

	std::string toString() const;
};