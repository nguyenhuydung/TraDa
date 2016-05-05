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
		maskRepair();
		DanhDau x = {BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC};
		maskSapBo(0, x);
		//soBai = RandomHelper::random_int(1, 4);


	} else {
		//Đỡ bài đánh sang:
		soBai = RandomHelper::random_int(-4, 4);

	}
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
	return baiDanh;
}

void GPlayer::maskRepair() {
	for (auto i = 0; i < 13; i++) {

		DanhDauBo[i] = BO_RAC; // { BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC };
	}
	SoQuanBaiLe = 13;
}

BaiDanhRa* GPlayer::maskKieuBo(int idx, DanhDau maskbai) {
	auto ret = findKieuBo(BO_DOITHONG, idx, 12, maskbai);
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DOITHONG, idx, 8, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DOITHONG, idx, 6, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_TUQUY, idx, 4, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 13, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 12, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 11, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 10, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 9, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 8, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 7, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 6, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 5, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 4, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DAY, idx, 3, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_BA, idx, 0, maskbai);
	}
	if (ret->soLuong == 0) {
		ret = findKieuBo(BO_DOI, idx, 0, maskbai);
	}
	return ret;
}

BaiDanhRa* GPlayer::findKieuBo(KieuXapBo type, int idx, int len, DanhDau maskbai) {
	if (maskbai == nullptr) {
		maskbai = new DanhDau{BO_RAC, BO_RAC ,BO_RAC, BO_RAC ,BO_RAC, BO_RAC ,BO_RAC, BO_RAC ,BO_RAC, BO_RAC ,BO_RAC, BO_RAC};
	}
	auto ret = new BaiDanhRa();
	///Doi thoong:
	if (type == BO_DOITHONG) {
		ret->kieuBai = BO_DOITHONG;
		auto count = 1;
		int doithong[12] = {idx, -1 ,-1 ,-1,-1 ,-1 ,-1, -1 ,-1 ,-1, -1, -1};
		bool danhdaudachon[13] = {false, false ,false, false ,false, false ,false, false ,false, false ,false, false};
		danhdaudachon[idx] = true;
		for (auto doi = 0; doi < len / 2; doi = doi + 2) {
			auto foundDoi = false;
			for (auto d = 0; d < 13; d++) {
				///tim cap doi voi idx
				if (!danhdaudachon[d] && Bai[d]->cardIndex == Bai[idx]->cardIndex && maskbai[d] == BO_RAC) {
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
					if (!danhdaudachon[d] && Bai[d]->cardIndex - 1 == Bai[idx]->cardIndex && maskbai[d] == BO_RAC) {
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
				maskbai[doithong[i]] = BO_DOITHONG;
			}
			ret->soLuong = count;
			return ret;
		}
		ret->soLuong = 0;
		return ret;;
	}
	///Danh dau sanh:
	if (type == BO_DAY) {
		ret->kieuBai = BO_DAY;
		auto count = 0;
		int sanh[13] = {idx, -1 ,-1 ,-1,-1 ,-1,-1 ,-1,-1 ,-1,-1 ,-1,-1};
		bool danhdaudachon[13] = {false, false ,false, false ,false, false ,false, false ,false, false ,false, false};
		danhdaudachon[idx] = true;
		for (auto i = 1; i < 13; i++) {
			for (auto j = 0; j < 13; j++) {
				if (!danhdaudachon[j] && Bai[j]->cardIndex - 1 == Bai[idx]->cardIndex && maskbai[j] == BO_RAC && count < len) {
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
			for (auto i = 0; i < 4; i++) {
				//danhDauXapBo[player][tuquy[i]] = BO_TUQUY;
				maskbai[sanh[i]] = BO_DAY;
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
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai[j] == BO_RAC) {
				count += 1;
				tuquy[count] = j;
			}
		}
		if (count == 3) {
			count = count + 1;
			for (auto i = 0; i < 4; i++) {
				//danhDauXapBo[player][tuquy[i]] = BO_TUQUY;
				maskbai[tuquy[i]] = BO_TUQUY;
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
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai[j] == BO_RAC && count < 2) {
				count += 1;
				boba[count] = j;
			}
		}
		if (count == 2) {
			for (auto i = 0; i < 3; i++) {
				//danhDauXapBo[player][boba[i]] = BO_BA;
				maskbai[boba[i]] = BO_BA;
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
			if (j != idx && Bai[j]->cardIndex == Bai[idx]->cardIndex && maskbai[j] == BO_RAC && count == 0) {
				count += 1;
				bodoi[count] = j;
			}
		}
		if (count == 1) {
			for (auto i = 0; i < 2; i++) {
				//danhDauXapBo[player][bodoi[i]] = BO_DOI;
				maskbai[bodoi[i]] = BO_DOI;
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

BaiDanhRa GPlayer::findBai(KieuXapBo type) {
	auto found = BaiDanhRa();


	return found;
}

void GPlayer::maskSapBo(int step, DanhDau maskbai) {
	///Trang thai de quay lui
	DanhDau danhdau = {BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC,BO_RAC};

	for (auto i = 0; i < 13; i++) {
		danhdau[i] = maskbai[i];
	}
	///De quy :
	for (auto i = 0; i < 13; i++) {
		if (danhdau[i] == BO_RAC) {
			///Tìm sắp bộ cho quân i:
			if (maskKieuBo(i, danhdau)->soLuong != 0) {
				maskSapBo(step + 1, danhdau);
			}
			///tối ưu đếm quân lẻ
			auto demquanle = 0;
			for (auto c = 0; c < 13; c++) {
				if (danhdau[c] == BO_RAC) {
					demquanle += 1;
				}
			}
			if (demquanle < SoQuanBaiLe) {
				///luu trang thai danh dau nay
				SoQuanBaiLe = demquanle;
				for (auto j = 0; j < 13; j++) {
					DanhDauBo[j] = danhdau[j];
				}
			}
		}
	}
}

void GPlayer::Sort() {
	for (auto i = 0; i < 13; i++) {
		for (auto j = i + 1; j < 13; j++) {
			if ((Bai[i]->cardIndex > Bai[j]->cardIndex) || (Bai[i]->cardIndex == Bai[j]->cardIndex && Bai[i]->cardElement > Bai[j]->cardElement) || Bai[j]->daDanh) {
				auto tmp = Bai[i];
				Bai[i] = Bai[j];
				Bai[j] = tmp;

				auto tmpd = DanhDauBo[i];
				DanhDauBo[i] = DanhDauBo[j];
				DanhDauBo[j] = tmpd;
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
	if (isValid) return BO_DAY;
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
	if (isValid) return BO_DOITHONG;
	return BO_FALSE;
}

