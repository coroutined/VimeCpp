#include "client.hpp"


std::ostream &operator<<(std::ostream &os, const RateHeader &rval) {
	os << rval.toString();
	return os;
}

std::string RateHeader::toString() const {
	return format(
		R"({"x-ratelimit-limit":{0},"x-ratelimit-remaining":{1},"x-ratelimit-reset-after":{2}})",
		limit, remaining, resetAfter
	);
}

VimeClient::VimeClient(const std::string _inDevToken): devToken(_inDevToken) {
	VimeResponse<Token> tokenValidity = getTokenInfo(this->devToken);
	if(!tokenValidity.first.valid) {
		std::cerr << "[VimeClient]: Invalid token, resetting." << std::endl;
		//this->devToken = "";
	}
}

VimeResponse<Json::Value> VimeClient::requestToMethod(const std::string	  _inMethodPathWithParameter,
													  const cpr::Parameters _inAdditionalParams) {
	Json::Value result;
	cpr::Response response = cpr::Get(
		cpr::Url(API_URL + _inMethodPathWithParameter),
		devToken.empty() ? cpr::Header{} : cpr::Header{{"Access-Token", devToken}},
		_inAdditionalParams
	);
	if(!parser.parse(response.text, result)) {
		return {result, PARSE_ERROR_CODE};
	}
	if(response.status_code == 200) {
		rateHeader.limit = std::atoi(response.header["x-ratelimit-limit"].c_str());
		rateHeader.remaining = std::atoi(response.header["x-ratelimit-remaining"].c_str());
		rateHeader.resetAfter = std::atoi(response.header["x-ratelimit-reset-after"].c_str());
	}

	if(result.isObject()) {
		if(!result["error"].isNull()) {
			int code = result["error"]["error_code"].asInt();
			return {result, code >= 10 ? RESOURCE_NOT_EXIST : static_cast<RequestStatus>(code)};
		}
		result.removeMember("error");
	}
	return {result, SUCCESS_CODE};
}

VimeResponse<std::vector<User>> VimeClient::getUsersByNames(std::vector<std::string> _inNames) {
	std::string namesString = toString(_inNames);
	VimeResponse<Json::Value> object = requestToMethod("user/name/" + namesString.substr(1, namesString.length() - 2));
	if(object.second) {
		return {std::vector<User>(), object.second};
	}
	return {std::vector<User>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::vector<User>> VimeClient::getUsersByIDs(std::vector<uint> _inIDs) {
	std::string idsString = toString(_inIDs);
	VimeResponse<Json::Value> object = requestToMethod("user/" + idsString.substr(1, idsString.length() - 2));
	if(object.second) {
		return {std::vector<User>(), object.second};
	}
	return {std::vector<User>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::vector<User>> VimeClient::getFriends(const uint _inUserID) {
	VimeResponse<Json::Value> object = requestToMethod("user/" + std::to_string(_inUserID) + "/friends");
	if(object.second) {
		return {std::vector<User>(), object.second};
	}
	return {std::vector<User>(object.first["friends"].begin(), object.first["friends"].end()), object.second};
}

VimeResponse<std::vector<User>> VimeClient::getFriends(const User _inUser) {
	return getFriends(_inUser.id);
}

VimeResponse<UserSession> VimeClient::getUserSession(const uint _inUserID) {
	VimeResponse<Json::Value> object = requestToMethod("user/" + std::to_string(_inUserID) + "/session");
	if(object.second) {
		return {UserSession(), object.second};
	}
	return {UserSession(object.first["online"]), object.second};
}

VimeResponse<UserSession> VimeClient::getUserSession(User _inUser) {
	return getUserSession(_inUser.id);
}

VimeResponse<Json::Value> VimeClient::getUserStats(const uint						 _inUserID,
												 std::vector<std::string> _inGames) {
	std::string gamesString = toString(_inGames);
	cpr::Parameters parameters = gamesString == "[]" ? cpr::Parameters{} :
		cpr::Parameters{{"games", gamesString.substr(1, gamesString.length() - 2)}};
	VimeResponse<Json::Value> object = requestToMethod(
		"user/" + std::to_string(_inUserID) + "/stats",
		parameters
	);
	if(object.second) {
		return {Json::Value(), object.second};
	}
	return {object.first["stats"], object.second};
}

VimeResponse<Json::Value> VimeClient::getUserStats(const User						 _inUser,
												 std::vector<std::string> _inGames) {
	return getUserStats(_inUser.id, _inGames);
}

VimeResponse<std::vector<UserAchievement>> VimeClient::getUserAchievements(const uint _inUserID) {
	VimeResponse<Json::Value> object = requestToMethod("user/" + std::to_string(_inUserID) + "/achievements");
	if(object.second) {
		return {std::vector<UserAchievement>(), object.second};
	}
	return {std::vector<UserAchievement>(
		object.first["achievements"].begin(), object.first["achievements"].end()
	), object.second};
}

VimeResponse<std::vector<UserAchievement>> VimeClient::getUserAchievements(const User _inUser) {
	return getUserAchievements(_inUser.id);
}

VimeResponse<std::vector<UserLeaderboard>> VimeClient::getUserLeaderboards(const uint _inUserID) {
	VimeResponse<Json::Value> object = requestToMethod("user/" + std::to_string(_inUserID) + "/leaderboards");
	if(object.second) {
		return {std::vector<UserLeaderboard>(), object.second};
	}
	return {std::vector<UserLeaderboard>(
		object.first["leaderboards"].begin(), object.first["leaderboards"].end()
	), object.second};
}

VimeResponse<std::vector<UserLeaderboard>> VimeClient::getUserLeaderboards(const User _inUser) {
	return getUserLeaderboards(_inUser.id);
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesOffset(const uint _inUserID,
																		const uint _inOffset,
																		const uint _inCount) {
	VimeResponse<Json::Value> object = requestToMethod(
		"user/" + std::to_string(_inUserID) + "/matches",
		cpr::Parameters{{"count", std::to_string(_inCount)}, {"offset", std::to_string(_inOffset)}}
	);
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first["matches"].begin(), object.first["matches"].end()), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesAfter(const uint		   _inUserID,
																	   const std::string   _inAfter,
																	   const uint		   _inCount) {
	VimeResponse<Json::Value> object = requestToMethod(
		"user/" + std::to_string(_inUserID) + "/matches",
		cpr::Parameters{{"count", std::to_string(_inCount)}, {"after", _inAfter}}
	);
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first["matches"].begin(), object.first["matches"].end()), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesBefore(const uint		  _inUserID,
																		const std::string _inBefore,
																		const uint		  _inCount) {
	VimeResponse<Json::Value> object = requestToMethod(
		"user/" + std::to_string(_inUserID) + "/matches",
		cpr::Parameters{{"count", std::to_string(_inCount)}, {"before", _inBefore}}
	);
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first["matches"].begin(), object.first["matches"].end()), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesOffset(const User _inUser,
																		const uint _inOffset,
																		const uint _inCount) {
	return getUserMatchesOffset(_inUser.id, _inOffset, _inCount);
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesAfter(const User		   _inUser,
																	   const std::string   _inAfter,
																	   const uint		   _inCount) {
	return getUserMatchesAfter(_inUser.id, _inAfter, _inCount);
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getUserMatchesBefore(const User		  _inUser,
																		const std::string _inBefore,
																		const uint	  	  _inCount) {
	return getUserMatchesBefore(_inUser.id, _inBefore, _inCount);
}

VimeResponse<std::map<uint, UserSession>> VimeClient::getUsersSessions(std::vector<uint> _inUserIDs) {
	std::map<uint, UserSession> sessions;
	std::string idsString = toString(_inUserIDs);
	VimeResponse<Json::Value> object = requestToMethod("user/session/" + idsString.substr(1, idsString.length() - 2));
	if(object.second) {
		return {sessions, object.second};
	}
	std::for_each(
		object.first.begin(),
		object.first.end(),
		[&](const Json::Value &item) { sessions[item["id"].asUInt()] = item["online"]; }
	);
	return {sessions, object.second};
}

VimeResponse<std::map<uint, UserSession>> VimeClient::getUsersSessions(std::vector<User> _inUsers) {
	std::vector<uint> usersIDs;
	std::for_each(_inUsers.begin(), _inUsers.end(), [&usersIDs](const User &item) { usersIDs.push_back(item.id); });
	return getUsersSessions(usersIDs);
}


VimeResponse<std::vector<GuildMeta>> VimeClient::searchGuild(const std::string _inQuery) {
	VimeResponse<Json::Value> object = requestToMethod("guild/search", cpr::Parameters{{"query", _inQuery}});
	if(object.second) {
		return {std::vector<GuildMeta>(), object.second};
	}
	return {std::vector<GuildMeta>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<Guild> VimeClient::getGuildID(const uint _inGuildID) {
	VimeResponse<Json::Value> object = requestToMethod("guild/get", cpr::Parameters{{"id", std::to_string(_inGuildID)}});
	if(object.second) {
		return {Guild(), object.second};
	}
	return {Guild(object.first), object.second};
}

VimeResponse<Guild> VimeClient::getGuildName(const std::string _inGuildName) {
	VimeResponse<Json::Value> object = requestToMethod("guild/get", cpr::Parameters{{"name", _inGuildName}});
	if(object.second) {
		return {Guild(), object.second};
	}
	return {Guild(object.first), object.second};
}

VimeResponse<Guild> VimeClient::getGuildTag(const std::string _inGuildTag) {
	VimeResponse<Json::Value> object = requestToMethod("guild/get", cpr::Parameters{{"tag", _inGuildTag}});
	if(object.second) {
		return {Guild(), object.second};
	}
	return {Guild(object.first), object.second};
}

VimeResponse<std::vector<LeaderboardInfo>> VimeClient::getLeaderboardList() {
	VimeResponse<Json::Value> object = requestToMethod("leaderboard/list");
	if(object.second) {
		return {std::vector<LeaderboardInfo>(), object.second};
	}
	return {std::vector<LeaderboardInfo>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<Leaderboard> VimeClient::getLeaderboard(const std::string _inType,
													 const ushort	   _inSize,
													 const ushort	   _inOffset,
													 const std::string _inSort) {
	VimeResponse<Json::Value> object = requestToMethod(
		"leaderboard/get/" + _inType + (_inSort != "" ? "/" + _inSort : ""),
		cpr::Parameters{{"size", std::to_string(_inSize)}, {"offset", std::to_string(_inOffset)}}
	);
	if(object.second) {
		return {Leaderboard(), object.second};
	}
	return {Leaderboard(object.first), object.second};
}


VimeResponse<Online> VimeClient::getOnline() {
	VimeResponse<Json::Value> object = requestToMethod("online");
	if(object.second) {
		return {Online(), object.second};
	}
	return {Online(object.first), object.second};
}

VimeResponse<std::vector<Stream>> VimeClient::getOnlineStreams() {
	VimeResponse<Json::Value> object = requestToMethod("online/streams");
	if(object.second) {
		return {std::vector<Stream>(), object.second};
	}
	return {std::vector<Stream>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::vector<OnlineStaff>> VimeClient::getOnlineStaff() {
	VimeResponse<Json::Value> object = requestToMethod("online/staff");
	if(object.second) {
		return {std::vector<OnlineStaff>(), object.second};
	}
	return {std::vector<OnlineStaff>(object.first.begin(), object.first.end()), object.second};
}


VimeResponse<Match> VimeClient::getMatch(const std::string _inMatchID) {
	VimeResponse<Json::Value> object = requestToMethod("match/" + _inMatchID);
	if(object.second) {
		return {Match(), object.second};
	}
	return {Match(object.first), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getLatestMatches(const ushort _inCount) {
	VimeResponse<Json::Value> object = requestToMethod("match/latest", cpr::Parameters{{"count", std::to_string(_inCount)}});
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getMatchesBefore(const std::string _inMatchIDBefore,
																		const ushort	  _inCount) {
	VimeResponse<Json::Value> object = requestToMethod(
		"match/list",
		cpr::Parameters{{"before", _inMatchIDBefore}, {"count", std::to_string(_inCount)}}
	);
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::vector<MatchMeta>> VimeClient::getMatchesAfter(const std::string _inMatchIDAfter,
																	   const ushort		 _inCount) {
	VimeResponse<Json::Value> object = requestToMethod(
		"match/list",
		cpr::Parameters{{"after", _inMatchIDAfter}, {"count", std::to_string(_inCount)}}
	);
	if(object.second) {
		return {std::vector<MatchMeta>(), object.second};
	}
	return {std::vector<MatchMeta>(object.first.begin(), object.first.end()), object.second};
}


VimeResponse<Locale> VimeClient::getLocale(const std::string				 _inLanguage,
											 std::vector<std::string>		 _inParts) {
	std::string partsString = toString(_inParts);
	cpr::Parameters params = partsString == "[]" ? cpr::Parameters{} :
		cpr::Parameters{{"parts", partsString.substr(1, partsString.length() - 2)}};
	VimeResponse<Json::Value> object = requestToMethod("locale/" + _inLanguage, params);
	if(object.second) {
		return {Locale(), object.second};
	}
	return {Locale(object.first), object.second};
}


VimeResponse<std::vector<Game>> VimeClient::getGames() {
	VimeResponse<Json::Value> object = requestToMethod("misc/games");
	if(object.second) {
		return {std::vector<Game>(), object.second};
	}
	return {std::vector<Game>(object.first.begin(), object.first.end()), object.second};
}

VimeResponse<std::map<std::string, std::map<std::string, GameMap>>> VimeClient::getAllMaps() {
	std::map<std::string, std::map<std::string, GameMap>> maps;
	VimeResponse<Json::Value> object = requestToMethod("misc/maps");
	if(object.second) {
		return {maps, object.second};
	}
	for(std::string &key: object.first.getMemberNames()) {
		maps[key] = std::map<std::string, GameMap>();
		for(std::string &map: object.first[key].getMemberNames()) {
			maps[key][map] = object.first[key][map];
		}
	}
	return {maps, object.second};
}

VimeResponse<std::map<std::string, std::vector<Achievement>>> VimeClient::getAllAchievements() {
	std::map<std::string, std::vector<Achievement>> achievements;
	VimeResponse<Json::Value> object = requestToMethod("misc/achievements");
	if(object.second) {
		return {achievements, object.second};
	}
	for(std::string &key: object.first.getMemberNames()) {
		achievements[key] = std::vector<Achievement>();
		for(auto &item: object.first[key]) {
			achievements[key].push_back(item);
		}
	}
	return {achievements, object.second};
}

VimeResponse<Token> VimeClient::getTokenInfo(std::string _inToken) {
	VimeResponse<Json::Value> object = requestToMethod("misc/token/" + _inToken);
	return {Token(object.first), object.second};
}