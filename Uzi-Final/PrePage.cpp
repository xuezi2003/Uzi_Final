#include "PrePage.h"
#include "Assigned_Game.h"
#include "Chess_Util.h"
PrePage::PrePage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    loadOptions();
    showInfo();
    
    connect(ui.Confirm_Btn, &QPushButton::clicked, this, &PrePage::startGame);
    connect(ui.Reset_Btn, &QPushButton::clicked, this, &PrePage::resetInfo);
    connect(ui.Player_Btn, &QPushButton::clicked, this, &PrePage::showInfo);
    connect(ui.AI_Btn, &QPushButton::clicked, this, &PrePage::showInfo);
    connect(ui.Assigned_Btn, &QPushButton::clicked, this, &PrePage::showInfo);
    connect(ui.Free_Btn, &QPushButton::clicked, this, &PrePage::showInfo);
    connect(ui.Five_N_Box, &QSpinBox::valueChanged,this, &PrePage::showInfo);
    connect(ui.First_Three_Box, &QComboBox::currentIndexChanged, this, &PrePage::showInfo);

}

PrePage::~PrePage()
{}

void PrePage::collectInfo()
{
    GameInfo.insert(Mode, ui.Assigned_Btn->isChecked() ? Assigned : Free);
    GameInfo.insert(First, ui.Player_Btn->isChecked() ? Player : AI);
    GameInfo.insert(FiveN, ui.Five_N_Box->value());
    GameInfo.insert(FirstThree, ui.First_Three_Box->currentIndex());
    
}
void PrePage::loadOptions()
{
    for (int i = 0; i < 26; i++)
    {
        ui.First_Three_Box->addItem(QString::number(i+1));
    }
}
void PrePage::showInfo()
{
    QPixmap img(QString(":/new/options/Resource/%1.jpg").arg(ui.First_Three_Box->currentIndex() ));
    img=img.scaled(ui.FirstThree_img->size());
    ui.FirstThree_img->setPixmap(img);
    ui.Info_Browser->setText("Rule:" +
        QString(ui.Assigned_Btn->isChecked() ? "Assigned" : "Free") +
        "\nThe first:" + (ui.Player_Btn->isChecked() ? "Player" : "AI") +
        "\nFifth N:" + QString::number(ui.Five_N_Box->value()) + 
        "\nFirst three:");
}
void PrePage::resetInfo()
{
    ui.Assigned_Btn->setChecked(true);
    ui.Player_Btn->setChecked(true);
    ui.Five_N_Box->setValue(2);
    ui.First_Three_Box->setCurrentIndex(0);
}
void PrePage::startGame()
{
    collectInfo();
    Game* game = new Assigned_Game(GameInfo);
    game->show();
}