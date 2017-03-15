#include "Player.h"

/* TODO Lab5:
		Initialize m_maxCards in all constructors
*/
unsigned char Player::cheat = 0;
// Default ctor
// In:	_name			The player's name
//		_maxCards		The maximum number of cards they can store

Player::Player(const char* _name, int _maxCards) : m_maxCards(_maxCards)
{
	/* TODO Lab2/4:
			Fill out the constructor body.
			Keep in mind that there are more than two data members.
	*/
	m_name = new char[strlen(_name) + 1];
	strcpy_s(m_name,strlen(_name) + 1, _name);
	m_hand = new Card[_maxCards];
}

/* TODO Lab4:
		Define and implement the copy constructor.

		Make sure to copy all data members (using deep copies when necessary).
*/
Player::Player(const Player& _cpy) : m_maxCards(_cpy.m_maxCards)
{
	m_name = new char[strlen(_cpy.m_name) + 1];
	strcpy_s(m_name, strlen(_cpy.m_name) + 1, _cpy.m_name);
	m_hand = new Card[_cpy.m_maxCards];
	for (int i = 0; i < _cpy.m_numCards; i++)
	{
		m_hand[i] = _cpy.m_hand[i];
	}
	//m_hand = _cpy.m_hand;
	//m_maxCards = _cpy.m_maxCards;
	m_numCards = _cpy.m_numCards;
	m_score = _cpy.m_score;
}
// Dtor
Player::~Player()
{
	/* TODO Lab4:
			Clean up any dynamic memory
	*/
	delete[] m_name;
	delete[] m_hand;
}

/* TODO Lab4:
		Define and implement the assignment operator.

		Make sure to copy all data members (using deep copies when necessary).

		* There will be a small change to this in Lab5 where you will have to comment out
		  the m_maxCards assignment, but go ahead and make the copy for now.
*/
Player& Player::operator=(const Player& _assign) 
{
	if (this != &_assign)
	{
		delete[] m_name;
		m_name = new char[strlen(_assign.m_name) + 1];
		strcpy_s(m_name, strlen(_assign.m_name) + 1, _assign.m_name);
		delete[] m_hand;
		m_hand = new Card[_assign.m_maxCards];
		for (int i = 0; i < _assign.m_numCards; i++)
		{
			m_hand[i] = _assign.m_hand[i];
		}
		//m_hand = _assign.m_hand;
		//m_maxCards = _assign.m_maxCards;
		m_numCards = _assign.m_numCards;
		m_score = _assign.m_score;
	}
	return *this;
}

/* Accessors */

/* TODO Lab2:
		Define the accessors if they were not inlined.
*/

// Access a Card from the player's hand
// In:	_index		The index of the card being accessed
//		_card		A reference to store that value in
//
// Return: True if there was a card actually stored at that index.
//		   False if the index was "empty"
bool Player::GetCard(int _index, Card& _card) const
{
	/* TODO Lab2:
			Implement this method.
	*/
	if (_index >= 0 && _index < m_numCards)
	{
		_card = m_hand[_index];
		return 1;
	}
	else 
	{
		return 0;
	}
	// Just here for compilation
	return true;

}

/* Mutators */

// Change the player's name to the value passed in
void Player::SetName(const char* _name)
{
	/* TODO Lab2/4:
			Implement this method.
	*/
	delete[] m_name;
	m_name = new char[strlen(_name) + 1];
	strcpy_s(m_name, strlen(_name)+1, _name);
}

// Update the player's score by some amount
void Player::AddToScore(int _add)
{
	/* TODO Lab2:
			Implement this method.
			Increase their score by the amount passed in.
	*/
	m_score += _add;
}

// Add a Card to the player's hand
// In:	_card		The card being added
//
// Return: True if the card was successfully added to their hand
//		   False if the player's hand was already full
bool Player::AddCard(const Card& _card)
{
	/* TODO Lab2:
			Implement this method.

			Should store the passed card in the next available empty index (if there is one).
			You should know how many cards are in the hand to know where that
			index will be.
	*/
	if (m_numCards >= m_maxCards)
	{
		return 0;
	}
	
	int i=0;
	for ( i; i < m_numCards; i++)
	{
		if (m_hand[i].GetSuit() == _card.GetSuit())
		{
			break;
		}
	}
	for (i; i < m_numCards; i++)
	{
		if (m_hand[i].GetFace() < _card.GetFace())
		{
			continue;
		}
		else if (m_hand[i].GetSuit() != _card.GetSuit())
		{
			break;
		}
	}
	m_numCards++;
	for (int j = m_numCards; j > i; j--)
	{
		m_hand[j + 1] = m_hand[j];
	}
	m_hand[i] = _card;
	
	return 1;
	
	// Just here for compilation
}

// Remove a Card from the player's hand
// In:	_index		The index of the card to remove from the array
//		_card		A reference to store that value in
//
// Return: True if there was a card actually stored at that index.
//		   False if the index was "empty"
bool Player::Discard(int _index, Card& _discard)
{
	/* TODO Lab2:
			Implement this method.
	
			Should store the requested card into the reference being passed in.
			After that, "shift" the array back to show this card has been removed.
			
			Example:
			[ 7♥ 3♣ 5♦ 9♥ ]		m_numCards: 4

					* discarding index 1 (the 3♣) *

			[ 7♥ 5♦ 9♥ 9♥ ]		m_numCards: 3

					* Even though it looks like there are two 9♥, we won't ever be displaying
					  that to the user, and it will be the first one that gets overwritten if 
					  another card is added to the hand. *
	*/

	if (_index < 0 || _index >= m_numCards)
	{
		return 0;
	}
	_discard = m_hand[_index];

	for (_index; _index <= m_numCards - 1; ++_index)
	{
		m_hand[_index] = m_hand[_index + 1];

	}
	m_numCards -= 1;
	return 1;
	
	
}

// Clear the player's hand so that they are holding 0 cards
void Player::Clear()
{
	/* TODO Lab2:
			Implement this method.
			*/
	for (int i = 0; i < m_numCards; i++)
	{
		m_hand[i] = 0;
	}
	
}

// Display method (empty for this class)
void Player::Show() const
{

}

//Get Cheat
bool Player::GetCheat(int ch_option)
{
	if (cheat & (1 << ch_option - 1))
		return true;
	return false;
}

void Player::SetCheat(int ch_option)
{
	cheat = cheat | (1 << (ch_option - 1));
}