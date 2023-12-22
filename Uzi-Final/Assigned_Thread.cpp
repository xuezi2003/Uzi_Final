#include "Assigned_Thread.h"
#include <qhash.h>
#include <qdebug.h>
static int max = 0;
Assigned_Thread::Assigned_Thread()
{
	setAutoDelete(true);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
			boardOfThread[i][j] = Chess_Util::Board[i][j];
	}
	GamerecOfThread = new  QHash<GameRecord, int>(Chess_Util::Gamerec);
	chessTypeCountOfThread = new  QHash<GameRecord, int>(Chess_Util::chessTypeCount);
	chessTypeCount_OldOfThread = new  QHash<GameRecord, int>(Chess_Util::chessTypeCount_Old);
}

Assigned_Thread::~Assigned_Thread()
{
	delete GamerecOfThread;
	delete chessTypeCountOfThread;
	delete chessTypeCount_OldOfThread;
}

Assigned_Thread::Assigned_Thread(int mode,QList<int> Poss)
{
	setAutoDelete(true);
	this->mode = mode;
	this->Poss = Poss;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
			boardOfThread[i][j] = Chess_Util::Board[i][j];
	}
	GamerecOfThread = new  QHash<GameRecord, int>(Chess_Util::Gamerec);
	chessTypeCountOfThread = new  QHash<GameRecord, int>(Chess_Util::chessTypeCount);
	chessTypeCount_OldOfThread = new  QHash<GameRecord, int>(Chess_Util::chessTypeCount_Old);
}

void Assigned_Thread::run()
{
	int drop=-1;
	system("cls");
	LL res=minMaxSearch(INT_MIN, INT_MAX, drop, 1, Chess_Util::Gamerec[X] * 100 + Chess_Util::Gamerec[Y]);
	qDebug() <<drop<< res;
	QPair<int, LL> ans(drop, res);
	emit Drop(ans);
}
//��ʼstepΪ1 ����AI ˫��Player
LL Assigned_Thread::minMaxSearch(int a,int b,int &x,int step,int drop)//�����ֱ�Ϊ�����·�Χ ��������λ�� ��ǰ���� ��һ���µ�λ��
{
	//����������������ָ����� ��Ҵ������� ĳһ����ʤ ��������
	//����ʱ���ص�ǰ�����ֵ
	int bestValue = (step % 2 == 1 ? INT_MIN : INT_MAX);

	QList<int> Positions;
	int res=0;
	if(step>1)
	{
		//step==1 ѡ��ai�����µ�λ�� ֮����Ǽ����һ��Ľ�� ��step==3 ��ʱ�����һ��player
		if (step % 2 == 1 && (*GamerecOfThread)[Playerchess] == BLACK) res = Chess_Util::checkForbidden((*GamerecOfThread)[Playerchess], chessTypeCountOfThread, chessTypeCount_OldOfThread, 1);
		if(step % 2 == 1 && (*GamerecOfThread)[Playerchess] == BLACK&&res==1) 
		{
			return eval(2, Player);
		}
		if ((step % 2 == 1 && res == 0)||(step%2==0)) res = Chess_Util::checkWin(step % 2 == 1 ? Player:AI, boardOfThread, GamerecOfThread, chessTypeCountOfThread);
		if (step > 7 || res) 
		{
			return eval(res, step % 2 == 1 ? Player : AI);
		}
	}
		
	if (mode == 1 && step == 1) 
	{
		Positions = Poss;
	}
	else Positions = getAvailablePos(drop/100,drop%100, step % 2 == 1?AI:Player);//������һ�ֵ�λ�ø�����ѡλ��
	if(Positions.isEmpty()) return eval(Chess_Util::checkWin(step % 2 == 1 ? AI : Player, boardOfThread, GamerecOfThread, chessTypeCountOfThread) , step % 2 == 1 ? Player : AI);

	int PreX = drop / 100;int PreY= drop % 100;

	std::sort(Positions.begin(), Positions.end(), [&](const int& p1, const int& p2) {
		double x1 = sqrt((double)pow(PreX - p1 / 100, 2) + pow(PreY - p1 % 100, 2));
		double x2 = sqrt((double)pow(PreX - p2 / 100, 2) + pow(PreY - p2 % 100, 2));
		return x1 < x2;
		});//����ѡλ�ý������� ��������ʱ������һ�����ӵľ��� �����ǵ�һ����
	for (int i=0; i<Positions.size(); i++) 
	{
		int pos = Positions[i];
		
		boardOfThread[pos / 100][pos % 100] = (step % 2 == 1 ? (*GamerecOfThread)[AIchess] : (*GamerecOfThread)[Playerchess]);
		Chess_Util::updateRec(boardOfThread,GamerecOfThread,chessTypeCountOfThread,chessTypeCount_OldOfThread);
		
		int newValue = minMaxSearch(a, b, x, step + 1, pos);
		boardOfThread[pos / 100][pos % 100] = BLANK;
		
		if (step % 2 == 1)
		{
			if (bestValue < newValue)
			{
				bestValue = newValue;
				a = qMax(bestValue, a);
				if (step == 1) x = pos;
				if (a >= b) break;
			}
		}
		else
		{
			if (bestValue > newValue)
			{
				bestValue = newValue;
				b = qMin(bestValue, b);
				if (a >= b) break;
			}
		}
	}
	return bestValue;
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
		if (res == 1) return -2*INFINITY;
		else if (res == 2) return INFINITY;
		else if (res == 0)
		{
			if (Chess_Util::Gamerec[Playerchess] == BLACK)
				return -((*chessTypeCountOfThread)[BlackHFour] * Chess_Util::chessTypeValue[BlackHFour]
					+ (*chessTypeCountOfThread)[BlackCFour] * Chess_Util::chessTypeValue[BlackCFour]
					+ (*chessTypeCountOfThread)[BlackHThree] * Chess_Util::chessTypeValue[BlackHThree]
					+ (*chessTypeCountOfThread)[BlackTThree] * Chess_Util::chessTypeValue[BlackTThree]
					+ (*chessTypeCountOfThread)[BlackCThree] * Chess_Util::chessTypeValue[BlackCThree]
					+ (*chessTypeCountOfThread)[BlackHTwo] * Chess_Util::chessTypeValue[BlackHTwo]) * 10
				+ ((*chessTypeCountOfThread)[WhiteHFour] * Chess_Util::chessTypeValue[WhiteHFour]
					+ (*chessTypeCountOfThread)[WhiteCFour] * Chess_Util::chessTypeValue[WhiteCFour]
					+ (*chessTypeCountOfThread)[WhiteHThree] * Chess_Util::chessTypeValue[WhiteHThree]
					+ (*chessTypeCountOfThread)[WhiteTThree] * Chess_Util::chessTypeValue[WhiteTThree]
					+ (*chessTypeCountOfThread)[WhiteCThree] * Chess_Util::chessTypeValue[WhiteCThree]
					+ (*chessTypeCountOfThread)[WhiteHTwo] * Chess_Util::chessTypeValue[WhiteHTwo]);
			else
				return ((*chessTypeCountOfThread)[BlackHFour] * Chess_Util::chessTypeValue[BlackHFour]
					+ (*chessTypeCountOfThread)[BlackCFour] * Chess_Util::chessTypeValue[BlackCFour]
					+ (*chessTypeCountOfThread)[BlackHThree] * Chess_Util::chessTypeValue[BlackHThree]
					+ (*chessTypeCountOfThread)[BlackTThree] * Chess_Util::chessTypeValue[BlackTThree]
					+ (*chessTypeCountOfThread)[BlackCThree] * Chess_Util::chessTypeValue[BlackCThree]
					+ (*chessTypeCountOfThread)[BlackHTwo] * Chess_Util::chessTypeValue[BlackHTwo])
				- ((*chessTypeCountOfThread)[WhiteHFour] * Chess_Util::chessTypeValue[WhiteHFour]
					+ (*chessTypeCountOfThread)[WhiteCFour] * Chess_Util::chessTypeValue[WhiteCFour]
					+ (*chessTypeCountOfThread)[WhiteHThree] * Chess_Util::chessTypeValue[WhiteHThree]
					+ (*chessTypeCountOfThread)[WhiteTThree] * Chess_Util::chessTypeValue[WhiteTThree]
					+ (*chessTypeCountOfThread)[WhiteCThree] * Chess_Util::chessTypeValue[WhiteCThree]
					+ (*chessTypeCountOfThread)[WhiteHTwo] * Chess_Util::chessTypeValue[WhiteHTwo] ) * 10;
		}
}

QList<int> Assigned_Thread::getAvailablePos(int x,int y,int now)//����ÿһ��ģ���µ�λ�� ����ʱ��x y
{
	
	int U=0, D=0, L=0, R=0;
	QList<int> res;
	if ((*GamerecOfThread)[CountTotal] == 225) return res;//������ ���ؿ�����
	range(U, D, L, R, x, y,now);
	for (int i = U; i <= D; i++)
	{
		for (int j = L; j <= R; j++)
		{
			if (boardOfThread[i][j] == BLANK)
			{
				int nowchess = (now == Player ? Chess_Util::Gamerec[Playerchess] : Chess_Util::Gamerec[AIchess]);
				boardOfThread[i][j] = nowchess;//�жϴ˲��Ƿ������
				Chess_Util::updateRec(boardOfThread, (GamerecOfThread), (chessTypeCountOfThread),(chessTypeCount_OldOfThread));
				if (nowchess == (*GamerecOfThread)[AIchess] &&nowchess==BLACK&& Chess_Util::checkForbidden(nowchess, (chessTypeCountOfThread),(chessTypeCount_OldOfThread), 1))//�˴��ǵ���ʹ��check
				{
					boardOfThread[i][j] = BLANK;
					continue;
				}
				res.append(i*100+j);
				boardOfThread[i][j] = BLANK;//�ָ�
				Chess_Util::updateRec(boardOfThread, GamerecOfThread, (chessTypeCountOfThread),(chessTypeCount_OldOfThread));
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
				if (boardOfThread[i][j] == BLANK)
				{
					int nowchess = (now == Player ? Chess_Util::Gamerec[Playerchess] : Chess_Util::Gamerec[AIchess]);
					boardOfThread[i][j] = nowchess;//�жϴ˲��Ƿ������
					Chess_Util::updateRec(boardOfThread, (GamerecOfThread), (chessTypeCountOfThread),( chessTypeCount_OldOfThread));
					if (nowchess ==(*GamerecOfThread)[AIchess] && nowchess == BLACK && Chess_Util::checkForbidden(nowchess, (chessTypeCountOfThread), (chessTypeCount_OldOfThread), 1))//�˴��ǵ���ʹ��check
					{
						boardOfThread[i][j] = BLANK;
						continue;
					}
					count++;
					boardOfThread[i][j] = BLANK;//�ָ�
					Chess_Util::updateRec(boardOfThread, (GamerecOfThread), (chessTypeCountOfThread),( chessTypeCount_OldOfThread));
				}
				
			}
		}
		if (count-1 <= (R-L+1) * (D-U+1) * 0.5) r++;
		else break;
	}
}