
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "IntroScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "Mat16.h"

class MainRunner
{
public:
	const bool RUN_TESTS = true;

public:
	static inline MainRunner* getInstance()
	{
		return instance;
	}

public:
	MainRunner();
	~MainRunner();

	void SetUpShaders();
	void SetUpScenes();
	void DrawScenes();
	void TearDownScenes();
	void UpdateCamera();
	bool RunTests();

	void FocusOnScene(Scene* scene);

	inline int getMVPLocation() { return mvp_location; }

private:
	vector<shared_ptr<Scene>> scenes;
	Vector3 cameraPos;
	Vector3 cameraForward;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

private:
	string ExePath();
	static MainRunner* instance;
	Mat16 cameraMVP;
};

int main(int argc, char* argv[]);
