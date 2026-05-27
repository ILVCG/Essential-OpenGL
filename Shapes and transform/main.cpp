#include "prop.h"

void init(void)
{
	glClearColor(bgColor->r, bgColor->g, bgColor->b, bgColor->a);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(lineColor->r, lineColor->g, lineColor->b);
	glLineWidth(window->lineWidth);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, window->lineStipple);
	glBegin(window->drawMode);
	for (uint32_t i = 0; i < window->pointNum; i++)
	{
		glVertex2f(point2dArr[i].point2dX, point2dArr[i].point2dY);
	}
	glEnd();
	glBegin(window->drawMode);
	for (uint32_t i = 0; i < window->pointNum; i++)
	{
		glVertex2f(transPoint2dMiddle[i].point2dX, transPoint2dMiddle[i].point2dY);
	}
	glEnd();
	glBegin(window->drawMode);
	for (uint32_t i = 0; i < window->pointNum; i++)
	{
		glVertex2f(transPoint2dArr4[i].point2dX, transPoint2dArr4[i].point2dY);
	}
	glEnd();
	glFlush();
}

void ReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLfloat(newHeight), 0.0, GLfloat(newWidth));
	glClear(GL_COLOR_BUFFER_BIT);
}

void SetupLineInfo()
{
	char ch = NULL;
	uint32_t lineStipple = 0;
	std::cout << "画线红色分量值（0.0~1.0）：";
	std::cin >> lineColor->r;
	std::cout << "画线绿色分量值（0.0~1.0）：";
	std::cin >> lineColor->g;
	std::cout << "画线蓝色分量值（0.0~1.0）：";
	std::cin >> lineColor->b;
	std::cout << "画线线宽（单位：像素）：";
	std::cin >> window->lineWidth;
	std::cout << "线型模式 (0、实线 1、短连续线 2、中等连续线 3、长连续）：";
	std::cin >> lineStipple;
	switch (lineStipple)
	{
	case 1:
		window->lineStipple = 0x3333;
		break;
	case 2:
		window->lineStipple = 0x0F0F;
		break;
	case 3:
		window->lineStipple = 0x00FF;
		break;
	default:
		window->lineStipple = 0xFFFF;
	}
	std::cout << "绘制点点数（>=0）：";
	std::cin >> window->pointNum;
	for (uint32_t i = 0; i < window->pointNum; i++)
	{
		std::cout << "点 " << i + 1 << " 的x分量（单位：像素）：";
		std::cin >> point2dArr[i].point2dX;
		std::cout << "点 " << i + 1 << " 的y分量（单位：像素）：";
		std::cin >> point2dArr[i].point2dY;
	}
	while ((ch = std::cin.get()) != '\n')
		continue;
	std::cout << "画线信息设置完成！" << std::endl;
}

void SetupWindowInfo()
{
	char ch = NULL;
	uint32_t drawMode = 0;
	const int titleLength = 100;
	char* title = new char[titleLength];
	std::cout << "窗体 x 坐标位置（单位：像素）：";
	std::cin >> window->screenX;
	std::cout << "窗体 y 坐标位置（单位：像素）：";
	std::cin >> window->screenY;
	std::cout << "窗体长度（单位：像素）：";
	std::cin >> window->windowWidth;
	std::cout << "窗体宽度（单位：像素）：";
	std::cin >> window->windowHeight;
	std::cout << "背景颜色红色分量（0.0~1.0）：";
	std::cin >> bgColor->r;
	std::cout << "背景颜色绿色分量（0.0~1.0）：";
	std::cin >> bgColor->g;
	std::cout << "背景颜色蓝色分量（0.0~1.0）：";
	std::cin >> bgColor->b;
	std::cout << "窗体画线模式，1、点绘制 2、 线绘制 3、折线绘制 4、封闭折线绘制：";
	std::cin >> drawMode;
	if (drawMode == 1)
		window->drawMode = GL_POINTS;
	else if (drawMode == 3)
		window->drawMode = GL_LINE_STRIP;
	else if (drawMode == 4)
		window->drawMode = GL_LINE_LOOP;
	else
		window->drawMode = GL_LINES;
	while ((ch = std::cin.get()) != '\n')
		continue;
	std::cout << "窗体信息设置完成！" << std::endl;
}

void Setup2DTransInfo()
{
	char ch = NULL;
	matrix2dPre->scaleX = 1.0;
	matrix2dPre->scaleY = 1.0;
	matrix2dPre->shearX = 0.0;
	matrix2dPre->shearY = 0.0;
	matrix2dPre->transX = -point2dArr[0].point2dX;
	matrix2dPre->transY = -point2dArr[0].point2dY;
	matrix2dEnd->scaleX = 1.0;
	matrix2dEnd->scaleY = 1.0;
	matrix2dEnd->shearX = 0.0;
	matrix2dEnd->shearY = 0.0;
	matrix2dEnd->transX = point2dArr[0].point2dX;
	matrix2dEnd->transY = point2dArr[0].point2dY;
	std::cout << "##########################" << std::endl;
	std::cout << "####第一次变换矩阵设置开始####" << std::endl;
	std::cout << "X轴方向缩放倍数：";
	std::cin >> matrix2d1->scaleX;
	std::cout << "Y轴方向缩放倍数：";
	std::cin >> matrix2d1->scaleY;
	std::cout << "X轴方向拉伸倍数：";
	std::cin >> matrix2d1->shearX;
	std::cout << "Y轴方向拉伸倍数：";
	std::cin >> matrix2d1->shearY;
	std::cout << "X轴方向平移数（单位：像素）：";
	std::cin >> matrix2d1->transX;
	std::cout << "Y轴方向平移数（单位：像素）：";
	std::cin >> matrix2d1->transY;
	std::cout << "##########################" << std::endl;
	std::cout << "####第二次变换矩阵设置开始####" << std::endl;
	std::cout << "X轴方向缩放倍数：";
	std::cin >> matrix2d2->scaleX;
	std::cout << "Y轴方向缩放倍数：";
	std::cin >> matrix2d2->scaleY;
	std::cout << "X轴方向拉伸倍数：";
	std::cin >> matrix2d2->shearX;
	std::cout << "Y轴方向拉伸倍数：";
	std::cin >> matrix2d2->shearY;
	std::cout << "X轴方向平移数（单位：像素）：";
	std::cin >> matrix2d2->transX;
	std::cout << "Y轴方向平移数（单位：像素）：";
	std::cin >> matrix2d2->transY;
	std::cout << "##########################" << std::endl;
	while ((ch = std::cin.get()) != '\n')
		continue;
	std::cout << "变换矩阵设置完成！" << std::endl;
}

void Setup2DProp()
{
	char ch = NULL;
	SetupLineInfo();
	SetupWindowInfo();
	Setup2DTransInfo();
	transPoint2dArr1 = matrix2dPre->pointLeftMultMatrix(point2dArr);
	transPoint2dArr2 = matrix2d1->pointLeftMultMatrix(transPoint2dArr1);
	transPoint2dMiddle = matrix2dEnd->pointLeftMultMatrix(transPoint2dArr2);
	transPoint2dArr3 = matrix2d2->pointLeftMultMatrix(transPoint2dArr2);
	transPoint2dArr4 = matrix2dEnd->pointLeftMultMatrix(transPoint2dArr3);
	std::cout << "完成！" << std::endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	Setup2DProp();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(window->screenX, window->screenY);
	glutInitWindowSize(window->windowWidth, window->windowHeight);
	glutCreateWindow(window->title.c_str());
	init();
	glutDisplayFunc(lineSegment);
	glutReshapeFunc(ReshapeFunc);
	glutMainLoop();
	return 0;
}