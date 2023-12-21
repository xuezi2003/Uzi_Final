#pragma once

#include <QWidget>
#include "ui_Assigned_Game.h"
#include "Game.h"
#include "Chess_Util.h"
#include "PrePage.h"
#include <qthreadpool.h>
#include <qhash.h>
#include "Assigned_Thread.h"
#include "qmutex.h"
class Assigned_Game : public Game
{
	Q_OBJECT

public:
	Assigned_Game(const QHash<Info, int>& startInfo, QWidget *parent = nullptr);
	Assigned_Game() {}
	~Assigned_Game();

private:
	QThreadPool* threadpool;
	Ui::Assigned_GameClass ui;
	int CountFifthN = 0;
	int countThread;
	QPair<int, LL> bestPos;
	bool isSimulate=false;
	void dealwithWin(int winner);
	void set_First_Three();
	void exchange_In_Three();
	void FifthN();
	const int Threadnum = 4;
	QMutex mutex;
	QList<int> Fifth;
	// Í¨¹ý Game ¼Ì³Ð
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void playerTurn() override;
	virtual void AITurn();
private slots:
    void receiveRes(QPair<int,LL> res);
	void exclude(QPair<int, LL> res);
};
