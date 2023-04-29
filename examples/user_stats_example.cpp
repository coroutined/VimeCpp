#include <iostream>
#include "client.hpp"

int main(int argc, char *argv[]) {
	std::setlocale(LC_ALL, "en_US.utf8");

	VimeClient api;
	auto [stats, status] = api.getUserStats(38609);
	std::cout << "BlockParty global stats:" << std::endl;
	for(std::string &key: stats["BP"]["global"].getMemberNames()) {
		std::cout << format("\t{0}: {1}", key, stats["BP"]["global"][key]) << std::endl;
	}
	std::cout << "BlockParty season stats:" << std::endl;
	for(std::string &key: stats["BP"]["season"]["monthly"].getMemberNames()) {
		std::cout << format("\t{0}: {1}", key, stats["BP"]["season"]["monthly"][key]) << std::endl;
	}
	auto bwhypeGlobal = stats["BWHYPE"]["global"];
	std::cout << format("BedWars Hype total kills/deaths: {0}/{1}",
						bwhypeGlobal["kills"], bwhypeGlobal["deaths"]) << std::endl;

	return 0;
}

