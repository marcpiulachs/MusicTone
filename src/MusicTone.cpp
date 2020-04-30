#include "MusicTone.h"

const uint16_t melody[3][4] =
{
		{ 3830, 2028, 2550, 3830 },
		{ 1800, 1100, 1500, 1800 },
		{ 1000, 1200, 800, 1000 }
};

const uint16_t tempo[3][4] =
{
		{120, 80, 40, 50},
		{120, 80, 40, 50},
		{120, 80, 40, 100},
};

MusicTone::MusicTone(int buzzerPin)
{
	// Set the pin where the buzzer is conected.
	_buzzerPin = buzzerPin;

	// Set pin as output.
	pinMode(buzzerPin, OUTPUT);

	reset();
}

MusicTone::~MusicTone()
{

}

void MusicTone::begin()
{
	setMelody(2);
}

void MusicTone::setMelody(int melody)
{
	reset();
	_melody = melody;
}

void MusicTone::play()
{
	reset();
	_play = true;
}

void MusicTone::stop()
{
	reset();
	_play = false;
}

void MusicTone::reset()
{
	_note = 0;
	_play = false;
	_previousMillis = 0;

	// poner el Pin en HIGH
	noTone(_buzzerPin);
}

void MusicTone::run()
{
	// here is where you'd put code that needs to be running all the time.

	// check to see if it's time to blink the LED; that is, if the difference
	// between the current time and last time you blinked the LED is bigger than
	// the interval at which you want to blink the LED.
	unsigned long currentMillis = millis();

	if (!_play)
		return;

	if (currentMillis - _previousMillis >= tempo[_melody][_note])
	{
		// save the last time you blinked the LED
		_previousMillis = currentMillis;

		if (_note == 3)
		{
			reset();
			return;
		}

		_note++;
	}

	tone(_buzzerPin, (int)melody[_melody][_note]);
}
