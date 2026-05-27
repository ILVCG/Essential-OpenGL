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
	std::string title;
	Window()
	{
		this->screenX = 200;
		this->screenY = 200;
		this->windowWidth = 400;
		this->windowHeight = 300;
		this->title = "Hello OpenGL!";
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

class Bres2DCircle
{
public:
	GLfloat radius;
	GLfloat originX;
	GLfloat originY;
	GLuint arrLength;
	Point2DArray circleArr;
	Bres2DCircle()
	{
		this->radius = 100.0;
		this->originX = 150.0;
		this->originY = 150.0;
	}
	Bres2DCircle(GLfloat radius, GLfloat originX = 100.0, GLfloat originY = 100.0)
	{
		this->radius = radius;
		this->originX = originX;
		this->originY = originY;
	}
	void DrawCircle()
	{
		this->arrLength = (int)(2 * 3.14159 * this->radius);
		this->circleArr = new Point2D[this->arrLength];
		GLfloat beginX = 0.0;
		GLfloat beginY = radius;
		GLfloat funcX = 0.0;
		uint32_t i = 1;
		this->circleArr[0].point2dX = beginX;
		this->circleArr[0].point2dY = beginY;
		GLuint endX = (int)(this->radius / 1.414213) + 1;
		while (i <= endX)
		{
			this->circleArr[i].point2dX = ++beginX;
			funcX = sqrt(pow(this->radius, 2) - pow(beginX, 2));
			this->circleArr[i].point2dY = abs(funcX - this->circleArr[i - 1].point2dY) >= 0.5 ? --beginY : beginY;
			this->circleArr[i].homo2d = 1.0;
			i++;
		}
		for (int j = this->arrLength / 4 - 1, i = 0; i <= j; i++, j--)
		{
			this->circleArr[j].point2dX = this->circleArr[i].point2dY;
			this->circleArr[j].point2dY = this->circleArr[i].point2dX;
			this->circleArr[j].homo2d = this->circleArr[i].homo2d;
		}
		for (int j = this->arrLength / 2 - 1, i = 0; i <= j; i++, j--)
		{
			this->circleArr[j].point2dX = this->circleArr[i].point2dX;
			this->circleArr[j].point2dY = -this->circleArr[i].point2dY;
			this->circleArr[j].homo2d = this->circleArr[i].homo2d;
		}
		for (int j = this->arrLength - 1, i = 0; i <= j; i++, j--)
		{
			this->circleArr[j].point2dX = -this->circleArr[i].point2dX;
			this->circleArr[j].point2dY = this->circleArr[i].point2dY;
			this->circleArr[j].homo2d = this->circleArr[i].homo2d;
		}
		for (int i = 0; i < this->arrLength; i++)
		{
			if (circleArr[i].point2dX == 0.0 && circleArr[i].point2dY == 0.0)
				continue;
			else
			{
				this->circleArr[i].point2dX += this->originX;
				this->circleArr[i].point2dY += this->originY;
			}
		}
	}
};

Bres2DCircle* bres2dCirc;

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
RGBModel* circleColor = new RGBModel();