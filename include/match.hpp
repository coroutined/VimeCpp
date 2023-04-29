#pragma once
#include <iostream>
#include "json/json.h"
#include "base_types.hpp"
#include "utils.hpp"
#include "user.hpp"


const std::vector<std::string> MATCH_BASE_FIELDS({"version", "game", "server", "start", "end", "mapName",
												  "mapId", "winner", "players", "events", "error"});

struct MatchMap {
	std::string					id;
	std::string					name;
	ushort						teams;
	ushort						playersInTeam;

	MatchMap() = default;
	MatchMap(const MatchMap &rval) = default;
	MatchMap(MatchMap &&old) noexcept;
	MatchMap(const Json::Value &object);
	~MatchMap() = default;

	MatchMap &operator=(const MatchMap &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const MatchMap &rval);

	std::string toString() const;
};

struct MatchMeta {
	std::string					id;
	std::string					game;
	std::shared_ptr<MatchMap>	map;
	ulonglong					date;
	ushort						duration;
	ushort						players;
	std::shared_ptr<bool>		win;
	std::shared_ptr<ushort>		state;

	MatchMeta() = default;
	MatchMeta(const MatchMeta &rval) = default;
	MatchMeta(MatchMeta &&old) noexcept;
	MatchMeta(const Json::Value &object);
	~MatchMeta() = default;

	MatchMeta &operator=(const MatchMeta &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const MatchMeta &rval);

	std::string toString() const;
};

struct Match {
	ushort						 version;
	std::string					 game;
	std::string					 server;
	ulonglong					 start;
	ulonglong					 end;
	std::shared_ptr<std::string> mapName;
	std::shared_ptr<std::string> mapID;
	Json::Value					 winner;
	Json::Value					 players;
	Json::Value					 events;
	Json::Value					 additional;

	Match() = default;
	Match(const Match &rval) = default;
	Match(Match &&old) noexcept;
	Match(const Json::Value &object);
	~Match() = default;

	Match &operator=(const Match &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Match &rval);

	std::string toString() const;
};