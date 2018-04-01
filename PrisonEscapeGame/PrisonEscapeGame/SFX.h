#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "OptionsMenu.h"
class SFX
{
public:
	SFX();
	~SFX();

	// punching sound effect
	void punchEffect(OptionsMenu &options);
	// colliding with wall sound effect
	void collisionEffect(OptionsMenu &options);
	// Danger sound effect
	void dangerEffect(OptionsMenu &options);
	// door opening
	void openDoorEffect(OptionsMenu &options);

};

