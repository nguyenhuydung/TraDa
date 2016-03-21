#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "Card.h"

class GPlayer {
	public:
	GPlayer();
	~GPlayer();

	Card* Bai[13];

	void cpuDanh(GPlayer* benTrai, GPlayer benPhai, GPlayer doiDien);
};


#endif
