/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHGame.h"
#include "SHPlayer.h"
#include "SHDealer.h"
#include <iostream>
using namespace std;

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
SHGame::SHGame(SHPlayer& shp, SHDealer& shd)
    : menu(sizeof(menuItems)/sizeof(char*), menuItems), player(shp), dealer(shd)
{
    dealer.setPoint(initCredit);
	player.setPoint(initCredit);
    restart();
}

void printGameOver() {
    cout << "GAME_OVER!" << endl;
}

void handleGameStatus(Status& gameStatus) {
    if (gameStatus == ENDED || gameStatus == GAME_OVER) {
        printGameOver();
    } else {
        cout << "Game is not over yet. Choose 'give up' to end a game" << endl;
    }
}


// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
bool
SHGame::oneRun()
{
    player.showCards();
	dealer.showCards();

    menu.print();

    switch(menu.getAnswer()) {

        // ONE_MORE:
		case 1:
			if(gameStatus != IN_PROGRESS) {
				handleGameStatus(gameStatus);
			}
			else {
				moreCard();
				if(player.getNumCards() >= 5) {
					gameStatus = ENDED;
					endTurn(dealer.judge(player));
				}
			}
			break;

		// GIVE_UP:
		case 2:
			handleGameStatus(gameStatus);
            if (gameStatus != ENDED && gameStatus != GAME_OVER) {
                gameStatus = ENDED;
                giveUp(); 
            }
            break;

		// RESTART:
		case 3:
			if(gameStatus == GAME_OVER) {
				cout << "Sorry. Game over. No loan here." << endl;
			} else if(gameStatus == ENDED) {
				restart();
			} else {
				cout << "Game is not over yet. Choose 'give up' to end a game" << endl;
			}
			break;
				
		// QUIT:
		case 4:
			return false;
			break;
    }

    return true;
}


// give the player and dealer one more card
// check if we can do that first.
// and judge who has win the round if the player have 5 cards
void
SHGame::moreCard()
{
    if(player.getNumCards() == 5) {
		cout << "Game already ended!\n";
		return;
	}

    /*dealer.addCard();
	player.addCard(dealer.giveCard());*/
	Card newCard1(dealer.giveCard());
	Card newCard2(dealer.giveCard());
	player.addCard(newCard1);
	dealer.addCard(newCard2);
}


// give up this round,
// and you'll lose your credit
// the bet is equivalent to the number of card you keep
void
SHGame::giveUp()
{
    endTurn(Player_LOSE);
}


// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void
SHGame::restart()
{
    player.start();
	player.openFirstCard();
	dealer.start();

	player.addCard(dealer.giveCard());
	dealer.addCard(dealer.giveCard());
	player.addCard(dealer.giveCard());
	dealer.addCard(dealer.giveCard());
	
	gameStatus = IN_PROGRESS;
}

void
SHGame::endTurn(Result turnResult)
{
	dealer.openFirstCard();

	if(turnResult == Player_WIN){
		cout<< "You win. Good job.";
		player.setPoint(player.getPoint() + player.getNumCards());
		dealer.setPoint(dealer.getPoint() - dealer.getNumCards());
	}
	else if(turnResult == Player_LOSE){
		cout << "I win. Try again.";
		player.setPoint(player.getPoint() - player.getNumCards());
		dealer.setPoint(dealer.getPoint() + dealer.getNumCards());
	} else {
		cout << "TIE. Please restart the game!";
		player.setPoint(player.getPoint());
		dealer.setPoint(dealer.getPoint());
	}

	cout << "(You have " << player.getPoint() << " points, I Have " << dealer.getPoint() << " points.)" << endl;
	
	if(player.getPoint() < 1 || dealer.getPoint() < 1) {
		gameStatus = GAME_OVER;
	} else {
		gameStatus = ENDED;
	}
}
