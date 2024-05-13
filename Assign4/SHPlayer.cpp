/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"
#include <algorithm>
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
    :ncards(0), is_first_open(true), name(playerName)
{

}

// destructor
SHPlayer::~SHPlayer(){
	
}

// initialize the number of cards to 0
void
SHPlayer::start()
{
    ncards = 0;
	is_first_open = false;
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
    if(ncards != kMaxCards){
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
		char arr[kCardWidth + 1];
		if(i < (int)name.size()) {
			cout << name[i];
        } else {
			cout << ' ';
        }
		for(int j = 0; j < ncards; j++) {
			if(j == 0 && is_first_open == false) {
				for(int k = 0; k < kCardWidth; k++) {
					arr[k] = card[13][i][k];
                }
			} else {
				for(int k = 0; k < kCardWidth; k++) {
					arr[k] = card[cards[j].getPip() % 13][i][k];
					if(arr[k] == 'x') {
						arr[k] = cardAbbrev[cards[j].getSuit()];
                    }	
				}
			}
			AnsiPrint(arr, cardColor[cards[j].getSuit()], white);
			cout << ' ';
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
		sum += cards[i].getPip() + 1;
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
    else if(isFourOfAKind() == true) {
        return FOUR_OF_A_KIND;
    }
    else if(isFullHouse() == true) {
        return FULL_HOUSE;
    }
    else if(isTwoPair() == true) {
        return TWO_PAIR;
    }
    else if(isThreeOfAKind() == true) {
        return THREE_OF_A_KIND;
    }
    else if(isFlush() == true) {
        return FLUSH;
    }
    else if(isStraight() == true) {
        return STRAIGHT;
    }
    else if(isOnePair() == true) {
        return ONE_PAIR;
    }
    else {
        return OTHER;
    }
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
    afterSortedCard = beforeSortedCard;
    sort(afterSortedCard.begin(), afterSortedCard.end(), [](const Card& a, const Card& b) {
            return a.getID() < b.getID();
        });
}

int
SHPlayer::getPoint() const
{
    return point;
}

void
SHPlayer::setPoint(int point)
{
    this->point = point;
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


