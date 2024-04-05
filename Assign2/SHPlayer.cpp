/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"


using namespace std;

const char* HandTypeName[9] = {
    "Straight flush",
    "Four of a kind",
    "Full house",
    "Flush",
    "Straight",
    "Three of a kind",
    "Two pair",
    "One pair",
    "Other"
};

// constructor
SHPlayer::SHPlayer(const char* playerName)
:ncards(0), is_first_open(false) 
{

}


// initialize the number of cards to 0
void
SHPlayer::start()
{
	is_first_open = true;
	ncards = 0;
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
	if(ncards != kMaxCards) {
		cards[ncards] = newCard;
		ncards += 1;
	}
}

// open the first card so it faces up
void
SHPlayer::openFirstCard()
{
	is_first_open = true;
}

// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
	for(int i = 0; i < kCardHeight; i++) {
        for(int j = 0; j < kNCardPerRow; j++) {
            string temp = card[cards[j].getPip()][i];
            for(int k = 0; k < kCardWidth; k++) {
                if(temp[k] == 'x') {
                    temp[k] = cardAbbrev[cards[j].getSuit()];
                }
            }
            if(j == 0 && is_first_open == true) {
                AnsiPrint(card[13][i], nochange, white, false, false);
            } else {
                AnsiPrint(temp.c_str(), cardColor[cards[j].getSuit()], white, false, false);
            }
            cout << " ";
        }
        cout << endl;
    }
}
                    
// get the total points of the current hand
int
SHPlayer::totalPips() const
{
	int sum = 0;
	for(int i = 0; i < ncards; ++i) {
		sum = sum + cards[i].getPip() + 1;
	}
	return sum;
}

// judge what kind of hand type you own
// you need to have 5 cards
HandType
SHPlayer::getHandPattern() 
{
	sortCards();
	if(isStraightFlush() == true) {
		return STRAIGHT_FLUSH;
	}
	if(isFourOfAKind() == true) {
		return FOUR_OF_A_KIND;
	}
	if(isFullHouse() == true) {
		return FULL_HOUSE;
	}
	if(isTwoPair() == true) {
		return TWO_PAIR;
	}
	if(isThreeOfAKind() == true) {
		return THREE_OF_A_KIND;
	}
	if(isFlush() == true) {
		return FLUSH;
	}
	if(isStraight() == true) {
		return STRAIGHT;
	}
	if(isOnePair() == true) {
		return ONE_PAIR;
	}
	return OTHER;
}

// return the number of cards at hand
int
SHPlayer::getNumCards() const
{
	return ncards;
}

void
SHPlayer::sortCards() 
{
	bool copied[kMaxCards] = {};
	for(int i = 0; i < ncards; ++i) {
		int min_val = 10000;
		int min_index = -1;
		
		for(int j = 0; j < ncards; ++j) {
			if(copied[j] == 0){
				if(cards[j].getID() < min_val) {
					min_val = cards[j].getID();
					min_index = j;
				}
			}
		}
		sortedCards[i] = cards[min_index];
		copied[min_index] = 1;
	}
}

// any five card sequence of same suit
bool 
SHPlayer::isStraightFlush() const
{
	return isStraight() && isFlush();
}

// four cards of the same pip
bool 
SHPlayer::isFourOfAKind() const
{
    // O O O O X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[0].getPip() == sortedCards[2].getPip() )
        return true;
    // X O O O O
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() &&
            sortedCards[1].getPip() == sortedCards[3].getPip() )
        return true;

    return false;
}

// three of a kind combined with a pair
bool 
SHPlayer::isFullHouse() const
{
    // O O O X X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X X X O O
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// five cards of the same suit
bool
SHPlayer::isFlush() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
            return false;

    return true;
}

// five cards in sequence
bool 
SHPlayer::isStraight() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
            return false;

    return true;
}

// three cards of the same pip
bool 
SHPlayer::isThreeOfAKind() const
{
    for( int i = 0; i < kMaxCards - 2; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
                sortedCards[i].getPip() == sortedCards[i+2].getPip() )
            return true;

    return false;
}

// two cards of one pip, two cards of another pip
bool 
SHPlayer::isTwoPair() const
{
    // O O @ @ X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() )
        return true;
    // O O X @ @
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X O O @ @
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// two cards of one pip
bool 
SHPlayer::isOnePair() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
            return true;

    return false;
}
