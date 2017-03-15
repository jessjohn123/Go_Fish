#include "Deck.h"
#include "Card.h"
#include "Stack.h"
#include "stdafx.h"
using std::swap;

// Default ctor
Deck::Deck() 
{
	/* TODO Lab3:
			Implement this method.

			Get everything set up by calling Initialize.
	*/
	Initialize();
}

// Sets up the array of cards to be a unique deck
void Deck::Initialize()
{
	/* TODO Lab3:
			Implement this method.
	
			Set the values in the m_cards array to be the appropriate values for your game.

			For Go Fish: 13 cards of each of the 4 suits

			For UNO: 19 (B)lue cards (one 0, two each 1-9)
					 19 (G)reen cards (one 0, two each 1-9)
					 19 (R)ed cards (one 0, two each 1-9)
					 19 (Y)ellow cards (one 0, two each 1-9)
					  8 Draw 2 cards (two in each color) - Face value 10
					  8 Reverse cards (two in each color) - Face value 11
					  8 Skip cards (two in each color) - Face value 12
					  4 Wild cards (even though these are "colorless," making one each color is easier) - Face value 13
					  4 Wild Draw 4 cards (even though these are "colorless," making one in each color is easier) - Face value 14
	*/
	int count = 0;
	for (int i = 2; i <= 14; i++)
	{
		for (int j = 3; j <= 6; j++)
		{
			m_cards[count].SetFace(i);
			m_cards[count].SetSuit(j);
			count++;
		}
	}

}

// Clears any cards that are already in the stack, shuffles the array, and then pushes
// all of the shuffled cards onto the stack.
void Deck::Shuffle()
{
	/* TODO Lab3:
			Implement this method.
	*/
	int index1, index2;
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < 1800; i++)
	{
		index1 = rand() % 52;
		index2 = rand() % 52;
		if (index1 != index2)
			swap(m_cards[index1], m_cards[index2]);	
	}

	for (int i = 0; i < 52; i++)
	{
		m_Stack.Push(m_cards[i]);
	}
}



// Draw the top-most card off of the stack
// In:	_card			A reference to store the drawn card
//
// Return: True if a card was removed
//		   False if the deck was empty
bool Deck::Draw(Card& _card)
{
	/* TODO Lab3:
			Implement this method.
	*/
	return m_Stack.Pop(_card);	
	
}

// Clear the stack for re-use
void Deck::Clear()
{
	/* TODO Lab3:
			Implement this method.
	*/
	m_Stack.Clear();
}

// Check to see if there are any cards left in the stack
//
// Return: True if the stack is empty
//		   False if there are any cards left in the stack
bool Deck::IsEmpty() const
{
	/* TODO Lab3:
			Implement this method.
	*/
	if (m_Stack.GetCurrSize() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}