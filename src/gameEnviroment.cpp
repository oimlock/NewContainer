#define _CRT_SECURE_NO_WARNINGS

#include "gameEnviroment.h"

namespace oimlock {

int getRandomNumber(int min, int max) {
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int rollDices(bool has2Dices) {
	int command;
	if (has2Dices) {
		std::cout <<
			"1.Roll only one dice \n"
			"2.Roll both dices\n"
			">>";
		std::cin >> command;
		switch (command) {
		case 1:
			return getRandomNumber(1, 6);
		case 2:
			return getRandomNumber(1, 6) + getRandomNumber(1, 6);
		default:
			return getRandomNumber(1, 6);
		}
	}
	else {
		std::cout << "1.Roll the dice (press any key): \n"
			">>";
		std::cin >> command;
		int result;
		std::cin >> result;
		return result;
		//return getRandomNumber(1, 6);
	}
}

Card::Card(std::string cardName, std::string cardType, std::string cardSpec_, int value, int price, int income) :
	cardName_(cardName), cardType_(cardType), cardSpec_(cardSpec_), value_(value), price_(price), income_(income) {};

Sight::Sight(const std::string sightName, const int price): sightName_(sightName), price_(price) {};

Player::Player() : money_(3), income_(0), hasRailStation_(false), playerName_("Default"), hasCityMall_(false) {};

void Player::addProperty(Card& CardName) {
	properties_.push_back(CardName);
}

void Player::addCityCenter(Sight& cityCenter) {
	cityCenter_.push_back(cityCenter);
}

void Player::renamePlayer(std::string newPlayerName) {
	playerName_ = newPlayerName;
}

std::string Player::getPlayerName() {
	return playerName_;
}

bool Player::purchaseProperty(Card& CardName) {
	if (money_ >= CardName.price_) {
		properties_.push_back(CardName);
		money_ -= CardName.price_;
		return true;
	}
	else {
		return false;
	}
};

bool Player::purchaseCityCenter(Sight& cityCenter) {
	if (money_ >= cityCenter.price_) {
		cityCenter_.push_back(cityCenter);
		money_ -= cityCenter.price_;
		return true;
	}
	else {
		return false;
	}
};

bool Player::hasRailStation() {
	return hasRailStation_;
}

GameTable::GameTable(int n) : numberOfPlayers_(n) {};

void GameTable::addPlayer(Player* player) {
	queuePlayer_.push(player);
	circleAllPlayers.push(player);
}

void GameTable::nextTurn() {
	Player* temp = queuePlayer_.front();
	queuePlayer_.pop();
	queuePlayer_.push(temp);
}

void GameTable::rollNext() {
	Player* temp = circleAllPlayers.front();
	circleAllPlayers.pop();
	circleAllPlayers.push(temp);
}

}//namespace
