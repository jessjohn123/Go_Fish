#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Console.h"
#include <String>
#include "stdafx.h"
#include "windows.h"
#include "fmod.hpp"

FMOD::System	*fmod_system;

FMOD::Channel	*channel;
void			*extradriverdata;
FMOD::Sound *MenuMusic;
FMOD::Sound *GameMusic;


//#pragma comment(lib, "winmm.lib")

using std::cin;
using std::cout;
using std::endl;
using namespace System;

// Default ctor
Game::Game()
{
	m_state = GAME_INIT;
	m_currPlayer = 0;
}

// Dtor
Game::~Game()
{
	while (m_numPlayers){
		m_numPlayers--;
		delete m_players[m_numPlayers];
	}
}
struct HighScore
{
	int playersScores;
	string playersName;
};
HighScore highScores[];
string Menu[4] = { "Play", "Rules of The Game", "Cheats", "Exit" };
int numOpponents;
static bool secondChance = false;
int menuChoice = -1 ;
void InitFMOD();
void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool bRun = true;

			char titleScreen[6][60] = {
					{ "y.------..------.     .------..------..------..------." },
					{ "g|G.--. ||O.--. |.-.  |F.--. ||I.--. ||S.--. ||H.--. |" },
					{ "m| :/\\: || :/\\: ((5)) | :(): || (\\/) || :/\\: || :/\\: |" },
					{ "c| :\\/: || :\\/: |'-.-.| ()() || :\\/: || :\\/: || (__) |" },
					{ "r| '--'G|| '--'O| ((2)) '--'F|| '--'I|| '--'S|| '--'H|" },
					{ "d`------'`------'  '-'`------'`------'`------'`------'" },
			};

			int shown = 0;
			char sevenScreen[45][100] = {
					{ "                                                    g                             " },
					{ "                                                    g                             " },
					{ "                                                g     rBBBB  g                      " },
					{ "                                    w   BBB         r BBBBB     g                   " },
					{ "                 g B                 w  BBBBB       r  BBBBBBBBB g                   " },
					{ "                g BBBBB              w  BBBBB        r BBBBBBBBB g                    " },
					{ "                 g BBBBB             w BBBBBB bB      r BBBBBBB g                      " },
					{ "               g BBBBBBBBBB           w BBBB bB       rB g                          " },
					{ "                gBBBBBBBBBBB         w   B bBBB       r  g                             " },
					{ "                 gBBBBB BBBBB      wBBBB bBBBB                                     " },
					{ "                  g     B      w   BBBBB  bBBwBBBBB                                 " },
					{ "                  g     BB     w  BBBBBB   BBBBBBBB                                " },
					{ "                        g      w  BBBBBBBB  BB  BBB                                " },
					{ "                               w BBBBBBBBBBBBBBBB                                 " },
					{ "                               w BBBBBBBBBBBBBBBB                                 " },
					{ "                               w BBBBBBBB BBBBBBB                                 " },
					{ "                              w   BBBBBBBBBBBBBBB                                 " },
					{ "                                 wBBBB BBBBBBBBBB                                 " },
					{ "                    g            w   BBBBBBBBBBB                                   " },
					{ "                    g              w BBBBBBBBBBB       g     B                      " },
					{ "                    g r B           wBBBBBBBBBBBB       g  BBBB                      " },
					{ "                    g  rBBBB b      w BBBBBBBBBBBB      gBBBBBBB                      " },
					{ "                    g  r BBBBBB b   w BBBBBBBBBBBBB   g BBBBBBBB                      " },
					{ "                    g  r BBBBBBBb   w BBBBBBBBBBBB    g BB BBBB                       " },
					{ "                    g   r BBBBBBb   w BBBBBBBBBBBB     g B  BB                        " },
					{ "                    g      r BBBb   w BBBBBBBBBBBB    gBBB                            " },
					{ "        b                b      r=b   wBBBBBBBBBBBB    g   =                           " },
					{ "  b                                wBBBBBBBBBBBB b                                  " },
					{ "                                  wBBBBBBBBBBB       g                             " },
					{ "                                  wBBBBB BBBBBb                           BBB      " },
					{ "        BBBBBB           BBBBBBB  wBBBBbBBBBBBBBBBBBBBBBBB BBBBBBBBBBBBBBBBBBBB    " },
					{ "     BBBBBBBBBBB       BBBBBBBBBBBwBBBBbBBBBBBBBBBBBBBBBB  BBBBBBBBBBBBBBBBBBBB    " },
					{ "    BBBBB    BBBB     BBBBB    BBBBwBBbBBBBwBBB   bBBBBBBBBB                         " },
					{ "   BBBBB     BBBBB   BBBBB     BBBBwBBbBBBwBBBB   bBBBBBBB  BBBBBBBBBB               " },
					{ "  BBBBBB     BBBBB  BBBBBB     BBBBwBBBBBBBBB  bBBBBBBB  BB   BBB                  " },
					{ " BBBBBB      BBBBB BBBBBB     BBBBB wBBBBBBBB bBBBBBBB  BBB   BB                    " },
					{ " BBBBB      BBBBBB BBBBB      BBBBB w  BBBBBbBBBBBBB   B B   B                     " },
					{ " BBBBB      BBBBB  BBBBB     BBBBBB     wBBbBBBBBBB   BBBBBBBBB                    " },
					{ " BBBB      BBBBBB BBBBB      BBBBB    w BBbBBBBBB                                 " },
					{ "bBBBB      BBBBB  BBBBB     BBBBBB     bBBBBBBBwBB                                 " },
					{ "b BBBB     BBBBB    BBBB    BBBBBB     bBBBBBBBwBBBB                                " },
					{ "b BBBBB  BBBBBB     BBBB   BBBBBB     bBBBBBBBBwBBB                                 " },
					{ " b BBBBBBBBBBB       BBBBBBBBBBB     bBBBBBBBB wBBB                                 " },
					{ " b  BBBBBBBB          BBBBBBBB       bBBBBBBBB wBB                                  " },
					
			};

	// Loop while our bool remains true.
	while (bRun)
	{
		switch (m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.
			//m_numPlayers = 4;
			InitFMOD();
			
			m_Deck.Shuffle();
			m_players[0] = new Human();

			

			// m_currPlayer = m_player[0]
			m_currPlayer;
			m_numPlayers =0;

			m_state = GAME_MENU;
			break;
		case GAME_MENU:
			// Insert menu code here;
			//PlaySound(L"James_Bond_007_Blood_Stone_-_Theme_Music.wav", NULL, SND_ASYNC | SND_LOOP);
			
			fmod_system->playSound(MenuMusic, 0, false, &channel);

			//screen seven
			Console::BackgroundColor(Black);
			for (int i = 0; i < 45; i++){
				shown = 0;
				for (int j = 0; j < 100 && shown<80; j++){
					if (sevenScreen[i][j] == 'b'){
						Console::ForegroundColor(Green);
						continue;
					}
					else if (sevenScreen[i][j] == 'r'){
						Console::ForegroundColor(Red);
						continue;
					}
					else if (sevenScreen[i][j] == 'g')
					{
						Console::ForegroundColor(DarkBlue);
						continue;
					}

					else if (sevenScreen[i][j] == 'w')
					{
						Console::ForegroundColor(White);
						continue;
					}
					cout << sevenScreen[i][j];
					shown++;
				}
				cout << '\n';
			}
			Console::ResetColor();
			Sleep(2000);
			Console::Clear();

			// Fish Ascii Art
			Console::BackgroundColor(Black);
			Console::SetCursorPosition(Console::WindowWidth() / 2 - 28, Console::WindowHeight() / 2 - 3);
			for (size_t i = 0; i < 6; i++)
			{ 
				for (size_t j = 0; j < 60; j++)
				{
					if (titleScreen[i][j] == 'y')
					{
						Console::ForegroundColor(Yellow);
						continue;
					}
					else if (titleScreen[i][j] == 'g')
					{
						Console::ForegroundColor(DarkGreen);
						continue;
					}
					else if (titleScreen[i][j] == 'm')
					{
						Console::ForegroundColor(Magenta);
						continue;
					}
					else if (titleScreen[i][j] == 'c')
					{
						Console::ForegroundColor(Cyan);
						continue;
					}
					else if (titleScreen[i][j] == 'r')
					{
						Console::ForegroundColor(Red);
						continue;
					}
					else if (titleScreen[i][j] == 'd')
					{
						Console::ForegroundColor(DarkBlue);
						continue;
					}
					cout << titleScreen[i][j];
				}
			
				Console::ResetColor();
				cout << endl;
				Console::SetCursorPosition(Console::WindowWidth() / 2 - 28, Console::CursorTop());
			}
			Console::SetCursorPosition(30, 40);
			cout << "\n\n Created By : Jessica Jose\n\n";
			
			Sleep(2000);
			
			//menu
			Console::Clear();
			/*for (;;)
			{*/
				Console::ForegroundColor(Cyan);
				Console::Lock(true);
				Console::Clear();
				Console::SetCursorPosition(26, 16);
				cout << "===============================================";
				Console::SetCursorPosition(26, 18);
				cout << "                  GAME MENU                    ";
				Console::SetCursorPosition(26, 20);
				cout << "===============================================";
				Console::SetCursorPosition(26, 22);
				cout << "                  1. Play                      ";
				Console::SetCursorPosition(26, 24);
				cout << "                  2. Rules Of The Game         ";
				Console::SetCursorPosition(26, 26);
				cout << "                  3. Cheats                    ";
				Console::SetCursorPosition(26, 28);
				cout << "                  4. Exit                      ";
				Console::SetCursorPosition(26, 30);
				cout << "Press the Number on your keypad.......";
				/*Console::SetCursorPosition(26, 32);
				cout << "===============================================";*/

				Console::Lock(false);

				/*if (GetAsyncKeyState(VK_NUMPAD1))
				{
					Console::FlushKeys();
					menuChoice = 1;
					break;
				}

				if (GetAsyncKeyState(VK_NUMPAD2))
				{
					Console::FlushKeys();
					menuChoice = 2;
					break;
				}

				 if (GetAsyncKeyState(VK_NUMPAD3))
				{
					Console::FlushKeys();
					menuChoice = 3;
					break;
				}
*/
				 /*if (GetAsyncKeyState(VK_NUMPAD4))
				{
					Console::FlushKeys();
					menuChoice = 4;
					break;
				}*/
		//	}
				
				
				switch (getUserChoice() + 1)
				{
				case 1:
					
					Console::Clear();
					IntroPlay();
					Game::SetState(GAME_PLAY);
					break;
					

				case 2:
					
					RulesofTheGame();
					IntroPlay();
					Game::SetState(GAME_PLAY);
					break;
					

				case 3:
					
					cheatMenu();
					IntroPlay(); 
					Game::SetState(GAME_PLAY);
					
					break;
				case 4:
					bRun = false;
					DeleteMusic();
				default:
					
					break;
				
			}
			
		case GAME_PLAY:
		{
			bool gameEnd = true;
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (m_players[i]->GetNumCards() != 0)
				{
					gameEnd = false;
					break;
				}
			}
			if (gameEnd)
			{
				SetState(GAME_END);
				break;
			}
			// Insert game play code here.
			Card playerCard;
			Card computerCard;
			int playerChoice = 0, cardChoice = 0;

			deckIsEmpty();

			if (m_currPlayer == 0)
			{
				// this function is to ask the player for their choice and see if there choice match with the cards in the deck.
				if (Player::GetCheat(3))
					secondChance = true;
				playerCorrectChoice(cardChoice, playerCard,m_players[m_currPlayer]);
				Console::ForegroundColor(Magenta);
				cout << "\n\n";
				if (m_currPlayer == 1)
				{
					continue;
				}
				else{

					cout << "Whom do you want to ask for a match?" << endl;
					for (int i = 1; i < m_numPlayers; i++)
					{
						cout << "Player " << i << ": " << m_players[i]->GetName() << endl;
					}
					Console::ResetColor();
					for (;;)
					{
						if (cin >> playerChoice && playerChoice>0 && playerChoice < m_numPlayers && m_players[playerChoice]->GetNumCards() != 0)
						{
							cin.sync();
							break;
						}

						cin.clear();
						cin.sync();

					}
				}
				//Comparing with the computer
				MatchPairs(cardChoice, computerCard,playerChoice);

				NoMatchPair(cardChoice, computerCard);
			}
			else
			{
				// Computer's turn
				while (m_players[m_currPlayer]->GetNumCards() == 0)
					m_currPlayer = (m_currPlayer + 1) % m_numPlayers;

				system("cls");
				for (int i = 0; i < m_numPlayers; i++)
				{
					m_players[i]->Show();
				}

				m_players[m_currPlayer]->GetCard(rand() % m_players[m_currPlayer]->GetNumCards(), computerCard);
				int faceValue1 = computerCard.GetFace();
				
				Console::ForegroundColor(DarkYellow);
				cout << "Now it's the computer's turn to draw in ..." << endl;

				Console::ForegroundColor(White);
				int opponentChoice = rand() % m_numPlayers;
				
				while (opponentChoice == m_currPlayer || m_players[opponentChoice]->GetNumCards() == 0)
					opponentChoice = rand() % m_numPlayers;
				
				
				cout << m_players[m_currPlayer]->GetName() << " asked " << m_players[opponentChoice]->GetName() << " for " << computerCard;

				MatchPairs(faceValue1, computerCard, opponentChoice);

				NoMatchPair(faceValue1, computerCard);

				cout << "\n\n";
				cout << "End of computer's turn.";
				system("pause");
			}
			if (m_players[0]->GetScore() + m_players[1]->GetScore() == 26)
			{
				m_state = GAME_END;
			}
			}
			break;
		case ROUND_END:
		{
			bRun = false;
			cout << "game end!";
			break;
		}
		case GAME_END:
		{
			// The game is over, change the bool to stop the loop.
			bRun = false;
			int winScore = m_players[0]->GetScore();
			for (int wnscore = 1; wnscore < m_numPlayers; wnscore++)
			{
				if (winScore < m_players[wnscore]->GetScore())
				{
					winScore = m_players[wnscore]->GetScore();
				}
			}

			Console::Clear();
			for (int wnscore2 = 0; wnscore2 < m_numPlayers; wnscore2++)
			{
				if (m_players[wnscore2]->GetScore() == winScore)
				{
					Console::ForegroundColor(DarkYellow);
					Console::SetCursorPosition(26, 16);
					cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
					Console::SetCursorPosition(26, 18);
					cout << "      \1    WINNER'S ON BOARD    \1      " << endl;
					Console::SetCursorPosition(26, 20);
					cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
					Console::SetCursorPosition(26, 22);
					cout << "The winner is " << m_players[wnscore2]->GetName() << "!" << endl;
					Console::ResetColor();
				}
			}
			break;
		}
		}
		
		}
	}


int Game::Score(Player* _player)
{
	bool scoreToAdd = 0;
	Card card1; Card card2;
	for (int i = 0; i < _player->GetNumCards(); i++)
	{
		for (int j = 0; j < _player->GetNumCards(); j++)
		{
			if (i == j)
				continue;
			_player->GetCard(i, card1);
			_player->GetCard(j, card2);
			if (card1.GetFace() == card2.GetFace())
			{
				_player->Discard(j, card2);
				_player->Discard(i, card1);
				scoreToAdd++;
				if (_player->GetCheat(0) == true)
				{
					scoreToAdd += rand() % 15+1;
				}
				i--;
			}
		}
	}
	return scoreToAdd;
}

void Game::deckIsEmpty()
{

	for (int k = 0; k < m_numPlayers; k++)
	{
		if (m_players[k]->GetNumCards() == 0 && !m_Deck.IsEmpty())
		{
			for (int addCard = 0; addCard < 7; addCard++)
			{
				if (m_Deck.IsEmpty())
				{
					cout << "The deck is empty.\n";
					break;
				}
				Card newCards;
				m_Deck.Draw(newCards);
				m_players[k]->AddCard(newCards);
			}
		}
	}
}

void Game::playerCorrectChoice(int &pl_Choice, Card matchedWithCard, Player* _player)
{
	do
	{
		system("cls");
		for (int i = 0; i < m_numPlayers; i++)
		{
			m_players[i]->Show();
		}
		//_player->Show();
		//m_players[1]->Show();
		//m_players[0]->Show();
		if (m_currPlayer == 0)
		{
			cout << "Pick a card ? ";
			cin >> pl_Choice;
			if (cin.good() && pl_Choice < 15 && pl_Choice > 1)
			{
				cin.sync();
				for (int i = 0; i < _player->GetNumCards(); i++)
				{
					_player->GetCard(i, matchedWithCard);

					if (pl_Choice == matchedWithCard.GetFace())
					{
						Console::ForegroundColor(Cyan);
						cout << "\nYou are good to go ahead! \2\n";
						Console::ResetColor();
						system("pause");
						break;
					}
				}
			}
			cin.clear();
			cin.sync();
		}
	} while (pl_Choice != matchedWithCard.GetFace());
}

void Game::MatchPairs(int &pl_Choice, Card& computerCard, int &opponent)
{
	for (int j = 0; j < m_players[opponent]->GetNumCards(); j++)
	{
		m_players[opponent]->GetCard(j, computerCard);

		if (pl_Choice == computerCard.GetFace())
		{
			m_players[opponent]->Discard(j, computerCard);
			if (m_players[opponent]->GetNumCards() == 0)
			{
				for (int i = 0; i < 7; i++)
				{
					if (m_Deck.IsEmpty())
						break;
					Card temp;
					m_Deck.Draw(temp);
					m_players[opponent]->AddCard(temp);
				}
			}
			m_players[m_currPlayer]->AddCard(computerCard);

			Console::ForegroundColor(DarkGreen);
			cout << "\nMatch was successful! "
				<< "\nYou're doing good, Keep it up." << endl;
			Console::ResetColor();

			m_players[m_currPlayer]->AddToScore(Score(m_players[m_currPlayer]));
			cout << m_players[m_currPlayer]->GetName() << " Score: " << m_players[m_currPlayer]->GetScore() << endl;
			if (m_players[m_currPlayer]->GetNumCards() == 0)
			{
				for (int i = 0; i < 7; i++)
				{
					if (m_Deck.IsEmpty()){
						if (m_players[m_currPlayer]->GetNumCards() == 0)
							m_currPlayer  = (m_currPlayer + 1) % m_numPlayers;
						break;
					}
					Card temp;
					m_Deck.Draw(temp);
					m_players[m_currPlayer]->AddCard(temp);
				}
			}
			cout << "\n\n";
			Console::ForegroundColor(DarkRed);
			cout << "It's your turn again, play mindfully! \n";
			Console::ResetColor();
			break;
		}

	}
}


void Game::NoMatchPair(int pl_Choice, Card computerCard)
{
	if (Player::GetCheat(3) && m_currPlayer == 0)
	{
		secondChance = false;
		playerCorrectChoice(pl_Choice, computerCard, m_players[0]);
	}
	if (pl_Choice != computerCard.GetFace())
	{
		Console::ForegroundColor(Blue);
		cout << "\n\n";
		cout << "No match was found, ";
		if (m_Deck.IsEmpty() == true)
			{
					Console::ForegroundColor(Blue);
					cout << " and the deck is empty!" << endl;
					m_currPlayer = (m_currPlayer+1)%m_numPlayers;
					Console::ResetColor();
			}
		else
			{
				Card c;
				if (m_Deck.Draw(c) == true)
					{
						m_players[m_currPlayer]->AddCard(c);
						Console::ForegroundColor(Blue);
						cout << "Go fish! " << endl;
						if (m_currPlayer == 0)
						{
							cout <<  "You drew a " << c << ".";//16751079 rxbin603286rxpcnmedd
						}
						else
						{ 
						cout << m_players[m_currPlayer]->GetName()<<" drew a " << c << ".";
						}
						Console::ResetColor();
						// if the hands match in themselves.
							int temp = Score(m_players[m_currPlayer]);
							if (temp != 0)
							{
								m_players[m_currPlayer]->AddToScore(temp);
								Console::ForegroundColor(DarkMagenta);
								cout << " Smart Guess!\n";
							}
							Console::ResetColor();
							m_currPlayer = (m_currPlayer + 1) % m_numPlayers;
							while (m_players[m_currPlayer]->GetNumCards() == 0)
								m_currPlayer = (m_currPlayer + 1) % m_numPlayers;
					}	
			}
	}
	cout << "\n\n";
	system("pause");
}

void Game::cheatMenu()
{
	// CheatMenu //
	Console::Clear();
	Console::ForegroundColor(DarkMagenta);
	cout << "||oooooooooooooooooooooooooooooooooooo||\n";
	cout << "         \2  CHEAT MENU  \2             \n";
	cout << "||oooooooooooooooooooooooooooooooooooo||\n";
	cout << "\n\n";
	cout << "    1) Random Scores    " << endl;
	cout << "    2) See Opponent's Cards    " << endl;
	cout << "    3) Getting Two Chances    " << endl;
	cout << "\n\n";
	int userInput;
	for (;;)
	{
		cout << "What would you like to go for: ";
		if (cin >> userInput && userInput >= 1 && userInput <= 3)
		{
			cin.sync();
			break;
		}
		cin.clear();
		cin.sync();
	}
	Player::SetCheat(userInput);
}

void Game::IntroPlay()
{
	channel->stop();
	fmod_system->playSound(GameMusic, 0, false, &channel);

	//PlaySound(L"Casino_Royale_-_Chris_Cornell_-_You_Know_My_Name.wav", NULL, SND_ASYNC | SND_LOOP);
	string messageYou;
	char pl_Name[32];
	for (;;)
	{

		Console::Clear();
		Console::ForegroundColor(Yellow);
		messageYou = { "You: Welcome to Mission GoldenEye!\n\n"
			"You: M told me she was sending someone,Mr.......\n\n"
			"007: Bond, James Bond!\n\n"
			"You: Sounds, good! I will be assiting you in the mission, Mr.Bond.\n\n"
			"007: By the way, I didn't catch your name Mr./Ms....(Press enter to continue)\n\n" };

		for (unsigned i = 0; i < messageYou.length(); i++)

		{

			cout << messageYou[i];

			if ((i + 1) < messageYou.length() && messageYou[i + 1] != '\n')
				cout << char(129);

			_sleep(100);

			if ((i + 1) < messageYou.length() && messageYou[i + 1] != '\n')
				cout << char(8);
		}

		cout << ' ' << char(8);
		cin.get();


		cout << "My name is:          \b\b\b\b\b\b\b\b\b\b";;
		if (cin.get(pl_Name, 32, '\n'))
		{
			cin.sync();
			break;
		}

		cin.clear();
		cin.sync();
	}
	cout << "\n";
	cout << "007: Nice to meet you," << pl_Name << "! " << endl;
	m_players[0]->SetName(pl_Name);
	Console::ResetColor();
	//system("cls");

	cout << "\n\n";
	Console::ForegroundColor(Yellow);
	for (;;)
	{
		messageYou = { "You: We will be leaving for Czech Republic soon.\n\n"
			"007: How many players do you think Xenia would be \n"
			"     bringing with him at the casino, (1 - 3) ?"
			"{Press enter to continue)" };


		for (unsigned i = 0; i < messageYou.length(); i++)

		{
			cout << messageYou[i];

			if ((i + 1) < messageYou.length() && messageYou[i + 1] != '\n')
				cout << char(129);

			_sleep(100);

			if ((i + 1) < messageYou.length() && messageYou[i + 1] != '\n')
				cout << char(8);
		}

		cout << ' ' << char(8);
		cin.get();
		if (cin >> numOpponents && numOpponents < 4 && numOpponents>0)
		{
			cin.sync();
			break;
		}
		cin.clear();
		cin.sync();
	}
	cout << "\n\n";
	cout << "You: Mr.Bond!, I guess we will be facing ";
	switch (numOpponents)
	{
	case 3:
		m_players[3] = new Computer("Xenia Onatopp");
		cout << m_players[3]->GetName() << " and ";
	case 2:
		m_players[2] = new Computer("Le Chiffre");
		cout << m_players[2]->GetName() << " and ";
	case 1:
		m_players[1] = new Computer("Rosa Klebb");
		cout << m_players[1]->GetName() << "." << endl;
	}
	cout << "\n\n";
	string textMes = { "007: Here are few instructions on the game, Do you want check it out?\n\n"
	"You: Yeah sure.\n\n"
	"Instructions - The player to the left of the dealer starts by asking another player for a \n"

		"Do you have a seven ?. The player asking must already hold at least one \n"

		"card of the requested rank,in this case the seven. If the player who was \n"

		"asked them to the person who asked for them. That player then gets another \n"

		"turn. They may now ask any player for any rank card as long as they hold at \n"

		"least one card of that rank. If the person asked does not have any of the \n"

		"cards asked for, they will say GO FISH!.The person who asked then draws a \n"

		"card from the top of the deck. If the card is of the rank asked for they \n"

		"show it to the other players and receive another turn. If it is not a card \n"

		"of the requested rank they keep the card and it is now the turn of the person \n"

		"who said GO FISH!\n\n\n"

	"007: Then shall will leave for our mission?\n\n"
	"You: After you...Mr.Bond!" };
	for (unsigned i = 0; i < textMes.length(); i++)

	{
		cout << textMes[i];

		if ((i + 1) < textMes.length() && textMes[i + 1] != '\n')
			cout << char(129);

		_sleep(100);

		if ((i + 1) < textMes.length() && textMes[i + 1] != '\n')
			cout << char(8);
	}
	Console::ResetColor();
	cout << endl;
	system("pause");
	m_numPlayers = numOpponents + 1;


	//Initial Drawing of cards
	for (int i = 0; i < m_numPlayers; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Card firstDraw;
			m_Deck.Draw(firstDraw);
			m_players[i]->AddCard(firstDraw);
		}
		m_players[i]->AddToScore(Score(m_players[i]));
	}

	m_state = GAME_PLAY;

}

void Game::RulesofTheGame()
{
	Console::Clear();
	Console::ForegroundColor(DarkGreen);
	string str;
	channel->stop();
	fmod_system->playSound(MenuMusic, 0, false, &channel);
	str = { 
			"M: Where have you been? \n\n"
			"007: Enjoying death! 007, reporting for duty!\n\n"
			"M: All right  007, it's time to get down to business. Some time ago, Pirate,\n"
			"  a top-secret combat helicopter, was hijacked from a French war vessel in\n" 
			"  Monte Carlo. Pirate was stolen by Xenia Onatopp. She was assisted by several\n" 
			"  mysterious comrades.\n\n"
			"  Xenia, a former Soviet pilot, is a known accomplice if the Janus Syndicate, an\n"
			"  international organization that is world renowned for its dealings in topflight\n"
			"  illegal arms. They are currently based in St. Petersburg, Russia.\n\n"
			"  Pirate reappeared two days ago in Russia near the site of an unusual disturbance\n"
			"  believed to be the result of the discharge of the GoldenEye weapon satellite.\n\n"
			"  The situation is serious, 007. If Pirate or GoldenEye has fallen into the wrong hands,\n"
			"  I don't have to tell you that the security of the free world could be in jeopardy.\n"
			"  We want you to recover the pirate helicopter and get to the bottom of this.\n\n"
			"  Pirate is the million dollar winning memo of Casino Royale.\n\n"
			"007: So your saying I'm playing a game of some sort, am I right.\n\n"
			"M: Correct. You'll be playing a game of cunning and witt.... GOLDFISH!\n\n"
			"007: Wait! GoldFish? The Stake are big. I'm not fimilar with this game\n\n"
			"M: Yes it is. You will be given with state of the art Deck of playing card fitted will pointers\n"
			" and nodes and a thing called a 'strut'.\n\n"
			"007: Oh! I see, so M do you think i can go for my vacation after this......\2\n\n"
			"M: Will see.....!"
	};

	for (unsigned i = 0; i < str.length(); i++)

	{

		cout << str[i];

		if ((i + 1) < str.length() && str[i + 1] != '\n')
			cout << char(129);

		_sleep(100);

		if ((i + 1) < str.length() && str[i + 1] != '\n')
			cout << char(8);
	}

	cout << ' ' << char(8);
	cin.get();
}

int Game::getUserChoice()
{
	int numItems = 4;
	int curSel = 0, textAttrib;
	bool selectionMade = false, needsUpdate = true;// clears the screen 

	while (!selectionMade)
	{
		if (needsUpdate)
		{
			for (int i = 0; i < 4; i++)
			{
				Console::SetCursorPosition(40, 22 + i * 2);
				if (curSel == i)
				{
					cout << "*";
				}
				else
				{
					cout << " ";
				}
			}
			needsUpdate = false;
			
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			curSel--;
			needsUpdate = true;
		}

		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			curSel++;
			needsUpdate = true;
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			return curSel;
		}

		if (curSel < 0)
		{
			curSel = numItems;
		}
		else if (curSel >(numItems - 1))
		{
			curSel = 0;
		}
		Sleep(100);
	}
	//char dummy[10];
	//cin.getline(dummy, 10);     // clear the enter key from the buffer
	return curSel;
}

void Game::InitFMOD()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmod_system);

	result = fmod_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK)
	{
		fmod_system->close();
		fmod_system->release();
	}

	fmod_system->createSound("James Bond 007 Blood Stone - Theme Music.mp3", FMOD_DEFAULT, 0,&MenuMusic);
	fmod_system->createSound("Casino Royale - Chris Cornell - You Know My Name.mp3", FMOD_DEFAULT, 0, &GameMusic);

	

}



void Game::DeleteMusic()
{
	if (MenuMusic)
	{
		MenuMusic->release();
		MenuMusic = 0;
	}

	if (GameMusic)
	{
		MenuMusic->release();
		MenuMusic = 0;
	}

	fmod_system->close();
	fmod_system->release();
}