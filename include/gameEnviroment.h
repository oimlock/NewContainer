#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>

namespace oimlock {

int rollDices(bool has2Dices);

struct Card {
	Card(std::string cardName, std::string cardType, std::string cardSpec_, int value, int price, int income);

	const std::string cardName_;
	const std::string cardType_;
	const std::string cardSpec_;
	const int value_;
	const int price_;
	const int income_;
};

struct Sight {
	Sight(const std::string sightName, const int price);

	const std::string sightName_;
	const int price_;
};

struct Player {
	Player();

	void addProperty(Card& CardName);
	void addCityCenter(Sight& cityCenter);
	void renamePlayer(std::string newPlayerName);
	std::string getPlayerName();
	bool purchaseProperty(Card& CardName);
	bool purchaseCityCenter(Sight& cityCenter);
	bool hasRailStation();

	std::vector <Card> properties_;
	std::vector <Sight> cityCenter_;
	int money_;
	int income_;
	bool hasRailStation_;
	bool hasCityMall_;
	std::string playerName_;
};

struct GameTable {
	GameTable(int n);
	void addPlayer(Player* player);
	void nextTurn();
	void rollNext();
	
	std::queue <Player*> queuePlayer_;
	std::queue <Player*> circleAllPlayers;
	int numberOfPlayers_;
};

}//namespace