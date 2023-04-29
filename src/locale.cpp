#include "locale.hpp"


GameLocale::GameLocale(const Json::Value &object): GameLocale() {
	if(object.empty()) { return; }

	name = object["name"].asString();
}

GameLocale::GameLocale(GameLocale &&old) noexcept:
	name(std::move(old.name)) {}

std::ostream &operator<<(std::ostream &os, const GameLocale &rval) {
	os << rval.toString();
	return os;
}

std::string GameLocale::toString() const {
	return format(R"({"name":{0}})", ::toString(name, true));
}


RankLocale::RankLocale(const Json::Value &object): RankLocale() {
	if(object.empty()) { return; }

	name = object["name"].asString();
	prefix = object["prefix"].asString();
}

RankLocale::RankLocale(RankLocale &&old) noexcept:
	name(std::move(old.name)),
	prefix(std::move(old.prefix)) {}

std::ostream &operator<<(std::ostream &os, const RankLocale &rval) {
	os << rval.toString();
	return os;
}

std::string RankLocale::toString() const {
	return format(R"({"name":{0},"prefix":{1}})", ::toString(name, true), ::toString(prefix, true));
}


Locale::Locale(const Json::Value &object): Locale() {
	if(object.empty()) { return; }

	for(std::string &key: object["games"].getMemberNames()) {
		games[key] = object["games"][key];
	}
	for(std::string &key : object["game_stats"].getMemberNames()) {
		gameStats[key] = object["game_stats"][key];
	}
	for(std::string &key : object["ranks"].getMemberNames()) {
		ranks[key] = object["ranks"][key];
	}
}

Locale::Locale(Locale &&old) noexcept:
	games(std::move(old.games)),
	gameStats(std::move(old.gameStats)),
	ranks(std::move(old.ranks)) {}

std::ostream &operator<<(std::ostream &os, const Locale &rval) {
	os << rval.toString();
	return os;
}

std::string Locale::toString() const {
	return format(
		R"({"games":{0},"game_stats":{1},"ranks":{2}})",
		::toString(games), ::toString(gameStats, true), ::toString(ranks)
	);
}