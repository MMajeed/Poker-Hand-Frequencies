/** @file: Deck.hpp
	@author Mohammed Majeed
	@author m_majeed@fanshaweonline.ca
	@date 2011/10/15
	@version 1.0
	@note Developed for Visual Studio C++ 2010
	@brief - A deck class that uses the card class to develop a deck of playing cards
*/

#ifndef __Deck_HPP__
#define __Deck_HPP__

#include "card.hpp"
#include <vector>

class Deck 
{
public:
	std::vector<Card> deck_;
	std::vector<Card> hand_;
	/** Default constructor  */
	Deck();
	/** Shuffles the cards */
	void shuffe();
	/** Takes the top 5 hands from the deck and puts them in the hand */
	void draw();
};

enum {NoPair = 0, OnePair, TwoPair, ThreeOfaKind, Straight,
	  Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush};

/** Take a vector of 5 cards and figures out what type of hand it is */
int checkHand(std::vector<Card> hand);


#endif