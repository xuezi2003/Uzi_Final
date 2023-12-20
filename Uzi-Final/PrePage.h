#pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#include <QtWidgets/QWidget>
#include "ui_PrePage.h"
#include <qmap.h>
#include "Chess_Util.h"
class PrePage : public QWidget
{
    Q_OBJECT

public:
    PrePage(QWidget *parent = nullptr);
    ~PrePage();
    
private:
    void collectInfo();
    QHash<Info, int> GameInfo;
    Ui::PrePageClass ui;
    void loadOptions();
    void showInfo();
private slots:
    void startGame();
    void resetInfo();
};
