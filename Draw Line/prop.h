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

class Bres2DLine
{
public:
	Point2D p1;
	Point2D p2;
	GLfloat lineK;
	GLfloat lineB;
	GLuint arrLength;
	Point2DArray curve2dArr;
	GLuint kMode;	
	Bres2DLine()
	{
		this->p1.point2dX = 50;
		this->p1.point2dY = 50;
		this->p1.homo2d = 1;
		this->p2.point2dX = 150;
		this->p2.point2dY = 150;
		this->p2.homo2d = 1;
		this->lineK = (this->p2.point2dY - this->p1.point2dY) / (this->p2.point2dX - this->p1.point2dX);
		this->lineB = this->p1.point2dY - this->lineK * this->p1.point2dX;
		this->kMode = abs(this->lineK) <= 1.0 ? 1 : 0;
		if (this->kMode)
			this->arrLength = abs(this->p2.point2dX - this->p1.point2dX) + 1;
		else
			this->arrLength = abs(this->p2.point2dY - this->p1.point2dY) + 1;
		this->curve2dArr = new Point2D[this->arrLength];
	}
	Bres2DLine(Point2D p1, Point2D p2)
	{
		if (p1.point2dX <= p2.point2dX)
		{
			this->p1.point2dX = p1.point2dX;
			this->p1.point2dY = p1.point2dY;
			this->p1.homo2d = p1.homo2d;
			this->p2.point2dX = p2.point2dX;
			this->p2.point2dY = p2.point2dY;
			this->p2.homo2d = p2.homo2d;
		}
		else
		{
			this->p1.point2dX = p2.point2dX;
			this->p1.point2dY = p2.point2dY;
			this->p1.homo2d = p2.homo2d;
			this->p2.point2dX = p1.point2dX;
			this->p2.point2dY = p1.point2dY;
			this->p2.homo2d = p1.homo2d;
		}
		this->lineK = (this->p2.point2dY - this->p1.point2dY) / (this->p2.point2dX - this->p1.point2dX);
		this->lineB = this->p1.point2dY - this->lineK * this->p1.point2dX;
		this->kMode = abs(this->lineK) <= 1.0 ? 1 : 0;
		if (kMode)
			this->arrLength = abs(this->p2.point2dX - this->p1.point2dX) + 1;
		else
			this->arrLength = abs(this->p2.point2dY - this->p1.point2dY) + 1;
		this->curve2dArr = new Point2D[this->arrLength];
	}
	void DrawLine()
	{
		this->curve2dArr[0].point2dX = this->p1.point2dX;
		this->curve2dArr[0].point2dY = this->p1.point2dY;
		GLfloat p1x = this->curve2dArr[0].point2dX;
		GLfloat p1y = this->curve2dArr[0].point2dY;
		GLfloat funcX = 0.0;
		GLfloat funcY = 0.0;
		if (kMode)
		{
			for (int i = 1; i < abs(this->p2.point2dX - this->p1.point2dX) + 1; i++)
			{
				this->curve2dArr[i].point2dX = ++p1x;
				funcX = lineK * p1x + lineB;
				if (lineK >= 0)
					this->curve2dArr[i].point2dY = abs(funcX - this->curve2dArr[i - 1].point2dY) >= 0.5 ? ++p1y : p1y;
				else
					this->curve2dArr[i].point2dY = abs(funcX - this->curve2dArr[i - 1].point2dY) >= 0.5 ? --p1y : p1y;
				this->curve2dArr[i].homo2d = 1.0;
			}
		}
		else
		{
			for (int i = 1; i < abs(this->p2.point2dY - this->p1.point2dY); i++)
			{
				if (lineK >= 0)
				{
					this->curve2dArr[i].point2dY = ++p1y;
					funcY = (p1y - lineB) / lineK;
					this->curve2dArr[i].point2dX = abs(funcY - this->curve2dArr[i - 1].point2dX) >= 0.5 ? ++p1x : p1x;
				}
				else
				{
					this->curve2dArr[i].point2dY = --p1y;
					funcY = (p1y - lineB) / lineK;
					this->curve2dArr[i].point2dX = abs(funcY - this->curve2dArr[i - 1].point2dX) >= 0.5 ? ++p1x : p1x;
				}
				this->curve2dArr[i].homo2d = 1.0;
			}
		}
	}
};

Bres2DLine* bres2dCurve;

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