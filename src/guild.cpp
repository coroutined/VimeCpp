#include "guild.hpp"


GuildPerk::GuildPerk(const Json::Value &object): GuildPerk() {
	if(object.empty()) { return; }

	name = object["name"].asString();
	level = object["level"].asUInt();
}

GuildPerk::GuildPerk(GuildPerk &&old) noexcept:
	name(std::move(old.name)),
	level(std::move(old.level)) {}

std::ostream &operator<<(std::ostream &os, const GuildPerk &rval) {
	os << rval.toString();
	return os;
}

std::string GuildPerk::toString() const {
	return format(R"({"name":{0},"level":{1}})", ::toString(name, true), level);
}


GuildMember::GuildMember(const Json::Value &object): GuildMember() {
	if(object.empty()) {
		return;
	}
	user = object["user"];
	status = object["status"].asString();
	joined = object["joined"].asUInt64();
	guildCoins = object["guildCoins"].asUInt();
	guildExp = object["guildExp"].asUInt();
}

GuildMember::GuildMember(GuildMember &&old) noexcept:
	user(std::move(old.user)),
	status(std::move(old.status)),
	joined(std::move(old.joined)),
	guildCoins(std::move(old.guildCoins)),
	guildExp(std::move(old.guildExp)) {}

std::ostream &operator<<(std::ostream &os, const GuildMember &rval) {
	os << rval.toString();
	return os;
}

std::string GuildMember::toString() const {
	return format(R"({"user":{0},"status":{1},"joined":{2},"guildCoins":{3},"guildExp":{4}})",
				  user.toString(), ::toString(status, true), joined, guildCoins, guildExp);
}


Guild::Guild(const Json::Value &object): Guild() {
	if(object.empty()) {
		return;
	}
	guildMeta = object;
	totalExp = object["totalExp"].asUInt();
	totalCoins = object["totalCoins"].asUInt();
	created = object["created"].asUInt64();
	webInfo = object["web_info"].isNull() ?
		nullptr : std::make_shared<std::string>(object["web_info"].asString());
	for(std::string &key: object["perks"].getMemberNames()) {
		perks[key] = object["perks"][key];
	}
	members = std::vector<GuildMember>(object["members"].begin(), object["members"].end());
}

Guild::Guild(Guild &&old) noexcept:
	guildMeta(std::move(old.guildMeta)),
	totalExp(std::move(old.totalExp)),
	totalCoins(std::move(old.totalCoins)),
	created(std::move(old.created)),
	webInfo(std::move(old.webInfo)),
	perks(std::move(old.perks)),
	members(std::move(old.members)) {}

std::ostream &operator<<(std::ostream &os, const Guild &rval) {
	os << rval.toString();
	return os;
}

std::string Guild::toString() const {
	std::string metaString = guildMeta.toString();
	std::string rawWeb = (webInfo ? *webInfo : "null");
	if(rawWeb != "null") {
		do {
			std::size_t index = rawWeb.find_first_of("\n\t");
			if(index == std::string::npos) {
				break;
			}
			rawWeb.replace(index, 1, rawWeb[index] == '\n' ? "\\n" : "\\t");
		} while(true);
	}

	return metaString.substr(0, metaString.length() - 1) + format(
		R"(,"totalExp":{0},"totalCoins":{1},"created":{2},"web_info":{3},"perks":{4},"members":{5}})",
		totalExp, totalCoins, created, rawWeb == "null" ? rawWeb : ::toString(rawWeb, true),
		::toString(perks), ::toString(members)
	);
}
