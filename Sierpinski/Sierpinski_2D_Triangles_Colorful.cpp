/*Jongkhurun-2017.12.10
怎么产生"随机"的随机数?	^.^
怎么实现颜色不同的点？	^.^
怎么实现其他形状？
怎么弄成3D的？
怎么实现拖动三个点？
*/

#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct GLpoint {
	GLfloat x;
	GLfloat y;
}GLpoint;


////获得随机数
//static int seed = time(null);
//int getrandnum(int min, int max) {
//	srand(seed);
//	seed = rand();
//	return (min + rand() % (max - min + 1));
//}

//获得随机数
int getRandNum(int min, int max) {
	return (min + rand() % (max - min + 1));
}

//改变点的颜色
void changeColor(GLfloat &_red, GLfloat &_green, GLfloat &_blue) {
	_red = _red + 0.1;
	if (fabs(_red - 1.0) < 1e-6) {
		_red = 0.0;
	}
	_green = _green + 0.1;
	if (fabs(_green - 1.0) < 1e-6) {
		_green = 0.0;
	}
	_blue = _blue + 0.1;
	if (fabs(_blue - 1.0) < 1e-6) {
		_blue = 0.0;
	}
	glColor3f(_red, _green, _blue);
}

//画点
void drawDot(GLpoint point) {
	glBegin(GL_POINTS);
	glVertex2f(point.x, point.y);
	glEnd();
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);		//背景颜色
	glColor3f(0.0f, 0.0f, 0.0f);		//绘图颜色
	glPointSize(2.0);		//点的大小
	glMatrixMode(GL_PROJECTION);		//设置合适的矩阵
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


void Sierpinski_render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLpoint T[3] = { { 100,100 } ,{ 600,100 },{ 300,300 },};
	srand((unsigned int)time(NULL));

	int render = getRandNum(0,2);		//产生0~2的随机数
	GLpoint point = T[render];
	drawDot(point);

	GLfloat _red = 0.5;		//设置绘图的初始值
	GLfloat _green = 0.8;
	GLfloat _blue = 0.4;
	
	for (int i = 0; i < 550000; i++) {
		render = getRandNum(0, 2);		
		point.x = (point.x + T[render].x) / 2;
		point.y = (point.y + T[render].y) / 2;
		drawDot(point);
		changeColor(_red, _green, _blue);
	}
	
	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);		//初始化工具包		
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		//初始化显示模式：单个显示缓存、颜色由红绿蓝来指定
	glutInitWindowSize(640, 480);		//指定屏幕窗口的初始尺寸
	glutInitWindowPosition(100, 150);		//窗口左上角在屏幕上相对于左上角的位置
	glutCreateWindow("Sierpinski_2D_Triangles");		//打开并显示屏幕窗口,标上标题

	glutDisplayFunc(Sierpinski_render);		//注册回调函数
	myInit();		//必要的其他初始化工作

	glutMainLoop();		//进入循环
}