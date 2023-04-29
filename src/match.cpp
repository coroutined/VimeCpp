#include "match.hpp"


MatchMap::MatchMap(MatchMap &&old) noexcept:
	id(std::move(old.id)),
	name(std::move(old.name)),
	teams(std::move(old.teams)),
	playersInTeam(std::move(old.playersInTeam)) {}

MatchMap::MatchMap(const Json::Value &object): MatchMap() {
	if(object.empty()) { return; }

	id = object["id"].asString();
	name = object["name"].asString();
	teams = object["teams"].asUInt();
	playersInTeam = object["playersInTeam"].asUInt();
}

std::ostream &operator<<(std::ostream &os, const MatchMap &rval) {
	os << rval.toString();
	return os;
}

std::string MatchMap::toString() const {
	return format(R"({"id":{0},"name":{1},"teams":{2},"playersInTeam":{3}})",
				  ::toString(id, true), ::toString(name, true), teams, playersInTeam);
}


MatchMeta::MatchMeta(MatchMeta &&old) noexcept:
	id(std::move(old.id)),
	game(std::move(old.game)),
	map(std::move(old.map)),
	date(std::move(old.date)),
	duration(std::move(old.duration)),
	players(std::move(old.players)),
	win(std::move(old.win)),
	state(std::move(old.state)) {}

MatchMeta::MatchMeta(const Json::Value &object): MatchMeta() {
	if(object.empty()) { return; }

	id = object["id"].asString();
	game = object["game"].asString();
	map = object["map"].isNull() ?
		nullptr : std::make_shared<MatchMap>(object["map"]);
	date = object["date"].asUInt64();
	duration = object["duration"].asUInt64();
	players = object["players"].asUInt();
	win = object.isMember("win") && !object["win"].isNull() ?
		std::make_shared<bool>(object["win"].asBool()) : nullptr;
	state = object.isMember("state") && !object["state"].isNull() ? 
		std::make_shared<ushort>(object["state"].asUInt()) : nullptr;
}

std::ostream &operator<<(std::ostream &os, const MatchMeta &rval) {
	os << rval.toString();
	return os;
}

std::string MatchMeta::toString() const {
	return format(R"({"id":{0},"game":{1},"map":{2},"date":{3},)"
				  R"("duration":{4},"players":{5},"win":{6},"state":{7}})",
				  ::toString(id, true), ::toString(game, true), map ? map->toString() : "null",
				  date, duration, players, win ? ::toString(*win) : "null",
				  state ? ::toString(*state) : "null");
}


Match::Match(Match &&old) noexcept:
	version(std::move(old.version)),
	game(std::move(old.game)),
	server(std::move(old.server)),
	start(std::move(old.start)),
	end(std::move(old.end)),
	mapName(std::move(old.mapName)),
	mapID(std::move(old.mapID)),
	winner(std::move(old.winner)),
	players(std::move(old.players)),
	events(std::move(old.events)),
	additional(std::move(old.additional)) {}

Match::Match(const Json::Value &object): Match() {
	if(object.empty()) { return; }

	version = object["version"].asUInt();
	game = object["game"].asString();
	server = object["server"].asString();
	start = object["start"].asUInt64();
	end = object["end"].asUInt64();
	mapName = object["mapName"].isNull() ? nullptr : std::make_shared<std::string>(object["mapName"].asString());
	mapID = object["mapId"].isNull() ? nullptr : std::make_shared<std::string>(object["mapId"].asString());
	winner = object["winner"];
	players = object["players"];
	events = object["events"];
	
	Json::Value copied = object;
	for(const std::string &item: MATCH_BASE_FIELDS) {
		copied.removeMember(item);
	}
	additional = copied;
}

std::ostream &operator<<(std::ostream &os, const Match &rval) {
	os << rval.toString();
	return os;
}

std::string Match::toString() const {
	std::string mainInfo = format(R"({"version":{0},"game":{1},"server":{2},"start":{3},"end":{4},)"
								  R"("mapName":{5},"mapId":{6},"winner":{7},"players":{8},"events":{9},)",
								  version, ::toString(game, true), ::toString(server, true), start, end,
								  mapName ? ::toString(*mapName, true) : "null",
								  mapID ? ::toString(*mapID, true) : "null", ::toString(winner),
								  ::toString(players), ::toString(events));
	if(additional.empty()) {
		mainInfo[mainInfo.length() - 1] = '}';
		return mainInfo;
	}
	return mainInfo + ::toString(additional).substr(1);
}