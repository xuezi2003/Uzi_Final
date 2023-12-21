#pragma once

#include <QObject>
using LL = long long;
enum GameRecord
{
	BLACK = 1,
	WHITE = 2,
	Red = 3,//�����������N��ʱ��λ��
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
	static QHash<int, QPair<GameRecord, int> > chessTypeInfo;//�洢�����Լ���Ӧ�ķ��� �ض�λ�� ����
	static QHash<GameRecord, int> chessTypeValue;//��¼ÿ������value ����
	static QHash<Info, int> StartInfo;//�洢������Ϣ ���� ����N�� �������� ����
	static QHash<GameRecord, int> Gamerec;//�洢��Ϸ����Ϣ ˫��ִ�� ��ǰ����
	static QHash<GameRecord, int> chessTypeCount;//��¼ÿ����������
	static QHash<GameRecord, int> chessTypeCount_Old;//��¼ÿ����������
	static void initMap();
	static void updateRec();
	static int checkWin(int now,int mode=0 );
	static int checkForbidden(int chess,int mode=0);
	static int checkDoubleFour(int chess);
	static int checkDoubleThree(int chess);
	static int checkFourThree(int chess);
	static int checkSix(int chess);
	//threadר�����ذ汾
	static void updateRec(const int board[17][17], QHash<GameRecord, int> *rec, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkWin(int now, const int board[17][17], QHash<GameRecord, int> *rec, QHash<GameRecord, int> *Count, int mode = 0);
	static int checkForbidden(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old,int mode = 0);
	static int checkDoubleFour(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkDoubleThree(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkFourThree(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);
	static int checkSix(int chess, QHash<GameRecord, int> *Count, QHash<GameRecord, int> *Count_Old);

	static int Board[17][17];//���ӱ߽� ��Ϊ�����ε��ж��ڱ߽��� ��ҪΪ�� �߽��ر�����Ϊ5
	static void showInfo();
};
