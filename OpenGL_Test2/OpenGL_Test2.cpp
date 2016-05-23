// OpenGL_Test2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>


HGLRC hRC = NULL;					//������ɫ��������
HDC hDC = NULL;						//OpenGL��Ⱦ��������
HWND hWnd = NULL;					//�������ǵĴ��ھ��
HINSTANCE hInstance = NULL;			//��������ʵ��
bool keys[256];						//������̰���������
bool active = TRUE;					//���ڵĻ��־��ȱʡΪtrue
bool fullscreen = TRUE;				//ȫ����־��ȱʡΪȫ��ģʽ

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);		//WndProc�Ķ���

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		//����OpenGL���ڴ�С
{
	if (height == 0)									//��ֹ�����
	{
		height = 1;							
	}
	glViewport(0,0,width,height);						//���õ�ǰ���ӿ�
	glMatrixMode(GL_PROJECTION);						//ѡ��ͶӰ����
	glLoadIdentity();									//����ͶӰ����
	//�����ӿڵĴ�С
	gluPerspective(45.0,(GLfloat)width/(GLfloat)height,0.1,100);			
	glMatrixMode(GL_MODELVIEW);							//ѡ��ģ�͹۲����
	glLoadIdentity();									//����ģ�͹۲����
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);							//������Ӱƽ��
	glClearColor(0.0,0.0,0.0,0.0);						//��ɫ����

	glClearDepth(1.0);									//������Ȼ���
	glEnable(GL_DEPTH_TEST);							//������Ȳ���
	glDepthFunc(GL_LEQUAL);								//������Ȳ��Ե�����

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	//����ϵͳ�Բ��Խ�������
	return TRUE;										//��ʼ��OK
}

int DrawGLScene(GLvoid)									//�����￪ʼ�������еĻ���
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);//�����Ļ����Ȼ���
	glLoadIdentity();									//���õ�ǰ��ģ�͹۲����
	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								//�������ٴ���
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);					//�ǵĻ����л�������
		ShowCursor(TRUE);								//��ʾ���ָ��
	}
	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))					//�����ܷ��ͷ�DC��RC������
		{
			MessageBox(NULL, _T("�ͷ�DC��RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))						//�ܷ�ɾ��RC
		{
			MessageBox(NULL, _T("�ͷ�RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										//��RC��ΪNULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC))					//�����ܷ��ͷ�DC
	{
		MessageBox(NULL, _T("�ͷ�DCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))					//�ܷ����ٴ���
	{
		MessageBox(NULL, _T("���ٴ���ʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;									//�Ѵ��ھ����ΪNULL
	}
	if (!UnregisterClass(_T("OpenG"),hInstance))		//�ܷ�ע����
	{
		MessageBox(NULL, _T("����ע�������ࡣ"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;								//��hInstance��ΪNULL
	}
}

BOOL CreateGLWindow(LPCWSTR title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;									//�������ƥ��Ľ��
	WNDCLASS wc;										//������ṹ
	DWORD dwExStyle;									//��չ���ڷ��
	DWORD dwStyle;										//���ڷ��
	RECT WindowRect;									//ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left = (long)0;							//��Left ��Ϊ0
	WindowRect.right = (long)width;						//��Right ��ΪҪ��Ŀ��
	WindowRect.bottom = (long)height;					//��Bottom ��ΪҪ��ĸ߶�
	WindowRect.top = (long)0;							//��Top ��Ϊ0
	fullscreen = fullscreenflag;						//����ȫ��ȫ����־

	hInstance = GetModuleHandle(NULL);					//ȡ�����Ǵ��ڵ�ʵ��
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		//�ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc = (WndProc);							//WndProc������Ϣ
	wc.cbClsExtra = 0;									//�޶��ⴰ������
	wc.cbWndExtra = 0;									//�޶��ⴰ������
	wc.hInstance = hInstance;							//����ʵ��
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);				//װ��ȱʡͼ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//װ�����ָ��
	wc.hbrBackground = NULL;							//GL����Ҫ����
	wc.lpszMenuName = NULL;								//����Ҫ�˵�
	wc.lpszClassName = _T("OpenGL");					//�趨������

	if (!RegisterClass(&wc))							//����ע�ᴰ����
	{
		MessageBox(NULL,_T("ע�ᴰ��ʧ��"),_T("����"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									//�˳�������FALSE
	}

	if (fullscreen)																			//Ҫ����ȫ��ģʽ��
	{
		DEVMODE dmScreenSettings;															//�豸ģʽ
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));								//ȷ���ڴ����Ϊ0
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);									//Devmode�ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth = width;												//��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight = height;												//��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel = bits;												//ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;			

		//����������ʾģʽ�����ؽ����ע��CDS_FULLSCREEN��ȥ��״̬��
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			//��ģʽʧ�ܣ��ṩ����ѡ��:�˳����ڴ���������
			if (MessageBox(NULL,_T("ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\n ʹ�ô���ģʽ"),_T("NeHe GL"),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen = FALSE;															//ѡ�񴰿�ģʽ
			}
			else
			{
			//����һ���Ի��򣬸����û��������
				MessageBox(NULL,_T("���򽫹ر�"),_T("����"),MB_OK|MB_ICONSTOP);
				return FALSE;																//�˳�������
			}
		}
	}
	if (fullscreen)																			//�Դ���ȫ��ģʽ��
	{
		dwExStyle = WS_EX_APPWINDOW;														//��չ������
		dwStyle = WS_POPUP;																	//������
		ShowCursor(FALSE);																	//�������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;										//��չ������
		dwStyle = WS_OVERLAPPEDWINDOW;														//������
	}
	AdjustWindowRectEx(&WindowRect,dwStyle,FALSE,dwExStyle);								//�������ڴﵽ����Ҫ��Ĵ�С

	if (!(hWnd = CreateWindowEx(dwExStyle,													//��չ������
		_T("OpenGL"),																		//������
		title,																				//���ڱ���
		WS_CLIPSIBLINGS |																	//����Ĵ���������
		WS_CLIPCHILDREN |																	//����Ĵ���������
		dwStyle,																			//ѡ��Ĵ�������
		0, 0,																				//����λ��
		WindowRect.right - WindowRect.left,													//��������õĴ��ڿ��
		WindowRect.bottom - WindowRect.top,													//��������õĴ��ڸ߶�
		NULL,																				//�޸�����
		NULL,																				//�޲˵�
		hInstance,																			//ʵ��
		NULL)))																				//����WM_CREATE�����κζ���
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL,_T("���ܴ���һ�������豸������"),_T("����"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd =														//pfd���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),														//�����������Ĵ�С
		1,																					//�汾��
		PFD_DRAW_TO_WINDOW|																	//��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL|																	//��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,																	//��ʽ����֧��˫����
		PFD_TYPE_RGBA,																		//����RGBA��ʽ
		bits,																				//ѡ��ɫ�����
		0,0,0,0,0,0,																		//���Ե�ɫ��λ
		0,																					//��Alpha����
		0,																					//����Shift Bit
		0,																					//���ۼӻ���
		0,0,0,0,																			//���Ծۼ�λ
		16,																					//16λ Z-���棨��Ȼ��棩
		0,																					//���ɰ建��
		0,																					//�޸�������
		PFD_MAIN_PLANE,																		//����ͼ��
		0,																					//Reserved
		0,0,0																				//���Բ�����
	};

	if (!(hDC=GetDC(hWnd)))																	//��ȡ���豸����������
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL,_T("���ܴ���һ����ƥ������ظ�ʽ"),_T("����"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		//���� FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))											//Windows�ҵ���Ӧ�����ظ�ʽ����
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL,_T("�����������ظ�ʽ"),_T("����"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	if (!(SetPixelFormat(hDC,PixelFormat,&pfd)))											//�ܹ��������ظ�ʽ��
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL, _T("�����������ظ�ʽ"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))														//�ܷ�ȡ����ɫ������
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL, _T("���ܴ���OpenGL��Ⱦ������"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	if (!wglMakeCurrent(hDC,hRC))															//���Լ�����ɫ������
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL, _T("���ܼ��ǰ��OpenGL��Ⱦ������"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	ShowWindow(hWnd,SW_SHOW);																//��ʾ����
	SetForegroundWindow(hWnd);																//����������ȼ�
	SetFocus(hWnd);																			//���ü��̵Ľ������˴���
	ReSizeGLScene(width,height);															//����GL͸����Ļ

	if (!InitGL())																			//��ʼ���½���GL����
	{
		KillGLWindow();																		//������ʾ��
		MessageBox(NULL, _T("��ʼ��ʧ��"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;																		//����FALSE
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(
	HWND hWnd,																				//���ڵľ��
	UINT uMsg,																				//���ڵ���Ϣ
	WPARAM wParam,																			//���ӵ���Ϣ����
	LPARAM lParam)																			//���ӵ���Ϣ����
{
	switch (uMsg)
	{
		case WM_ACTIVATE:																	//���Ӵ��ڼ�����Ϣ
		{
			if (!HIWORD(wParam))															//�����С��״̬
			{
				active = TRUE;																//�����ڼ���״̬
			}
			else
			{
				active = FALSE;																//�����ټ���
			}
			return 0;																		//������Ϣѭ��
		}
		case WM_SYSCOMMAND:																	//ϵͳ�ж�����
		{
			switch (wParam)																	//���ϵͳ����
			{
				case SC_SCREENSAVE:															//����Ҫ���У�
				case SC_MONITORPOWER:														//��ʾ��Ҫ����ڵ�ģʽ��
				return 0;																	//��ֹ����
			}
			break;																			//�˳�
		}
		case WM_CLOSE:																		//�յ�Close��Ϣ
		{
			PostQuitMessage(0);																//�����˳���Ϣ
			return 0;																		//����
		}
		case WM_KEYUP:																		//�м��ſ�ô��
		{
			keys[wParam] = FALSE;															//����ǣ���ΪFALSE
			return 0;																		//����
		}
		case WM_SIZE:																		//����OpenGL���ڴ�С	
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));									//LoWord=Width,HiWord=Height
			return 0;																		//����
		}
	}
	//��DefWindowProc��������δ������Ϣ��
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(		HINSTANCE hInstance,												//��ǰ����ʵ��
						HINSTANCE hPrevInstance,											//ǰһ������ʵ��
						LPSTR	lpCmdLine,													//�����в���
						int nCmdShow														//������ʾ״̬
				  )
{
	MSG msg;																				//Windows��Ϣ�ṹ
	BOOL done = FALSE;																		//����ѭ����BOOL����
	//��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL,_T("������ȫ��ģʽ��������"),_T("����ȫ��ģʽ"),MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;																	//FALSEΪ����ģʽ
	}
	//����OpenGL����
	if (!CreateGLWindow(_T("OpenGL������"),640,480,16,fullscreen))
	{
		return 0;																			//ʧ���˳�
	}
	while (!done)																			//����ѭ��ֱ��done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))											//����Ϣ�ڵȴ���
		{
			if (msg.message = WM_QUIT)														//�յ��˳���Ϣ
			{
				done = TRUE;																//�ǣ���done=TRUE
			}
			else                                                                            //���ǣ���������Ϣ
			{
				TranslateMessage(&msg);														//������Ϣ
				DispatchMessage(&msg);														//������Ϣ
			}
		}
		else																				//���û����Ϣ
		{
			//���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active)																		//���򼤻�����
			{
				if (keys[VK_ESCAPE])														//ESC���Ƿ񱻰��£�
				{
					done = TRUE;															//ESC�����˳��ź�
				}
				else																		//�����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();															//���Ƴ���
					SwapBuffers(hDC);														//�������棨˫���棩
				}
			}
			if (keys[VK_F1])																//F1���Ƿ񱻰���
			{
				keys[VK_F1] = FALSE;														//���ǣ�ʹ��Ӧ��Key�����е�ֵΪFALSE
				KillGLWindow();																//���ٵ�ǰ�Ĵ���
				fullscreen = !fullscreen;													//�л�ȫ��/����ģʽ
				//�ؽ�OpenGL����
				if (!CreateGLWindow(_T("OpenGL������"),640,480,16,fullscreen))
				{
					return 0;																//�������δ�ܴ����������˳�
				}
			}
		}
	}
	//�رճ���
	KillGLWindow();																			//���ٴ���
	return (msg.wParam);																	//�˳�����
}

