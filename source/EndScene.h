#pragma once

#include "Scene.h"

using namespace std;

class EndScene : public Scene
{
public:
	EndScene(Vector3 position, Vector3 forward, Vector3 scale);
	void InitializeScene() override;
	void TearDownScene() override;
};

