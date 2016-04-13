#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
#include "Card.h"
#include <SimpleAudioEngine.h>
#include "ui/CocosGUI.h"

const Vec2 PP0 = Vec2(45, 110);
const Vec2 PP1 = Vec2(940, 375);
const Vec2 PP2 = Vec2(940, 560);
const Vec2 PP3 = Vec2(335, 560);
static float scaleX = 0.0f;
static float scaleY = 0.0f;

static float scaleXL = 0.0f;
static float scaleYL = 0.0f;

enum KieuXapBo {
	BO_RAC,
	BO_DOI,
	BO_BA,
	BO_TUQUY,
	BO_DAY,
	BO_DOITHONG,
	BO_FALSE
};

struct BaiDanhRa {
	int soLuong;
	Card *danhSach[13];
	KieuXapBo kieuBai;
};
///Đánh bài là việc fill đầy cái Log này
struct LuotDanh {
	int nguoiDangDanh = 0;
	bool nguoiDaBoVong[4] = {false,false,false,false};
	int nguoiDaBoVongCount = 0;
	BaiDanhRa *baiDanh;
	bool vongKetThuc = false; //nếu true -> nguoiDangDanh là nguoi danh tiếp theo
};



class GameTienLenMNScene : public Layer {
	public:
	GameTienLenMNScene();
	~GameTienLenMNScene();
	static Scene* createScene();
	///create:
	static GameTienLenMNScene* create() {
		auto pRet = new(std::nothrow) GameTienLenMNScene();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	};
	//------------------------------------------------------------------
	bool init() override;
	///Bai bac
	int chiaBaiIndex = 0;
	void chiaBai(Node* sender);
	void chiaBaiAnimation(Node* sender);
	///danh bai
	int logDanhBaiIndex = -1; //Trận đầu tiên
	LuotDanh* logDanhBai[104];

	void danhBai();
	void danhBaiAnimationDone(Node* sender);
	void danhBaiAnimation();

	void drawInitPlayerStatus();
	void drawUpdatePlayerStatus();

	int danhBaiTaoLog(); //retun player đánh tiếp theo

	private://------------------------------------------------------------------
	///Kiểm tra kiểu của các quân bài được chọn
	KieuXapBo tlmnTimKieuSapBo(Card* selectedCrad[13], int selectedCradLen);

	//CPU playing:
	/// tìm quân đánh tối ưu
	BaiDanhRa *tlmnTryTimBaiDanhRa(Card* selectedCrad[13]);
	///tìm bai để đánh vòng mới
	BaiDanhRa* tlmnCpuTimBaiDanh(int player);
	///tìm bài đỡ baidanh
	BaiDanhRa* tlmnCpuTimBaiDo(BaiDanhRa *baidanh);
	///kiem tra xem bai danh có đúng không
	bool tlmnKiemTraBaiDanhRa(BaiDanhRa *baidanhra);
	///Gọi để CPU thực hiện việc select bài
	bool tlmnCpuChonBaiDanhRa(int player, int level);
	void tlmnBoLuot(int player);
	///UI
	ui::Button *btnConfig = nullptr, *btnBack = nullptr, *btnUserPlay = nullptr, *btnUserThoi = nullptr, *btnUserXep = nullptr, *btnUserBoChon = nullptr;
	///Message and S
	Label* messageBox = nullptr, *lblP1CardCount = nullptr, *lblP2CardCount = nullptr, *lblP3CardCount = nullptr;
	///Bỏ lượt overlay icon:
	Sprite *iconSkipPlayer[4], *iconWinner = nullptr;

	void EnableControls(bool state);
	//bool 
	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
};

#endif

