#pragma once
#include <iostream>
#include <cmath>
#include <gl/glut.h>

class Window
{
public:
	GLint screenX;
	GLint screenY;
	GLuint windowWidth;
	GLuint windowHeight;
	GLfloat lineWidth;
	GLuint pointNum;
	GLenum drawMode;
	GLuint lineStipple;
	std::string title;
	Window()
	{
		this->screenX = 200;
		this->screenY = 200;
		this->windowWidth = 400;
		this->windowHeight = 300;
		this->lineWidth = 1.0;
		this->pointNum = 4;
		this->drawMode = GL_LINES;
		this->title = "Hello OpenGL!";
		this->lineStipple = 0xFFFF;
	}
};

Window* window = new Window();

class Point2D
{
public:
	GLfloat point2dX;
	GLfloat point2dY;
	GLfloat homo2d;
	Point2D()
	{
		this->point2dX = 0.0;
		this->point2dY = 0.0;
		this->homo2d = 1.0;
	}
	Point2D(GLfloat point2dX, GLfloat point2dY)
	{
		this->point2dX = point2dX;
		this->point2dY = point2dY;
		this->homo2d = 1.0;
	}
};

typedef Point2D* Point2DArray;

Point2DArray point2dArr = new Point2D[window->pointNum];
Point2DArray transPoint2dArr1;
Point2DArray transPoint2dArr2;
Point2DArray transPoint2dArr3;
Point2DArray transPoint2dArr4;
Point2DArray transPoint2dMiddle;

class Matrix2D
{
public:
	GLfloat scaleX;
	GLfloat scaleY;
	GLfloat shearX;
	GLfloat shearY;
	GLfloat transX;
	GLfloat transY;
	Matrix2D()
	{
		this->scaleX = 1.0;
		this->scaleY = 1.0;
		this->shearX = 0.0;
		this->shearY = 0.0;
		this->transX = 0.0;
		this->transY = 0.0;
	}
	Matrix2D(GLfloat scaleX, GLfloat scaleY, GLfloat shearX, GLfloat shearY, GLfloat transX, GLfloat transY)
	{
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->shearX = shearX;
		this->shearY = shearY;
		this->transX = transX;
		this->transY = transY;
	}
	Point2DArray pointLeftMultMatrix(Point2DArray point2DArr)
	{
		Point2DArray transPoint2DArr = new Point2D[window->pointNum];
		for (uint32_t i = 0; i < window->pointNum; i++)
		{
			transPoint2DArr[i].point2dX = point2DArr[i].point2dX * this->scaleX + point2DArr[i].point2dY * this->shearX + point2DArr[i].homo2d * this->transX;
			transPoint2DArr[i].point2dY = point2DArr[i].point2dX * this->shearY + point2DArr[i].point2dY * this->scaleY + point2dArr[i].homo2d * this->transY;
			transPoint2DArr[i].homo2d = point2DArr[i].homo2d;
		}
		return transPoint2DArr;
	}
};

class RGBModel
{
public:
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
	RGBModel()
	{
		this->r = 0.0;
		this->g = 0.0;
		this->b = 0.0;
		this->a = 1.0;
	}
	RGBModel(GLfloat red, GLfloat green, GLfloat blue)
	{
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = 1.0;
	}
};

RGBModel* bgColor = new RGBModel();
RGBModel* lineColor = new RGBModel();
Matrix2D* matrix2d1 = new Matrix2D(); 
Matrix2D* matrix2d2 = new Matrix2D();
Matrix2D* matrix2dPre = new Matrix2D();
Matrix2D* matrix2dEnd = new Matrix2D();