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

void SetupBres2DCircle()
{
	bres2dCirc = new Bres2DCircle();
	std::cout << "请输入圆的颜色R分量：";
	std::cin >> circleColor->r;
	std::cout << "请输入圆的颜色G分量：";
	std::cin >> circleColor->g;
	std::cout << "请输入圆的颜色B分量：";
	std::cin >> circleColor->b;
	std::cout << "请输入圆的半径：";
	std::cin >> bres2dCirc->radius;
	std::cout << "请输入圆心X坐标：";
	std::cin >> bres2dCirc->originX;
	std::cout << "请输入圆心Y坐标：";
	std::cin >> bres2dCirc->originY;
	SetupWindowInfo();
	bres2dCirc->DrawCircle();
}

void DisplayBres2DCircle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(circleColor->r, circleColor->g, circleColor->b);
	glBegin(GL_POINTS);
	for (uint32_t i = 0; i < bres2dCirc->arrLength; i++)
		glVertex2f(bres2dCirc->circleArr[i].point2dX, bres2dCirc->circleArr[i].point2dY);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	SetupBres2DCircle();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(window->screenX, window->screenY);
	glutInitWindowSize(window->windowWidth, window->windowHeight);
	glutCreateWindow(window->title.c_str());
	init();
	glutDisplayFunc(DisplayBres2DCircle);
	glutReshapeFunc(ReshapeFunc);
	glutMainLoop();
	return 0;
}