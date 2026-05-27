#include "prop.h"

void init(void)
{
	glClearColor(bgColor->r, bgColor->g, bgColor->b, bgColor->a);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 200);
}

void ReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLfloat(newHeight), 0.0, GLfloat(newWidth));
	glClear(GL_COLOR_BUFFER_BIT);
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
	while ((ch = std::cin.get()) != '\n')
		continue;
	std::cout << "窗体信息设置完成！" << std::endl;
}

void SetupLineInfo()
{
	char ch = NULL;
	std::cout << "画线红色分量值（0.0~1.0）：";
	std::cin >> lineColor->r;
	std::cout << "画线绿色分量值（0.0~1.0）：";
	std::cin >> lineColor->g;
	std::cout << "画线蓝色分量值（0.0~1.0）：";
	std::cin >> lineColor->b;
	while ((ch = std::cin.get()) != '\n')
		continue;
	std::cout << "画线信息设置完成！" << std::endl;
}

void SetupBres2DCurve()
{
	GLfloat beginX = 0.0, beginY = 0.0;
	GLfloat endX = 0.0, endY = 0.0;
	std::cout << "Bezier画线起点X坐标（单位：像素）：";
	std::cin >> beginX;
	std::cout << "Bezier画线起点Y坐标（单位：像素）：";
	std::cin >> beginY;
	std::cout << "Bezier画线终点X坐标（单位：像素）：";
	std::cin >> endX;
	std::cout << "Bezier画线终点Y坐标（单位：像素）：";
	std::cin >> endY;
	bres2dCurve = new Bres2DLine(Point2D(beginX, beginY), Point2D(endX, endY));
	SetupLineInfo();
	SetupWindowInfo();
	bres2dCurve->DrawLine();
}

void DisplayBres2DCurve()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(lineColor->r,lineColor->g,lineColor->b);
	glBegin(GL_POINTS);
	for (uint32_t i = 0; i < bres2dCurve->arrLength; i++)
		glVertex2f(bres2dCurve->curve2dArr[i].point2dX, bres2dCurve->curve2dArr[i].point2dY);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	SetupBres2DCurve();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(window->screenX, window->screenY);
	glutInitWindowSize(window->windowWidth, window->windowHeight);
	glutCreateWindow(window->title.c_str());
	init();
	glutDisplayFunc(DisplayBres2DCurve);
	glutReshapeFunc(ReshapeFunc);
	glutMainLoop();
	return 0;
}