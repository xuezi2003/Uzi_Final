#include "Chess_Util.h"
#include <qhash.h> 
#include <qdebug.h>
QHash<int, QPair<GameRecord, int>> Chess_Util::chessTypeInfo;
QHash<GameRecord, int> Chess_Util::chessTypeValue;
QHash<Info, int> Chess_Util::StartInfo;
QHash<GameRecord, int> Chess_Util::Gamerec;
QHash<GameRecord, int> Chess_Util::chessTypeCount;
QHash<GameRecord, int> Chess_Util::chessTypeCount_Old;
int Chess_Util::Board[17][17];
Chess_Util::Chess_Util(QObject *parent)
	: QObject(parent)
{}

Chess_Util::~Chess_Util()
{}
void Chess_Util::initMap()
{
	Gamerec[Playerchess] = (StartInfo[First] == Player ? BLACK : WHITE);
	Gamerec[AIchess] = (StartInfo[First] == AI ? BLACK : WHITE);
	Gamerec[NowTurn] = (StartInfo[First] == Player ? Player : AI);
	//以下是白色棋形
	chessTypeInfo[422224] = QPair<GameRecord, int>({ WhiteHFour,1 });//活四
	chessTypeValue[WhiteHFour] = 300000;

	chessTypeInfo[122224] = QPair<GameRecord, int>({ WhiteCFour,1 });//冲四
	chessTypeInfo[422221] = QPair<GameRecord, int>({ WhiteCFour,6 });
	chessTypeInfo[522224] = QPair<GameRecord, int>({ WhiteCFour,1 });
	chessTypeInfo[422225] = QPair<GameRecord, int>({ WhiteCFour,6 });

	chessTypeInfo[4224224] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[1224221] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[5224225] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[1224225] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[5224221] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[1224224] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[4224221] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[5224224] = QPair<GameRecord, int>({ WhiteCFour,4 });
	chessTypeInfo[4224225] = QPair<GameRecord, int>({ WhiteCFour,4 });

	chessTypeInfo[4242224] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[5242225] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[4242225] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[5242224] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[1242221] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[1242225] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[5242221] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[1242224] = QPair<GameRecord, int>({ WhiteCFour,5 });
	chessTypeInfo[4242221] = QPair<GameRecord, int>({ WhiteCFour,5 });

	chessTypeInfo[5222424] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[4222425] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[4222424] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[1222421] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[5222425] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[1222424] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[4222421] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[1222425] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeInfo[5222421] = QPair<GameRecord, int>({ WhiteCFour,3 });
	chessTypeValue[WhiteCFour] = 30000;

	chessTypeInfo[4242424] = QPair<GameRecord, int>({ WhiteTThree,3 });//活三和跳三
	chessTypeInfo[4422241] = QPair<GameRecord, int>({ WhiteHThree,6 });
	chessTypeInfo[1422244] = QPair<GameRecord, int>({ WhiteHThree,2 });
	chessTypeInfo[4422245] = QPair<GameRecord, int>({ WhiteHThree,6 });
	chessTypeInfo[5422244] = QPair<GameRecord, int>({ WhiteHThree,2 });
	chessTypeInfo[4422244] = QPair<GameRecord, int>({ WhiteHThree,2 });
	chessTypeInfo[424224] = QPair<GameRecord, int>({ WhiteHThree,4 });
	chessTypeInfo[422424] = QPair<GameRecord, int>({ WhiteHThree,3 });
	chessTypeValue[WhiteHThree] = 300000;
	chessTypeValue[WhiteTThree] = 300000;

	chessTypeInfo[122244] = QPair<GameRecord, int>({ WhiteCThree,0 });//眠三
	chessTypeInfo[522244] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[442221] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[442225] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[122424] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[522424] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[422421] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[422425] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[124224] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[524224] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeInfo[124224] = QPair<GameRecord, int>({ WhiteCThree,0 });
	chessTypeValue[WhiteHThree] = 1800;

	chessTypeInfo[442244] = QPair<GameRecord, int>({ WhiteHTwo,0 });//活二
	chessTypeValue[WhiteHTwo] = 1800;

	chessTypeInfo[4222224] = QPair<GameRecord, int>({ WhiteFive,0 });//五连
	chessTypeInfo[122224] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[1222221] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[4222221] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[5222221] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[5222224] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[4222225] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[4222221] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeInfo[5222225] = QPair<GameRecord, int>({ WhiteFive,0 });
	chessTypeValue[WhiteFive] = 0x3f3f3f3f;

	chessTypeInfo[222222] = QPair<GameRecord, int>({ WhiteSix,0 });//长连为负
	chessTypeValue[WhiteSix] = -0x3f3f3f3f;

	//以下是黑色棋形
	chessTypeInfo[411114] = QPair<GameRecord, int>({ BlackHFour,1 });//活四
	chessTypeValue[BlackHFour] = 3000000;

	chessTypeInfo[211114] = QPair<GameRecord, int>({ BlackCFour,6 });//冲四
	chessTypeInfo[411112] = QPair<GameRecord, int>({ BlackCFour,6 });
	chessTypeInfo[511114] = QPair<GameRecord, int>({ BlackCFour,1 });
	chessTypeInfo[411115] = QPair<GameRecord, int>({ BlackCFour,6 });

	chessTypeInfo[4114114] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[2114112] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[5114115] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[2114115] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[5114112] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[2114114] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[4114112] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[5114114] = QPair<GameRecord, int>({ BlackCFour,4 });
	chessTypeInfo[4114115] = QPair<GameRecord, int>({ BlackCFour,4 });

	chessTypeInfo[4141114] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[5141115] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[4141115] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[5141114] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[2141112] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[2141115] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[5141112] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[2141114] = QPair<GameRecord, int>({ BlackCFour,5 });
	chessTypeInfo[4141112] = QPair<GameRecord, int>({ BlackCFour,5 });

	chessTypeInfo[5111414] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[4111415] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[4111414] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[2111412] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[5111415] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[2111414] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[4111412] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[2111415] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeInfo[5111412] = QPair<GameRecord, int>({ BlackCFour,3 });
	chessTypeValue[BlackCFour] = 80000;

	chessTypeInfo[4141414] = QPair<GameRecord, int>({ BlackTThree,3 });//活三和跳三
	chessTypeInfo[4411142] = QPair<GameRecord, int>({ BlackHThree,6 });
	chessTypeInfo[2411144] = QPair<GameRecord, int>({ BlackHThree,2 });
	chessTypeInfo[4411145] = QPair<GameRecord, int>({ BlackHThree,6 });
	chessTypeInfo[5411144] = QPair<GameRecord, int>({ BlackHThree,2 });
	chessTypeInfo[4411144] = QPair<GameRecord, int>({ BlackHThree,2 });
	chessTypeInfo[414114] = QPair<GameRecord, int>({ BlackHThree,4 });
	chessTypeInfo[411414] = QPair<GameRecord, int>({ BlackHThree,3 });
	chessTypeValue[BlackHThree] = 300000;
	chessTypeValue[BlackTThree] = 300000;

	chessTypeInfo[211144] = QPair<GameRecord, int>({ BlackCThree,0 });//眠三
	chessTypeInfo[511144] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[441112] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[441115] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[211414] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[511414] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[411412] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[411415] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[214114] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[514114] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeInfo[214114] = QPair<GameRecord, int>({ BlackCThree,0 });
	chessTypeValue[BlackHThree] = 1800;

	chessTypeInfo[441144] = QPair<GameRecord, int>({ BlackHTwo,0 });//活二
	chessTypeValue[BlackHTwo] = 1800;

	chessTypeInfo[4111114] = QPair<GameRecord, int>({ BlackFive,0 });//五连
	chessTypeInfo[1111114] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[2111112] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[4111112] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[5111112] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[5111114] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[4111115] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[4111112] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeInfo[5111115] = QPair<GameRecord, int>({ BlackFive,0 });
	chessTypeValue[BlackFive] = 0x3f3f3f3f;

	chessTypeInfo[111111] = QPair<GameRecord, int>({ BlackSix,0 });//长连为负
	chessTypeValue[BlackSix] = -0x3f3f3f3f;

}
void Chess_Util::updateRec()
{
	chessTypeCount_Old = chessTypeCount;//每次更新保存旧值
	chessTypeCount.clear();
	LL temp = 0;
	//检查行 注意范围
	for (int i = 0; i < 17; i++)
	{
		temp = 0;
		for (int j = 0; j < 17; j++)
		{
			if (i <= 12 && i >= 4 && j >= 4 && j <= 12 && Board[i][j] == Gamerec[AIchess]) Gamerec[CountAICentral]++;
			if (i <= 12 && i >= 4 && j >= 4 && j <= 12 && Board[i][j] == Gamerec[Playerchess]) Gamerec[CountPlayerCentral]++;
			temp *= 10;//一条包含边界的线
			temp += Board[i][j];

		}

		for (int k = 0; temp / 100000 > 0; k++)
		{
			int t1 = temp % 1000000;
			int t2 = temp % 10000000;
			if (chessTypeInfo.contains(t1))
			{
				chessTypeCount[chessTypeInfo[t1].first]++;//如果有这种棋形 则对应计数++
			}
			if (chessTypeInfo.contains(t2) && t2 / 1000000 > 0)
			{
				chessTypeCount[chessTypeInfo[t2].first]++;
			}
			temp /= 10;
		}
	}
	//检查列
	for (int i = 0; i < 17; i++)
	{
		temp = 0;
		for (int j = 0; j < 17; j++)
		{
			if (i <= 12 && i >= 4 && j >= 4 && j <= 12 && Board[j][i] == Gamerec[AIchess]) Gamerec[CountAICentral]++;
			if (i <= 12 && i >= 4 && j >= 4 && j <= 12 && Board[j][i] == Gamerec[Playerchess]) Gamerec[CountPlayerCentral]++;
			temp *= 10;
			temp += Board[j][i];
		}
		for (int k = 0; temp / 100000 > 0; k++)
		{
			int t1 = temp % 1000000;
			int t2 = temp % 10000000;
			if (chessTypeInfo.contains(t1))
			{
				chessTypeCount[chessTypeInfo[t1].first]++;//如果有这种棋形 则对应计数++
			}
			if (chessTypeInfo.contains(t2) && t2 / 1000000 > 0)
			{
				chessTypeCount[chessTypeInfo[t2].first]++;
			}
			temp /= 10;
		}
	}
	//检查对角线 /
	for (int i = 0; i <= 32; i++)
	{
		temp = 0;
		for (int j = i; j >= 0; j--)
		{
			if (j <= 12 && j >= 4 && -j + i >= 4 && -j + i <= 12 && Board[j][-j + i] == Gamerec[AIchess]) Gamerec[CountAICentral]++;
			if (j <= 12 && j >= 4 && -j + i >= 4 && -j + i <= 12 && Board[j][-j + i] == Gamerec[Playerchess]) Gamerec[CountPlayerCentral]++;
			if (j <= 16 && j >= 0 && -j + i >= 0 && -j + i <= 16)
			{
				temp *= 10;
				temp += Board[j][-j + i];
			}
		}
		for (; temp / 1000000 > 0;)
		{
			int t1 = temp % 1000000;
			int t2 = temp % 10000000;
			if (chessTypeInfo.contains(t1)) chessTypeCount[chessTypeInfo[t1].first]++;//如果有这种棋形 则对应计数++
			if (chessTypeInfo.contains(t2) && t2 / 1000000 > 0) chessTypeCount[chessTypeInfo[t2].first]++;
			temp /= 10;
		}
	}
	//检查对角线
	for (int i = 16; i >= -16; i--)
	{
		temp = 0;
		for (int j = 0; j + i <= 14; j++)
		{
			if (j <= 12 && j >= 4 && j + i >= 4 && j + i <= 12 && Board[j][j + i] == Gamerec[AIchess]) Gamerec[CountAICentral]++;
			if (j <= 12 && j >= 4 && j + i >= 4 && j + i <= 12 && Board[j][j + i] == Gamerec[Playerchess]) Gamerec[CountPlayerCentral]++;
			if (j <= 16 && j >= 0 && j + i >= 0 && j + i <= 16)
			{
				temp *= 10;
				temp += Board[j][j + i];
			}
		}
		for (; temp / 1000000 > 0;)
		{
			int t1 = temp % 1000000;
			int t2 = temp % 10000000;
			if (chessTypeInfo.contains(t1)) chessTypeCount[chessTypeInfo[t1].first]++;//如果有这种棋形 则对应计数++
			if (chessTypeInfo.contains(t2) && t2 / 1000000 > 0) chessTypeCount[chessTypeInfo[t2].first]++;
			temp /= 10;
		}
	}
}
//参数 模式 下的位置
int Chess_Util::checkWin(int now,int mode)//判断获胜 己方获胜条件：己方五连 对方触犯禁手
{
	int res=0;
	if (mode == 0)
	{
		//if(now==Player && Gamerec[Playerchess]==BLACK && checkForbidden(Gamerec[Playerchess])) res=2;
		/*if (now == Player && Gamerec[Playerchess] == WHITE && checkForbidden(Gamerec[Playerchess], x, y)) res = 1;
		if (now == AI && Gamerec[Playerchess] == BLACK && checkForbidden(Gamerec[Playerchess], x, y)) res = 2;
		if (now == AI && Gamerec[Playerchess] == WHITE && checkForbidden(Gamerec[Playerchess], x, y)) res = 1;*/

		if (Gamerec[Playerchess] == BLACK && chessTypeCount[BlackFive] > 0 && now == Player) res=1;
		if (Gamerec[AIchess] == BLACK && chessTypeCount[BlackFive] > 0 && now == AI) res=2;

		if (Gamerec[Playerchess] == BLACK && chessTypeCount[WhiteFive] > 0 && now == Player) res = 2;
		if (Gamerec[AIchess] == BLACK && chessTypeCount[WhiteFive] > 0 && now == AI) res = 1;

		if (Gamerec[Playerchess] == WHITE && chessTypeCount[WhiteFive] > 0 && now == Player) res=1;
		if (Gamerec[AIchess] == WHITE && chessTypeCount[WhiteFive] > 0 && now == AI) res=2;
		if (Gamerec[AIchess] == WHITE && chessTypeCount[BlackFive] > 0 && now == AI) res = 1;
		if (Gamerec[Playerchess] == WHITE && chessTypeCount[BlackFive] > 0 && now == Player) res = 2;
	}

	return res;
}

int Chess_Util::checkForbidden(int chess, int mode)//mode含义 若为0 则意为判赢时的判禁手 此时已更新 若1 则是单独判断是否触犯禁手
{
	if (checkDoubleFour(chess) ||
		checkDoubleThree(chess)||
		checkSix(chess))
	{
		return 1;
	}//判断新值是否触犯禁手
	return 0;
}

int Chess_Util::checkDoubleFour(int chess)//1 一步下出两个活四 0 没有
{
	if (chess == BLACK && chessTypeCount[BlackHFour] + chessTypeCount[BlackCFour]-(chessTypeCount_Old[BlackHFour] + chessTypeCount_Old[BlackCFour]) >= 2) { return 1; };
	if (chess == WHITE && chessTypeCount[WhiteHFour] + chessTypeCount[WhiteCFour] - (chessTypeCount_Old[WhiteHFour] + chessTypeCount_Old[WhiteCFour]) >= 2) { return 1; };
	return 0;
}

int Chess_Util::checkDoubleThree(int chess)//1 一步下出两个活三 0 没有
{
	
	if (chess == BLACK && chessTypeCount[BlackHThree]-chessTypeCount_Old[BlackHThree]>= 2) {  return 1; };
	if (chess == WHITE && chessTypeCount[WhiteHThree]-chessTypeCount_Old[WhiteHThree] >= 2) {   return 1; };
	return 0;
}

int Chess_Util::checkFourThree(int chess)//1 一步同时一个四和一个三 0 没有
{
	if (chess == BLACK && chessTypeCount[BlackCFour] + chessTypeCount[BlackHFour] - (chessTypeCount_Old[BlackCFour] + chessTypeCount_Old[BlackHFour]) >= 1 && chessTypeCount[BlackHThree] - chessTypeCount_Old[BlackHThree] >= 1) { return 1; };
	if (chess == WHITE && chessTypeCount[WhiteCFour] + chessTypeCount[WhiteHFour] - (chessTypeCount_Old[WhiteCFour] + chessTypeCount_Old[WhiteHFour]) >= 1 && chessTypeCount[WhiteHThree] - chessTypeCount_Old[WhiteHThree] >= 1) { return 1; };
	return 0;
}

int Chess_Util::checkSix(int chess)//1 触犯 0 未触犯
{
	if (chess == BLACK) return chessTypeCount[BlackSix]>0;
	else return chessTypeCount[WhiteSix] > 0;
}

void Chess_Util::showInfo()
{
	system("cls");
	qDebug() << "PlayerChess:" << (Gamerec[Playerchess] == BLACK ? "BLACK" : "WHITE") << "AIChess:" << (Gamerec[AIchess] == BLACK ? "BLACK" : "WHITE");
	qDebug() << "NowTurn:" << (Gamerec[NowTurn] == Player ? "Player" : "AI");
	qDebug() << "BLACKHFour" << chessTypeCount[BlackHFour] << "BLACKCFour" << chessTypeCount[BlackCFour];
	qDebug() << "WhiteHFour" << chessTypeCount[WhiteHFour] << "WhiteCFour" << chessTypeCount[WhiteCFour];
	qDebug() << "BLACKHThree" << chessTypeCount[BlackHThree] << "BLACKCThree" << chessTypeCount[BlackCThree];
	qDebug() << "WhiteHThree" << chessTypeCount[WhiteHThree] << "WhiteCThree" << chessTypeCount[WhiteCThree];


}
