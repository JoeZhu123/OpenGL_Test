#include "stdafx.h"
#include<gl/glut.h>

GLfloat rtri = 0.2;//���������εĽǶ�
GLfloat rquad = 0.2;//�����ı��εĽǶ�

void renderScene(void)
{
	rtri = 0.2;
	rquad = 0.2;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�����Լ���Ȼ���
	glLoadIdentity();//�����ǽ�֮ǰ����任���±仯����ջ���������¹�λ����Ϊ��λ���󣡵�����֮ǰ�ľ���任������Ӱ�쵽��Ϊֹ�ˣ�//����ģ�͹۲����
	
	glTranslatef(-0.5,0.0,0.0);
	glRotatef(rtri, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);//glBegin��glEnd�����޶���һ������ͼԪ�Ķ��㶨��
	glColor3f(1.0,0.0,0.0);//���¶�������Ϊ��ɫ
	glVertex3f(-0.4,-0.0,0.0);//���������ռ�ʸ���㣬ʸ��������Ϊfloat
	glColor3f(0.0, 1.0, 0.0);//���¶�������Ϊ��ɫ
	glVertex3f(0.4, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);//���¶�������Ϊ��ɫ
	glVertex3f(0.0, 0.4, 0.0);
	glEnd();

	glLoadIdentity();//����ģ�͹۲����
	glTranslatef(1.0, 0.0, 0.0);	
	glRotatef(rquad, 1.0, 0.0, 0.0);//��X����ת�ı���
	glColor3f(0.5,0.5,1.0);
	glBegin(GL_QUADS);//glBegin��glEnd�����޶���һ������ͼԪ�Ķ��㶨��
	glVertex3f(-0.4, -0.4, 0.0);//�����ĸ��ռ�ʸ���㣬ʸ��������Ϊfloat
	glVertex3f(-0.4, 0.4, 0.0);
	glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.4, -0.4, 0.0);	
	glEnd();

	rtri += 0.2;
	rquad += 0.2;
	glutSwapBuffers();//����������.����ʹ�õ���˫���弼�����������ּ����Ļ��������еĻ��ƶ��ǻ��Ƶ�һ����̨�Ļ���������ģ�������������������Ϳ��������ƵĶ�����
}

int _tmain(int argc, _TCHAR* argv[])
{

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(renderScene);
	glutMainLoop();//����GLUT�¼�����ѭ��
	
	return 0;
}

