#pragma once

#include <QObject>
#include <qthread.h>
#include <qrunnable.h>
#include "Chess_Util.h"
#include <qhash.h>
using LL = long long;
class Assigned_Thread  : public QObject,public QRunnable
{
	Q_OBJECT

public:
	Assigned_Thread();
	~Assigned_Thread();
	Assigned_Thread(int mode, QList<int> poss);
	void run();
	LL minMaxSearch(int a, int b, int& x, int step,int drop);

	void destroy();
	void destroyHThree();
	void destroyHFour();
	void destroyDoubleThree();
	void destroyDoubleFour();
	void destroyFourThree();

	LL eval(int res,int now);
	QList<int> getAvailablePos(int x,int y,int now);
	void range(int& U, int& D, int& L, int& R, int x, int y, int now);

	QHash<GameRecord, int> *GamerecOfThread;
	QHash<GameRecord, int> *chessTypeCountOfThread;
	QHash<GameRecord, int> *chessTypeCount_OldOfThread;

private:
	int mode=0;//0 普通模式 1 五手n打
	QList<int> Poss;
	int boardOfThread[17][17];
signals:
	void Drop(QPair<int,LL> res);
    void rePaint();
};
