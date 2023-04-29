#pragma once
#include <iostream>
#include <map>
#include "json/json.h"
#include "utils.hpp"


struct GameLocale {
	std::string name;

	GameLocale() = default;
	GameLocale(const GameLocale &rval) = default;
	GameLocale(const Json::Value &object);
	GameLocale(GameLocale &&old) noexcept;
	~GameLocale() = default;

	GameLocale &operator=(const GameLocale &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const GameLocale &rval);

	std::string toString() const;
};

struct RankLocale {
	std::string name;
	std::string prefix;

	RankLocale() = default;
	RankLocale(const RankLocale &rval) = default;
	RankLocale(const Json::Value &object);
	RankLocale(RankLocale &&old) noexcept;
	~RankLocale() = default;
	
	RankLocale &operator=(const RankLocale &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const RankLocale &rval);

	std::string toString() const;
};

struct Locale {
	std::map<std::string, GameLocale> games;
	std::map<std::string, Json::Value> gameStats;
	std::map<std::string, RankLocale>  ranks;

	Locale() = default;
	Locale(const Locale &rval) = default;
	Locale(const Json::Value &object);
	Locale(Locale &&old) noexcept;
	~Locale() = default;

	Locale &operator=(const Locale &rval) = default;
	friend std::ostream &operator<<(std::ostream &os, const Locale &rval);

	std::string toString() const;
};