#pragma once
#include "stdafx.h"
#include "Player.h"

#define LB (char)200
#define LT (char)201
#define RT (char)187
#define RB (char)188
#define VT (char)186
#define HT (char)205

/* TODO Lab2:
		Make Computer a child of Player
*/
class Computer : public Player
{

public:
	// Default ctor
	// In:	_name		The name of the computer player
	Computer(char _name);
	/* TODO Lab2:
			Set the default value of _name to "Computer"
	*/
	Computer(const char* _name = "Computer");
	
	void set();
	// Display the computer's name and card backs
	void Show() const;
	
	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;
};

