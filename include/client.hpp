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
    /// ���������� ������ �� ��������� API ������ � ����������
    /// ��������������� �����������.
    /// </summary>
    /// <param name="_inMethodPathWithParameter">- API �����;</param>
    /// <param name="_inAdditionalParams">- ��������� �������.</param>
    /// <returns>Json::Value - JSON-������ ������.</returns>
    VimeResponse<Json::Value> requestToMethod(
        const std::string _inMethodPathWithParameter,
        const cpr::Parameters _inAdditionalParams = cpr::Parameters{});

public:
    std::string devToken;
    RateHeader rateHeader;
    const std::string API_URL = "https://api.vimeworld.com/";

    /// <summary>
    /// ����������� ������� �� ���������, ��������� ���������� 
    /// �� 60 �������� � ������.
    /// </summary>
    VimeClient() = default;
    /// <summary>
    /// ����������� �������, ��������� ���������� �� 300 �������� � ������ � 
    /// ������������ ������� ������������. ���� ����� �� ����������, �� ��
    /// ������������.
    /// </summary>
    /// <param name="_inDevToken">- ����� ������������.</param>
    VimeClient(const std::string _inDevToken);

    /// <summary>
    /// ���������� ���������� �� ������ ��� ���������� ������� �� �� ����. 
    /// ���� ����� �� ������, �� �� �� ����� ������������ � ������.
    /// </summary>
    /// <param name="_inNames">- �������� ������� (�� 1 �� 50 ���������).</param>
    /// <returns>std::vector[User] - ������ �������.</returns>
    VimeResponse<std::vector<User>> getUsersByNames(
        std::vector<std::string> _inNames);
    /// <summary>
    /// ���������� ���������� �� ������ ��� ���������� ������� �� �� ID. 
    /// ���� ����� � ������� ID �� ������, �� �� �� ����� ������� � ������.
    /// </summary>
    /// <param name="_inUserIDs">- ID ������� (�� 1 �� 50 ID).</param>
    /// <returns>std::vector[User] - ������ �������.</returns>
    VimeResponse<std::vector<User>> getUsersByIDs(
        std::vector<uint> _inUserIDs);
    /// <summary>
    /// ���������� ������ ������ ������.
    /// </summary>
    /// <param name="_inUserID">- ID ������.</param>
    /// <returns>std::vector[User] - ������ ������ ������.</returns>
    VimeResponse<std::vector<User>> getFriends(
        const uint _inUserID);
    /// <summary>
    /// ���������� ������ ������ ������.
    /// </summary>
    /// <param name="_inUser">- ������ ������.</param>
    /// <returns>std::vector[User] - ������ ������ ������.</returns>
    VimeResponse<std::vector<User>> getFriends(
        const User _inUser);
    /// <summary>
    /// �������� ������-������ ������, ���������������� ��������� � 
    /// �������� ����.
    /// </summary>
    /// <param name="_inUserID">- ID ������.</param>
    /// <returns>UserSession - ������ ������.</returns>
    VimeResponse<UserSession> getUserSession(
        const uint _inUserID);
    /// <summary>
    /// �������� ������-������ ������, ���������������� ��������� � 
    /// �������� ����.
    /// </summary>
    /// <param name="_inUser">- ������ ������.</param>
    /// <returns>UserSession - ������ ������.</returns>
    VimeResponse<UserSession> getUserSession(
        const User _inUser);
    /// <summary>
    /// ���������� ���������� ���� ���, � ������� ����� ������������� �����. 
    /// ������ ��� � �� ��������� �������� ���������� ����� ������ � 
    /// ������� ������ getGames().
    /// </summary>
    /// <param name="_inUserID">- ID ������;</param>
    /// <param name="_inGames">- ����������, �� ��������� ���.</param>
    /// <returns>Json::Value - Json-������ �� ����������� ������.</returns>
    VimeResponse<Json::Value> getUserStats(
        const uint _inUserID,
        std::vector<std::string> _inGames = {});
    /// <summary>
    /// ���������� ���������� ���� ���, � ������� ����� ������������� �����. 
    /// ������ ��� � �� ��������� �������� ���������� ����� ������ � 
    /// ������� ������ getGames().
    /// </summary>
    /// <param name="_inUser">- ������ ������;</param>
    /// <param name="_inGames">- ����������, �� ��������� ���.</param>
    /// <returns>Json::Value - Json-������ �� ����������� ������.</returns>
    VimeResponse<Json::Value> getUserStats(
        const User _inUser,
        std::vector<std::string> _inGames = {});
    /// <summary>
    /// ���������� ������ ���� ���������� ������. ������ ���� ��������� 
    /// ���������� ����� ������ � ������� ������ getAllAchievements().
    /// </summary>
    /// <param name="_inUserID">- ID ������.</param>
    /// <returns>std::vector[UserAchievement] - ������ ���������� 
    /// ����������.</returns>
    VimeResponse<std::vector<UserAchievement>> getUserAchievements(
        const uint _inUserID);
    /// <summary>
    /// ���������� ������ ���� ���������� ������. ������ ���� ��������� 
    /// ���������� ����� ������ � ������� ������ getAllAchievements().
    /// </summary>
    /// <param name="_inUser">- ������ ������.</param>
    /// <returns>std::vector[UserAchievement] - ������ ���������� 
    /// ����������.</returns>
    VimeResponse<std::vector<UserAchievement>> getUserAchievements(
        const User _inUser);
    /// <summary>
    /// ���������� ������ ������ ��������, ���� ����� ������ �����, 
    /// � ����� � ���. ������ ���� ��������� ����� ����� ������ 
    /// � ������� ������ getLeaderboardList().
    /// </summary>
    /// <param name="_inUserID">- ID ������.</param>
    /// <returns>std::vector[UserLeaderboard] - ������ ������� � 
    /// �����.</returns>
    VimeResponse<std::vector<UserLeaderboard>> getUserLeaderboards(
        const uint _inUserID);
    /// <summary>
    /// ���������� ������ ������ ��������, ���� ����� ������ �����, 
    /// � ����� � ���. ������ ���� ��������� ����� ����� ������ 
    /// � ������� ������ getLeaderboardList().
    /// </summary>
    /// <param name="_inUser">- ������ ������.</param>
    /// <returns>std::vector[UserLeaderboard] - ������ ������� � 
    /// �����.</returns>
    VimeResponse<std::vector<UserLeaderboard>> getUserLeaderboards(
        const User _inUser);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID ������;</param>
    /// <param name="_inOffset">- ���������� ����������� �� ������ 
    /// ������. �� ��������� - 0, ����������� - 2000;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesOffset(
        const uint _inUserID,
        const uint _inOffset = 0,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID ������;</param>
    /// <param name="_inAfterID">- ID �����, �� �������� ������ 
    /// ��������� �����;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesAfter(
        const uint _inUserID,
        const std::string _inAfterID,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUserID">- ID ������;</param>
    /// <param name="_inBeforeID">- ID �����, ����� �������� ������ 
    /// ��������� �����;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50;</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesBefore(
        const uint _inUserID,
        const std::string _inBeforeID,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUser">- ������ ������;</param>
    /// <param name="_inOffset">- ���������� ����������� �� ������ 
    /// ������. �� ��������� - 0, ����������� - 2000;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesOffset(
        const User _inUser,
        const uint _inOffset = 0,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUser">- ������ ������;</param>
    /// <param name="_inAfterID">- ID �����, �� �������� ������ 
    /// ��������� �����;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesAfter(
        const User _inUser,
        const std::string _inAfterID,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ��������� ������ ������. ���� ����� ��������� 
    /// �������� ������ ���������� � ������ getLatestMatches().
    /// ��������� ���������� � ���������� ����� ����� �������� � 
    /// ������� ������ getMatch().
    /// </summary>
    /// <param name="_inUser">- ������ ������;</param>
    /// <param name="_inBeforeID">- ID �����, ����� �������� ������ 
    /// ��������� �����;</param>
    /// <param name="_inCount">- ���������� ������, ������� ������ 
    /// ������. �� ��������� - 20, ����������� - 50.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ���������� 
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getUserMatchesBefore(
        const User _inUser,
        const std::string _inBeforeID,
        const uint _inCount = 20);
    /// <summary>
    /// ���������� ������ ������� ������, ���������������� ��������� 
    /// � �������� ����, ��� ������ �� ��� ���������.
    /// </summary>
    /// <param name="_inUserIDs">- ������ ID ������� 
    /// (�� 1 �� 50 ID).</param>
    /// <returns>std::map[uint, UserSession] - ����������� ID �������
    /// � ������-������� ������.</returns>
    VimeResponse<std::map<uint, UserSession>> getUsersSessions(
        std::vector<uint> _inUserIDs);
    /// <summary>
    /// ���������� ������ ������� ������, ���������������� ��������� 
    /// � �������� ����, ��� ������ �� ��� ���������.
    /// </summary>
    /// <param name="_inUser">- ������ ������� (�� 1 �� 50).</param>
    /// <returns>std::map[uint, UserSession] - ����������� ID �������
    /// � ������-������� ������.</returns>
    VimeResponse<std::map<uint, UserSession>> getUsersSessions(
        std::vector<User> _inUsers);

    /// <summary>
    /// ���������� ������ �������, �������� ��� ��� ������� �������� 
    /// �������� ������. ������������ ���������� ������� � ������ 10. 
    /// ��� ���������� ������� � ������ ����������� ������ ���������� 
    /// �� ����/��������, ������� � ��� ���� ������ ����.
    /// </summary>
    /// <param name="_inQuery">- ������ ��� ������ 
    /// (������� 2 �������).</param>
    /// <returns>std::vector[GuildMeta] - ������ ������� 
    /// ���������� � ��������.</returns>
    VimeResponse<std::vector<GuildMeta>> searchGuild(
        const std::string _inQuery);
    /// <summary>
    /// ����� ������� ����� �� � ID.
    /// </summary>
    /// <param name="_inGuildID">- ID �������.</param>
    /// <returns>Guild - �������.</returns>
    VimeResponse<Guild> getGuildID(
        const uint _inGuildID);
    /// <summary>
    /// ����� ������� ����� �� � �����.
    /// </summary>
    /// <param name="_inGuildName">- ��� �������.</param>
    /// <returns>Guild - �������.</returns>
    VimeResponse<Guild> getGuildName(
        const std::string _inGuildName);
    /// <summary>
    /// ����� ������� ����� �� � ����.
    /// </summary>
    /// <param name="_inGuildTag">- ��� �������.</param>
    /// <returns>Guild - �������.</returns>
    VimeResponse<Guild> getGuildTag(
        const std::string _inGuildTag);

    /// <summary>
    /// ���������� ������ ���� ��������� ������ ��������.
    /// </summary>
    /// <returns>std::vector[LeaderboardInfo] - ������ 
    /// ���������� ������ ��������.</returns>
    VimeResponse<std::vector<LeaderboardInfo>> getLeaderboardList();
    /// <summary>
    /// ���������� ������� ��������.
    /// </summary>
    /// <param name="_inType">- ��� ������� ��������. ������ ������
    /// ���������� ����� getLeaderboardList();</param>
    /// <param name="_inSize">- ���������� �������, ������� ����� 
    /// ������.�� ��������� - 100, ����������� - 1000;</param>
    /// <param name="_inOffset">- ���������� ����������� �� ������ 
    /// �������. �� ��������� - 0;</param>
    /// <param name="_inSort">- ������� ������� �������� 
    /// (�� �����������).</param>
    /// <returns>Leaderboard - ������� ��������.</returns>
    VimeResponse<Leaderboard> getLeaderboard(
        const std::string _inType,
        const ushort _inSize = 100,
        const ushort _inOffset = 0,
        const std::string _inSort = "");

    /// <summary>
    /// ���������� ���������� ������� ������. � ����� � �� ������ 
    /// ���� ��������. ������ ���� ������ �������� ��� ����� 
    /// ���������� � ������� ������ getGames().
    /// </summary>
    /// <returns>Online - ������ ������� Minigames.</returns>
    VimeResponse<Online> getOnline();
    /// <summary>
    /// ���������� ������ �������� ������� �� �������. ���� ������ 
    /// ��������� ����, ��� ������������ �� ������� MiniGames � 
    /// ���� �� ������� /streams.
    /// </summary>
    /// <returns>std::vector[Stream] - ������ �������.</returns>
    VimeResponse<std::vector<Stream>> getOnlineStreams();
    /// <summary>
    /// ���������� ������ �����������, ������� � ������ ������ 
    /// ��������� �� �������.
    /// </summary>
    /// <returns>std::vector[OnlineStaff] 
    /// - ������ ������ �����������.</returns>
    VimeResponse<std::vector<OnlineStaff>> getOnlineStaff();

    /// <summary>
    /// ���������� ������ ���������� � �����. ���������:
    /// https://vimeworld.github.io/api-docs/#apimatch_get
    /// </summary>
    /// <param name="_inMatchID">- ID �����.</param>
    /// <returns>Match - ������ ���������� � �����.</returns>
    VimeResponse<Match> getMatch(
        const std::string _inMatchID);
    /// <summary>
    /// ������ ��������� ������ �� �������.
    /// </summary>
    /// <param name="_inCount">- ���������� ��������� ������, ������� 
    /// ����� ������. �� ��������� - 20, ����������� - 100.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ����������
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getLatestMatches(
        const ushort _inCount = 20);
    /// <summary>
    /// ������ ������ �� �������.
    /// </summary>
    /// <param name="_inMatchIDBefore">- ID �����, �� �������� ������ 
    /// ��������� �����.</param>
    /// <param name="_inCount">- ���������� ������, ������� 
    /// ������ ������. �� ��������� - 20, ����������� - 100.</param>
    /// <returns>std::vector[MatchMeta] - ������ ������� ����������
    /// � ������.</returns>
    VimeResponse<std::vector<MatchMeta>> getMatchesBefore(
        const std::string _inMatchIDBefore,
        const ushort _inCount = 20);
    /// <summary>
    /// ������ ������ �� �������.
    /// </summary>
    /// <param name="_inMatchIDAfter">- ID �����, ����� �������� ������ 
    /// ��������� �����.</param>
    /// <param name="_inCount">- ���������� ������, ������� 
    /// ������ ������. �� ��������� - 20, ����������� - 100.</param>
    /// <returns></returns>
    VimeResponse<std::vector<MatchMeta>> getMatchesAfter(
        const std::string _inMatchIDAfter,
        const ushort _inCount = 20);

    /// <summary>
    /// ���������� �������� ������������ �����, ������� ����� 
    /// ������������ ��� ����������� ����������.
    /// </summary>
    /// <param name="_inLanguage">�������� ��� �����, � ������ ������ 
    /// �������� ru, en.</param>
    /// <param name="_inParts">���������� ������ ��������� ����� 
    /// �����������. �� ��������� �������� ���, ���������: games, 
    /// game_stats, ranks.</param>
    /// <returns>Locale - �����������.</returns>
    VimeResponse<Locale> getLocale(
        const std::string _inLanguage,
        std::vector<std::string> _inParts = {});

    /// <summary>
    /// ���������� ������ ���� ���, ������� �������������� API.
    /// </summary>
    /// <returns>std::vector[Game] - ������ ���.</returns>
    VimeResponse<std::vector<Game>> getGames();
    /// <summary>
    /// ���������� ������ ���� ���� �� VimeWorld. ����� ����� 
    /// ���� ����, ������� ��� � ������ misc/games, �������� SWT. 
    /// ���������� ��� ���� ����, �� ������ ���� ��� SW � SWT ������.
    /// </summary>
    /// <returns>std::map[std::string, std::map[std::string, GameMap]]
    /// - ����������� ������������ �������� �������� � ������.</returns>
    VimeResponse<std::map<std::string, std::map<std::string, GameMap>>>
        getAllMaps();
    /// <summary>
    /// ���������� ������ ���� ��������� ���������� � �� ���������, 
    /// ����� ���������. ��� ���������� ��������� �� ������ 
    /// (����������, �����, SkyWars � �.�.), � ������ �� ������� ����� 
    /// ���� ������� ������ ����������.
    /// </summary>
    /// <returns>std::map[std::string, std::vector[Achievement]]
    /// - ����������� ������ � ������� ����������.</returns>
    VimeResponse<std::map<std::string, std::vector<Achievement>>>
        getAllAchievements();
    /// <summary>
    /// ���������� ���������� � ������.
    /// </summary>
    /// <param name="_inToken">- �����.</param>
    /// <returns>Token - ���������� � ������.</returns>
    VimeResponse<Token> getTokenInfo(
        std::string _inToken);
};