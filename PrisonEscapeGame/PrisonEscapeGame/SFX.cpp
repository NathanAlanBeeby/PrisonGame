#include "SFX.h"

sf::Sound soundEffect;
sf::SoundBuffer punchBuffer, collideBuffer, dangerBuffer, doorBuffer;

SFX::SFX()
{
	if (!punchBuffer.loadFromFile("../assets/sound_assets/SFX/Punch.wav")) {
		std::cout << "Sound effect Punch not working" << std::endl;
	}
	if (!collideBuffer.loadFromFile("../assets/sound_assets/SFX/hitWall.ogg")) {
		std::cout << "Sound effect collide not working" << std::endl;
	}
	if (!dangerBuffer.loadFromFile("../assets/sound_assets/SFX/Danger.wav")) {
		std::cout << "Sound effect danger not working" << std::endl;
	}
	if (!doorBuffer.loadFromFile("../assets/sound_assets/SFX/DoorOpen.wav")) {
		std::cout << "Sound effect door open not working" << std::endl;
	}
}


SFX::~SFX()
{
}

void SFX::punchEffect(OptionsMenu &options) {
	std::cout << "Punched" << std::endl;
	soundEffect.setBuffer(punchBuffer);
	soundEffect.setVolume(options.Sound);
	soundEffect.play();
}

void SFX::collisionEffect(OptionsMenu &options) {
	std::cout << "Hit Wall" << std::endl;
	soundEffect.setBuffer(collideBuffer);
	soundEffect.setVolume(options.Sound);
	soundEffect.play();
}

void SFX::dangerEffect(OptionsMenu &options) {
	std::cout << "Danger" << std::endl;
	soundEffect.setBuffer(dangerBuffer);
	soundEffect.setVolume(options.Sound);
	soundEffect.play();
}

void SFX::openDoorEffect(OptionsMenu &options) {
	std::cout << "Door Sound" << std::endl;
	soundEffect.setBuffer(doorBuffer);
	soundEffect.setVolume(options.Sound);
	soundEffect.play();
}
