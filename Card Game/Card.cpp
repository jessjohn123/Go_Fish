#include "Card.h"

// Default constructor
// In:	_face			The face value of the card
//		_suit			The suit of the card

Card::Card(int _face, char _suit)
{
	/* TODO Lab1:
			Fill out the constructor body
			*/
	m_face = _face;
	m_suit = _suit;
}

Card::~Card()
{

}


/* Accessors */

/* TODO Lab1:
		Define the two accessors if they were not inlined.
		*/

/* Mutators */

/* TODO Lab1:
		Define the two mutators if they were not inlined.
		*/

// Display a card to the screen
void Card::Show() const
{
	/* TODO Lab1:
			Display the Card object.

			Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
			or something similar instead of their numeric value.

			*Note - This unit test is not automated, so make sure you verify
			the face card is displaying correctly.
			*/
	switch (m_face)
	{
	case 11:
	{
		cout << " J ";
		break;
	}
	case 12:
	{
		cout << " Q ";
		break;
	}
	case 13:
	{
		cout << " K ";
		break;
	}
	case 14:
	{
		cout << " A ";
		break;
	}
	}
}

// Relational operators

/* TODO Lab1:
		Define the six relational operators if they were not inlined.
		*/


// Insertion operator to display Cards with cout (or any other ostream object)

/* TODO Lab1:
		Define the insertion operator to display a card.

		Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
		or something similar instead of their numeric value.

		*Note - This unit test is not automated, so make sure you verify
		the face card is displaying correctly.
		*/
ostream& operator<<(ostream& _lhs, const Card& _rhs)
{
	if (_rhs.GetFace() < 11)
		_lhs << (_rhs.m_face);

	switch (_rhs.m_face)
	{
	case 11:
	{
		_lhs << "J";
		break;
	}
	case 12:
	{
		_lhs << "Q";
		break;
	}
	case 13:
	{
		_lhs << "K";
		break;
	}
	case 14:
	{
		_lhs << "A";
		break;
	}
	}
	if (_rhs.GetFace() != 10){
		cout << " ";
	}
	cout << " " << _rhs.GetSuit();
	return _lhs;
}