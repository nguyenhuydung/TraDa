#include "GPlayer.h"

//lksjdflk sjdglk jdslhkj
//Comit
GPlayer::GPlayer() {
}


GPlayer::~GPlayer() {
}

BaiDanhRa* GPlayer::cpuChonQuanDanh(LogLuotDanhBai* baidanhsang) {
	auto baiDanh = new BaiDanhRa();
	auto soBai = 0;
	if (baidanhsang->vongKetThuc) {
		//Đánh bài
		Sort();
		maskRepair(DanhDauBo);
		maskSapBo(0, DanhDauBo);
		///Chon bộ bé nhất
		
		///Tìm quân chưa đánh đầu tiên:
		auto f = 0;
		while (Bai[f]->daDanh) f++;
		Bai[f]->cardState = CARD_STATE_SELT;
		baiDanh->danhSach[0] = Bai[f];
		baiDanh->soLuong = 1;
		while (DanhDauBo->lienKet[f] != -1) {
			f = DanhDauBo->lienKet[f];
			Bai[f]->cardState = CARD_STATE_SELT;
			baiDanh->danhSach[baiDanh->soLuong] = Bai[f];
			baiDanh->soLuong++;
		}
		baiDanh->kieuBai = ValidateBaiDanhRa(baiDanh);
	} else {
		//Đỡ bài đánh sang:
		soBai = RandomHelper::random_int(-4, 4);
		///tesst
		if (soBai > 0) {
			auto i = 0;
			baiDanh->soLuong = 0;
			while (i < 13 && baiDanh->soLuong < soBai) {
				if (!Bai[i]->daDanh) {
					Bai[i]->cardState = CARD_STATE_SELT;
					baiDanh->danhSach[baiDanh->soLuong] = Bai[i];
					baiDanh->soLuong++;
				}
				i++;
			}
			baidanhsang->baiDanh = baiDanh;
			SoQuanBaiConLai = SoQuanBaiConLai - baiDanh->soLuong;
		} else {
			baiDanh->soLuong = 0;
		}
	}
	return baiDanh;
}

void GPlayer::maskRepair(DanhDau *danhdau) {
	if (danhdau == nullptr) {
		danhdau = new DanhDau();
	}
	SoQuanBaiLe = 13;
	for (auto i = 0; i < 13; i++) {
		if (Bai[i]->daDanh) {
			SoQuanBaiLe -= 1;
			danhdau->danhDau[i] = BO_FALSE;
			danhdau->lienKet[i] = -1;
		} else {
			danhdau->danhDau[i] = BO_RAC;
			danhdau->lienKet[i] = -1;
		}
	}
}

///Tim bộ kiểu: type, bắt đầu từ idx, với hệ đánh dấu maskbai:
BaiDanhRa* GPlayer::findKieuBo(KieuXapBo type, int idx, DanhDau *maskbai) {
	auto len = 0;
	auto ret = new BaiDanhRa();
	///TÌM ĐÔI THÔNG:
	if (type == BO_DOITHONG3 || type == BO_DOITHONG4 || type == BO_DOITHONG5 || type == BO_DOITHONG6) {
		switch (type) {
			case BO_DOITHONG3:
				len = 6;
				ret->kieuBai = BO_DOITHONG3;
				break;
			case BO_DOITHONG4:
				len = 8;
				ret->kieuBai = BO_DOITHONG3; 
				break;
			case BO_DOITHONG5: 
				len = 10;
				ret->kieuBai = BO_DOITHONG3;
				break;
			case BO_DOITHONG6:
				len = 12;
				ret->kieuBai = BO_DOITHONG3;
				break;
		}
		
		auto count = 1;
		int doithong[12] = {idx, -1 ,-1 ,-1,-1 ,-1 ,-1, -1 ,-1 ,-1, -1, -1};
		bool danhdaudachon[13] = {false, false ,false, false ,false, false ,false, false ,false, false ,false, false};
		danhdaudachon[idx] = true;
		for (auto doi = 0; doi < len / 2; doi = doi + 2) {
			auto foundDoi = false;
			for (auto d = 0; d < 13; d++) {
				///tim cap doi voi idx
				if (!danhdaudachon[d] && Bai[d]->cardIndex == Bai[idx]->cardIndex && maskbai->danhDau[d] == BO_RAC) {
					doithong[doi + 1] = d;
					danhdaudachon[d] = true;
					count = count + 1;
					foundDoi = true;
					break;
				}
			}
			if (foundDoi) {
				///tim doi lon hon
				auto foundNext = -1;
				for (auto d = 0; d < 13; d++) {
					if (!danhdaudachon[d] && Bai[d]->cardIndex - 1 == Bai[idx]->cardIndex && maskbai->danhDau[d] == BO_RAC) {
						doithong[doi + 2] = d;
						danhdaudachon[d] = true;
						count = count + 1;
						foundNext = d;
						break;
					}
				}
				if (foundNext == -1) {
					ret->soLuong = 0;
					return ret;
				}
				idx = foundNext;
			} else {
				ret->soLuong = 0;
				return ret;
			}
		}

		if (count == len) {
			count = count + 1;
			for (auto i = 0; i <= count; i++) {
				maskbai->danhDau[doithong[i]] = ret->kieuBai;
				maskbai->lienKet[doithong[i]] = (i < len) ? doithong[i + 1] : -1;
			}
			ret->soLuong = count;
			return ret;
		}
		ret->soLuong = 0;
		return ret;;
	}
	///TÌM SẢNH:
	if (type == BO_SANH3 || type == BO_SANH4 || type == BO_SANH5 || type == BO_SANH6 || type == BO_SANH7 || type == BO_SANH8 || type == BO_SANH9 || type == BO_SANH10 || type == BO_SANH11 || type == BO_SANH12 || type == BO_SANH13) {
		switch (type) {
			case BO_SANH3:
				len = 3;
				ret->kieuBai = BO_SANH3;
				break;
			case BO_SANH4:
				len = 4;
				ret->kieuBai = BO_SANH4;
				break;
			case BO_SANH5:
				len = 5;
				ret->kieuBai = BO_SANH5;
				break;
			case BO_SANH6:
				len = 6;
				ret->kieuBai = BO_SANH6;
				break;
			case BO_SANH7:
				len = 7;
				ret->kieuBai = BO_SANH7;
				break;
			case BO_SANH8:
				len = 8;
				ret->kieuBai = BO_SANH8;
				break;
			case BO_SANH9:
				len = 9;
				ret->kieuBai = BO_SANH9;
				break;
			case BO_SANH10:
				len = 10;
				ret->kieuBai = BO_SANH10;
				break;
			case BO_SANH11:
				len = 11;
				ret->kieuBai = BO_SANH11;
				break;
			case BO_SANH12:
				len = 12;
				ret->kieuBai = BO_SANH12;
				break;
			case BO_SANH13:
				len = 13;
				ret->kieuBai = BO_SANH13;
				break;
		}
		auto count = 0;
		int sanh[13] = {idx, -1 ,-1 ,-1,-1 ,-1,-1 ,-1,-1 ,-1,-1 ,-1,-1};
		bool danhdaudachon[13] = {false, false ,false, false ,false, false ,false, false ,false, false ,false, false};
		danhdaudachon[idx] = true;
		for (auto i = 1; i < 13; i++) {
			for (auto j = 0; j < 13; j++) {
				if (!danhdaudachon[j] && Bai[j]->cardIndex - 1 == Bai[idx]->cardIndex && maskbai->danhDau[j] == BO_RAC && count < len) {
					count += 1;
					sanh[count] = j;
					idx = j;
					danhdaudachon[idx] = true;
					break;
				}
			}
		}

		if (count == len) {
			count = count + 1;
			for (auto i = 0; i < count; i++) {
				//danhDauXapBo[player][tuquy[i]] = BO_TUQUY;
				maskbai->danhDau[sanh[i]] = ret->kieuBai;
				maskbai->lienKet[sanh[i]] = (i < len) ? sanh[i + 1] : -1;
			}
			ret->soLuong = count;
			return ret;
		}
		ret->soLuong = 0;
		return ret;
	}
	///Danh dau tu quy:
	if (type == BO_TUQUY) {
		ret->kieuBai = BO_TUQUY;
		auto count = 0;
		int tuquy[4] = {idx, -1 ,-1 ,-1};
		for (auto j = 0; j < 13; j++) {
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai->danhDau[j] == BO_RAC) {
				count += 1;
				tuquy[count] = j;
			}
		}
		if (count == 3) {
			count = count + 1;
			for (auto i = 0; i < 4; i++) {
				//danhDauXapBo[player][tuquy[i]] = BO_TUQUY;
				maskbai->danhDau[tuquy[i]] = BO_TUQUY;
				maskbai->lienKet[tuquy[i]] = (i < 3) ? tuquy[i + 1] : -1;
			}
			ret->soLuong = count;
			return ret;
		}
		ret->soLuong = 0;
		return ret;
	}
	///Danh dau Bo ba:
	if (type == BO_BA) {
		ret->kieuBai = BO_BA;
		auto count = 0;
		int boba[3] = {idx, -1 ,-1};
		for (auto j = 0; j < 13; j++) {
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai->danhDau[j] == BO_RAC && count < 2) {
				count += 1;
				boba[count] = j;
			}
		}
		if (count == 2) {
			for (auto i = 0; i < 3; i++) {
				//danhDauXapBo[player][boba[i]] = BO_BA;
				maskbai->danhDau[boba[i]] = BO_BA;
				maskbai->lienKet[boba[i]] = (i < 2) ? boba[i + 1] : -1;
			}
			ret->soLuong = count;
			return ret;
		}
		ret->soLuong = 0;
		return ret;
	}
	///Danh dau Bo doi:
	if (type == BO_DOI) {
		ret->kieuBai = BO_DOI;
		auto count = 0;
		int bodoi[2] = {idx, -1};
		for (auto j = 0; j < 13; j++) {
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai->danhDau[j] == BO_RAC && count == 0) {
				count += 1;
				bodoi[count] = j;
			}
		}
		if (count == 1) {
			for (auto i = 0; i < 2; i++) {
				//danhDauXapBo[player][bodoi[i]] = BO_DOI;
				maskbai->danhDau[bodoi[i]] = BO_DOI;
				maskbai->lienKet[bodoi[i]] = (i < 1) ? bodoi[i + 1] : -1;
			}
			ret->soLuong = count;
			return ret;;
		}
		ret->soLuong = 0;
		return ret;
	}
	ret->soLuong = 0;
	return ret;
}

BaiDanhRa GPlayer::findBai(KieuXapBo type, int length) {
	auto found = BaiDanhRa();


	return found;
}

void GPlayer::maskSapBo(int step, DanhDau *maskbai) {
	///Trang thai de quay lui
	auto hasvip = false;
	auto masklocal = new DanhDau();
	///copy masklocal:
	for (auto i =0; i<13; i++) {
		masklocal->danhDau[i] = maskbai->danhDau[i];
		masklocal->lienKet[i] = maskbai->lienKet[i];
	}
	///De quy :
	for (auto i = 0; i < 13; i++) {
		if (masklocal->danhDau[i] == BO_RAC && masklocal->danhDau[i] != BO_FALSE) {
			for (auto k = BO_DOI; k < BO_DOITHONG6; k = static_cast<KieuXapBo>(k + 1)) {
				auto res = findKieuBo(k, i, masklocal);
				if (res->soLuong != 0) {
					if (res->kieuBai == BO_TUQUY || res->kieuBai == BO_DOITHONG3 || res->kieuBai == BO_DOITHONG4 || res->kieuBai == BO_DOITHONG5) {
						hasvip = true;
					}
					maskSapBo(step + 1, masklocal);
				}
			}
		}
	}
	///tối ưu đếm quân lẻ
	auto demquanle = 0;
	if (!hasvip) {
		for (auto c = 0; c < 13; c++) {
			if (masklocal->danhDau[c] == BO_RAC) {
				demquanle += 1;
			}
		}
	}
	if (demquanle < SoQuanBaiLe) {
		///luu trang thai danh dau nay
		SoQuanBaiLe = demquanle;
		///copy đanhau:
		for (auto i = 0; i<13; i++) {
			DanhDauBo->danhDau[i] = masklocal->danhDau[i];
			DanhDauBo->lienKet[i] = masklocal->lienKet[i];
		}
	}
	delete masklocal;
}

void GPlayer::Sort() {
	///Dồn quân đã đánh:
	for (auto i = 0; i < 13; i++) {
		if (!Bai[i]->daDanh) {
			for (auto j = i + 1; j < 13; j++) {
				if (Bai[j]->daDanh) {
					auto tmp = Bai[i];
					Bai[i] = Bai[j];
					Bai[j] = tmp;

					if (DanhDauBo != nullptr) {
						auto tmpd = DanhDauBo->danhDau[i];
						auto tmpl = DanhDauBo->lienKet[i];
						DanhDauBo->danhDau[i] = DanhDauBo->danhDau[j];
						DanhDauBo->lienKet[i] = DanhDauBo->lienKet[j];
						DanhDauBo->danhDau[j] = tmpd;
						DanhDauBo->lienKet[j] = tmpl;
					}
				}
			}
		}
	}
	///Sắp xếp nhỏ đến lớn:
	for (auto i = 0; i < 13; i++) {
		if (!Bai[i]->daDanh) {
			for (auto j = i + 1; j < 13; j++) {
				if (Bai[j]->cardIndex < Bai[i]->cardIndex || (Bai[i]->cardIndex == Bai[j]->cardIndex && Bai[j]->cardElement < Bai[i]->cardElement)) {
					auto tmp = Bai[i];
					Bai[i] = Bai[j];
					Bai[j] = tmp;
					if (DanhDauBo != nullptr) {
						auto tmpd = DanhDauBo->danhDau[i];
						auto tmpl = DanhDauBo->lienKet[i];
						DanhDauBo->danhDau[i] = DanhDauBo->danhDau[j];
						DanhDauBo->lienKet[i] = DanhDauBo->lienKet[j];
						DanhDauBo->danhDau[j] = tmpd;
						DanhDauBo->lienKet[j] = tmpl;
					}
				}
			}
		}
	}
}

KieuXapBo GPlayer::ValidateBaiDanhRa(BaiDanhRa* baidanh) {
	auto selectedCrad = baidanh->danhSach;
	auto selectedCradLen = baidanh->soLuong;
	if (selectedCradLen == 1) {
		///Rác:
		return BO_RAC;
	}
	if (selectedCradLen == 2) {
		///Đôi
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex) {
			return BO_DOI;
		}
		return BO_FALSE;
	}
	if (selectedCradLen == 3) {
		///Sám
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex) {
			return BO_BA;
		}
	}
	if (selectedCradLen == 4) {
		///Tứ quý
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex && selectedCrad[2]->cardIndex == selectedCrad[3]->cardIndex) {
			return BO_TUQUY;
		}
	}
	///Kiểm tra sảnh:
	Card* tmpar[13];
	for (auto i = 0; i < selectedCradLen; i++) {
		tmpar[i] = selectedCrad[i];
	}
	///sort teamp
	for (auto i = 0; i < selectedCradLen; i++) {
		for (auto j = i + 1; j < selectedCradLen; j++) {
			if ((tmpar[i]->cardIndex > tmpar[j]->cardIndex) || (tmpar[i]->cardIndex == tmpar[j]->cardIndex && tmpar[i]->cardElement > tmpar[j]->cardElement)) {
				auto tmpx = tmpar[i];
				tmpar[i] = tmpar[j];
				tmpar[j] = tmpx;
			}
		}
	}
	///dây
	auto i = 1;
	auto isValid = true;
	do {
		if (tmpar[0]->cardIndex != tmpar[i]->cardIndex - i) {
			isValid = false;
		}
		i++;
	} while (isValid && i < selectedCradLen);
	if (isValid) {
		switch (i){
			case 3: return BO_SANH3;
			case 4: return BO_SANH4;
			case 5: return BO_SANH5;
			case 6: return BO_SANH6;
			case 7: return BO_SANH7; 
			case 8: return BO_SANH8; 
			case 9: return BO_SANH9; 
			case 10: return BO_SANH10; 			
			case 11: return BO_SANH11; 
			case 12: return BO_SANH12; 
			case 13: return BO_SANH13; 
		}
	};
	///Đôi thông
	if (selectedCradLen == 6 || selectedCradLen == 8 || selectedCradLen == 10 || selectedCradLen == 12) {
		i = 0;
		do {
			if ((tmpar[i]->cardIndex != tmpar[i + 1]->cardIndex) && (tmpar[i]->cardIndex != tmpar[i + 2]->cardIndex - 1) && (tmpar[i + 1]->cardIndex != tmpar[i + 3]->cardIndex - 1)) {
				isValid = false;
			}
			i = i + 2;
		} while (isValid && i < selectedCradLen - 4);
	}
	if (isValid) {
		switch (i) {
			case 6: return BO_DOITHONG3; 
			case 8: return BO_DOITHONG4; 
			case 10: return BO_DOITHONG5; 
			case 12: return BO_DOITHONG6; 
		}
	};
	return BO_FALSE;
}

void GPlayer::GPlayerTest() {
	Sort();
	maskRepair(DanhDauBo);
	//DanhDau danhdau = { BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC };
	maskSapBo(0, DanhDauBo);
}
