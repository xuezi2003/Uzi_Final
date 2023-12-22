#include "Game.h"

Game::Game(const QHash<Info, int>& startInfo, QWidget* parent) :QWidget(parent)
{
	
	Chess_Util::StartInfo = startInfo;
	Chess_Util::initMap();
	ui.setupUi(this);
}

Game::~Game()
{}
QList<int> Game::getAvailablePos(int x, int y, int now)//这是每一次模拟下的位置 是临时的x y
{

	int U = 0, D = 0, L = 0, R = 0;
	QList<int> res;
	if (Chess_Util::Gamerec[CountTotal] == 225) return res;//已下满 返回空容器
	range(U, D, L, R, x, y, now);
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
				res.append(i * 100 + j);
				Chess_Util::Board[i][j] = BLANK;//恢复
				Chess_Util::updateRec();
			}
		}
	}
	return res;
}

void Game::range(int& U, int& D, int& L, int& R, int x, int y, int now)
{
	int r = 2;
	if (Chess_Util::Gamerec[CountTotal] < 8) r = 1;
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
					if (nowchess == BLACK && Chess_Util::checkForbidden(nowchess, 1))//此处是单独使用check
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
		if (count - 1 <= (R - L + 1) * (D - U + 1) * 0.5) r++;
		else break;
	}
}