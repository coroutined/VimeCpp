#include <iostream>
#include "client.hpp"

int main(int argc, char *argv[]) {
	std::setlocale(LC_ALL, "en_US.utf8");

	VimeClient api;
	auto [match, status] = api.getMatch("572314156045172736");
	if(match.game == "BP") {
		std::cout << "Found BlockParty:" << std::endl;
		std::cout << "\tTotal levels: " << match.additional["levels"];
		std::cout << "Events:" << std::endl;
		for(uint index = 0; index < match.events.size(); index++) {
			auto gameEvent = match.events[index];
			std::cout << format("\tEvent #{0}: {1}, player {2}, time elapsed {3};",
								index + 1, gameEvent["type"], gameEvent["player"],
								gameEvent["time"]) << std::endl;
		}
		std::cout << "Winner: " << match.winner["player"] << std::endl;
	} // else ...

	return 0;
}

