#pragma once
#include <iostream>
#include "cpr/cpr.h"
#include "json/json.h"
#include "utils.hpp"
#include "user.hpp"
#include "guild.hpp"
#include "match.hpp"
#include "leaderboard.hpp"
#include "online.hpp"
#include "locale.hpp"
#include "misc.hpp"

struct RateHeader {
    uint limit;
    uint remaining;
    uint resetAfter;

    friend std::ostream &operator<<(std::ostream &, const RateHeader &);
    RateHeader &operator=(const RateHeader &rval) = default;

    std::string toString() const;
};

class VimeClient {
protected:
    Json::Reader            parser;

    /// <summary>
    /// Отправляет запрос по заданному API методу с возможными
    /// дополнительными параметрами.
    /// </summary>
    /// <param name="_inMethodPathWithParameter">- API метод;</param>
    /// <param name="_inAdditionalParams">- Параметры запроса.</param>
    /// <returns>Json::Value - JSON-объект ответа.</returns>
    VimeResponse<Json::Value> requestToMethod(
        const std::string _inMethodPathWithParameter,
        const cpr::Parameters _inAdditionalParams = cpr::Parameters{});

public:
    std::string devToken;
    RateHeader rateHeader;
    const std::string API_URL = "https://api.vimeworld.com/";

    /// <summary>
    /// Конструктор клиента по умолчанию, позволяет отправлять 
    /// до 60 запросов в минуту.
    /// </summary>
    VimeClient() = default;
    /// <summary>
    /// Конструктор клиента, позволяет отправлять до 300 запросов в минуту с 
    /// существующим токеном разработчика. Если токен не существует, то он
    /// сбрасывается.
    /// </summary>
    /// <param name="_inDevToken">- Токен разработчика.</param>
    VimeClient(const std::string _inDevToken);

    /// <summary>
    /// Возвращает информацию об игроке или нескольких игроках по их нику. 
    /// Если игрок не найден, то он не будет показываться в ответе.
    /// </summary>
    /// <param name="_inNames">- Никнеймы игроков (от 1 до 50 никнеймов).</param>
    /// <returns>std::vector[User] - Вектор игроков.</returns>
    VimeResponse<std::vector<User>> getUsersByNames(
        std::vector<std::string> _inNames);
    /// <summary>
    /// Возвращает информацию об игроке или нескольких игроках по их ID. 
    /// Если игрок с заданым ID не найден, то он не будет показан в ответе.
    /// </summary>
    /// <param name="_inUserIDs">- ID игроков (от 1 до 50 ID).</param>
    /// <returns>std::vector[User] - Вектор игроков.</returns>
    VimeResponse<std::vector<User>> getUsersByIDs(
        std::vector<uint> _inUserIDs);
    /// <summary>
    /// Возвращает список друзей игрока.
    /// </summary>
    /// <param name="_inUserID">- ID игрока.</param>
    /// <returns>std::vector[User] - Вектор друзей игрока.</returns>
    VimeResponse<std::vector<User>> getFriends(
        const uint _inUserID);
    /// <summary>
    /// Возвращает список друзей игрока.
    /// </summary>
    /// <param name="_inUser">- Объект игрока.</param>
    /// <returns>std::vector[User] - Вектор друзей игрока.</returns>
    VimeResponse<std::vector<User>> getFriends(
        const User _inUser);
    /// <summary>
    /// Получает онлайн-статус игрока, человекопонятное сообщение и 
    /// название игры.
    /// </summary>
    /// <param name="_inUserID">- ID игрока.</param>
    /// <returns>UserSession - Статус игрока.</returns>
    VimeResponse<UserSession> getUserSession(
        const uint _inUserID);
    /// <summary>
    /// Получает онлайн-статус игрока, человекопонятное сообщение и 
    /// название игры.
    /// </summary>
    /// <param name="_inUser">- Объект игрока.</param>
    /// <returns>UserSession - Статус игрока.</returns>
    VimeResponse<UserSession> getUserSession(
        const User _inUser);
    /// <summary>
    /// Возвращает статистику всех игр, в которые играл запрашиваемый игрок. 
    /// Список игр и их возможные значения статистики можно узнать с 
    /// помощью метода getGames().
    /// </summary>
    /// <param name="_inUserID">- ID игрока;</param>
    /// <param name="_inGames">- Минирежимы, по умолчанию все.</param>
    /// <returns>Json::Value - Json-объект со статистикой игрока.</returns>
    VimeResponse<Json::Value> getUserStats(
        const uint _inUserID,
        std::vector<std::string> _inGames = {});
    /// <summary>
    /// Возвращает статистику всех игр, в которые играл запрашиваемый игрок. 
    /// Список игр и их возможные значения статистики можно узнать с 
    /// помощью метода getGames().
    /// </summary>
    /// <param name="_inUser">- Объект игрока;</param>
    /// <param name="_inGames">- Минирежимы, по умолчанию все.</param>
    /// <returns>Json::Value - Json-объект со статистикой игрока.</returns>
    VimeResponse<Json::Value> getUserStats(
        const User _inUser,
        std::vector<std::string> _inGames = {});
    /// <summary>
    /// Возвращает список всех достижений игрока. Список всех возможных 
    /// достижений можно узнать с помощью метода getAllAchievements().
    /// </summary>
    /// <param name="_inUserID">- ID игрока.</param>
    /// <returns>std::vector[UserAchievement] - Вектор полученных 
    /// достижений.</returns>
    VimeResponse<std::vector<UserAchievement>> getUserAchievements(
        const uint _inUserID);
    /// <summary>
    /// Возвращает список всех достижений игрока. Список всех возможных 
    /// достижений можно узнать с помощью метода getAllAchievements().
    /// </summary>
    /// <param name="_inUser">- Объект игрока.</param>
    /// <returns>std::vector[UserAchievement] - Вектор полученных 
    /// достижений.</returns>
    VimeResponse<std::vector<UserAchievement>> getUserAchievements(
        const User _inUser);
    /// <summary>
    /// Возвращает список таблиц рекордов, куда попал данный игрок, 
    /// и место в них. Список всех возможных топов можно узнать 
    /// с помощью метода getLeaderboardList().
    /// </summary>
    /// <param name="_inUserID">- ID игрока.</param>
    /// <returns>std::vector[UserLeaderboard] - Вектор позиций в 
    /// топах.</returns>
    VimeResponse<std::vector<UserLeaderboard>> getUserLeaderboards(
        const uint _inUserID);
    /// <summary>
    /// Возвращает список таблиц рекордов, куда попал данный игрок, 
    /// и место в них. Список всех возможных топов можно узнать 
    /// с помощью метода getLeaderboardList().
    /// </summary>
    /// <param name="_inUser">- Объект игрока.</param>
    /// <returns>std::vector[UserLeaderboard] - Вектор позиций в 
    /// топах.</returns>
    VimeResponse<std::vector<UserLeaderboard>> getUserLeaderboards(
        const User _inUser);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID игрока;</param>
    /// <param name="_inOffset">- Количество пропущенных от начала 
    /// матчей. По умолчанию - 0, максимально - 2000;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesOffset(
        const uint _inUserID,
        const uint _inOffset = 0,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID игрока;</param>
    /// <param name="_inAfterID">- ID матча, до которого искать 
    /// последние матчи;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesAfter(
        const uint _inUserID,
        const std::string _inAfterID,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID игрока;</param>
    /// <param name="_inBeforeID">- ID матча, после которого искать 
    /// последние матчи;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50;</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesBefore(
        const uint _inUserID,
        const std::string _inBeforeID,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUser">- Объект игрока;</param>
    /// <param name="_inOffset">- Количество пропущенных от начала 
    /// матчей. По умолчанию - 0, максимально - 2000;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesOffset(
        const User _inUser,
        const uint _inOffset = 0,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUser">- Объект игрока;</param>
    /// <param name="_inAfterID">- ID матча, до которого искать 
    /// последние матчи;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesAfter(
        const User _inUser,
        const std::string _inAfterID,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает список последних матчей игрока. Чуть более подробное 
    /// описание можете посмотреть в методе getLatestMatches().
    /// Подробную информацию о конкретном матче можно получить с 
    /// помощью метода getMatch().
    /// </summary>
    /// <param name="_inUser">- Объект игрока;</param>
    /// <param name="_inBeforeID">- ID матча, после которого искать 
    /// последние матчи;</param>
    /// <param name="_inCount">- Количество матчей, которые вернет 
    /// сервер. По умолчанию - 20, максимально - 50.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации 
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesBefore(
        const User _inUser,
        const std::string _inBeforeID,
        const uint _inCount = 20);
    /// <summary>
    /// Возвращает статус игроков онлайн, человекопонятное сообщение 
    /// и название игры, где каждый из них находится.
    /// </summary>
    /// <param name="_inUserIDs">- Вектор ID игроков 
    /// (от 1 до 50 ID).</param>
    /// <returns>std::map[uint, UserSession] - Отображение ID игроков
    /// к онлайн-статусу игрока.</returns>
    VimeResponse<std::map<uint, UserSession>> getUsersSessions(
        std::vector<uint> _inUserIDs);
    /// <summary>
    /// Возвращает статус игроков онлайн, человекопонятное сообщение 
    /// и название игры, где каждый из них находится.
    /// </summary>
    /// <param name="_inUser">- Вектор игроков (от 1 до 50).</param>
    /// <returns>std::map[uint, UserSession] - Отображение ID игроков
    /// к онлайн-статусу игрока.</returns>
    VimeResponse<std::map<uint, UserSession>> getUsersSessions(
        std::vector<User> _inUsers);

    /// <summary>
    /// Возвращает список гильдий, название или тег которых содержит 
    /// заданный запрос. Максимальное количество гильдий в ответе 10. 
    /// При сортировке гильдий в ответе учитывается полное совпадение 
    /// по тегу/названию, уровень и еще пару хитрых штук.
    /// </summary>
    /// <param name="_inQuery">- Запрос для поиска 
    /// (минимум 2 символа).</param>
    /// <returns>std::vector[GuildMeta] - Вектор краткой 
    /// информации о гильдиях.</returns>
    VimeResponse<std::vector<GuildMeta>> searchGuild(
        const std::string _inQuery);
    /// <summary>
    /// Поиск гильдию можно по её ID.
    /// </summary>
    /// <param name="_inGuildID">- ID гильдии.</param>
    /// <returns>Guild - гильдия.</returns>
    VimeResponse<Guild> getGuildID(
        const uint _inGuildID);
    /// <summary>
    /// Поиск гильдию можно по её имени.
    /// </summary>
    /// <param name="_inGuildName">- Имя гильдии.</param>
    /// <returns>Guild - гильдия.</returns>
    VimeResponse<Guild> getGuildName(
        const std::string _inGuildName);
    /// <summary>
    /// Поиск гильдию можно по её тегу.
    /// </summary>
    /// <param name="_inGuildTag">- Тег гильдии.</param>
    /// <returns>Guild - гильдия.</returns>
    VimeResponse<Guild> getGuildTag(
        const std::string _inGuildTag);

    /// <summary>
    /// Возвращает список всех доступных таблиц рекордов.
    /// </summary>
    /// <returns>std::vector[LeaderboardInfo] - Вектор 
    /// информации таблиц рекордов.</returns>
    VimeResponse<std::vector<LeaderboardInfo>> getLeaderboardList();
    /// <summary>
    /// Возвращает таблицу рекордов.
    /// </summary>
    /// <param name="_inType">- Тип таблицы рекордов. Список таблиц
    /// возвращает метод getLeaderboardList();</param>
    /// <param name="_inSize">- Количество записей, которые вернёт 
    /// сервер.По умолчанию - 100, максимально - 1000;</param>
    /// <param name="_inOffset">- Количество пропущенных от начала 
    /// записей. По умолчанию - 0;</param>
    /// <param name="_inSort">- Вариант таблицы рекордов 
    /// (не обязательно).</param>
    /// <returns>Leaderboard - Таблица рекордов.</returns>
    VimeResponse<Leaderboard> getLeaderboard(
        const std::string _inType,
        const ushort _inSize = 100,
        const ushort _inOffset = 0,
        const std::string _inSort = "");

    /// <summary>
    /// Возвращает количество игроков онлайн. В сумме и по каждой 
    /// игре отдельно. Список всех полных названий игр можно 
    /// посмотреть с помощью метода getGames().
    /// </summary>
    /// <returns>Online - Онлайн сервера Minigames.</returns>
    VimeResponse<Online> getOnline();
    /// <summary>
    /// Возвращает список активных стримов на сервере. Этот список 
    /// идентичен тому, что показывается на сервере MiniGames в 
    /// меню по команде /streams.
    /// </summary>
    /// <returns>std::vector[Stream] - Вектор стримов.</returns>
    VimeResponse<std::vector<Stream>> getOnlineStreams();
    /// <summary>
    /// Возвращает список модераторов, которые в данный момент 
    /// находятся на сервере.
    /// </summary>
    /// <returns>std::vector[OnlineStaff] 
    /// - Вектор онлайн модераторов.</returns>
    VimeResponse<std::vector<OnlineStaff>> getOnlineStaff();

    /// <summary>
    /// Возвращает полную информацию о матче. Подробнее:
    /// https://vimeworld.github.io/api-docs/#apimatch_get
    /// </summary>
    /// <param name="_inMatchID">- ID матча.</param>
    /// <returns>Match - Полная информация о матче.</returns>
    VimeResponse<Match> getMatch(
        const std::string _inMatchID);
    /// <summary>
    /// Список последних матчей на сервере.
    /// </summary>
    /// <param name="_inCount">- Количество последних матчей, которые 
    /// вернёт сервер. По умолчанию - 20, максимально - 100.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getLatestMatches(
        const ushort _inCount = 20);
    /// <summary>
    /// Список матчей на сервере.
    /// </summary>
    /// <param name="_inMatchIDBefore">- ID матча, до которого искать 
    /// последние матчи.</param>
    /// <param name="_inCount">- Количество матчей, которые 
    /// вернет сервер. По умолчанию - 20, максимально - 100.</param>
    /// <returns>std::vector[MatchMeta] - Вектор краткой информации
    /// о матчах.</returns>
    VimeResponse<std::vector<MatchMeta>> getMatchesBefore(
        const std::string _inMatchIDBefore,
        const ushort _inCount = 20);
    /// <summary>
    /// Список матчей на сервере.
    /// </summary>
    /// <param name="_inMatchIDAfter">- ID матча, после которого искать 
    /// последние матчи.</param>
    /// <param name="_inCount">- Количество матчей, которые 
    /// вернет сервер. По умолчанию - 20, максимально - 100.</param>
    /// <returns></returns>
    VimeResponse<std::vector<MatchMeta>> getMatchesAfter(
        const std::string _inMatchIDAfter,
        const ushort _inCount = 20);

    /// <summary>
    /// Возвращает названия всевозможных вещей, которые могут 
    /// понадобиться при отображении информации.
    /// </summary>
    /// <param name="_inLanguage">Короткое имя языка, в данный момент 
    /// доступны ru, en.</param>
    /// <param name="_inParts">Возвращает только указанные части 
    /// локализации. По умолчанию выбирает все, доступные: games, 
    /// game_stats, ranks.</param>
    /// <returns>Locale - Локализация.</returns>
    VimeResponse<Locale> getLocale(
        const std::string _inLanguage,
        std::vector<std::string> _inParts = {});

    /// <summary>
    /// Возвращает список всех игр, которые поддерживаются API.
    /// </summary>
    /// <returns>std::vector[Game] - Вектор игр.</returns>
    VimeResponse<std::vector<Game>> getGames();
    /// <summary>
    /// Возвращает список всех карт на VimeWorld. Здесь могут 
    /// быть игры, которых нет в ответе misc/games, например SWT. 
    /// Технически это одна игра, но список карт для SW и SWT разный.
    /// </summary>
    /// <returns>std::map[std::string, std::map[std::string, GameMap]]
    /// - Отображение сокращённого названия миниигры к картам.</returns>
    VimeResponse<std::map<std::string, std::map<std::string, GameMap>>>
        getAllMaps();
    /// <summary>
    /// Возвращает список всех возможных достижений с их описанием, 
    /// кроме секретных. Все достижения разделены на группы 
    /// (Глобальные, Лобби, SkyWars и т.д.), в каждой из которых может 
    /// быть сколько угодно достижений.
    /// </summary>
    /// <returns>std::map[std::string, std::vector[Achievement]]
    /// - Отображение группы к вектору достижений.</returns>
    VimeResponse<std::map<std::string, std::vector<Achievement>>>
        getAllAchievements();
    /// <summary>
    /// Возвращает информацию о токене.
    /// </summary>
    /// <param name="_inToken">- Токен.</param>
    /// <returns>Token - Информация о токене.</returns>
    VimeResponse<Token> getTokenInfo(
        std::string _inToken);
};