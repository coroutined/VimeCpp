#pragma once
#include <iostream>
#include "base_types.hpp"
#include "user.hpp"
#include "utils.hpp"


struct Game {
	std::string				 id;
	std::string				 name;
	std::vector<std::string> globalStats;
	std::vector<std::string> seasonMonthly;
	std::vector<std::string> seasonManual;

	Game() = default;
	Game(const Game &rval) = default;
	Game(Game &&old) noexcept;
	Game(const Json::Value &object);
	~Game() = default;

	Game &operator=(const Game &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Game &rval);

	std::string toString() const;
};

struct GameMap {
	std::string				 name;
	ushort					 teams;
	ushort					 playersInTeam;

	GameMap() = default;
	GameMap(const GameMap &rval) = default;
	GameMap(GameMap &&old) noexcept;
	GameMap(const Json::Value &object);
	~GameMap() = default;

	GameMap &operator=(const GameMap &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const GameMap &rval);

	std::string toString() const;
};

struct Achievement {
	ushort					 id;
	std::string				 title;
	ushort					 reward;
	std::vector<std::string> description;

	Achievement() = default;
	Achievement(const Achievement &rval) = default;
	Achievement(Achievement &&old) noexcept;
	Achievement(const Json::Value &object);
	~Achievement() = default;

	Achievement &operator=(const Achievement &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Achievement &rval);

	std::string toString() const;
};

struct Token {
	std::string				token;
	bool					valid;
	std::string				type;
	ushort					limit;
	std::shared_ptr<User>	owner;

	Token() = default;
	Token(const Token &rval) = default;
	Token(Token &&old) noexcept;
	Token(const Json::Value &object);
	~Token() = default;

	Token &operator=(const Token &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Token &rval);

	std::string toString() const;
};