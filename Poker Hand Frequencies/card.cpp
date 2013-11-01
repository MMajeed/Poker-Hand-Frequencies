/** @file: Card.cpp
	@author Mohammed Majeed
	@author m_majeed@fanshaweonline.ca
	@date 2011/10/15
	@version 1.0
	@note Developed for Visual Studio C++ 2010
	@brief - Extends the card class
*/

#include "card.hpp"

/** Custom constructor */
Card::Card( int CardInit, Suit SuitInit )
	: suit_(SuitInit)
	, rank_ (CardInit)
{
}
/** Default constructor initializes to Ace-of-Spades. */
Card::Card()
	: suit_(Spades)
	, rank_(1)
{
}

/* Query suit value */
Card::Suit Card::GetSuit() const
{
	return suit_;
}

/** Query rank value. */
int Card::GetRank() const
{
	return rank_;
}