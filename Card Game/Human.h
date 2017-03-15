#pragma once
#include "stdafx.h"
#include "Player.h"
using namespace std;
//#include "Console.h"
//using namespace System;

#define LB (char)200
#define LT (char)201
#define RT (char)187
#define RB (char)188
#define VT (char)186
#define HT (char)205



/* TODO Lab2:
		Make Human a child of Player
*/

class Human :public Player
{
private:

public:
	// Default ctor
	// In:	_name		The name of the human player

	/* TODO Lab2:
	Set the default value of _name to "Human"
	*/
	Human(const char* _name = "Human");

	// Display the computer's name and card backs
	void Show() const;

	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;

};

