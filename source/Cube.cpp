#include "Cube.h"



Cube::Cube()
: Cube(Vector3::zero(), Vector3::one(), Vector3::one(), Vector3::one())
{
}

Cube::Cube(Vector3 pos, Vector3 forward, Vector3 scale, Vector3 baseColor, string textureFileName)
	: pos(pos), forward(forward), scale(scale), baseColor(baseColor), textureFileName(textureFileName)
{
}


Cube::~Cube()
{
}
