
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
string Cube::textureFileName = "TTT.png";
unsigned int Cube::texWidth;
unsigned int Cube::texHeight;
std::vector<unsigned char> Cube::texBuffer;
GLuint Cube::textureID;

Cube::Cube()
	: Cube(glm::vec3(0,0,0), glm::vec3(1, 1, 1))
{
	mvp = glm::mat4(1.0f);
	mvp = glm::translate(mvp, pos);
	mvp = glm::scale(mvp, scale);
}
	
Cube::Cube(Cube &c)
	: Cube(c.pos, c.scale)
{
}

Cube::Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 scenePos, glm::vec3 sceneScale)
	: pos(pos), scale(scale), scenePos(scenePos), sceneScale(sceneScale)
{
	mvp = glm::mat4(1.0f);
	mvp = glm::translate(mvp, pos);
	mvp = glm::scale(mvp, scale);
	mvp = glm::rotate<float>(mvp, 3.1415f / 2.0f, glm::vec3(0, 0, 1));
}


Cube::~Cube()
{
}

void Cube::updateRotation()
{

}

void Cube::setFace(Face face)
{
	destFace = face;
	start = Clock::now();
	end = Clock::now() + chrono::milliseconds(MS_TO_SPIN);
	moving = true;
}

void Cube::setFaceHelper(Face face, float fractional)
{
	mvp = glm::mat4(1.0f);
	mvp = glm::translate(mvp, pos);
	mvp = glm::scale(mvp, scale);
	mvp = glm::rotate<float>(mvp, 3.1415f / 2.0f, glm::vec3(0, 0, 1));

	switch (face) {
		case 0: {
			mvp = glm::rotate<float>(mvp, -3.1415f / 2.0f * fractional, glm::vec3(0, 1, 0));
			break;
		}
		case 1: {
			mvp = glm::rotate<float>(mvp, 3.1415f / 2.0f * fractional, glm::vec3(0, 1, 0));
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			mvp = glm::rotate<float>(mvp, 3.1415f * fractional, glm::vec3(0, 1, 0));
			mvp = glm::rotate<float>(mvp, -3.1415f / 2.0f * fractional, glm::vec3(0, 0, 1));
			break;
		}
		case 4: {
			mvp = glm::rotate<float>(mvp, 3.1415f / 2 * fractional, glm::vec3(1, 0, 0));
			mvp = glm::rotate<float>(mvp, 3.1415f / 2.0f * fractional, glm::vec3(0, 1, 0));
			break;
		}
		case 5: {
			mvp = glm::rotate<float>(mvp, -3.1415f / 2 * fractional, glm::vec3(1, 0, 0));
			mvp = glm::rotate<float>(mvp, 3.1415f / 2.0f * fractional, glm::vec3(0, 1, 0));
			break;
		}
		default: {
			break;
		}
	}
}

void Cube::draw(glm::mat4 parentMVP)
{
	time_point<Clock> now = Clock::now();
	if (moving && duration_cast<milliseconds>(now - end).count() < 0) {
		milliseconds diffES = duration_cast<milliseconds>(end - start);
		milliseconds diffNS = duration_cast<milliseconds>(now - start);
		float fraction = diffNS.count() == 0 ? 0 : (float)diffNS.count() / (float)diffES.count();
		setFaceHelper(destFace, fraction);
	}
	else if (moving) {
		setFaceHelper(destFace, 1.0f);
		face = destFace;
		moving = false;
	}

	targetMVP = parentMVP * mvp;

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
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(texSampler, 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!once) {
		once = true;
		cout << "Draw with glGetError" << glGetError() << "\n";
	}
}

void Cube::setup()
{

}

void Cube::SetUpCube()
{
	//generate vertex and uv arrays
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
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texSampler = glGetUniformLocation(MainRunner::getInstance()->getProgram(), "texSampler");

	//decode texture and set up opengl texture
	string fullPath = MainRunner::ExePath() + "\\" + textureFileName;
	unsigned error = lodepng::decode(texBuffer, texWidth, texHeight, fullPath.c_str());
	if (error) {
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << " ; with input file " << fullPath << std::endl;
	}
	else {
		glGenTextures(1, &textureID);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texBuffer[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Cube::TearDownCube()
{
}

void Cube::raycastClick(glm::vec3 rayPos, glm::vec3 ray)
{
	glm::vec3 worldP = pos + scenePos;
	glm::vec3 worldS = scale * sceneScale;

	//want to know if rayPos->ray ever comes within a scaled sphere according to the above vector of the center point of the sphere
	//p = rayPos + t * (ray)
	float t = -1 * glm::dot(rayPos - worldP, ray);
	glm::vec3 p = rayPos + ray * t;
	glm::vec3 diff = p - worldP;

	if ((abs(diff[0]) < worldS[0]) && (abs(diff[1]) < worldS[1]) && (abs(diff[2]) < worldS[2])) {
		for (Listener* l : listeners) {
			l->OnClick(this);
		}
	}
}