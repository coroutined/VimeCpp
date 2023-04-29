#pragma once
#include <iostream>
#include "json/json.h"
#include "base_types.hpp"
#include "utils.hpp"


struct GuildMeta {
	ushort							id;
	std::string						name;
	std::shared_ptr<std::string>	tag;
	std::string						color;
	ushort							level;
	float							levelPercentage;
	std::shared_ptr<std::string>	avatarUrl;

	GuildMeta()	= default;
	GuildMeta(const GuildMeta &rval) = default;
	GuildMeta(const Json::Value &object);
	GuildMeta(GuildMeta &&old) noexcept;

	GuildMeta &operator=(const GuildMeta &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const GuildMeta &rval);

	std::string toString() const;
};

struct User {
	uint							id;
	std::string						username;
	ushort							level;
	float							levelPercentage;
	std::string						rank;
	uint							playedSeconds;
	ulonglong						lastSeen;
	std::shared_ptr<GuildMeta>		guild;

	User() = default;
	User(const User &rval) = default;
	User(const Json::Value &object);
	User(User &&old) noexcept;

	User &operator=(const User &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const User &rval);

	std::string toString() const;
};

struct UserSession {
	bool							value;
	std::string						message;
	std::shared_ptr<std::string>	game;

	UserSession() = default;
	UserSession(const UserSession &rval) = default;
	UserSession(const Json::Value &object);
	UserSession(UserSession &&old) noexcept;

	UserSession &operator=(const UserSession &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const UserSession &rval);

	std::string toString() const;
};

struct UserAchievement {
	ushort							id;
	ulonglong						time;

	UserAchievement() = default;
	UserAchievement(const UserAchievement &rval) = default;
	UserAchievement(const Json::Value &object);
	UserAchievement(UserAchievement &&old) noexcept;

	UserAchievement &operator=(const UserAchievement &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const UserAchievement &rval);

	std::string toString() const;
};

struct UserLeaderboard {
	std::string						type;
	std::string						sort;
	ushort							place;

	UserLeaderboard() = default;
	UserLeaderboard(const UserLeaderboard &rval) = default;
	UserLeaderboard(const Json::Value &object);
	UserLeaderboard(UserLeaderboard &&old) noexcept;

	UserLeaderboard &operator=(const UserLeaderboard &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const UserLeaderboard &rval);

	std::string toString() const;
};
