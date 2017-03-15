#include "Computer.h"
#include "Game.h"
// Default ctor
Computer::Computer(const char* _name) : Player(_name)
{
	/* TODO Lab2:
			Implement this method.//
			Send back the appropriate information to the parent/base class.
			*/

}
// Display the computer's name and card backs
void Computer::Show() const
{
	/* TODO Lab2:
			Implement this method.

			Should display the name of the player as well as their card backs.

			Example:		Computer
			XX XX XX XX

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
		if (Player::GetCheat(2) == true)
		{

			cout << _card;
		}
		else
			cout << "    ";//_card
		Console::ResetColor();

		cout << VT << endl;
		Console::SetCursorPosition(x, y + 2);
		cout << LB << HT << HT << HT << HT << RB << endl;
		x += 7;
	}
	cout << endl;

	

#define OLDWAY 0
#if OLDWAY
	Card _card;
	cout << this->GetName() << endl;
	for (int i = 0; GetCard(i, _card); i++)
	{
		Console::BackgroundColor(White);
		Console::ForegroundColor(Blue);
		cout << _card;//"XX";
		Console::ResetColor();
		cout << " ";
	}
	cout << endl;
#endif
}