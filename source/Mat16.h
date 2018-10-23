#pragma once
#include <gl/GL.h>
#include <stdio.h>
#include "Vector3.h"
#include <iostream>

using namespace std;

class Mat16
{
public:

	GLfloat* matrix;


	inline Mat16(Vector3 position, Vector3 forward, Vector3 scale)
	{
		//todo, rotation

		matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16);
		
		Update(position, forward, scale);
	}

	inline Mat16()
		: Mat16(Vector3::zero(), Vector3::z(), Vector3::one())
	{
	}

	inline Mat16(Mat16 &m)
	{
		matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16);
		memcpy(matrix, m.matrix, sizeof(GLfloat) * 16);
	}

	inline ~Mat16()
	{
		delete matrix;
	}

	inline static int getIndex(int x, int y)
	{
		return x + y * 4;
	}

	inline static void print(const Mat16& A)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << A.matrix[getIndex(i, j)];
				if (j < 3) {
					cout << ", ";
				}
			}
			cout << "\n";
		}
	}

	inline void Update(Vector3 position, Vector3 forward, Vector3 scale)
	{
		Vector3 up = Vector3::y();
		Vector3 right = forward.Cross(up).Normalize();

		matrix[0] = right.X;
		matrix[1] = right.Y;
		matrix[2] = right.Z;
		matrix[3] = position.X;

		matrix[4] = up.X;
		matrix[5] = up.Y;
		matrix[6] = up.Z;
		matrix[7] = position.Y;

		matrix[8] = forward.X;
		matrix[9] = forward.Y;
		matrix[10] = forward.Z;
		matrix[11] = position.Z;

		matrix[12] = scale.X;
		matrix[13] = scale.Y;
		matrix[14] = scale.Z;
		matrix[15] = 1;
	}

	inline Mat16 operator * (const Mat16& A) const
	{
		Mat16 toRet;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				toRet.matrix[getIndex(i, j)] = 0;
				for (int k = 0; k < 4; k++) {
					toRet.matrix[getIndex(i, j)] += matrix[getIndex(i,k)] + A.matrix[getIndex(k,j)];
				}
			}
		}

		print(*this);
		cout << "\n";
		print(A);
		cout << "\n";
		print(toRet);
		cout << "-----\n";

		return toRet;
	}
};