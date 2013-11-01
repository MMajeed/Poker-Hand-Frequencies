/** @file: Deck.cpp
	@author Mohammed Majeed
	@author m_majeed@fanshaweonline.ca
	@date 2011/10/15
	@version 1.0
	@note Developed for Visual Studio C++ 2010
	@brief - Extends the deck.hpp
*/

#include "deck.hpp"

#include <cassert>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

/** Default constructor  */
Deck::Deck()
{
	for(int y = 0; y <= 3; ++y)
	{
	   for( int i = 1; i <= 14; ++i )
		   deck_.push_back( Card( i, static_cast<Card::Suit>(y) ));
	}
}

/** Shuffles the cards */
void Deck::shuffe()
{
	for (int i=0; i<(52-1); ++i) 
	{
        int randnum = i + (rand() % (52-i));
		swap(deck_[i], deck_[randnum]);
    }
}


/** Takes the top 5 hands from the deck and puts them in the hand */
void Deck::draw()
{
	hand_.clear();
	for (int i= 0; i<5; ++i) 
	{
		hand_.push_back(deck_[i]);
    }
}

/** Take a vector of 5 cards and figures out what type of hand it is */
int checkHand(std::vector<Card> hand)
{
	int typeToReturn = NoPair;

	for ( int j = 0; j < hand.size(); j++ )
	{
		for(int y=0; y < hand.size(); y++)
		{
			for ( int k =0; k < hand.size() -1-y; k++ )
			{
				if(hand[k].GetRank()>hand[k+1].GetRank())
				{
					Card temp = hand[k+1];
 
					hand[k+1] = hand[k];
 
					hand[k] = temp;
				}
			}
		}
	}

	for ( int i = 0; i < 4; ++i)
	{
		// Check to see if it is one Pair
		if(hand[i].GetRank() == hand[i+1].GetRank())
		{
			typeToReturn = OnePair;
			break;
		}
	}
	
	if (typeToReturn == OnePair)
	{
		
		// Check to see if it is two pair
		if(hand[0].GetRank() == hand[1].GetRank() && 
			(
				hand[1].GetRank() == hand[2].GetRank() ||
				hand[2].GetRank() == hand[3].GetRank() ||
				hand[3].GetRank() == hand[4].GetRank() 
			)  )
		{
			typeToReturn = TwoPair;
		}
		else if(hand[1].GetRank() == hand[2].GetRank() && 
			(
				hand[2].GetRank() == hand[3].GetRank() ||
				hand[3].GetRank() == hand[4].GetRank() 
			)  )
		{
			typeToReturn = TwoPair;
		}
		
	}
	
	if (typeToReturn > NoPair)
	{
		for ( int i = 0; i < 3; ++i)
		{
			// Check to see if it is three of a kind
			if(hand[i].GetRank() == hand[i+1].GetRank() &&
			   hand[i+1].GetRank() == hand[i+2].GetRank())
			{
				typeToReturn = ThreeOfaKind;
				break;
			}
		}
	}

	// Check to see if it is straight
	if(hand[0].GetRank() + 1 == hand[1].GetRank() && 
	   hand[1].GetRank() + 1 == hand[2].GetRank() && 
	   hand[2].GetRank() + 1 == hand[3].GetRank() &&
	   hand[3].GetRank() + 1 == hand[4].GetRank() )
	{
		typeToReturn = Straight;
	}
	
	// Check to see if it is Flush
	if (	hand[0].GetSuit() == hand[1].GetSuit() && 
			hand[1].GetSuit() == hand[2].GetSuit() && 
			hand[2].GetSuit() == hand[3].GetSuit() &&
			hand[3].GetSuit() == hand[4].GetSuit() )
	{
		typeToReturn = Flush;
	}

	if (typeToReturn > TwoPair)
	{
		// Check to see if it is full House
		if (   hand[0].GetRank() == hand[1].GetRank() && 
			   hand[1].GetRank() == hand[2].GetRank() && 
			   hand[3].GetRank() == hand[4].GetRank() )
		{
			typeToReturn = FullHouse;
		}
		else if (  hand[0].GetRank() == hand[1].GetRank() && 
				   hand[2].GetRank() == hand[3].GetRank() && 
				   hand[3].GetRank() == hand[4].GetRank() )
		{
			typeToReturn = FullHouse;
		}
	}

	// Check to see if it is Four of a Kind
	if (typeToReturn > TwoPair)
	{
		for ( int i = 0; i < 2; ++i)
		{
			if( hand[i].GetRank() == hand[i+1].GetRank() &&
				hand[i+1].GetRank() == hand[i+2].GetRank() &&
				hand[i+2].GetRank() == hand[i+3].GetRank())
			{
				typeToReturn = FourOfAKind;
				break;
			}
		}
	}

	// Check to see if it is Straight Flush
	if (typeToReturn == Flush)
	{
		// Check to see if it is straight
		if(hand[0].GetRank() == hand[1].GetRank() - 1 && 
		   hand[1].GetRank() == hand[2].GetRank() - 1 && 
		   hand[2].GetRank() == hand[3].GetRank() - 1 &&
		   hand[3].GetRank() == hand[4].GetRank() - 1 )
		{
			typeToReturn = StraightFlush;
		}

		// Check to see if it is Royal Flush
		if (typeToReturn == StraightFlush)
		{
			// Check to see if it is straight
			if(	hand[4].GetRank() == 14)
			{
				typeToReturn = RoyalFlush;
			}

		}

	}

	return typeToReturn;
}

