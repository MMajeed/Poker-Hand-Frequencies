/** @file: Card.hpp
	@author Mohammed Majeed
	@author m_majeed@fanshaweonline.ca
	@date 2011/10/15
	@version 1.0
	@note Developed for Visual Studio C++ 2010
	@brief - A playing card class
*/

#ifndef __CARD_HPP__
#define __CARD_HPP__

class Card {
public:
   enum Suit {
      Diamonds,
      Hearts,
      Clubs,
      Spades
   };

   // Declare two constructors: a default constructor,
   //  and a constructor that sets the cardinal and
   //  suit value of the new card.
   Card();
   Card( int CardInit, Suit SuitInit );

   // Get and Set functions.
   int Card::GetRank() const;			          // Get cardinal value of card.
   Card::Suit Card::GetSuit() const;              // Get suit of card.
private:
   Suit  suit_;
   short   rank_;

};


#endif