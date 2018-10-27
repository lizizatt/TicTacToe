#pragma once

#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class Cube
{
public:
	const long MS_TO_SPIN = 100;

	enum Face
	{
		logo,
		startGame,
		X,
		lose,
		win,
		O
	};

public:
	class Listener
	{
	public:
		virtual void OnClick(Cube *c) = 0;
	};

public:
	Cube();
	Cube(Cube &c);
	Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 scenePos = glm::vec3(), glm::vec3 sceneScale = glm::vec3());
	~Cube();

	void draw(glm::mat4 mvp);
	void setup();

	static void SetUpCube();
	static void TearDownCube();

	Face getFace() { return face; }
	void setFace(Face face);

	void raycastClick(glm::vec3 rayPos, glm::vec3 ray);

	void updateRotation();

	inline void addListener(Listener *l) { listeners.push_back(l); }
	inline void removeListener(Listener *l) { listeners.remove(l); }

private:
	glm::vec3 pos;
	glm::vec3 scale;

	Face face;

	glm::mat4 mvp;
	glm::mat4 targetMVP;
	
	static string textureFileName;
	static unsigned int texWidth;
	static unsigned int texHeight;
	static std::vector<unsigned char> texBuffer;
	static GLuint textureID;
	static GLuint VertexArrayID;
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	static GLuint texSampler;

	bool once = false;

	glm::vec3 scenePos;
	glm::vec3 sceneScale;

	time_point<Clock> start;
	time_point<Clock> end;
	bool moving = false;
	Face destFace;

	list<Listener*> listeners;

private:
	void setFaceHelper(Face face, float fractional = 1.0f);
};

