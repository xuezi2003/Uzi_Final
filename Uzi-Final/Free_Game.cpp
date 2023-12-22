#include <qpainter.h>
#include "QMouseEvent"
#include "qpaintevent"
#include "Assigned_Thread.h"
#include <qmessagebox.h>
#include <qmovie.h>
#include "Free_Game.h"
Free_Game::Free_Game(const QHash<Info, int>& startInfo, QWidget* parent) :Game(startInfo)
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
    bestPos = QPair<int, LL>(-1, -10 * INFINITY);
    connect(ui.Regret_Btn, &QPushButton::clicked, this, &Free_Game::Regret);
    connect(ui.Pass_Btn, &QPushButton::clicked, this, &Free_Game::Regret);
    if (Chess_Util::StartInfo[First] == AI) AITurn();
}

Free_Game::~Free_Game()
{}
void Free_Game::Regret()
{
    int r1 = Chess_Util::Track.takeLast();
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

void Free_Game::dealwithWin(int winner)
{
    if (winner == 1) QMessageBox::information(nullptr, "Game over", "Player win");
    else if (winner == 2) QMessageBox::information(nullptr, "Game over", "AI win");
}

void Free_Game::mousePressEvent(QMouseEvent* event)
{
    if (Chess_Util::Gamerec[NowTurn] != Player)
    {
        return;
    }
    int getx = event->pos().y();
    int gety = event->pos().x();
    if (getx < 90 || getx>510 || gety < 90 || gety>510) return;
    getx = (getx - 90) / 30 + ((getx - 90) % 30 > 15 ? 1 : 0);
    gety = (gety - 90) / 30 + ((gety - 90) % 30 > 15 ? 1 : 0);
    if (Chess_Util::Board[getx+1][gety+1]!=BLANK) return;

    Chess_Util::Gamerec[X] = getx + 1; Chess_Util::Gamerec[Y] = gety + 1;

    playerTurn();
}

void Free_Game::paintEvent(QPaintEvent* event)
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
            if (Chess_Util::Board[i + 1][j + 1] == BLACK) { painter.setBrush(QColor(0, 0, 0)); painter.drawEllipse(j * 30 + 80, i * 30 + 80, 20, 20); }
            else if (Chess_Util::Board[i + 1][j + 1] == WHITE) { painter.setBrush(QColor(255, 255, 255)); painter.drawEllipse(j * 30 + 80, i * 30 + 80, 20, 20); }
        }

    }
}

void Free_Game::playerTurn()
{
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
    if (Chess_Util::Gamerec[Playerchess] == BLACK) res = Chess_Util::checkForbidden(Chess_Util::Gamerec[Playerchess], 1);//依据原来的和现在的比较
    if (res == 1) dealwithWin(2);
    if (res == 0 || Chess_Util::Gamerec[Playerchess] == WHITE) res = Chess_Util::checkWin(Player);//先判断禁手 没有触犯禁手再判断 如果是白棋触犯禁手也无妨
    dealwithWin(res);

    Chess_Util::Gamerec[CountPlayer]++;
    Chess_Util::Gamerec[CountTotal]++;
    Chess_Util::Gamerec[NowTurn] = AI;
    
    AITurn();


}

void Free_Game::AITurn()
{
    ui.Regret_Btn->setEnabled(false);
    ui.Thinking_img->move(510, 0);
    QList<int> poss = getAvailablePos(Chess_Util::Gamerec[X], Chess_Util::Gamerec[Y], AI);
    std::sort(poss.begin(), poss.end(), [&](const int& p1, const int& p2) {
        double x1 = sqrt((double)pow(Chess_Util::Gamerec[X] - p1 / 100, 2) + pow(Chess_Util::Gamerec[Y] - p1 % 100, 2));
        double x2 = sqrt((double)pow(Chess_Util::Gamerec[X] - p2 / 100, 2) + pow(Chess_Util::Gamerec[Y] - p2 % 100, 2));
        return x1 < x2;
        });//对所选位置进行排序 排序依据时距离上一步棋子的距离 或者是第一步？
    int subnum = qCeil((float)poss.size() / Threadnum);
    for (int i = 0; i <= poss.size(); i += subnum)
    {
        QList<int> subposs;
        if (i + subnum <= poss.size())
        {
            subposs = poss.mid(i, subnum);
        }
        else  if (poss.size() - i > 0)
        {
            subposs = poss.mid(i, poss.size() - i);
        }
        try
        {
            Assigned_Thread* aithread = new Assigned_Thread(1, subposs);
            connect(aithread, &Assigned_Thread::Drop, this, &Free_Game::receiveRes);
            threadpool->start(aithread);
        }
        catch (const std::exception&)
        {
            qDebug() << "wrong";
        }

    }

}

void Free_Game::receiveRes(QPair<int, LL> res)
{
    int x = res.first;
    mutex.lock();
    if (threadpool->activeThreadCount() == Threadnum - 1) { bestPos = res; }//得到了一个结果
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
    Chess_Util::Board[x / 100][x % 100] = Chess_Util::Gamerec[AIchess];
    Chess_Util::Track.append(x);
    Chess_Util::Gamerec[CountAI]++;
    Chess_Util::Gamerec[CountTotal]++;
    Chess_Util::Gamerec[NowTurn] = Player;
    showLabel();
    repaint();
    ui.Thinking_img->move(0, 0);

}

void Free_Game::showLabel()
{
    ui.Info_label->setText(QString("<-- Player chess:%1   AI chess:%2 -->\nNow:%3\nCountTatol:%4").arg(Chess_Util::Gamerec[Playerchess] == BLACK ? "BLACK" : "WHITE").arg(Chess_Util::Gamerec[AIchess] == BLACK ? "BLACK" : "WHITE").arg(Chess_Util::Gamerec[NowTurn] == Player ? "Player" : "AI").arg(Chess_Util::Gamerec[CountTotal]));
}

void Free_Game::Pass()
{
    if (Chess_Util::Gamerec[NowTurn] == Player) return;
    if (Chess_Util::Gamerec[NowTurn] == Player) AITurn();
}
