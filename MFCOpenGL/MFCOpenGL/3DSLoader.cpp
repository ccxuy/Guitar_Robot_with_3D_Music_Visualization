//�ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�:
#include <stdio.h>
#include <math.h>
#include "stdafx.h"
#include "5DG_Window.h"
#include "Texture.h"
#include "3ds.h"
#include "Camera.h"
#include "Com.h"


//�ڴ˴��������Ҫ��Ŀ⵽��������:
#pragma comment( lib, "opengl32.lib")
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "glaux.lib" )

void actionJump(float* height, bool* jumpFlag);
void calculateFPS();
GLvoid BuildFont(GLvoid);
GLvoid KillFont(GLvoid)	;
GLvoid glPrint(const char *fmt, ...);
float GetTime();

//�ڴ˴�����ȫ�ֱ���:
GL_Window*	OGL_window;
Keys*		OGL_keys;
//extern bool g_NoteEight2Jump;

//�ڴ˴������û�����:
int fps(72);			//֡��
float last_time(0.0f);

CCamera camera;

C3DSModel skybox;

C3DSModel	tower3DS;
C3DSModel	gundam3DS;
C3DSModel	background3DS;
C3DSModel	noteEighth3DS;
C3DSModel	noteEighth23DS;
C3DSModel	noteFourth3DS;
C3DSModel	noteNoteOneth3DS;
C3DSModel	note_Whole3DS;
C3DSModel	note_Half3DS;
C3DSModel	note_Quater3DS;
C3DSModel	note_Eighth3DS;
C3DSModel	note_Sixteenth3DS;
C3DSModel	note_ThirtySecond3DS;
C3DSModel	note_SixtyFourth3DS;
GLfloat		angle_Y;
GLuint		groundTex;
BOOL		showTower;

//volatile bool g_NoteEight2Jump=true;
float noteWholeY=0.0f;
float noteHalfY=0.0f;
float noteQuaterY=0.0f;
float noteEighthY=0.0f;
float noteSixteenthY=0.0f;
float noteThirtySecondY=0.0f;
float noteEighthDoubleY=0.0f;

// ���ù���
GLfloat posl[] = {0.0f, 22.0f, 1.0f, 1.0f};
GLfloat amb[]  = {0.3f, 0.3f, 0.3f ,1.0f};
GLfloat spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat df = 100.0;

BOOL Initialize(GL_Window* window, Keys* keys)						// ��ʼ������
{
	//����ȫ�ֱ���
	OGL_window	= window;
	OGL_keys	= keys;

	// �ڴ˴���ʼ�����Ƴ���
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// ����Ϊ��ɫ
	glClearDepth(1.0f);												// ������Ȼ���
	glDepthFunc(GL_LEQUAL);											// ѡ����Ȳ��Է�ʽ
	glEnable(GL_DEPTH_TEST);										// ������Ȳ���
	glShadeModel(GL_SMOOTH);										// �����������ƽ����ʽ
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// �ϸ��͸�Ӽ���


	//tower3DS.Load("tower.3ds");										// ����3ds�ļ�
	//gundam3DS.Load("gundam.3ds");									// ����3ds�ļ�
	//background3DS.Load("model/GardonBackground.3DS");
	noteEighth3DS.Load("model/musicalNoteEighth.3DS");
	/*noteEighth3DS.Load("model/musicalNoteEighth.3DS");
	noteEighth23DS.Load("model/musicalNoteEighth_Two.3DS");
	noteFourth3DS.Load("model/musicalNoteFourth.3DS");*/
	note_Whole3DS.Load("model/WholeNote.3DS");
	note_Half3DS.Load("model/HalfNote.3DS");
	noteFourth3DS.Load("model/FourthNote.3DS");
	note_Eighth3DS.Load("model/EighthNote.3DS");
	note_Sixteenth3DS.Load("model/SixteenthNote.3DS");
	note_ThirtySecond3DS.Load("model/ThirtySecondNote.3DS");

	
	noteEighth23DS.Load("model/EighthNoteDouble.3DS");

	BuildFont();		//��������

	//BuildTexture("ground.jpg",groundTex);

	// ���ù��պͲ���
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, &df);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, posl);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glEnable(GL_LIGHT0);

	GLfloat LightAmbient[]= { 0.6f, 0.6f, 0.6f, 1.0f }; 
	GLfloat LightDiffuse[]= { 0.8f, 0.8f, 0.8f, 0.8f };
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);
 
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	skybox.Load("model/galaxy.3DS");

	return TRUE;													// ��ʼ���ɹ�����TRUE
}

void DrawSceneGL(void)												// ���Ƴ���
{
	calculateFPS();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// �����������Ȼ���
	glLoadIdentity();												// ���õ�ǰ����
	
	//glRasterPos2f(-640, -480);
	glPrint("FPS:%d", fps);
	//�ڴ˴���Ӵ�����л���:

	// �����ӵ�
	gluLookAt(0.0f, 32.0f, 53.0f,
				0.0f, 27.0f, 0.0f,
				0.0f, 1.0f, 0.0f);

	
	//camera.Look();
	//camera.SetViewByMouse();

	//��ת����
	glRotatef(angle_Y, 0.0f, 1.0f, 0.0f);

	// ���Ƶ���
	/*glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTex);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(4.0f, 0.0f); glVertex3f( 20.0f, 0.0f, 20.0f);
		glTexCoord2f(4.0f, 4.0f); glVertex3f( 20.0f, 0.0f,-20.0f);
		glTexCoord2f(0.0f, 4.0f); glVertex3f(-20.0f, 0.0f,-20.0f);
	glEnd();*/

	//���Ƴ���
	//background3DS.Render();
	skybox.Render();

	// ��ʾTower��Gundam
	glEnable(GL_LIGHTING);
	
	//glMatrixMode (GL_MODELVIEW);
    /*glLoadIdentity ();*/
	glScalef (0.3f,0.3f,0.3f);//Resize all unit below
    glTranslatef (0.0f, 50.0f, 0.0f);//Stage height
	glPushMatrix();
    glTranslatef (0.0f, 20.0f, 0.0f);//Raise self height
	actionJump(&noteWholeY,&g_NoteWholeJump);
    glTranslatef (20.0f, noteWholeY, 48.0f);
	glScalef (0.6f,0.6f,0.6f);
	note_Whole3DS.Render();
	glPopMatrix();

	//Note2
	glPushMatrix();
	glScalef (0.7f,0.7f,0.7f);
    glTranslatef (0.0f, 15.0f, 0.0f);//Raise self height
	actionJump(&noteHalfY,&g_NoteHalfJump);
    glTranslatef (48.0f, noteHalfY, 20.0f);
	note_Half3DS.Render();
	glPopMatrix();

	//Note4
	glPushMatrix();
	//glScalef (2.0f,2.0f,2.0f);
	actionJump(&noteQuaterY,&g_NoteFourthJump);
    glTranslatef (48.0f, noteQuaterY, -20.0f);
	noteFourth3DS.Render();
	glPopMatrix();

	//Note8
	glPushMatrix();
	glScalef (1.7f,1.7f,1.7f);
	actionJump(&noteEighthY,&g_NoteEightJump);
    glTranslatef (20.0f, noteEighthY, -48.0f);
	note_Eighth3DS.Render();
	glPopMatrix();

	//note 16
	glPushMatrix();
	glScalef (1.8f,1.8f,1.8f);
	actionJump(&noteSixteenthY,&g_NoteSixteenthJump);
    glTranslatef (-20.0f, noteSixteenthY, -48.0f);
	note_Sixteenth3DS.Render();
	glPopMatrix();

	//Note 32
	glPushMatrix();
	glScalef (1.8f,1.8f,1.8f);
	actionJump(&noteThirtySecondY,&g_NoteThirtySecondJump);
    glTranslatef (-48.0f, noteThirtySecondY, -20.0f);
	note_ThirtySecond3DS.Render();
	glPopMatrix();

	//Note 8 * 2
	glPushMatrix();
	actionJump(&noteEighthDoubleY,&g_NoteEight2Jump);
    glTranslatef (-48.0f, noteEighthDoubleY, 20.0f);
	noteEighth23DS.Render();
	glPopMatrix();

	/*glPushMatrix();
    glTranslatef (-40.0f, 0.0f, 40.0f);
	noteEighth3DS.Render();
	glPopMatrix();
	glPushMatrix();
    glTranslatef (40.0f, 0.0f, 40.0f);
	noteEighth23DS.Render();
	glPopMatrix();
	glPushMatrix();
    glTranslatef (-40.0f, 0.0f, -40.0f);
	noteFourth3DS.Render();
	glPopMatrix();*/
	/*if (showTower)
	{
		glDisable(GL_CULL_FACE);
		tower3DS.Render();
	}
	else
	{
		glEnable(GL_CULL_FACE);
		gundam3DS.Render();
	}*/

	angle_Y += 0.4f;


	glFlush ();														// ˢ��GL�������
}

void Update()														// �ڴ˴����¶���Ϣ�Ķ���
{
	if (OGL_keys->keyDown[VK_ESCAPE] == TRUE)						// �ж�ESC���Ƿ���
	{
		TerminateApplication (OGL_window);							// �������� 	   
	}

	if (OGL_keys->keyDown[VK_F1] == TRUE)							// �ж�F1�Ƿ���
	{
		PostMessage (OGL_window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);	// ��ȫ��/����ģʽ���л�
	}

	//if (OGL_keys->keyDown['1'] == TRUE)								// �жϰ���'1'�Ƿ���
	//{
	//	showTower = FALSE;											// ��ʾGundam
	//}

	//if (OGL_keys->keyDown['2'] == TRUE)								// �жϰ���'2'�Ƿ���
	//{
	//	showTower = TRUE;											// ��ʾTower
	//}
}

void Deinitialize(void)												// �ڴ˴����˳�ǰɨβ����
{
	KillFont();			//ɾ������
	tower3DS.Release();
	gundam3DS.Release();
}

void actionJump(float* height, bool* jumpFlag){
	if( (*height)<=21.0 && (*jumpFlag)==true){
		(*height) +=5;
	}else if( (*height)>=21){
		(*height)-=5;
		(*jumpFlag)=false;
	}else if( (*height)>0 && (*jumpFlag)==false){
		(*height)-=5;
	}
}

void calculateFPS(){
	//���� FPS
	static int counter=0;
	if(GetTime()-last_time>=1.0f)
	{
		fps=counter;
		counter=0;
		last_time=GetTime();
	}
	counter++;
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Font Begin /////////////////////////////////////////////

GLuint	base;				// Base Display List For The Font Set

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-50,							// Height Of Font
						50,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Arial");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Font End ////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ��׼�ļ�ʱ�� ////////////////////////////////////////
float GetTime()
{
  static bool init = false;
  static bool hires = false;
  static __int64 freq = 1;
  if(!init)
  {
    hires = !QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
    if(!hires)
      freq = 1000;
    init = true;
  }

  __int64 now;

  if(hires)
    QueryPerformanceCounter((LARGE_INTEGER *)&now);
  else
    now = GetTickCount();

  return (float)((double)now / (double)freq);
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ��׼�ļ�ʱ������ ////////////////////////////////////