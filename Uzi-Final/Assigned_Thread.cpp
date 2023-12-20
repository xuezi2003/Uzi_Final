#include "Assigned_Thread.h"
#include <qhash.h>
#include <qdebug.h>
Assigned_Thread::Assigned_Thread()
{
	setAutoDelete(true);
}

Assigned_Thread::Assigned_Thread(int mode,QList<int> Fifth)
{
	setAutoDelete(true);
	this->mode = mode;
	this->Fifth = Fifth;
}

void Assigned_Thread::run()
{
	int drop=-1;
	minMaxSearch(INT_MIN, INT_MAX, drop, 1, Chess_Util::Gamerec[X] * 100 + Chess_Util::Gamerec[Y]);
	emit Drop(QString::number(drop));
}
//初始step为1 单数AI 双数Player
LL Assigned_Thread::minMaxSearch(int a,int b,int &x,int step,int drop)//参数分别为α，β范围 最终落子位置 当前层数 上一层下的位置
{
	//结束的条件：超过指定深度 玩家触犯禁手 某一方获胜 棋盘下满
	//结束时返回当前棋面估值
	int bestValue = (step % 2 == 1 ? INT_MIN : INT_MAX);
	QList<int> Positions;
	int res=0;
	if(step>1)
	{
		if (Chess_Util::Gamerec[Playerchess] == BLACK) res = Chess_Util::checkForbidden(Chess_Util::Gamerec[Playerchess], 1);
		if(res==0) res = Chess_Util::checkWin(step % 2 == 1 ? Player : AI);
		if (step > 5 || res) return eval(res, step % 2 == 1 ? Player : AI);
	}
		
	if (mode == 1 && step == 1) 
	{
		Positions = Fifth;
		qDebug() << "fifth";
	}
	else Positions = getAvailablePos(drop/100,drop%100, step % 2 == 1?Player:AI);//依据上一轮的位置给出可选位置
	if(Positions.isEmpty()) return eval(Chess_Util::checkWin(step % 2 == 1 ? Player : AI), step % 2 == 1 ? Player : AI);

	int PreX = drop / 100;int PreY= drop % 100;

	std::sort(Positions.begin(), Positions.end(), [&](const int& p1, const int& p2) {
		double x1 = sqrt((double)pow(PreX - p1 / 100, 2) + pow(PreY - p1 % 100, 2));
		double x2 = sqrt((double)pow(PreX - p2 / 100, 2) + pow(PreY - p2 % 100, 2));
		return x1 < x2;
		});//对所选位置进行排序 排序依据时距离上一步棋子的距离 或者是第一步？
	
	for (int i=0; i<Positions.size(); i++) 
	{
		int pos = Positions[i];
		
		Chess_Util::Board[pos / 100][pos % 100] = (step % 2 == 1 ? Chess_Util::Gamerec[AIchess] : Chess_Util::Gamerec[Playerchess]);
		Chess_Util::Gamerec[Tempx] = pos / 100; Chess_Util::Gamerec[Tempx] = pos % 100;
		Chess_Util::updateRec();
		int newValue = minMaxSearch(a, b, x, step + 1, pos);
		Chess_Util::Board[pos / 100][pos % 100] = BLANK;
		
		if (step % 2 == 1)
		{
			if (bestValue < newValue)
			{
				bestValue = newValue;
				a = qMax(bestValue, a);
				if (step == 1) x = pos;
				
				if (a >= b)
				{
					break;
				}
			}
		}
		else
		{
			if (bestValue > newValue)
			{
				bestValue = newValue;
				b = qMin(bestValue, b);
				if (a >= b) 
				{
					break;
				}
			}
		}
	}
	return (step % 2 == 1 ? a : b);
}
//destroy family
void Assigned_Thread::destroy()
{

}

void Assigned_Thread::destroyHThree()
{

}

void Assigned_Thread::destroyHFour()
{

}

void Assigned_Thread::destroyDoubleThree()
{

}

void Assigned_Thread::destroyDoubleFour()
{

}

void Assigned_Thread::destroyFourThree()
{

}

LL Assigned_Thread::eval(int res,int now)
{
		if (res == 1) return -INFINITY;
		else if (res == 2) return INFINITY;
		else if (res == 0)
		{
			if (Chess_Util::Gamerec[Playerchess] == BLACK)
				return -(Chess_Util::chessTypeCount[BlackHFour] * Chess_Util::chessTypeValue[BlackHFour]
					+ Chess_Util::chessTypeCount[BlackCFour] * Chess_Util::chessTypeValue[BlackCFour]
					+ Chess_Util::chessTypeCount[BlackHThree] * Chess_Util::chessTypeValue[BlackHThree]
					+ Chess_Util::chessTypeCount[BlackTThree] * Chess_Util::chessTypeValue[BlackTThree]
					+ Chess_Util::chessTypeCount[BlackCThree] * Chess_Util::chessTypeValue[BlackCThree]
					+ Chess_Util::chessTypeCount[BlackHTwo] * Chess_Util::chessTypeValue[BlackHTwo]) * 3
				+ (Chess_Util::chessTypeCount[WhiteHFour] * Chess_Util::chessTypeValue[WhiteHFour]
					+ Chess_Util::chessTypeCount[WhiteCFour] * Chess_Util::chessTypeValue[WhiteCFour]
					+ Chess_Util::chessTypeCount[WhiteHThree] * Chess_Util::chessTypeValue[WhiteHThree]
					+ Chess_Util::chessTypeCount[WhiteTThree] * Chess_Util::chessTypeValue[WhiteTThree]
					+ Chess_Util::chessTypeCount[WhiteCThree] * Chess_Util::chessTypeValue[WhiteCThree]
					+ Chess_Util::chessTypeCount[WhiteHTwo] * Chess_Util::chessTypeValue[WhiteHTwo]);
			else
				return (Chess_Util::chessTypeCount[BlackHFour] * Chess_Util::chessTypeValue[BlackHFour]
					+ Chess_Util::chessTypeCount[BlackCFour] * Chess_Util::chessTypeValue[BlackCFour]
					+ Chess_Util::chessTypeCount[BlackHThree] * Chess_Util::chessTypeValue[BlackHThree]
					+ Chess_Util::chessTypeCount[BlackTThree] * Chess_Util::chessTypeValue[BlackTThree]
					+ Chess_Util::chessTypeCount[BlackCThree] * Chess_Util::chessTypeValue[BlackCThree]
					+ Chess_Util::chessTypeCount[BlackHTwo] * Chess_Util::chessTypeValue[BlackHTwo])
				- (Chess_Util::chessTypeCount[WhiteHFour] * Chess_Util::chessTypeValue[WhiteHFour]
					+ Chess_Util::chessTypeCount[WhiteCFour] * Chess_Util::chessTypeValue[WhiteCFour]
					+ Chess_Util::chessTypeCount[WhiteHThree] * Chess_Util::chessTypeValue[WhiteHThree]
					+ Chess_Util::chessTypeCount[WhiteTThree] * Chess_Util::chessTypeValue[WhiteTThree]
					+ Chess_Util::chessTypeCount[WhiteCThree] * Chess_Util::chessTypeValue[WhiteCThree]
					+ Chess_Util::chessTypeCount[WhiteHTwo] * Chess_Util::chessTypeValue[WhiteHTwo]) * 3;
		}
}

QList<int> Assigned_Thread::getAvailablePos(int x,int y,int now)//这是每一次模拟下的位置 是临时的x y
{
	
	int U=0, D=0, L=0, R=0;
	QList<int> res;
	if (Chess_Util::Gamerec[CountTotal] == 225) return res;//已下满 返回空容器
	range(U, D, L, R, x, y,now);
	for (int i = U; i <= D; i++)
	{
		for (int j = L; j <= R; j++)
		{
			if (Chess_Util::Board[i][j] == BLANK)
			{
				int nowchess = (now == Player ? Chess_Util::Gamerec[Playerchess] : Chess_Util::Gamerec[AIchess]);
				Chess_Util::Board[i][j] = nowchess;//判断此步是否可以下
				Chess_Util::updateRec();
				if (nowchess == BLACK && Chess_Util::checkForbidden(nowchess, 1))//此处是单独使用check
				{
					Chess_Util::Board[i][j] = BLANK;
					continue;
				}
				res.append(i*100+j);
				Chess_Util::Board[i][j] = BLANK;//恢复
				Chess_Util::updateRec();
			}
		}
	}
	return res;
}

void Assigned_Thread::range(int& U, int& D, int& L, int& R,int x,int y,int now)
{
	int r = 1;
	while (true)
	{
		int count = 0;
		L = y - r >= 1 ? y - r : 1;
		R = y + r <= 15 ? y + r : 15;
		U = x - r >= 1 ? x - r : 1;
		D = x + r <= 15 ? x + r : 15;
		for (int i = U; i <= D; i++)
		{
			for (int j = L; j <= R; j++)
			{
				if (Chess_Util::Board[i][j] == BLANK) 
				{
					int nowchess = (now == Player ? Chess_Util::Gamerec[Playerchess] : Chess_Util::Gamerec[AIchess]);
					Chess_Util::Board[i][j] = nowchess;//判断此步是否可以下
					Chess_Util::updateRec();
					if (nowchess == BLACK && Chess_Util::checkForbidden(nowchess,1))//此处是单独使用check
					{
						Chess_Util::Board[i][j] = BLANK;
						continue;
					}
					count++;
					Chess_Util::Board[i][j] = BLANK;//恢复
					Chess_Util::updateRec();
				}
				
			}
		}
		if (count-1 < (R-L+1) * (D-U+1) * 0.5) r++;
		else break;
	}
}

