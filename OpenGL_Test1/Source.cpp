#include "stdafx.h"
#include<gl/glut.h>

GLfloat rtri = 0.2;//用于三角形的角度
GLfloat rquad = 0.2;//用于四边形的角度

void renderScene(void)
{
	rtri = 0.2;
	rquad = 0.2;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓冲以及深度缓冲
	glLoadIdentity();//等于是将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵！等于是之前的矩阵变换带来的影响到此为止了！//重置模型观察矩阵
	
	glTranslatef(-0.5,0.0,0.0);
	glRotatef(rtri, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);//glBegin和glEnd函数限定了一组或多组图元的定点定义
	glColor3f(1.0,0.0,0.0);//将下顶点设置为红色
	glVertex3f(-0.4,-0.0,0.0);//定义三个空间矢量点，矢量点坐标为float
	glColor3f(0.0, 1.0, 0.0);//将下顶点设置为绿色
	glVertex3f(0.4, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);//将下顶点设置为蓝色
	glVertex3f(0.0, 0.4, 0.0);
	glEnd();

	glLoadIdentity();//重置模型观察矩阵
	glTranslatef(1.0, 0.0, 0.0);	
	glRotatef(rquad, 1.0, 0.0, 0.0);//绕X轴旋转四边形
	glColor3f(0.5,0.5,1.0);
	glBegin(GL_QUADS);//glBegin和glEnd函数限定了一组或多组图元的定点定义
	glVertex3f(-0.4, -0.4, 0.0);//定义四个空间矢量点，矢量点坐标为float
	glVertex3f(-0.4, 0.4, 0.0);
	glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.4, -0.4, 0.0);	
	glEnd();

	rtri += 0.2;
	rquad += 0.2;
	glutSwapBuffers();//交换缓冲区.程序使用的是双缓冲技术；用了这种技术的话，你所有的绘制都是绘制到一个后台的缓冲区里面的，如果不交换缓冲区，就看不到绘制的东西了
}

int _tmain(int argc, _TCHAR* argv[])
{

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(renderScene);
	glutMainLoop();//进入GLUT事件处理循环
	
	return 0;
}

