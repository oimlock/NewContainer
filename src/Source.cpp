#define _CRT_SECURE_NO_WARNINGS

#include "gameEnviroment.h"

int main() {
	srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа

	//cards
	oimlock::Card Field("Field", "Blue", "Agriculture", 1, 1, 1);
	oimlock::Card Farm("Farm", "Blue", "Meat", 2, 1, 1);
	oimlock::Card Forest("Forest", "Blue", "Industry", 5, 3, 1);
	oimlock::Card FurnitureIndustry("FurnitureIndustry", "Facility", "Industry", 8, 3, 3);
	oimlock::Card Store("Store", "Green", "Goods", 4, 2, 3);

	oimlock::Sight cityHall("City Hall", 0);
	oimlock::Sight railStation("Rail Station", 4);
	oimlock::Sight cityMall("City Mall", 10);

	//players
	oimlock::Player player_1;
	player_1.addProperty(Field);
	player_1.addCityCenter(cityHall);
	player_1.renamePlayer("UltraRight");
	oimlock::Player* player_1_ptr = &player_1;

	oimlock::Player player_2;
	player_2.addProperty(Field);
	player_2.addCityCenter(cityHall);
	player_2.renamePlayer("DungeonMaster");
	oimlock::Player* player_2_ptr = &player_2;

	oimlock::Player player_3;
	player_3.addProperty(Field);
	player_3.addCityCenter(cityHall);
	player_3.renamePlayer("GenaGorin");
	oimlock::Player* player_3_ptr = &player_3;

	//multiplayer

	std::cout << "How many players?\n"
		">>";
	int numberOfPlayers;
	std::cin >> numberOfPlayers;
	oimlock::GameTable gameTable(numberOfPlayers);
	
	switch (numberOfPlayers) {
	case 3:
		gameTable.addPlayer(player_1_ptr);
		gameTable.addPlayer(player_2_ptr);
		gameTable.addPlayer(player_3_ptr);
		break;

	case 2:
		gameTable.addPlayer(player_1_ptr);
		gameTable.addPlayer(player_2_ptr);
		break;

	default:
		gameTable.addPlayer(player_1_ptr);
		break;
	}

	/*
	for (int i = 0; i < numberOfPlayers; ++i) {
		string playerName;
		Player* deafultPlayer = new Player();
		gameTable.addPlayer();
		cout << "Enter your name\n"
			">>";
		cin >> playerName;
		deafultPlayer->renamePlayer(playerName);
	}*/

	//Player* this_player = &gameTable.getHowsTurn();

	int n = 1;
	while (n > 0) {
		int command;
		oimlock::Player* this_player = gameTable.queuePlayer_.front();
		std::cout << "--------------------------------\n" 
		<< this_player->playerName_ << "'s turn\n"
		<< "--------------------------------\n"
		<< "Your cash: " << this_player->money_ << "\n"
		"--------------------------------\n"
		"Your city: \n";
		int number = 1;
		for (oimlock::Card s : this_player->properties_) {
			std::cout << number << ". " << s.cardName_ << "\n";
			++number;
		}
		std::cout << "--------------------------------\n";
		number = 1;
		for (oimlock::Sight s : this_player->cityCenter_) {
			std::cout << number << ". " << s.sightName_ << "\n";
			++number;
		}
		std::cout << "--------------------------------\n";

		//roll the dices stage
		int diceResult;
		diceResult = oimlock::rollDices(this_player->hasRailStation());

		std::cout << "_____\n";
		std::cout << "| " << diceResult << " |" << std::endl;
		std::cout << "|___|\n";


		std::cout << "--------------------------------\n";
		std::cout << "Income Log\n";
		std::cout << "--------------------------------\n";
		//income stage

		int playersAwaitng = gameTable.numberOfPlayers_;
		while (playersAwaitng > 0) {
			oimlock::Player* actualPlayer = gameTable.circleAllPlayers.front();
			for (int i = 0; i < actualPlayer->properties_.size(); ++i) {
				if (actualPlayer->properties_[i].cardType_ == "Blue" && diceResult == actualPlayer->properties_[i].value_) {					
					actualPlayer->income_ += actualPlayer->properties_[i].income_;
					std::cout << actualPlayer->properties_[i].cardName_ << " makes to " << actualPlayer->playerName_ << " + " << actualPlayer->properties_[i].income_ << " income" << std::endl;
				}
			}
			actualPlayer->money_ += actualPlayer->income_;
			actualPlayer->income_ = 0;
			gameTable.rollNext();
			--playersAwaitng;
		}

		for (int i = 0; i < this_player->properties_.size(); ++i) {
			if (diceResult == this_player->properties_[i].value_) {
				if (this_player->properties_[i].cardType_ == "Facility") {
					int subIncome = 0;
					for (int j = 0; j < this_player->properties_.size(); ++j) {
						if (this_player->properties_[i].cardSpec_ == this_player->properties_[j].cardSpec_ && this_player->properties_[j].cardType_ == "Blue") {
							subIncome += this_player->properties_[i].income_;
						}
					}
					std::cout << this_player->properties_[i].cardName_ << " makes you +" << subIncome << " income" << std::endl;
					this_player->income_ += subIncome;
				}
				if (this_player->properties_[i].cardType_ == "Green") {
					if (this_player->hasCityMall_) {
						std::cout << this_player->properties_[i].cardName_ << " makes you +" << this_player->properties_[i].income_ + 1 << " income (City Mall bonus)" << std::endl;
						this_player->income_ += this_player->properties_[i].income_ + 1;
					}
					else {
						std::cout << this_player->properties_[i].cardName_ << " makes you +" << this_player->properties_[i].income_ << " income" << std::endl;
						this_player->income_ += this_player->properties_[i].income_;
					}
				}
			}
		}

		//ратуша
		/*
		if (this_player->money_ == 0 && this_player->income_ == 0) {
			std::cout << "City Hall' charity\n";
			this_player->income_ = 1;
		}*/

		this_player->money_ += this_player->income_;
		std::cout << "--------------------------------\n"
			<< this_player->playerName_ << " has "<< this_player->money_ << "coins \n"
		"--------------------------------\n";
		this_player->income_ = 0;

		//building stage
		int buildingChoice;
		std::cout << "Choose a bulding to build: \n";
		std::cout <<
			"1.Field (1, 1, 1)\n"
			"2.Farm (2, 1, 1)\n"
			"3.Forest (5, 3, 1)\n"
			"4.FurnitureIndustry (8, 3, 3)\n"
			"5.Store (4, 2, 3)\n"
			"6.Rail Station (cost 4)\n"
			"7.City Mall (cost 10)\n"
			"0.Buy nothing\n"
			">>";
		std::cin >> buildingChoice;

		std::string optionName;

		switch (buildingChoice) {

		case 1:
			optionName = "Field";
			this_player->purchaseProperty(Field);
			break;

		case 2:
			optionName = "Farm";
			this_player->purchaseProperty(Farm);
			break;

		case 3:
			optionName = "Forest";
			this_player->purchaseProperty(Forest);
			break;

		case 4:
			optionName = "Furniture Industry";
			this_player->purchaseProperty(FurnitureIndustry);
			break;

		case 5:
			optionName = "Store";
			this_player->purchaseProperty(Store);
			break;

		case 6:
			optionName = "Rail Station";
			if (this_player->purchaseCityCenter(railStation)) {
				this_player->hasRailStation_ = true;
			}
			break;

		case 7:
			optionName = "City Mall";
			if (this_player->purchaseCityCenter(cityMall)) {
				this_player->hasCityMall_ = true;
			}
			break;

		case 0:
			break;
		};

		std::cout << this_player->playerName_ << " has purchased " << optionName << "\n"
			"--------------------------------\n"
			<< this_player->playerName_ << " cash: " << this_player->money_ << "\n"
			"--------------------------------\n"
			"1. to end " << this_player->playerName_ << "'s turn \n"
			">>";
		std::cin >> command;
		if (command == 1) {
			gameTable.nextTurn();
			system("cls");
		}
	}

	return 0;
}

