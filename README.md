![CMake Workflow](https://github.com/coroutined/VimeCpp/actions/workflows/cmake.yml/badge.svg)

----
# VimeCpp
C++ библиотека для работы с VimeWorld API.

## Зависимости и версии
**Стандарт:** C++17 и новее.
**CMake:** 3.11 и новее.
Внешние зависимости:
1. **libcpr 1.10.2** - Легковесная библиотека для HTTP-запросов, <a href="https://github.com/libcpr/cpr">ссылка на репозиторий</a>.
2. **jsoncpp 1.9.5** - Легковесная библиотека для JSON, <a href="https://github.com/open-source-parsers/jsoncpp">ссылка на репозиторий</a>.

## Установка
```sh
git clone https://github.com/coroutined/VimeCpp.git
mkdir VimeCpp\build && cd VimeCpp\build && cmake ..
cmake --build . --config=Release
```

## Примеры
Взаимодействие с игроками:
```cpp
auto [users, status] = api.getUsersByNames({"AlesteZ", "Okssi", "CharkosOff"});
std::tie(users, status) = api.getUsersByIDs({1476864, 94245, 4278493});
std::cout << "Users by nicknames:" << std::endl;
if(status == RequestStatus::SUCCESS_CODE) {
    for(std::size_t index = 0; index < users.size(); index++) {
        User user = users.at(index);
        std::cout << format("\tUser #{0}: {1} ({2} lvl, {3}%)", 
                            index, user.username, user.level, user.levelPercentage * 100) << std::endl;
  }
} else {
    std::cout << "\tCode error: " << status << std::endl;
}
```

Взаимодействие со статистикой игрока:
```cpp
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
```

Взаимодействие с матчами игрока:
```cpp
auto [userMatches, status] = api.getUserMatchesOffset(38609); // 20 последних матчей игрока.
std::tie(userMatches, status) = api.getUserMatchesOffset(38609, 5); // 20 матчей игрока после 5 последних игр.
std::tie(userMatches, status) = api.getUserMatchesOffset(38609, 0, 1); // Последний матч.
```

Взаимодействие с таблицами рекордов:
```cpp
auto [leaders, status] = api.getLeaderboard("user", 20, 0); // Топ 20 пользователей по уровню.
std::cout << leaders.leaderboard << std::endl;
for(uint index = 0; index < leaders.records.size(); index++) {
	auto record = leaders.records[index];
    std::cout << format("#{0}: {1} ({2} lvl, {3}%);",
                        index + 1, record["username"], record["level"], 
                        record["levelPercentage"].asFloat() * 100) << std::endl;
}
std::tie(leaders, status) = api.getLeaderboard("guild", 10, 10, "total_coins"); // Топ 10 гильдий по вложенным коинам после 10 первых гильдий.
std::cout << std::endl << leaders.leaderboard << std::endl;
for(uint index = 0; index < leaders.records.size(); index++) {
	auto record = leaders.records[index];
    std::cout << format("#{0}: {1}, ({2} lvl, {3}%), {4} coins total;",
                        index + 11, record["name"], record["level"],
                        record["levelPercentage"].asFloat() * 100,
                        record["total_blocks"]) << std::endl;
}
std::tie(leaders, status) = api.getLeaderboard("prison", 5, 0); // Топ 5 игроков по блокам на Prison.
std::cout << std::endl << leaders.leaderboard << std::endl;
for(uint index = 0; index < leaders.records.size(); index++) {
	auto record = leaders.records[index];
	std::cout << format("#{0}: {1}, {2} blocks total;",
                        index + 1, record["user"]["username"],
                        record["total_blocks"]) << std::endl;
}
```

Взаимодействие с информацией о матчах:
```cpp
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
```
