#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "Card.h"

class BaiDanhRa {
public:
	int soLuong;
	Card *danhSach[13];
	KieuXapBo kieuBai;


};

struct TinhDiem {
	int soDiem;
	String noiDung;
};

class GPlayer {
	public:
	GPlayer();
	~GPlayer();

	Card* Bai[13];
	KieuXapBo DanhDauBo[13];
	int SoQuanBaiConLai = 13;
	int SoQuanBaiLe = 13;

	int Diem = 0; //Tổng điểm đang có
	int Thang = 0; //Số trận thắng
	int Thua = 0; // Số trận thua

	TinhDiem diemRoundReport[10]; //Luu thông tin chặt chém tính điểm
	int diemRoundIndex = 0; //Index của cái trên

	int State = 0;
	BaiDanhRa* cpuChonQuanDanh();
	BaiDanhRa* cpuChonQuanDo(BaiDanhRa *baidanhsang);
	void RepairMask();
	void Sort();

	//BaiDanhRa* DetectBai
};


#endif
