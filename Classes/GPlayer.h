#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "Card.h"

class BaiDanhRa {
public:
	int soLuong;
	Card *danhSach[13];
	KieuXapBo kieuBai;
};

///Đánh bài là việc fill đầy cái Log này
class LogLuotDanhBai {
public:
	int nguoiDangDanh = 0;
	bool nguoiDaBoVong[4] = { false,false,false,false };
	int nguoiDaBoVongCount = 0;
	BaiDanhRa *baiDanh;
	bool vongKetThuc = false; //nếu true -> nguoiDangDanh là nguoi danh tiếp theo
};

typedef KieuXapBo DanhDau[13];


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
	//BaiDanhRa* cpuChonQuanDanh();
	BaiDanhRa* cpuChonQuanDanh(LogLuotDanhBai *baidanhsang);
	KieuXapBo ValidateBaiDanhRa(BaiDanhRa *baidanh);
	void Sort();
	void maskRepair();
	void maskSapBo(int step, DanhDau maskbai);

private:
	BaiDanhRa* maskKieuBo(int idx, DanhDau maskbai);
	BaiDanhRa* findKieuBo(KieuXapBo type, int idx, int len, DanhDau maskbai);
	BaiDanhRa findBai(KieuXapBo type);
};


#endif
