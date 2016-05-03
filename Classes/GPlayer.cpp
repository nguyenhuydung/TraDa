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
