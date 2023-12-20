#include "Game.h"

Game::Game(const QHash<Info, int>& startInfo, QWidget* parent) :QWidget(parent)
{
	
	Chess_Util::StartInfo = startInfo;
	Chess_Util::initMap();
	ui.setupUi(this);
}

Game::~Game()
{}
