/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHPlayer.h"
#include "SHDealer.h"
#include "CardPattern.h"
#include "SHGame.h"
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;


// constructor
SHDealer::SHDealer()
    :SHPlayer("Dealer")
{
    start(); // use the constructor of SHPlayer
}


// destructor
SHDealer::~SHDealer()
{

}


// distribute a card to the player
int
SHDealer::giveCard()
{
    if (drew > 28) {
        return -1;
    }

    while (drew <= 28) {
        int cardValue = deck[drew] / 4;
        if (cardValue > 0 && cardValue < 8) {
            drew++;
        } else {
            break;
        }
    }

    if (drew > 28) {
        return -1;
    }

    return deck[drew++];
}

/*
// give the dealer a card
void
SHDealer::addCard()
{

}
*/
// use SHPlayer::addCard()


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
    // use SHPlayer::getHandPattern() and SHPlayer::totalPips()
    if(static_cast<int>(player.getHandPattern()) == static_cast<int>(getHandPattern())) {
		if(player.totalPips() == totalPips()) {
			return TIE;
        } else if(player.totalPips() > totalPips()) {
			return Player_WIN;
        } else {
		    return Player_LOSE;
        }
	} else if(static_cast<int>(player.getHandPattern()) < static_cast<int>(getHandPattern())) {
		return Player_WIN;
    } else {
	    return Player_LOSE;
    }
}


// start a new game(round)
// before starting a new game(round), you should have
// a new deck, and then shuffle it.
// The deck only has pips A, 8, 9, 10, J, Q, K.
void
SHDealer::start()
{
    SHPlayer::start(); // use member function

    drew = 0;
	shuffle();
}


// shuffle the deck of cards
void
SHDealer::shuffle()
{
    for(int i = 0; i < 52; i++) {
		deck[i] = i;
    }

	for(int i = 0; i < 52; i++) {
		int change = rand () % 52;
		int tmp = deck[change];
		deck[change] = deck[i];
		deck[i] = tmp;
	}
}


/*
// open the dealer's first card
void
SHDealer::openFirstCard()
{

}
*/
// use SHPlayer::openFirstCard()


/*
// show the dealer's hand to the screen
void
SHDealer::showCards() const
{

}
*/
// use SHPlayer::showCards()
