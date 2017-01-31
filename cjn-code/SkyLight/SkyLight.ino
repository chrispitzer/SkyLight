
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#define USE_OCTOWS2811

#define NUM_LEDS_PER_STRIP 64
#define NUM_STRIPS 7
#define ALL_SEXTANTS 6

#include<OctoWS2811.h>
#include<FastLED.h>
#include "ArtMap.h"

CRGB leds[NUM_STRIPS * SEXTANT_LED_COUNT];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
	LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
	mapInit();
}

void loop() {
	/*
	static uint8_t hue = 0;
	for (int i = 0; i < NUM_STRIPS; i++) {
		for (int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
			leds[(i*NUM_LEDS_PER_STRIP) + j] = CHSV((32 * i) + hue + j, 192, 255);
		}
	}

	// Set the first n leds on each strip to show which strip it is
	for (int i = 0; i < NUM_STRIPS; i++) {
		for (int j = 0; j <= i; j++) {
			leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
		}
	}

	hue++;

	LEDS.show();
	LEDS.delay(10);
	*/
}

void lightBox(int sextant, int box, CHSV color) {

	CRGB c = color;

	for (int i = shape_start_addr[sextant][box]; i < shape_start_addr[sextant][box + 1]; i++)
	{
		leds[i] = c;
	}
}

void lightLevelForSextant(int sextant, int level, CHSV color) {
	for (int j = 0; j < (level == 0 ? 2 : 4); j++) // only 2 shapes on level 0, 4 on all others
	{
		lightBox(sextant, levels[level][j], color);
	}
}

void lightLevel(int sextant, int level, CHSV color) {
	// Do for full piece
	if (sextant == ALL_SEXTANTS)
	{
		for (int i = 0; i < 6; i++)
		{
			lightLevelForSextant(i, level, color);
		}
	}
	// Do for a sextant
	else
	{
		lightLevelForSextant(sextant, level, color);
	}
}

void lightShapesForSextant(int sextant, int shape, CHSV color) {
	for (int j = 0; j < shape_count[shape]; j++) // only 2 shapes on level 0, 4 on all others
	{
		lightBox(sextant, shapes[shape][j], color);
	}
}

void lightShapes(int sextant, int shape, CHSV color) {
	// Do for full piece
	if (sextant == ALL_SEXTANTS)
	{
		for (int i = 0; i < 6; i++)
		{
			lightShapesForSextant(i, shape, color);
		}
	}
	// Do for a sextant
	else
	{
		lightShapesForSextant(sextant, shape, color);
	}
}