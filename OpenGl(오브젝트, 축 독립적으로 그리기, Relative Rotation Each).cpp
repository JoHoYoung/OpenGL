//--------------------------------------------------------------User's Guide---------------------------------------------------------------
//             1. 오른쪽 마우스의 메뉴를 따라 1. 폴리곤 그리기 2. 물체 회전 3. 축 회전 4. 프로젝션 모드 변환 5. 오브젝트 리셋
//					6. 축 리셋 7. 모두 리셋 8. 윈도우 초기화 9. 종료 등의 기능을 수행할 수 있다.
//				2. 축, 오브젝트 리셋시 축, 오브젝트 간의 상대적인 회전을 고려하여 리셋된다. 예를들어 축을 30도, 오브젝트 를 30도 회전한 후
//					축을 리셋하면 둘다 회전값이 없는 모양으로 표현된다/
//				3. Z축 회전은 반영하지 않았으며 각각 x, y축으로 회전이 가능하다.
//				4. 폴리곤의 앞 면의 Z값은 0으로 설정되어 있다.                                                     
//--------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include<gl.H>
using namespace std;

void InitGraphics();

GLfloat Vertex[20][3], VertexB[20][3]; //배열에 정점좌표(x좌표, y좌표)를 저장
GLint NumVertex = 0; //배열의 개수로 사용할 변수
GLint AddInputMode = 1; 
GLboolean ProjectionMode = GL_TRUE; // TRUE: Orthographic, FALSE: Perspective
GLfloat mx, my; //마우스누른위치 변수선언 
GLfloat mdx, mdy; //마우스놓은위치 변수선언
GLfloat bx_up = -1.0, by_up = -1.0, bx_lo = 1.0, by_lo = 1.0;
GLfloat centerx, centery, centerz;
GLfloat theta = 0.0, angle = 0.0;
GLfloat tx, ty;
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// 오브젝트의 회전값을 저장할 행렬
GLfloat TM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// M의 역행렬을 저장할 행렬
GLfloat AM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// 축의 회전값을 저장할 행렬
GLfloat TAM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// TM의 역행렬을 저장할 행렬
GLfloat ObjM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// 오브젝트를 그리는데 사용할 행렬
GLfloat AxisM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// 축을 그리는데 사용할 행렬
GLfloat slope, dx, dy;
int RotAxis = -1;

void TransPoseMatrix(GLfloat *start, GLfloat *destination)		// 회전행렬의 역행렬을 구해줄 함수
{																			//  회전행렬의 역행렬은 Tanspose 한것과 같기 때문 
	destination[0] = start[0];
	destination[1] = start[4];
	destination[2] = start[8];
	destination[3] = start[12];
	destination[4] = start[1];
	destination[5] = start[5];
	destination[6] = start[9];
	destination[7] = start[13];
	destination[8] = start[2];
	destination[9] = start[6];
	destination[10] = start[10];
	destination[11] = start[14];
	destination[12] = start[3];
	destination[13] = start[7];
	destination[14] = start[11];
	destination[15] = start[15];	
}

void ClearAll()						// 윈도우를 초기상태로 클리어 해주는 함수.
{	
	NumVertex = 0;
	AddInputMode = 1;
	ProjectionMode = GL_TRUE;
	InitGraphics();
	bx_up = -1.0, by_up = -1.0, bx_lo = 1.0, by_lo = 1.0;
	theta = 0.0, angle = 0.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, TM);
	glGetFloatv(GL_MODELVIEW_MATRIX, TAM);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);

	int RotAxis = -1;

}									// 모든 변수를 초기에 설정됐던 값으로 초기화한다.

void ResetObj()					// 오브젝트만 원래상태로 초기화 해줄 함수.
{
	TransPoseMatrix(M, TM);					// 돌렸던 오브젝트를 원래 대로 돌릴때 그만큼의 축의 상대적인 회전도 표현해 주어야한다.
													//	오브젝트를 30도 돌린것은 축을 -30도 돌린것과 같으므로 지금까지의 오브젝트의 회전값의 역행렬을
	glMatrixMode(GL_MODELVIEW);			// 축의 회전값에 곱해주어야한다. 역행렬은 Transpose한것과 같으므로 Transpose하여 축의 회전값을 오브젝트 회전값의 역 * 축의 회전값으로 바꿔준다.
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glMultMatrixf(TM);
	glMultMatrixf(AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);			//축의 회전값에 오브젝트 회전값의 역을 더해주는 과정.

	AM[12] = 0;
	AM[13] = 0;
	AM[14] = 0;
	
	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAxis()													//위의 오브젝트를 Reset하는 과정과 동일하며 축, 오브젝트의 입장만 바꾸어 똑같은 과정을 수행한다.				
{
	TransPoseMatrix(AM, TAM);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);
	glMultMatrixf(M);
	glMultMatrixf(TAM);
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);					//축의 회전값의 역을 현재 오브젝트의 회전값에 곱해주는 과정 수행.

	M[12] = 0;
	M[13] = 0;
	M[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAll()												// 축, 오브젝트만 리셋 시키는것이 아닌 두개 모두 초기의 상태로 돌려준다 ( 윈도우를 클리어하는것이 아니다.)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);
	
	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();

}

void AddInput(int button, int state, int x, int y) {

	mx = (x - 250.) / 250.;
	my = (250. - y) / 250.;

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)		//점을 찍을때
	{
		if (mx < bx_lo) bx_lo = mx;
		else if (mx > bx_up) bx_up = mx;
		if (my < by_lo) by_lo = my;
		else if (my > by_up) by_up = my;

		Vertex[NumVertex][0] = mx;
		Vertex[NumVertex][1] = my;
		Vertex[NumVertex][2] = 0.0;
		VertexB[NumVertex][0] = mx;
		VertexB[NumVertex][1] = my;
		NumVertex++;
	}
	else if (AddInputMode == 2 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)  //누적 로테이트 저장
	{
			glGetFloatv(GL_MODELVIEW_MATRIX, M);  //오브젝트 누적회전을 오브젝트누적회전행렬에 저장
			M[12] = 0;
			M[13] = 0;
			M[14] = 0;	
	}
	else if (AddInputMode == 3 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)   //누적 축 로테이트 저장
	{
			glGetFloatv(GL_MODELVIEW_MATRIX, AM);// 축 누적회전행렬에 저장
			AM[12] = 0;
			AM[13] = 0;
			AM[14] = 0;
	}
	glutPostRedisplay();

}


void MouseDrag(int x, int y) {
	if (AddInputMode != 1)  //점찍는 모드가 아니고, 오브젝트 회전일때
	{
		GLfloat centertx, centerty;

		mdx = (x - 250.) / 250.;
		mdy = (250. - y) / 250.;
		tx = (mdx - mx);
		ty = (mdy - my);

		slope = (mdx - mx) / (mdy - my);
		if (mdy < my)dx = sqrt(1.0 / (1. + slope * slope));
		else dx = -sqrt(1.0 / (1. + slope * slope));

		dy = -slope * dx;

		theta = atan(dy / dx)*180. / 3.14;

		if (my == mdy) theta = 90.;
		if (mdy > my) theta += 180.;

		angle = sqrt((mdy - my)*(mdy - my) + (mdx - mx)*(mdx - mx))*180. / 3.14*2.;

		glMatrixMode(GL_MODELVIEW); //모델뷰행렬을변환하겠다는의미.
		glLoadIdentity();
		gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.); // Set up viewing transformation, looking down -Z axis
		

		if (AddInputMode == 2)   //오브젝트 회전
		{
			RotAxis = 0;
		}
		else if (AddInputMode == 3)   //축 회전
		{
			RotAxis = 1;
		}

		if (RotAxis == 0)  //오브젝트회전일때
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(M);   //누적 회전
			glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);					// 오브젝트의 현재 회전값과 누적회전값을 곱하여 오브젝트를 표현할때 쓰는 행렬에 저장해준다.
		}
		else if (RotAxis == 1) //축회전일때
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(AM);   //누적 회전
			glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);					// 축의 현재 회전값과 누적 회전값을 곱하여 축을 회전할때 쓰는 행렬에 저장해 준다.
		}
		glutPostRedisplay();
	}
}

void InitGraphics(void)
{
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glShadeModel(GL_SMOOTH);
	glPointSize(5.0);
	
	glMatrixMode(GL_PROJECTION);						//현재 매트릭스모드를  GL_PROJECTION으로 변환
	glLoadIdentity();
	if (ProjectionMode) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0);			// parallel 모드로 변환
		RotAxis=-1;
	}
	else {
		gluPerspective(22.0f, 1.0, 0.1, 100.0);			// perspective 모드로 변환
		RotAxis = -1;
	}
	glutPostRedisplay();
}

void Display()
{
	int i;

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (AddInputMode == 1) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
	}
	else {
		if (RotAxis == 0)         // 오브젝트 회전일때는 회전하면서 바꾸는 모델뷰매트릭스가 오브젝트를 그리는 매트릭스 이므로 따로 매트릭스의 변경없이 그려준다.
		{							// 하지만 축을 그릴때는 오브젝트 회전값에 따라 바뀌면 안되기 때문에  Push, Pop을 이용해 독립적으로 그려지게한다.
			glPushMatrix();		
			glMatrixMode(GL_MODELVIEW);
			glLineWidth(3.0f);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glPopMatrix();
			glVertex3f(centerx, centery, centerz);
			glEnd();										// 0,0,0과 폴리곤의 무게중심을 잇는 선을 그리는 과정에서 오브젝트를 회전함에 따라 무게중심의 위치는 바뀌지만 0,0,0은 바뀌면 안되므로
															// push, pop을 이용해 그려준다.
			glColor3f(0.0, 0.0, 1.0);
			glFrontFace(GL_CW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(0.0, 1.0, 0.0);
			glFrontFace(GL_CCW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			}
			glEnd();

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			glVertex3f(centerx, centery, centerz);
			
			glEnd();
			glPushMatrix();									// 오브젝트 회전 모드에서 축은 그에 관계없이 독립적으로 그려져야 하므로  push

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glLoadMatrixf(AxisM);							// 지금까지 바꿨던 축의 회전등을 불러와서 그려줘야 하므로 축을 그릴때 쓰는 AxisM행렬을 현재 모델뷰에 불러옴.
			
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);

			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glEnd();													
			glPopMatrix();																		//다 그리면 다시 pop으로 원래것을 가져온다.
		}
		else if (RotAxis == 1)      //축 회전일때는 축과, 오브젝트의 입장만 바꿔서 위의 오브젝트회전시 축, 오브젝트를 그리는 과정을 동일하게 수행한다.
		{
			glPushMatrix();							//현재 모델뷰 푸쉬
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glLoadMatrixf(ObjM);					//오브젝트 그릴때 사용했던 행렬 불러옴.
			
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);					// 원점과 무게중심을 잇는 선을 그리기 위해.
			glLineWidth(3.0f);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glPopMatrix();
			glVertex3f(centerx, centery, centerz);
			glEnd();

			glColor3f(0.0, 0.0, 1.0);
			glFrontFace(GL_CW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(0.0, 1.0, 0.0);
			glFrontFace(GL_CCW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			}
			glEnd();

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			glVertex3f(centerx, centery, centerz);
			glEnd();

			glPopMatrix();								// 독립적으로 오브젝트를 그린후, 현재 축 회전 모드에서 바뀌고있는 모델뷰는 축을 그릴 모델뷰 이기때문에 지금 모델뷰에 계속 축을 그려준다.
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);

			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glEnd();
		}
		else {						//현재 모드가 축회전, 오브젝트 회전이 아닐경우
			glPushMatrix();						// 오브젝트를 독립적으로 그리기위해 푸쉬후 오브젝트를 그리기위한 행렬을 불러와 그린후 팝
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(ObjM);
			
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glLineWidth(3.0f);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glPopMatrix();
			glVertex3f(centerx, centery, centerz);
			glEnd();

			glColor3f(0.0, 0.0, 1.0);
			glFrontFace(GL_CW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
				glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
			}
			glEnd();

			glColor3f(0.0, 1.0, 0.0);
			glFrontFace(GL_CCW);
			glBegin(GL_POLYGON);
			for (i = 0; i < NumVertex; i++) {
				glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			}
			glEnd();
			
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			glVertex3f(centerx, centery, centerz);
			glEnd();

			glPopMatrix();										//오브젝트를 그린 후 팝.

			
			
			glPushMatrix();								//축을 그리기전 푸쉬

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(AxisM);									//축을 그리기위한 행렬을 불러옴
			
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);

			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glEnd();
			glPopMatrix();							//축을 그린후 팝.


		}
		glFlush();
	}

	glutSwapBuffers();
}

void MyMenu(int value)
{
	int i;

	switch (value) {
	case 1:										//폴리곤 그리기.
		AddInputMode = 0;
		centerx = 0.;
		centery = 0.;
		centerz = -(abs(bx_up - bx_lo) + abs(by_up - by_lo)) / 4.0;
		for (i = 0; i < NumVertex; i++) {
			centerx += Vertex[i][0];
			centery += Vertex[i][1];
			VertexB[i][2] = centerz * 2.;
		}
		centerx /= NumVertex;
		centery /= NumVertex;

		break;
	case 2:						// 오브젝트 회전
		AddInputMode = 2;
		break;
	case 3:						//축회전
		AddInputMode = 3;
		break;
	case 4:
		ProjectionMode = !ProjectionMode;	//Projection 모드 변환
		InitGraphics();
		break;
	case 5:									//오브젝트 리셋
		ResetObj();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 6:                        // 축 리셋
		ResetAxis();
		RotAxis = -1;
		glutPostRedisplay(); 
		break;
	case 7:						// 둘다 리셋.
		ResetAll();
		break;
	case 8:						//화면 클리어
		ClearAll();
		break;
	case 9:					//프로그램 종료
		exit(0);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// GLUT Window Initialization:
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("20146847_JHY");

	// Initialize OpenGL graphics state

	InitGraphics();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();											// 축을그리기위한 행렬과 오브젝트를 그리기위한 행렬을 View포인트를 설정하여 그 값들로 초기화 함.
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);
	
	// Register callbacks:
	glutDisplayFunc(Display);
	glutMouseFunc(AddInput);
	glutMotionFunc(MouseDrag);
	
	// Create our popup menu
	glutCreateMenu(MyMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("RotateObjects", 2);
	glutAddMenuEntry("RoatAxis", 3);
	glutAddMenuEntry("Orthographic/Perspective", 4);
	glutAddMenuEntry("ResetObjects", 5);
	glutAddMenuEntry("ResetAxis", 6);
	glutAddMenuEntry("ResetAll", 7);
	glutAddMenuEntry("Clear", 8);
	glutAddMenuEntry("Exit", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
} 