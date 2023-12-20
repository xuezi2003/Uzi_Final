#pragma once

#include <QWidget>
#include "ui_Assigned_Game.h"
#include "Game.h"
#include "Chess_Util.h"
#include "PrePage.h"
#include <qthreadpool.h>
#include <qhash.h>
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
	bool isSimulate=false;
	void dealwithWin(int winner);
	void set_First_Three();
	void exchange_In_Three();
	void FifthN();
	
	QList<int> Fifth;
	// Í¨¹ý Game ¼Ì³Ð
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void playerTurn() override;
	virtual void AITurn();
private slots:
    void receiveRes(QString res);
	void exclude(QString res);
};
