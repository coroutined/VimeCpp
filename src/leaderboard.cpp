#include "leaderboard.hpp"


LeaderboardInfo::LeaderboardInfo(const Json::Value &object): LeaderboardInfo() {
	if(object.empty()) { return; }

	type = object["type"].asString();
	description = object["description"].asString();
	maxSize = object["max_size"].asUInt();
	for(auto &item: object["sort"]) {
		sort.push_back(item.asString());
	}
}

LeaderboardInfo::LeaderboardInfo(LeaderboardInfo &&old) noexcept:
	type(std::move(old.type)),
	description(std::move(old.description)),
	maxSize(std::move(old.maxSize)),
	sort(std::move(old.sort)) {}

std::ostream &operator<<(std::ostream &os, const LeaderboardInfo &rval) {
	os << rval.toString();
	return os;
}

std::string LeaderboardInfo::toString() const {
	return format(R"({"type":{0},"description":{1},"max_size":{2},"sort":{3}})",
				  ::toString(type, true), ::toString(description, true),
				  maxSize, ::toString(sort, true));
}


LeaderboardMeta::LeaderboardMeta(const Json::Value &object): LeaderboardMeta() {
	if(object.empty()) { return; }

	type = object["type"].asString();
	sort = object["sort"].asString();
	offset = object["offset"].asUInt();
	size = object["size"].asUInt();
	maxSize = object["max_size"].asUInt();
}

LeaderboardMeta::LeaderboardMeta(LeaderboardMeta &&old) noexcept:
	type(std::move(old.type)),
	sort(std::move(old.sort)),
	offset(std::move(old.offset)),
	size(std::move(old.size)),
	maxSize(std::move(old.maxSize)) {}

std::ostream &operator<<(std::ostream &os, const LeaderboardMeta &rval) {
	os << rval.toString();
	return os;
}

std::string LeaderboardMeta::toString() const {
	return format(R"({"type":{0},"sort":{1},"offset":{2},"size":{3},"max_size":{4}})",
				  ::toString(type, true), ::toString(sort, true), offset, size, maxSize);
}

Leaderboard::Leaderboard(const Json::Value &object): Leaderboard() {
	if(object.empty()) { return; }

	leaderboard = object["leaderboard"];
	records = object["records"];
}

Leaderboard::Leaderboard(Leaderboard &&old) noexcept:
	leaderboard(std::move(old.leaderboard)),
	records(std::move(old.records)) {}

std::ostream &operator<<(std::ostream &os, const Leaderboard &rval) {
	os << rval.toString();
	return os;
}

std::string Leaderboard::toString() const {
	return format(R"({"leaderboard":{0},"records":{1}})",
				  leaderboard.toString(), ::toString(records));
}