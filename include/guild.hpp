#pragma once
#include <iostream>
#include <regex>
#include "json/json.h"
#include "base_types.hpp"
#include "user.hpp"
#include "utils.hpp"


struct GuildPerk {
	std::string		name;
	ushort			level;

	GuildPerk() = default;
	GuildPerk(const GuildPerk &rval) = default;
	GuildPerk(const Json::Value &object);
	GuildPerk(GuildPerk &&) noexcept;

	GuildPerk &operator=(const GuildPerk &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const GuildPerk &rval);

	std::string toString() const;
};

struct GuildMember {
	User			user;
	std::string		status;
	ulonglong		joined;
	uint			guildCoins;
	uint			guildExp;

	GuildMember() = default;
	GuildMember(const GuildMember &rval) = default;
	GuildMember(const Json::Value &object);
	GuildMember(GuildMember &&old) noexcept;

	GuildMember &operator=(const GuildMember &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const GuildMember &rval);

	std::string toString() const;
};

struct Guild {
	GuildMeta							guildMeta;
	uint								totalExp;
	uint								totalCoins;
	ulonglong							created;
	std::shared_ptr<std::string>		webInfo;
	std::map<std::string, GuildPerk>	perks;
	std::vector<GuildMember>			members;

	Guild() = default;
	Guild(const	Guild &rval) = default;
	Guild(const Json::Value &object);
	Guild(Guild &&old) noexcept;

	Guild &operator=(const Guild &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Guild &rval);

	std::string toString() const;
};
