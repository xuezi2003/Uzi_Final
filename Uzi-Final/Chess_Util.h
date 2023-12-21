#pragma once

#include <QObject>
using LL = long long;
enum GameRecord
{
	BLACK = 1,
	WHITE = 2,
	Red = 3,//红棋代表五手N打时的位置
	BLANK = 4,
	Edge = 5,

	Playerchess,
	AIchess,
	NowTurn,

	Tempx,
	Tempy,
	X,
	Y,

	CountPlayer,
	CountAI,
	CountTotal,
	CountAICentral,
	CountPlayerCentral,

	BlackHTwo,
	BlackTThree,
	BlackHThree,
	WhiteCThree,
	BlackCThree,
	BlackHFour,
	BlackCFour,
	BlackFive,
	BlackSix,
	WhiteHTwo,
	WhiteHThree,
	WhiteTThree,
	WhiteHFour,
	WhiteCFour,
	WhiteFive,
	WhiteSix,
};
enum Info
{
	Mode,
	First,
	FiveN,
	FirstThree,
	Assigned,
	Free,
	Player,
	AI
};
class Chess_Util  : public QObject
{
	Q_OBJECT

public:
	Chess_Util(QObject *parent);
	~Chess_Util();
	static QHash<int, QPair<GameRecord, int> > chessTypeInfo;//存储棋形以及对应的分数 截断位置 不变
	static QHash<GameRecord, int> chessTypeValue;//记录每种棋形value 不变
	static QHash<Info, int> StartInfo;//存储开局信息 先手 五手N打 开局三子 不变
	static QHash<GameRecord, int> Gamerec;//存储游戏中信息 双方执棋 当前棋手
	static QHash<GameRecord, int> chessTypeCount;//记录每种棋形数量
	static QHash<GameRecord, int> chessTypeCount_Old;//记录每种棋形数量
	static void initMap();
	static void updateRec();
	static int checkWin(int now,int mode=0 );
	static int checkForbidden(int chess,int mode=0);
	static int checkDoubleFour(int chess);
	static int checkDoubleThree(int chess);
	static int checkFourThree(int chess);
	static int checkSix(int chess);
	//thread专用重载版本
	static void updateRec(const int board[17][17], QHash<GameRecord, int> *rec, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkWin(int now, const int board[17][17], QHash<GameRecord, int> *rec, QHash<GameRecord, int> *Count, int mode = 0);
	static int checkForbidden(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old,int mode = 0);
	static int checkDoubleFour(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkDoubleThree(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkFourThree(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkSix(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);

	static int Board[17][17];//增加边界 因为有棋形的判断在边界上 主要为冲 边界特别设置为5
	static void showInfo();
};
