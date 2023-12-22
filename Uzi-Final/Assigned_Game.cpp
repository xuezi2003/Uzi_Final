#include "Assigned_Game.h"
#include <qpainter.h>
#include "QMouseEvent"
#include "qpaintevent"
#include "Assigned_Thread.h"
#include <qmessagebox.h>
#include <qmovie.h>
Assigned_Game::Assigned_Game(const QHash<Info, int>& startInfo, QWidget *parent):Game(startInfo)
{
    //初始化界面
    QPixmap pixmap(":/new/game/Resource/background.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    setPalette(palette);
	ui.setupUi(this);
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++) Chess_Util::Board[i][j] = BLANK;
    }
    for (int i = 0; i < 17; i++) 
    {
        Chess_Util::Board[0][i] = Edge;
        Chess_Util::Board[16][i] = Edge;
        Chess_Util::Board[i][0] = Edge;
        Chess_Util::Board[i][16] = Edge;
    }//将边界初始化为edge 则真正棋盘数组范围是1~15
    QMovie* timg = new QMovie(":/new/game/Resource/thinking.gif");
    ui.Thinking_img->setMovie(timg);
    timg->start();
    ui.Regret_Btn->setEnabled(false);
    threadpool = QThreadPool::globalInstance();
    showLabel();
    bestPos = QPair<int, LL>(-1, -10*INFINITY);
    countThread = Threadnum;
    connect(ui.Regret_Btn, &QPushButton::clicked, this, &Assigned_Game::Regret);
    connect(ui.Pass_Btn, &QPushButton::clicked, this, &Assigned_Game::Regret);
    set_First_Three();//指定前三步的位置
}

Assigned_Game::~Assigned_Game()
{}
void Assigned_Game::Regret()
{
    int r1=Chess_Util::Track.takeLast();
    int r2 = Chess_Util::Track.takeLast();
    Chess_Util::Board[r1 / 100][r1 % 100] = BLANK;
    Chess_Util::Board[r2 / 100][r2 % 100] = BLANK;
    Chess_Util::Gamerec[CountAI]--;
    Chess_Util::Gamerec[CountPlayer]--;
    Chess_Util::Gamerec[CountTotal]--;
    Chess_Util::updateRec();
    repaint();
    showLabel();
}

void Assigned_Game::dealwithWin(int winner)
{
    if (winner == 1) QMessageBox::information(nullptr, "Game over", "Player win");
    else if (winner == 2) QMessageBox::information(nullptr, "Game over", "AI win");
}

void Assigned_Game::set_First_Three()
{
    Chess_Util::Board[8][8] = BLACK;
    switch (Chess_Util::StartInfo[FirstThree])
    {
    case 0:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[6][8] = BLACK;
        Chess_Util::Gamerec[X] = 6; Chess_Util::Gamerec[Y] = 8;
        break;
    case 1:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[6][9] = BLACK;
        Chess_Util::Gamerec[X] = 6; Chess_Util::Gamerec[Y] = 9;
        break;
    case 2:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[6][10] = BLACK;
        Chess_Util::Gamerec[X] = 6; Chess_Util::Gamerec[Y] = 10;
        break;
    case 3:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[7][9] = BLACK;
        Chess_Util::Gamerec[X] = 7; Chess_Util::Gamerec[Y] = 9;
        break;
    case 4:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[7][10] = BLACK;
        Chess_Util::Gamerec[X] = 7; Chess_Util::Gamerec[Y] = 10;
        break;
    case 5:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[8][9] = BLACK;
        Chess_Util::Gamerec[X] = 8; Chess_Util::Gamerec[Y] = 9;
        break;
    case 6:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[8][10] = BLACK;
        Chess_Util::Gamerec[X] = 8; Chess_Util::Gamerec[Y] =10;
        break;
    case 7:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[9][8] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] =8;
        break;
    case 8:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[9][9] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] = 9;
        break;
    case 9:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[9][10] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] =10;
        break;
    case 10:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[10][8] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 8;
        break;
    case 11:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[10][9] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] =9;
        break;
    case 12:
        Chess_Util::Board[7][8] = WHITE;
        Chess_Util::Board[10][10] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 10;
        break;
    case 13:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[6][10] = BLACK;
        Chess_Util::Gamerec[X] = 6; Chess_Util::Gamerec[Y] = 10;
        break;
    case 14:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[7][10] = BLACK;
        Chess_Util::Gamerec[X] = 7; Chess_Util::Gamerec[Y] = 10;
        break;
    case 15:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[8][10] = BLACK;
        Chess_Util::Gamerec[X] = 8; Chess_Util::Gamerec[Y] = 10;
        break;
    case 16:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[9][10] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] = 10;
        break;
    case 17:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[10][10] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] =10;
        break;
    case 18:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[8][9] = BLACK;
        Chess_Util::Gamerec[X] = 8; Chess_Util::Gamerec[Y] =9;
        break;
    case 19:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[9][9] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] = 9;
        break;
    case 20:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[10][9] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 9;
        break;
    case 21:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[9][8] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] = 8;
        break;
    case 22:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[10][8] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 8;
        break;
    case 23:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[9][7] = BLACK;
        Chess_Util::Gamerec[X] = 9; Chess_Util::Gamerec[Y] = 7;
        break;
    case 24:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[10][7] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 7;
        break;
    case 25:
        Chess_Util::Board[7][9] = WHITE;
        Chess_Util::Board[10][6] = BLACK;
        Chess_Util::Gamerec[X] = 10; Chess_Util::Gamerec[Y] = 6;
        break;
   
    }

    if(Chess_Util::Gamerec[Playerchess]==BLACK) //增加计数器
    {
        Chess_Util::Gamerec[CountPlayer] += 2;
        Chess_Util::Gamerec[CountAI] ++;
    }
    else
    {
        Chess_Util::Gamerec[CountPlayer] ++;
        Chess_Util::Gamerec[CountAI]+=2;
    } 
    Chess_Util::Gamerec[CountTotal] += 3;

    repaint();
    showLabel();
    exchange_In_Three();//到达三首交换
}

void Assigned_Game::exchange_In_Three()
{
    if (Chess_Util::Gamerec[NowTurn] == Player)//三手交换时 now仍为黑棋 就是初始值
    {
        //ai方提出请求
       auto ans= QMessageBox::information(nullptr, "Requests", "Opponent requests exchange", QMessageBox::Yes, QMessageBox::No);
       if (ans == QMessageBox::Yes)//三手交换 若允许交换 则ai成为黑棋 player为白棋 此时应该轮到玩家也就是白棋下一步 now不变
       {
           std::swap(Chess_Util::Gamerec[Playerchess], Chess_Util::Gamerec[AIchess]);
           std::swap(Chess_Util::Gamerec[CountPlayer], Chess_Util::Gamerec[CountAI]);
           return;//轮到player白 选择一个位置
       }
       else if(ans==QMessageBox::No)//如果拒绝 则player仍然为黑棋 ai为白棋 此时轮到ai下一步
       {
           Chess_Util::Gamerec[NowTurn] = AI;
           showLabel();
           AITurn();//轮到AI白 落子
       }
    }
    else if (Chess_Util::Gamerec[NowTurn] == AI)//如果是ai先手 那么ai为黑 player为白 此时绝对会被拒绝 拒绝后player下一步棋
    {
        auto ans = QMessageBox::information(nullptr, "Requests", "Do you want to exchange", QMessageBox::Yes, QMessageBox::No);
        if (ans == QMessageBox::Yes) QMessageBox::information(nullptr, "Oh", "Opponent refused", QMessageBox::Yes, QMessageBox::No);
        Chess_Util::Gamerec[NowTurn] = Player;//轮到player白 选择一个位置
    }
}

void Assigned_Game::FifthN()
{
    ui.Thinking_img->move(510, 0);
    std::swap(Chess_Util::Gamerec[Playerchess], Chess_Util::Gamerec[AIchess]);
    Chess_Util::Gamerec[NowTurn] = AI;
    Assigned_Thread* aithread = new Assigned_Thread(1, Fifth);
    threadpool->start(aithread);
    connect(aithread, &Assigned_Thread::Drop, this, &Assigned_Game::exclude);
}

void Assigned_Game::exclude(QPair<int,LL> res)
{
    Fifth.remove(Fifth.indexOf(res.first));
    Chess_Util::Board[res.first / 100][res.first % 100] = BLANK;
    CountFifthN--;
    if (CountFifthN == 1)
    {
        Chess_Util::Board[Fifth[0]/100][Fifth[0] % 100] = BLACK;
        std::swap(Chess_Util::Gamerec[Playerchess], Chess_Util::Gamerec[AIchess]);
        Chess_Util::Gamerec[CountPlayer]++;
        Chess_Util::Gamerec[CountTotal]++;
        repaint();
        showLabel();
        AITurn();
        return;
    }
    FifthN();
}

void Assigned_Game::mousePressEvent(QMouseEvent * event)
{
    if (Chess_Util::Gamerec[NowTurn] != Player)
    {
        if (isSimulate == true && CountFifthN == Chess_Util::StartInfo[FiveN]);//此时是为了让player选则ai选的n个位置中的一个
        else return;
    }
	int getx = event->pos().y();
	int gety = event->pos().x();
    if (getx < 90 || getx>510 || gety < 90 || gety>510) return;
    getx = (getx - 90) / 30 + ((getx - 90) % 30 > 15 ? 1 : 0);
    gety = (gety - 90) / 30 + ((gety - 90) % 30 > 15 ? 1 : 0);
    if ((Chess_Util::Board[getx + 1][gety + 1] != BLANK && isSimulate == false) || (Chess_Util::Board[getx + 1][gety + 1] != Red && isSimulate == true)) return;
    
    Chess_Util::Gamerec[X] = getx+1; Chess_Util::Gamerec[Y] = gety+1;

    playerTurn();
}

void Assigned_Game::paintEvent(QPaintEvent* event)
{
    
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3));
    for (int i = 0; i < 15; i++)
    {
        painter.drawLine(i * 30 + 90, 0 + 90, i * 30 + 90, 14 * 30 + 90);
    }
    for (int i = 0; i < 15; i++)
    {
        painter.drawLine(0 + 90, i * 30 + 90, 14 * 30 + 90, i * 30 + 90);
    }
    painter.setBrush(QColor(0, 0, 0));
    painter.drawEllipse(7 * 30 + 85, 7 * 30 + 85, 10, 10);
    painter.drawEllipse(3 * 30 + 85, 3 * 30 + 85, 10, 10);
    painter.drawEllipse(11 * 30 + 85, 3 * 30 + 85, 10, 10);
    painter.drawEllipse(3 * 30 + 85, 11 * 30 + 85, 10, 10);
    painter.drawEllipse(11 * 30 + 85, 11 * 30 + 85, 10, 10);
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (Chess_Util::Board[i+1][j+1] == BLACK) { painter.setBrush(QColor(0, 0, 0)); painter.drawEllipse(j * 30 + 80, i * 30 + 80, 20, 20); }
            else if (Chess_Util::Board[i+1][j+1] == WHITE) { painter.setBrush(QColor(255, 255, 255)); painter.drawEllipse(j * 30 + 80, i * 30 + 80, 20, 20); }
            else if (Chess_Util::Board[i+1][j+1] == Red) { painter.setBrush(QColor(255, 0, 0)); painter.drawEllipse(j * 30 + 80, i * 30 + 80, 20, 20); }
        }

    }
}

void Assigned_Game::playerTurn()
{
    
    if (Chess_Util::Gamerec[CountTotal] == 4 && Chess_Util::StartInfo[First] == Player && Chess_Util::Gamerec[Playerchess] == BLACK)//开局player为黑 现为黑 拒绝了交换 刚才ai白下了一步 此时player正在选择n个位置
    {
        Chess_Util::Board[Chess_Util::Gamerec[X]][Chess_Util::Gamerec[Y]] = Red;
        Fifth.append(Chess_Util::Gamerec[X]*100 + Chess_Util::Gamerec[Y]);
        repaint();
        showLabel();
        CountFifthN++;//此时让player选n个位置 选了一个 ai位置已经选择完毕
        if (CountFifthN == Chess_Util::StartInfo[FiveN]) FifthN();
        return;
    }
    else if (isSimulate == true)
    {
        for (int pos : Fifth) Chess_Util::Board[pos / 100][pos % 100] = BLANK;
        Chess_Util::Board[Chess_Util::Gamerec[X]][Chess_Util::Gamerec[Y]] = Chess_Util::Gamerec[AIchess];
        Chess_Util::Gamerec[CountAI]++;
        Chess_Util::Gamerec[CountTotal]++;
        Chess_Util::Gamerec[NowTurn] = Player;
        isSimulate = false;//player帮ai选择完毕 继续player的下棋
        repaint();
        showLabel();
        return;
    }

    if (CountTotal >= 7) ui.Regret_Btn->setEnabled(true);
    else ui.Regret_Btn->setEnabled(false);

    ui.Thinking_img->move(0, 0);
    Chess_Util::Board[Chess_Util::Gamerec[X]][Chess_Util::Gamerec[Y]] = Chess_Util::Gamerec[Playerchess];
    Chess_Util::Track.append(Chess_Util::Gamerec[X] * 100 + Chess_Util::Gamerec[Y]);
    repaint();
    showLabel();
    Chess_Util::updateRec();//此时player落子后更新 并且保存原有的rec
    Chess_Util::showInfo();
    int res = 0;
    if(Chess_Util::Gamerec[Playerchess] == BLACK) res=Chess_Util::checkForbidden(Chess_Util::Gamerec[Playerchess], 1);//依据原来的和现在的比较
    if(res==1) dealwithWin(2);
    if(res==0|| Chess_Util::Gamerec[Playerchess]==WHITE) res=Chess_Util::checkWin(Player);//先判断禁手 没有触犯禁手再判断 如果是白棋触犯禁手也无妨
    dealwithWin(res);
   
    Chess_Util::Gamerec[CountPlayer]++;
    Chess_Util::Gamerec[CountTotal]++;
    Chess_Util::Gamerec[NowTurn] = AI;
    if (Chess_Util::Gamerec[CountTotal] == 4  && Chess_Util::Gamerec[Playerchess] == WHITE)//开局player为黑 现为白 只有可能发生了交换 刚才 player下了一步白 此时ai选择n个位置
    {
        isSimulate = true;//这一段共要执行n次 让ai选n个位置
        ui.Thinking_img->move(510, 0);
    }

    //此时就是流程中最绕的一段
    //1.player同意交换 player白落下一子后 ai选择n个位置 故执行fifthN
    AITurn();

    
}

void Assigned_Game::AITurn()
{
    ui.Regret_Btn->setEnabled(false);
    ui.Thinking_img->move(510, 0);
    QList<int> poss = getAvailablePos(Chess_Util::Gamerec[X], Chess_Util::Gamerec[Y],AI);
    std::sort(poss.begin(), poss.end(), [&](const int& p1, const int& p2) {
        double x1 = sqrt((double)pow(Chess_Util::Gamerec[X] - p1 / 100, 2) + pow(Chess_Util::Gamerec[Y] - p1 % 100, 2));
        double x2 = sqrt((double)pow(Chess_Util::Gamerec[X] - p2 / 100, 2) + pow(Chess_Util::Gamerec[Y] - p2 % 100, 2));
        return x1 < x2;
        });//对所选位置进行排序 排序依据时距离上一步棋子的距离 或者是第一步？
    int subnum = qCeil((float)poss.size() / Threadnum);
    for (int i=0;i<=poss.size();i+=subnum)
    {
       QList<int> subposs;
        if(i+subnum<=poss.size()) 
        {
            subposs = poss.mid(i, subnum);
        }
        else  if(poss.size() - i>0)
        {
            subposs = poss.mid(i, poss.size() - i);
        }
        try
        {
            Assigned_Thread* aithread = new Assigned_Thread(1, subposs);
            connect(aithread, &Assigned_Thread::Drop, this, &Assigned_Game::receiveRes);
            threadpool->start(aithread);
        }
        catch (const std::exception&)
        {
            qDebug() << "wrong";
        }
        
    }
    
}

void Assigned_Game::receiveRes(QPair<int, LL> res)
{
    int x = res.first;
    mutex.lock();
    if (threadpool->activeThreadCount() == Threadnum-1) { bestPos =res; }//得到了一个结果
    if (res.second >= bestPos.second)
    {
        bestPos = res;
    }
    mutex.unlock();
    if (threadpool->activeThreadCount() != 0)
    {
       return;
    }
    else if (threadpool->activeThreadCount() == 0)
    {
        x = bestPos.first;
    }
    if (isSimulate==true)//此时ai在选择n个对自己最有利的位置
    {
        Fifth.append(x);
        Chess_Util::Board[x/100][x%100] = Red;
        repaint();
        showLabel();
        CountFifthN++;
        //如果选完了 现在轮到player选择其中的一个
        if (CountFifthN == Chess_Util::StartInfo[FiveN])
        {
            ui.Thinking_img->move(0, 0);
            repaint();
            showLabel();
            showLabel();
            return;
        }
        //还没有选完 则继续执行
        AITurn();
        return;
    }
    Chess_Util::Board[x / 100][x % 100] = Chess_Util::Gamerec[AIchess];
    Chess_Util::Track.append(x);
    Chess_Util::Gamerec[CountAI]++;
    Chess_Util::Gamerec[CountTotal]++;
    Chess_Util::Gamerec[NowTurn] = Player;
    showLabel();
    repaint();
    ui.Thinking_img->move(0, 0);
    
}

void Assigned_Game::showLabel()
{
    ui.Info_label->setText(QString("<-- Player chess:%1   AI chess:%2 -->\nNow:%3\nCountTatol:%4").arg(Chess_Util::Gamerec[Playerchess] == BLACK ? "BLACK" : "WHITE").arg(Chess_Util::Gamerec[AIchess] == BLACK ? "BLACK" : "WHITE").arg(Chess_Util::Gamerec[NowTurn] == Player ? "Player" : "AI").arg(Chess_Util::Gamerec[CountTotal]));
}

void Assigned_Game::Pass()
{
    if (Chess_Util::Gamerec[NowTurn] == Player) return;
    if (Chess_Util::Gamerec[NowTurn] == Player) AITurn();
}
