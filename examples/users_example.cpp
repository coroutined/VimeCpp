#include <iostream>
#include "client.hpp"

int main(int argc, char *argv[]) {
	std::setlocale(LC_ALL, "en_US.utf8");

	VimeClient api;

	auto [users, status] = api.getUsersByNames({"AlesteZ", "Okssi", "CharkosOff"});
	//auto [users, status] = api.getUsersByIDs({1476864, 94245, 4278493});
	std::cout << "Users by nicknames:" << std::endl;
	if(status == RequestStatus::SUCCESS_CODE) {
		for(std::size_t index = 0; index < users.size(); index++) {
			User &user = users.at(index);
			std::cout << format("\tUser #{0}: {1} ({2} lvl, {3}%)", 
								index, user.username, user.level, user.levelPercentage * 100) << std::endl;
		}
	} else {
		std::cout << "\tCode error: " << status << std::endl;
	}

	return 0;
}

