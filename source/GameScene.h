#pragma once

#include "Scene.h"

using namespace std;

class GameScene : public Scene
{
public:
	void drawScene() override;
	void setUpScene() override;
	void tearDownScene() override;
};

