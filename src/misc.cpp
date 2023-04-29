#include "misc.hpp"

Game::Game(Game &&old) noexcept:
    id(std::move(old.id)),
    name(std::move(old.name)),
    globalStats(std::move(old.globalStats)),
    seasonMonthly(std::move(old.seasonMonthly)),
    seasonManual(std::move(old.seasonManual)) {}

Game::Game(const Json::Value &object): Game() {
    if(object.empty()) { return; }

    id = object["id"].asString();
    name = object["name"].asString();
    for(auto &item : object["global_stats"]) {
        globalStats.push_back(item.asString());
    }
    for(auto &item : object["season_stats"]["monthly"]) {
        seasonMonthly.push_back(item.asString());
    }
    for(auto &item : object["season_stats"]["manual"]) {
        seasonManual.push_back(item.asString());
    }
}

std::ostream &operator<<(std::ostream &os, const Game &rval) {
    os << rval.toString();
    return os;
}

std::string Game::toString() const {
    return format(
        R"({"id":{0},"name":{1},"global_stats":{2},"season_stats":{"monthly":{3},"manual":{4}}})",
        ::toString(id, true), ::toString(name, true), ::toString(globalStats, true),
        ::toString(seasonMonthly, true), ::toString(seasonManual, true));
}

GameMap::GameMap(GameMap &&old) noexcept
    : name(std::move(old.name)),
    teams(std::move(old.teams)),
    playersInTeam(std::move(old.playersInTeam)) {}

GameMap::GameMap(const Json::Value &object): GameMap() {
    if(object.empty()) { return; }

    name = object["name"].asString();
    teams = object["teams"].asUInt();
    playersInTeam = object["playersInTeam"].asUInt();
}

std::ostream &operator<<(std::ostream &os, const GameMap &rval) {
    os << rval.toString();
    return os;
}

std::string GameMap::toString() const {
    return format(R"({"name":{0},"teams":{1},"playersInTeam":{2}})",
                  ::toString(name, true), teams, playersInTeam);
}

Achievement::Achievement(Achievement &&old) noexcept:
    id(std::move(old.id)),
    title(std::move(old.title)),
    reward(std::move(old.reward)),
    description(std::move(old.description)) {}

Achievement::Achievement(const Json::Value &object): Achievement() {
    if(object.empty()) { return; }

    id = object["id"].asUInt();
    title = object["title"].asString();
    reward = object["reward"].asUInt();
    for(auto &item : object["description"]) {
        description.push_back(item.asString());
    }
}

std::ostream &operator<<(std::ostream &os, const Achievement &rval) {
    os << rval.toString();
    return os;
}

std::string Achievement::toString() const {
    return format(
        R"({"id":{0},"title":{1},"reward":{2},"description":{3}})", id,
        ::toString(title, true), reward, ::toString(description, true));
}

Token::Token(Token &&old) noexcept:
    token(std::move(old.token)),
    valid(std::move(old.valid)),
    type(std::move(old.type)),
    limit(std::move(old.limit)),
    owner(std::move(old.owner)) {}

Token::Token(const Json::Value &object): Token() {
    if(object.empty()) { return; }

    token = object["token"].asString();
    valid = object["valid"].asBool();
    type = object["type"].asString();
    limit = object["limit"].asUInt();
    owner = object["owner"].isNull() ?
        nullptr : std::make_shared<User>(object["owner"]);
}

std::ostream &operator<<(std::ostream &os, const Token &rval) {
    os << rval.toString();
    return os;
}

std::string Token::toString() const {
    return format(
        R"({"token":{0},"valid":{1},"type":{2},"limit":{3},"owner":{4}})",
        ::toString(token, true), valid, ::toString(type, true), limit,
        owner ? owner->toString() : "null");
}