#include "main.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

MainRunner* MainRunner::instance;

MainRunner::MainRunner()
{
	if (instance != nullptr) {
		cerr << "More than one instance of MainRunner! \n";
	}
	instance = this;

	//initialize one of each scene
	scenes.push_back(new IntroScene(glm::vec3(0, 10, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
	scenes.push_back(new GameScene(glm::vec3(0, 0, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
	scenes.push_back(new EndScene(glm::vec3(0, -10, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
}

MainRunner::~MainRunner()
{
	for (int i = 0; i < scenes.size(); i++) {
		delete scenes[i];
	}
	scenes.clear();
}

void MainRunner::SetUpShaders()
{
	string path = ExePath();

	//load from files
	ifstream tVert(path + "\\vertex.vert");
	stringstream bufferVert;
	bufferVert << tVert.rdbuf();
	string vertStr = bufferVert.str();
	const char* vertex_shader_text = vertStr.c_str();

	ifstream tFrag(path + "\\fragment.frag");
	stringstream bufferFrag;
	bufferFrag << tFrag.rdbuf();
	string fragStr = bufferFrag.str();
	const char* fragment_shader_text = fragStr.c_str();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertex_shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	//fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);
	cout << "Compiled fragment shader with error code:" << glGetError() << "\n";

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragment_shader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	//program
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	cout << "Created glProgram with error code:" << glGetError() << "\n";

	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glUseProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	cout << "Got MVP location with error code:" << glGetError() << "\n";
}

void MainRunner::SetUpScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->InitializeScene();
		scenes[i]->LoadCubeTextures();
	}
	FocusOnScene(scenes[0], true);
}

void MainRunner::DrawScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->drawScene(cameraMVP);
	}
}

void MainRunner::TearDownScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->TearDownScene();
	}
}

void MainRunner::FocusOnScene(Scene *scene, bool instant)
{
	if (instant) {
		cameraPos = scene->Position() - glm::vec3(0, 0, 5);
		cameraForward = glm::vec3(0, 0, 1);
	}
	else {
		destinationPos = scene->Position() - glm::vec3(0, 0, 5);
		destinationDir = glm::vec3(0, 0, 1);
		start = Clock::now();
		end = Clock::now() + chrono::seconds(3);
		moving = true;
	}
}

void MainRunner::UpdateCamera()
{
	time_point<Clock> now = Clock::now();
	if (moving && duration_cast<milliseconds>(now - end).count() < 0) {
		milliseconds diffES = duration_cast<milliseconds>(end - start);
		milliseconds diffNS = duration_cast<milliseconds>(now - start);
		float fraction = diffNS.count() == 0 ? 0 : (float) diffNS.count() / (float) diffES.count();
		cameraPos = cameraPos + (destinationPos - cameraPos) * fraction;
		cameraForward = cameraForward + (destinationDir - cameraForward) * fraction;
	}
	else if (moving) {
		cameraPos = destinationPos;
		cameraForward = destinationDir;
		moving = false;
	}

	cameraP = glm::perspective(glm::radians(FOV/2), (float) SCREENWIDTH / (float) SCREENHEIGHT, NEARCLIP, FARCLIP);
	cameraMVP = cameraP * glm::lookAt(cameraPos, cameraPos + cameraForward, glm::vec3(0, 1, 0));
}

bool MainRunner::RunTests()
{
	return true;
}

string MainRunner::ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void MainRunner::mouseClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_RELEASE == action) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			raycastFromScreenPoint(xpos, ypos);
		}
	}
}

void MainRunner::raycastFromScreenPoint(double x, double y)
{
	double xD = (x - (SCREENWIDTH / 2)) / SCREENWIDTH;
	double yD = (y - (SCREENHEIGHT / 2)) / SCREENHEIGHT;

	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(cameraForward, up));

	glm::vec3 pointOnCameraPlane = cameraPos + cameraForward;

	float FOVX = FOV * (float)SCREENWIDTH / (float)SCREENHEIGHT;
	float rightAngleInDegs = FOVX / 2.0f * xD;
	float upAngleInDegs = -FOV / 2.0f * yD;

	float rightContrb = tan(glm::radians(rightAngleInDegs));
	float upContrib = tan(glm::radians(upAngleInDegs));

	pointOnCameraPlane += rightContrb * right + upContrib * up;

	glm::vec3 ray = pointOnCameraPlane - cameraPos;
	ray = glm::normalize(ray);

	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->RaycastClickAgainstScene(cameraPos, ray);
	}
}

void MainRunner::StartGame()
{
	FocusOnScene(scenes[1]);
	ttt.StartGame();
	((GameScene*)scenes[1])->RenderBoard(ttt.getCurrentBoardString());
	cout << "Starting game... \n";
}

void MainRunner::PlacePiece(int spot)
{
	string boardString = ttt.getCurrentBoardString();
	boardString[spot] = 'X';
	ttt.updateBoardString(boardString);

	cout << "Board string before ai move: <" << boardString << ">\n";

	string aiChosenBoardString = ttt.getAIMove();
	((GameScene*)scenes[1])->RenderBoard(aiChosenBoardString);

	cout << "Board string after ai move: <" << aiChosenBoardString << ">\n";

	if (ttt.isGameOver()) {
		FinishGame();
	}
}

void MainRunner::FinishGame()
{
	FocusOnScene(scenes[2]);
	((EndScene*)scenes[2])->setPlayerWon(ttt.didWin('X'));
}

namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {
      int glfwInitRes = glfwInit();
      if (!glfwInitRes) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);

      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }

      return window;
   }
}

static void mouseClick(GLFWwindow* window, int button, int action, int mods)
{
	MainRunner::getInstance()->mouseClick(window, button, action, mods);
}

int main(int argc, char* argv[]) {


	MainRunner mainRunner;

	if (mainRunner.RUN_TESTS && !mainRunner.RunTests()) {
		return -1;
	}

	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = initialize();
	if (!window) {
		return 0;
	}

	glfwSetMouseButtonCallback(window, mouseClick);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mainRunner.SetUpShaders();

	Cube::SetUpCube();

	mainRunner.SetUpScenes();

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainRunner.UpdateCamera();
		mainRunner.DrawScenes();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//tear down cube arrays
	Cube::TearDownCube();
   
	//tear down scenes
	mainRunner.TearDownScenes();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
