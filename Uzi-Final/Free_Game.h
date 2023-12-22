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
class Free_Game : public Game
{
	Q_OBJECT

public:
	Free_Game(const QHash<Info, int>& startInfo, QWidget* parent = nullptr);
	Free_Game() {}
	~Free_Game();

private:
	QThreadPool* threadpool;
	Ui::Assigned_GameClass ui;
	QPair<int, LL> bestPos;
	void dealwithWin(int winner);
	const int Threadnum = 5;
	QMutex mutex;
	// Í¨¹ý Game ¼Ì³Ð
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void playerTurn() override;
	virtual void AITurn();
private slots:
	void Regret();
	void Pass();
	void receiveRes(QPair<int, LL> res);
	void showLabel();
};