#include "Cube.h"
#include "main.h"
#include <iostream>
#include "lodepng.h"

// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

GLuint Cube::vertexbuffer;
GLuint Cube::uvbuffer;
GLuint Cube::texSampler;
GLuint Cube::VertexArrayID;
unordered_map<string, GLuint> Cube::textures;
int Cube::texNumCounter = 0;
GLuint Cube::layerLocation = 0;
unordered_map<string, int> Cube::textureNums;

Cube::Cube()
	: Cube(glm::vec3(0,0,0), glm::mat3(1.0f), glm::vec3(1, 1, 1), "white.png")
{
}
	
Cube::Cube(Cube &c)
	: Cube(c.pos, c.rotation, c.scale, c.textureFileName)
{
}

Cube::Cube(glm::vec3 pos, glm::mat3 rotation, glm::vec3 scale, string textureFileName)
	: pos(pos), rotation(rotation), scale(scale), textureFileName(textureFileName)
{
	mvp = glm::mat4(1.0f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mvp[i][j] = rotation[i][j];
		}
	}
	mvp = glm::translate(mvp, pos);
	mvp = glm::scale(mvp, scale);
}


Cube::~Cube()
{
}


void Cube::draw(glm::mat4 parentMVP)
{
	glm::mat4 targetMVP = parentMVP * mvp;

	glGetError();

	glUniformMatrix4fv(MainRunner::getInstance()->getMVPLocation(), 1, GL_FALSE, &targetMVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glActiveTexture(GL_TEXTURE0);
	if (!once) {
		cout << "Draw tex setup 1 with glGetError" << glGetError() << " texNum " << texNum << "\n";
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	if (!once) {
		cout << "Draw tex setup 2 with glGetError" << glGetError() << "\n";
	}
	glUniform1i(texSampler, 0);
	if (!once) {
		cout << "Draw tex setup 3 with glGetError" << glGetError() << "\n";
	}
	glUniform1i(layerLocation, texNum);
	if (!once) {
		cout << "Draw tex setup 4 with glGetError" << glGetError() << "\n";
	}



	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	if (!once) {
		once = true;
		cout << "Draw with glGetError" << glGetError() << "\n";
	}
}

void Cube::setup()
{
	//decode texture
	string fullPath = MainRunner::ExePath() + "\\" + textureFileName;

	if (textures.find(fullPath) != textures.end()) {
		textureID = textures[fullPath];
		texNum = textureNums[fullPath];
		return;
	}

	unsigned error = lodepng::decode(texBuffer, texWidth, texHeight, fullPath.c_str());

	if (error) {
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else {
		glGenTextures(1, &textureID);

		texNum = texNumCounter;
		glActiveTexture(GL_TEXTURE0);
		texNumCounter++;

		glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, texWidth, texHeight, texNum, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texBuffer[0]);
		cout << "glTexImage3D glGetError" << glGetError() << "\n";

		textures[fullPath] = textureID;
		textureNums[fullPath] = texNum;
	}
}

void Cube::SetUpCube()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	cout << "Set up cube vertex and color buffer with glGetError " << glGetError() << "\n";

	glEnable(GL_DEPTH_TEST);
	if (glGetError()) {
		cout << 1 << "\n";
	}
	glDepthFunc(GL_LESS);
	if (glGetError()) {
		cout << 2 << "\n";
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 0);
	if (glGetError()) {
		cout << 4 << "\n";
	}
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (glGetError()) {
		cout << 5 << "\n";
	}
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (glGetError()) {
		cout << 6 << "\n";
	}

	texSampler = glGetUniformLocation(MainRunner::getInstance()->getProgram(), "texSampler");
	if (glGetError()) {
		cout << 7 << "\n";
	}
	layerLocation = glGetUniformLocation(MainRunner::getInstance()->getProgram(), "texLayer");
	if (glGetError()) {
		cout << 8 << "\n";
	}

	cout << "Set up Cube with glGetError" << glGetError() << "\n";

}

void Cube::TearDownCube()
{
	glDisable(GL_TEXTURE_2D);
}