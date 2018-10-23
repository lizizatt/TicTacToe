#pragma once

#include "Scene.h"

using namespace std;

class IntroScene : public Scene
{
public:
	IntroScene(Vector3 position, Vector3 forward, Vector3 scale);
	void InitializeScene() override;
	void TearDownScene() override;
};

