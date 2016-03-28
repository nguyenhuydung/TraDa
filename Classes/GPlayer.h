#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "Card.h"

struct TinhDiem {
	int soDiem;
	String noiDung;
};

class GPlayer {
	public:
	GPlayer();
	~GPlayer();

	Card* Bai[13];
	int Diem = 0; //Tổng điểm đang có
	int Thang = 0; //Số trận thắng
	int Thua = 0; // Số trận thua

	TinhDiem diemRoundReport[10]; //Luu thông tin chặt chém tính điểm
	int diemRoundIndex = 0; //Index của cái trên

	int State = 0;
	void cpuDanh();
};


#endif
