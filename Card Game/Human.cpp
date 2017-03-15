#include "Human.h"
#include "Player.h"
// Default ctor
Human::Human(const char* _name) : Player(_name)
{
	/* TODO Lab2:
	Implement this method.

	Send back the appropriate information to the parent/base class.
	*/
}

// Display the computer's name and card backs
void Human::Show() const
{
	/* TODO Lab2:
	Implement this method.

	Should display the name of the player as well as their card faces

					7♥ 3♣ 5♦ 9♥
	Example:		Human

	*/
	int face, suit;

	cout << this->GetName() << endl;
	int x = Console::CursorLeft();
	int y = Console::CursorTop();
	for (int i = 0; i < GetNumCards(); i++)
	{
//		x = Console::CursorLeft();
//		y = Console::CursorTop();
		Card _card;
		GetCard(i, _card);
		face = _card.GetFace();
		suit = _card.GetSuit();
		Console::SetCursorPosition(x, y);
		cout << LT << HT << HT << HT << HT << RT << endl;

		Console::SetCursorPosition(x, y + 1);
		cout << VT;
		Console::BackgroundColor(White);
		if (_card.GetSuit() == 3 || _card.GetSuit() == 4)
		{
			Console::ForegroundColor(Red);
		}
		else
		{
			Console::ForegroundColor(Black);
		}
		cout << _card;
		Console::ResetColor();
		//cout << " ";

		if (face == 10)
		{
			cout << VT << endl;
		}
		else
		{
			cout << VT << endl;
		}
		Console::SetCursorPosition(x, y+2);
		cout << LB << HT << HT << HT << HT << RB << endl;
		x += 7;
	}
	cout << endl;
}