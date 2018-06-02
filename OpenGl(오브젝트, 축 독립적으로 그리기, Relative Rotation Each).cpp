//--------------------------------------------------------------User's Guide---------------------------------------------------------------
//             1. ������ ���콺�� �޴��� ���� 1. ������ �׸��� 2. ��ü ȸ�� 3. �� ȸ�� 4. �������� ��� ��ȯ 5. ������Ʈ ����
//					6. �� ���� 7. ��� ���� 8. ������ �ʱ�ȭ 9. ���� ���� ����� ������ �� �ִ�.
//				2. ��, ������Ʈ ���½� ��, ������Ʈ ���� ������� ȸ���� ����Ͽ� ���µȴ�. ������� ���� 30��, ������Ʈ �� 30�� ȸ���� ��
//					���� �����ϸ� �Ѵ� ȸ������ ���� ������� ǥ���ȴ�/
//				3. Z�� ȸ���� �ݿ����� �ʾ����� ���� x, y������ ȸ���� �����ϴ�.
//				4. �������� �� ���� Z���� 0���� �����Ǿ� �ִ�.                                                     
//--------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include<gl.H>
using namespace std;

void InitGraphics();

GLfloat Vertex[20][3], VertexB[20][3]; //�迭�� ������ǥ(x��ǥ, y��ǥ)�� ����
GLint NumVertex = 0; //�迭�� ������ ����� ����
GLint AddInputMode = 1; 
GLboolean ProjectionMode = GL_TRUE; // TRUE: Orthographic, FALSE: Perspective
GLfloat mx, my; //���콺������ġ �������� 
GLfloat mdx, mdy; //���콺������ġ ��������
GLfloat bx_up = -1.0, by_up = -1.0, bx_lo = 1.0, by_lo = 1.0;
GLfloat centerx, centery, centerz;
GLfloat theta = 0.0, angle = 0.0;
GLfloat tx, ty;
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// ������Ʈ�� ȸ������ ������ ���
GLfloat TM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// M�� ������� ������ ���
GLfloat AM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };				// ���� ȸ������ ������ ���
GLfloat TAM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// TM�� ������� ������ ���
GLfloat ObjM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// ������Ʈ�� �׸��µ� ����� ���
GLfloat AxisM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };			// ���� �׸��µ� ����� ���
GLfloat slope, dx, dy;
int RotAxis = -1;

void TransPoseMatrix(GLfloat *start, GLfloat *destination)		// ȸ������� ������� ������ �Լ�
{																			//  ȸ������� ������� Tanspose �ѰͰ� ���� ���� 
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

void ClearAll()						// �����츦 �ʱ���·� Ŭ���� ���ִ� �Լ�.
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

}									// ��� ������ �ʱ⿡ �����ƴ� ������ �ʱ�ȭ�Ѵ�.

void ResetObj()					// ������Ʈ�� �������·� �ʱ�ȭ ���� �Լ�.
{
	TransPoseMatrix(M, TM);					// ���ȴ� ������Ʈ�� ���� ��� ������ �׸�ŭ�� ���� ������� ȸ���� ǥ���� �־���Ѵ�.
													//	������Ʈ�� 30�� �������� ���� -30�� �����Ͱ� �����Ƿ� ���ݱ����� ������Ʈ�� ȸ������ �������
	glMatrixMode(GL_MODELVIEW);			// ���� ȸ������ �����־���Ѵ�. ������� Transpose�ѰͰ� �����Ƿ� Transpose�Ͽ� ���� ȸ������ ������Ʈ ȸ������ �� * ���� ȸ�������� �ٲ��ش�.
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glMultMatrixf(TM);
	glMultMatrixf(AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);			//���� ȸ������ ������Ʈ ȸ������ ���� �����ִ� ����.

	AM[12] = 0;
	AM[13] = 0;
	AM[14] = 0;
	
	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAxis()													//���� ������Ʈ�� Reset�ϴ� ������ �����ϸ� ��, ������Ʈ�� ���常 �ٲپ� �Ȱ��� ������ �����Ѵ�.				
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
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);					//���� ȸ������ ���� ���� ������Ʈ�� ȸ������ �����ִ� ���� ����.

	M[12] = 0;
	M[13] = 0;
	M[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAll()												// ��, ������Ʈ�� ���� ��Ű�°��� �ƴ� �ΰ� ��� �ʱ��� ���·� �����ش� ( �����츦 Ŭ�����ϴ°��� �ƴϴ�.)
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

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)		//���� ������
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
	else if (AddInputMode == 2 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)  //���� ������Ʈ ����
	{
			glGetFloatv(GL_MODELVIEW_MATRIX, M);  //������Ʈ ����ȸ���� ������Ʈ����ȸ����Ŀ� ����
			M[12] = 0;
			M[13] = 0;
			M[14] = 0;	
	}
	else if (AddInputMode == 3 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)   //���� �� ������Ʈ ����
	{
			glGetFloatv(GL_MODELVIEW_MATRIX, AM);// �� ����ȸ����Ŀ� ����
			AM[12] = 0;
			AM[13] = 0;
			AM[14] = 0;
	}
	glutPostRedisplay();

}


void MouseDrag(int x, int y) {
	if (AddInputMode != 1)  //����� ��尡 �ƴϰ�, ������Ʈ ȸ���϶�
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

		glMatrixMode(GL_MODELVIEW); //�𵨺��������ȯ�ϰڴٴ��ǹ�.
		glLoadIdentity();
		gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.); // Set up viewing transformation, looking down -Z axis
		

		if (AddInputMode == 2)   //������Ʈ ȸ��
		{
			RotAxis = 0;
		}
		else if (AddInputMode == 3)   //�� ȸ��
		{
			RotAxis = 1;
		}

		if (RotAxis == 0)  //������Ʈȸ���϶�
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(M);   //���� ȸ��
			glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);					// ������Ʈ�� ���� ȸ������ ����ȸ������ ���Ͽ� ������Ʈ�� ǥ���Ҷ� ���� ��Ŀ� �������ش�.
		}
		else if (RotAxis == 1) //��ȸ���϶�
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(AM);   //���� ȸ��
			glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);					// ���� ���� ȸ������ ���� ȸ������ ���Ͽ� ���� ȸ���Ҷ� ���� ��Ŀ� ������ �ش�.
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
	
	glMatrixMode(GL_PROJECTION);						//���� ��Ʈ������带  GL_PROJECTION���� ��ȯ
	glLoadIdentity();
	if (ProjectionMode) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0);			// parallel ���� ��ȯ
		RotAxis=-1;
	}
	else {
		gluPerspective(22.0f, 1.0, 0.1, 100.0);			// perspective ���� ��ȯ
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
		if (RotAxis == 0)         // ������Ʈ ȸ���϶��� ȸ���ϸ鼭 �ٲٴ� �𵨺��Ʈ������ ������Ʈ�� �׸��� ��Ʈ���� �̹Ƿ� ���� ��Ʈ������ ������� �׷��ش�.
		{							// ������ ���� �׸����� ������Ʈ ȸ������ ���� �ٲ�� �ȵǱ� ������  Push, Pop�� �̿��� ���������� �׷������Ѵ�.
			glPushMatrix();		
			glMatrixMode(GL_MODELVIEW);
			glLineWidth(3.0f);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glPopMatrix();
			glVertex3f(centerx, centery, centerz);
			glEnd();										// 0,0,0�� �������� �����߽��� �մ� ���� �׸��� �������� ������Ʈ�� ȸ���Կ� ���� �����߽��� ��ġ�� �ٲ����� 0,0,0�� �ٲ�� �ȵǹǷ�
															// push, pop�� �̿��� �׷��ش�.
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
			glPushMatrix();									// ������Ʈ ȸ�� ��忡�� ���� �׿� ������� ���������� �׷����� �ϹǷ�  push

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glLoadMatrixf(AxisM);							// ���ݱ��� �ٲ�� ���� ȸ������ �ҷ��ͼ� �׷���� �ϹǷ� ���� �׸��� ���� AxisM����� ���� �𵨺信 �ҷ���.
			
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
			glPopMatrix();																		//�� �׸��� �ٽ� pop���� �������� �����´�.
		}
		else if (RotAxis == 1)      //�� ȸ���϶��� ���, ������Ʈ�� ���常 �ٲ㼭 ���� ������Ʈȸ���� ��, ������Ʈ�� �׸��� ������ �����ϰ� �����Ѵ�.
		{
			glPushMatrix();							//���� �𵨺� Ǫ��
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glLoadMatrixf(ObjM);					//������Ʈ �׸��� ����ߴ� ��� �ҷ���.
			
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);					// ������ �����߽��� �մ� ���� �׸��� ����.
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

			glPopMatrix();								// ���������� ������Ʈ�� �׸���, ���� �� ȸ�� ��忡�� �ٲ���ִ� �𵨺�� ���� �׸� �𵨺� �̱⶧���� ���� �𵨺信 ��� ���� �׷��ش�.
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
		else {						//���� ��尡 ��ȸ��, ������Ʈ ȸ���� �ƴҰ��
			glPushMatrix();						// ������Ʈ�� ���������� �׸������� Ǫ���� ������Ʈ�� �׸������� ����� �ҷ��� �׸��� ��
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

			glPopMatrix();										//������Ʈ�� �׸� �� ��.

			
			
			glPushMatrix();								//���� �׸����� Ǫ��

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(AxisM);									//���� �׸������� ����� �ҷ���
			
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
			glPopMatrix();							//���� �׸��� ��.


		}
		glFlush();
	}

	glutSwapBuffers();
}

void MyMenu(int value)
{
	int i;

	switch (value) {
	case 1:										//������ �׸���.
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
	case 2:						// ������Ʈ ȸ��
		AddInputMode = 2;
		break;
	case 3:						//��ȸ��
		AddInputMode = 3;
		break;
	case 4:
		ProjectionMode = !ProjectionMode;	//Projection ��� ��ȯ
		InitGraphics();
		break;
	case 5:									//������Ʈ ����
		ResetObj();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 6:                        // �� ����
		ResetAxis();
		RotAxis = -1;
		glutPostRedisplay(); 
		break;
	case 7:						// �Ѵ� ����.
		ResetAll();
		break;
	case 8:						//ȭ�� Ŭ����
		ClearAll();
		break;
	case 9:					//���α׷� ����
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
	glLoadIdentity();											// �����׸������� ��İ� ������Ʈ�� �׸������� ����� View����Ʈ�� �����Ͽ� �� ����� �ʱ�ȭ ��.
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