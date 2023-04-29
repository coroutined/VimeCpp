#include "user.hpp"


GuildMeta::GuildMeta(GuildMeta &&old) noexcept:
	id(std::move(old.id)),
	name(std::move(old.name)),
	color(std::move(old.color)),
	level(std::move(old.level)),
	levelPercentage(std::move(old.levelPercentage)),
	tag(std::move(old.tag)),
	avatarUrl(std::move(old.avatarUrl)) {}

GuildMeta::GuildMeta(const Json::Value &object): GuildMeta() {
	if(object.empty()) { return; }

	id = object["id"].asInt();
	name = object["name"].asString();
	tag = object["tag"].isNull() ?
		nullptr : std::make_shared<std::string>(object["tag"].asString());
	color = object["color"].asString();
	level = object["level"].asInt();
	levelPercentage = object["levelPercentage"].asFloat();
	avatarUrl = object["avatar_url"].isNull() ? 
		nullptr : std::make_shared<std::string>(object["avatar_url"].asString());
}

std::ostream &operator<<(std::ostream &os, const GuildMeta &rval) {
	os << rval.toString();
	return os;
}

std::string GuildMeta::toString() const {
	return format(R"({"id":{0},"name":{1},"tag":{2},"color":{3},"level":{4},)"
				  R"("levelPercentage":{5},"avatar_url":{6}})",
				  id, ::toString(name, true), tag ? ::toString(*tag, true) : "null",
				  ::toString(color, true), level, levelPercentage,
				  avatarUrl ? ::toString(*avatarUrl, true) : "null");
}


User::User(User &&old) noexcept:
	id(std::move(old.id)),
	username(std::move(old.username)),
	level(std::move(old.level)),
	levelPercentage(std::move(old.levelPercentage)),
	rank(std::move(old.rank)),
	playedSeconds(std::move(old.playedSeconds)),
	lastSeen(std::move(old.lastSeen)),
	guild(std::move(old.guild)) {}

User::User(const Json::Value &object): User() {
	if(object.empty()) { return; }

	id = object["id"].asInt();
	username = object["username"].asString();
	level = object["level"].asInt();
	levelPercentage = object["levelPercentage"].asFloat();
	rank = object["rank"].asString();
	playedSeconds = object["playedSeconds"].asInt();
	lastSeen = object["lastSeen"].asInt64();
	guild = object["guild"].isNull() ?
		nullptr : std::make_shared<GuildMeta>(object["guild"]);
}

std::ostream &operator<<(std::ostream &os, const User &rval) {
	os << rval.toString();
	return os;
}

std::string User::toString() const {
	return format(R"({"id":{0},"username":"{1}","level":{2},"levelPercentage":{3},)"
				  R"("rank":"{4}","playedSeconds":{5},"lastSeen":{6},"guild":{7}})",
				  id, username, level, levelPercentage, rank, playedSeconds,
				  lastSeen, guild ? guild->toString() : "null");
}


UserSession::UserSession(UserSession &&old) noexcept:
	value(std::move(old.value)),
	message(std::move(old.message)),
	game(std::move(old.game)) {}

UserSession::UserSession(const Json::Value &object): UserSession() {
	if(object.empty()) { return; }

	value = object["value"].asBool();
	message = object["message"].asString();
	game = object["game"].isNull() ?
		nullptr : std::make_shared<std::string>(object["game"].asString());
}

std::ostream &operator<<(std::ostream &os, const UserSession &rval) {
	os << rval.toString();
	return os;
}

std::string UserSession::toString() const {
	return format(R"({"value":{0},"message":{1},"game":{2}})",
				  value, ::toString(message, true),
				  game ? ::toString(*game, true) : "null");
}


UserAchievement::UserAchievement(UserAchievement &&old) noexcept:
	id(std::move(old.id)),
	time(std::move(old.time)) {}

UserAchievement::UserAchievement(const Json::Value &object): UserAchievement() {
	if(object.empty()) { return; }

	id = object["id"].asUInt();
	time = object["time"].asUInt64();
}

std::ostream &operator<<(std::ostream &os, const UserAchievement &rval) {
	os << rval.toString();
	return os;
}

std::string UserAchievement::toString() const {
	return format(R"({"id":{0},"time":{1}})", id, time);
}


UserLeaderboard::UserLeaderboard(UserLeaderboard &&old) noexcept:
	type(std::move(old.type)),
	sort(std::move(old.sort)),
	place(std::move(old.place)) {}

UserLeaderboard::UserLeaderboard(const Json::Value &object): UserLeaderboard() {
	if(object.empty()) { return; }

	type = object["type"].asString();
	sort = object["sort"].asString();
	place = object["place"].asUInt();
}

std::ostream &operator<<(std::ostream &os, const UserLeaderboard &rval) {
	os << rval.toString();
	return os;
}

std::string UserLeaderboard::toString() const {
	return format(R"({"type":{0},"sort":{1},"place":{2}})",
				  ::toString(type, true), ::toString(sort, true), place);
}
