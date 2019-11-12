#include "Graphics.h"

int anime = 0;

int AnimetionTex(int* currentFlame, int animetionFlame, int spriteNum) {

	if (currentFlame == nullptr) {
		return 0;
	}

	*currentFlame += 1;
	if (*currentFlame % animetionFlame == 0) {
		anime++;
	}
	else if (*currentFlame >= animetionFlame * spriteNum) {
		*currentFlame = 0;
		anime = 1;
	}

	return anime;
}