#include "GPlayer.h"

//lksjdflk sjdglk jdslhkj
//Comit
GPlayer::GPlayer() {
}


GPlayer::~GPlayer() {
}

void GPlayer::cpuDanh() {

}

void GPlayer::RepairMask() {
	for (auto i = 0; i < 13; i++) {
		DanhDauBo[i] = BO_RAC; // { BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC };
	}
	BaiLeCount = 13;
}

extern GPlayer* CPplayer[4];

void GPlayer::Sort() {
	for (auto i = 0; i < 13; i++) {
		for (auto j = i + 1; j < 13; j++) {
			if ((CPplayer[0]->Bai[i]->cardIndex > CPplayer[0]->Bai[j]->cardIndex) || (CPplayer[0]->Bai[i]->cardIndex == CPplayer[0]->Bai[j]->cardIndex && CPplayer[0]->Bai[i]->cardElement > CPplayer[0]->Bai[j]->cardElement) || CPplayer[0]->Bai[j]->daDanh) {
				auto tmp = CPplayer[0]->Bai[i];
				CPplayer[0]->Bai[i] = CPplayer[0]->Bai[j];
				CPplayer[0]->Bai[j] = tmp;

				auto tmpd = CPplayer[0]->DanhDauBo[i];
				CPplayer[0]->DanhDauBo[i] = CPplayer[0]->DanhDauBo[j];
				CPplayer[0]->DanhDauBo[j] = tmpd;
			}
		}
	}
}
