#include <iostream>
#include "client.hpp"

int main(int argc, char *argv[]) {
	std::setlocale(LC_ALL, "en_US.utf8");

	VimeClient api;
	auto [leaders, status] = api.getLeaderboard("user", 20, 0);
	std::cout << leaders.leaderboard << std::endl;
	for(uint index = 0; index < leaders.records.size(); index++) {
		auto record = leaders.records[index];
		std::cout << format("#{0}: {1} ({2} lvl, {3}%);",
							index + 1, record["username"], record["level"], 
							record["levelPercentage"].asFloat() * 100) << std::endl;
	}

	std::tie(leaders, status) = api.getLeaderboard("guild", 10, 10, "total_coins");
	std::cout << std::endl << leaders.leaderboard << std::endl;
	for(uint index = 0; index < leaders.records.size(); index++) {
		auto record = leaders.records[index];
		std::cout << format("#{0}: {1}, ({2} lvl, {3}%), {4} coins total;",
							index + 11, record["name"], record["level"],
							record["levelPercentage"].asFloat() * 100,
							record["totalCoins"]) << std::endl;
	}

	std::tie(leaders, status) = api.getLeaderboard("prison", 5, 0);
	std::cout << std::endl << leaders.leaderboard << std::endl;
	for(uint index = 0; index < leaders.records.size(); index++) {
		auto record = leaders.records[index];
		std::cout << format("#{0}: {1}, {2} blocks total;",
							index + 1, record["user"]["username"],
							record["total_blocks"]) << std::endl;
	}

	return 0;
}

