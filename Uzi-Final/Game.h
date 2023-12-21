#pragma once

#include <QWidget>
#include "ui_Game.h"
#include "PrePage.h"
#include "Chess_Util.h"
#include <qpair.h>
#include <iostream>
using LL = long long;
class Game : public QWidget
{
	Q_OBJECT

public:
	Game(const QHash<Info, int>& startInfo,QWidget *parent = nullptr);
	Game(){}
	~Game();
	virtual void mousePressEvent(QMouseEvent* event)=0;
	virtual void paintEvent(QPaintEvent* event)=0;
	virtual void playerTurn()=0;
	virtual void AITurn()=0;
	QList<int> getAvailablePos(int x, int y, int now);
	void range(int& U, int& D, int& L, int& R, int x, int y, int now);
private:
	Ui::GameClass ui;
};
