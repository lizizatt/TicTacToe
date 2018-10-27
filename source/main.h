#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "IntroScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "TicTacToeRunner.h"


class MainRunner
{
public:
	const bool RUN_TESTS = true;
	const float FOV = 75.0f;
	const int SCREENWIDTH = 1280;
	const int SCREENHEIGHT = 720;
	const float NEARCLIP = 1000.0f;
	const float FARCLIP = .01f;
	const long MS_TO_FLY = 3000;

public:
	static inline MainRunner* getInstance()
	{
		return instance;
	}

	static string ExePath();

public:
	inline Scene* getScene(int i) {
		return scenes[i];
	}

	inline int getNumScenes() {
		return scenes.size();
	}
	inline int getMVPLocation() { return mvp_location; }
	inline glm::mat4 getPMatrix() { return cameraP; }
	inline int getProgram() { return program; }

public:
	MainRunner();
	~MainRunner();

	void SetUpShaders();
	void SetUpScenes();
	void DrawScenes();
	void TearDownScenes();
	void UpdateCamera();
	bool RunTests();

	void mouseClick(GLFWwindow* window, int button, int action, int mods);

	void raycastFromScreenPoint(double x, double y);

	void FocusOnScene(Scene* scene, bool instant = false);

	void StartGame();
	void PlacePiece(int spot);
	void FinishGame();

private:
	vector<Scene*> scenes;
	glm::vec3 cameraPos;
	glm::vec3 cameraForward;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

private:
	static MainRunner* instance;
	glm::mat4 cameraP;
	glm::mat4 cameraV;
	glm::mat4 cameraMVP;

	TicTacToeRunner ttt;

	time_point<Clock> start; 
	time_point<Clock> end;
	float seconds = 2.0f;
	glm::vec3 destinationPos;
	glm::vec3 destinationDir;
	bool moving = false;
};

int main(int argc, char* argv[]);
static void mouseClick(GLFWwindow* window, int button, int action, int mods);
