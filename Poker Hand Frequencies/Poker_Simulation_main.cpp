/** @file: Poker_Simulation_main.CPP
	@author Mohammed Majeed
	@author m_majeed@fanshaweonline.ca
	@date 2011/10/15
	@version 1.0
	@note Developed for Visual Studio C++ 2010
	@brief - A parallel application using Open MPI to simulate drawing poker hands 
		and use this to compile statistics regarding the relative frequencies of each 5-card hand type.
*/

#include <iostream>
#include <string>
#include <ctime>
#include <mpi.h>
#include "deck.hpp"

using namespace std;
const int TAG_DATA = 1, TAG_QUIT = 2;


/** @fn tellAll
	@return void 
	@param 1st paramter: The type of card it found
		   2nd paramter: The rank of the process that is sending this message
		   3rd paramter: The number of process in the application
		   4th paramter: An MPI_TAG for either TAG_DATA or TAG_QUIT
	It will tell all the processes of what you have found */
void tellAll (int type, int rank, int numProcs, int tag)
{
	for(int p = 0; p < numProcs; p++)
	{
		MPI_Request temp;
		if ( p != rank )		// So that it dosn't tell it self that it found a card
		{
			MPI_Isend( &type, 1, MPI_INT, p, tag, MPI_COMM_WORLD, &temp);
		}
	}
}

int main(int argc, char* argv[])
{
	if( MPI_Init(&argc, &argv) == MPI_SUCCESS )
	{
		// Get the communicator size and the current rank
		int numProcs, rank;
		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		// Boolean to track of what cards have been found
		bool boolRoyalFlush = true, boolStraightFlush = true, boolFourOfAKind = true, 
			 boolFullHouse = true, boolFlush = true, boolStraight = true, boolThreeOfKind = true,
			 boolTwoPair = true, boolOnePair = true, boolNoPair = true;
	
		// int counter to track of how many times it has found cards
		int  intRoyalFlush = 0, intStraightFlush = 0, intFourOfAKind = 0, 
			 intFullHouse = 0, intFlush = 0, intStraight = 0, intThreeOfKind = 0,
			 intTwoPair = 0, intOnePair = 0, intNoPair = 0;

		Deck cardDeck;

		srand ( rank + 5 * MPI_Wtime() ); // This makes sure that every application gets it is own random number


		static MPI_Request request;
		static int msgBuff, recvFlag;
		MPI_Status status;

		if ( rank == 0)		// Only the master gets to print
		{
			// Display a starting message to the user
			cout << "Running Poker Frequencies Simulation using " << numProcs << " proccess." << endl;
		}
		// Get the starting time
		double time = MPI_Wtime();


		MPI_Irecv(&msgBuff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);		// Init the first recving message
		do
		{
			if( request )
			{
				// Already listening for a message

				// Test for a message from a slave
				MPI_Test( &request, &recvFlag, &status);

				if( recvFlag )
				{
					// Message received
					if( status.MPI_TAG == TAG_DATA )
					{
						switch (msgBuff) 
						{
							case TwoPair:
								boolTwoPair = false;
								break;
							case ThreeOfaKind:
								boolThreeOfKind = false;
								break;
							case Straight:
								boolStraight = false;
								break;
							case Flush:
								boolFlush = false;
								break;
							case FullHouse:
								boolFullHouse = false;
								break;
							case FourOfAKind:
								boolFourOfAKind = false;
								break;
							case StraightFlush:
								boolStraightFlush = false;
								break;
							case RoyalFlush:
								boolRoyalFlush = false;
								break;
						}
					}
					else
						break;
					MPI_Irecv(&msgBuff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);		// Restart the listening process
				}
				
			}

			cardDeck.shuffe();

			cardDeck.draw();

			int handType = checkHand(cardDeck.hand_);

			switch (handType) 
			{
				case NoPair:
					++intNoPair;
					if (boolNoPair)
					{
						boolNoPair = false;
					}
					break;
				case OnePair:
					++intOnePair;
					if (boolOnePair)
					{
						boolOnePair = false;
					}
					break;
				case TwoPair:
					++intTwoPair;
					if (boolTwoPair)
					{
						boolTwoPair = false;
						tellAll( TwoPair, rank, numProcs, TAG_DATA );
					}
					break;
				case ThreeOfaKind:
					++intThreeOfKind;
					if (boolThreeOfKind)
					{
						boolThreeOfKind = false;
						tellAll( ThreeOfaKind, rank, numProcs, TAG_DATA );
					}
					break;
				case Straight:
					++intStraight;
					if (boolStraight)
					{
						boolStraight = false;
						tellAll( Straight, rank, numProcs, TAG_DATA );
					}
					break;
				case Flush:
					++intFlush;
					if (boolFlush)
					{
						boolFlush = false;
						tellAll( Flush, rank, numProcs, TAG_DATA );
					}
					break;
				case FullHouse:
					++intFullHouse;
					if (boolFullHouse)
					{
						boolFullHouse = false;
						tellAll( FullHouse, rank, numProcs, TAG_DATA );
					}
					break;
				case FourOfAKind:
					++intFourOfAKind;
					if (boolFourOfAKind)
					{
						boolFourOfAKind = false;
						tellAll( FourOfAKind, rank, numProcs, TAG_DATA );
					}
					break;
				case StraightFlush:
					++intStraightFlush;
					if (boolStraightFlush)
					{
						boolStraightFlush = false;
						tellAll( StraightFlush, rank, numProcs, TAG_DATA );
					}
					break;
				case RoyalFlush:
					++intRoyalFlush;
					if (boolRoyalFlush)
					{
						boolRoyalFlush = false;
						tellAll( RoyalFlush, rank, numProcs, TAG_DATA );
					}
					break;
			}
	
		}while( boolRoyalFlush || boolStraightFlush || boolFourOfAKind || 
			 boolFullHouse || boolFlush || boolStraight || boolThreeOfKind ||
			 boolTwoPair || boolOnePair || boolNoPair );

		// Tell all process to quit
		if ( status.MPI_TAG != TAG_QUIT )
			tellAll( 0, rank, numProcs, TAG_QUIT );

		if ( rank == 0)	// Only the master gets to print and process everyones result
		{
			// Report
			cout << "Validation completed in " << MPI_Wtime() - time << " seconds. "<< endl;

			// Master has to recieve info from the slaves and process the result
			for(int i = 1; i < numProcs; i++)
			{
				int counter[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			
				MPI_Recv(counter, 10, MPI_INT, MPI_ANY_SOURCE, TAG_DATA, MPI_COMM_WORLD, &status);
				// Add em up
				intNoPair		+= counter[0];
				intOnePair		+= counter[1];
				intTwoPair		+= counter[2];
				intThreeOfKind	+= counter[3];
				intStraight		+= counter[4];
				intFlush		+= counter[5];
				intFullHouse	+= counter[6];
				intFourOfAKind	+= counter[7];
				intStraightFlush+= counter[8];
				intRoyalFlush	+= counter[9];
			}
			double total = intNoPair + intOnePair + intTwoPair + intThreeOfKind + intStraight + intFlush + intFullHouse + intFourOfAKind + intStraightFlush + intRoyalFlush ;
			// Print the result
			cout << fixed << "There were " << static_cast<int>(total) << " number of cards drawn" << endl;
			cout << fixed << "There were " << intNoPair << " of No Pairs drawn and it accounts for " << (intNoPair/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intOnePair << " of One Pairs drawn and it accounts for " << (intOnePair/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intTwoPair << " of Two Pairs drawn and it accounts for " << (intTwoPair/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intThreeOfKind << " of Three of a Kind drawn and it accounts for " << (intThreeOfKind/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intStraight << " of Straight drawn and it accounts for " << (intStraight/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intFlush << " of Flush drawn and it accounts for " << (intFlush/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intFullHouse << " of Full House drawn and it accounts for " << (intFullHouse/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intFourOfAKind << " of Four of a Kind drawn and it accounts for " << (intFourOfAKind/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intStraightFlush << " of Straight Flush drawn and it accounts for " << (intStraightFlush/total)*100 << "%. " << endl;
			cout << fixed << "There were " << intRoyalFlush << " of Royal Flush drawn and it accounts for " << (intRoyalFlush/total)*100 << "%. " << endl;
		}
		else
		{
			// Else, if your a slave then you must send your result
			int counter[] = { intNoPair, intOnePair, intTwoPair, intThreeOfKind, intStraight,
				intFlush, intFullHouse, intFourOfAKind, intStraightFlush, intRoyalFlush };

			MPI_Send(counter, 10, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD);
		}
		MPI_Finalize();
	}

	return 0;
}