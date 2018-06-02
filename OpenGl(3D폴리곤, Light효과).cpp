//--------------------------------------------------------------User's Guide---------------------------------------------------------------
//				
//						**�� ���α׷��� 4���� ���� �Է��ؾ��ϸ� �ð�ݴ���� ������ �Է��� �־�� �ùٸ� �������� �����ȴ�.***
//						**  �� ���α׷��� �ΰ��� ���� ����ϸ� �����ϼ� �ִ� ���� �ʱ���ġ�� 0,0,3 �̸� ����ִ� ���� 3,3,3�� �����Ǿ��ִ�.
//
//          1. ������ ���콺�� �޴��� ���� 1. ������ �׸��� 2. ��ü ȸ�� 3. �� ȸ�� 4. �������� ��� ��ȯ 5. �� �������� �׸���
//               6. Vertex�������� �׸��� 7. ������Ʈ ���� 8. ��(��) ���� 9. ��ü���� 10. Ŭ���� 11.���� ���� ����� ������ �� �ִ�.
//			2. ������ �簢���� �׸� �� ������ ���� �ð�ݴ���� ������ �Է��ؾ� �Ѵ�. �׷��������� ���ϴ� ����� ���� �� ����.
//          3. ��, ������Ʈ ���½� ��, ������Ʈ ���� ������� ȸ���� ����Ͽ� ���µȴ�. ������� ���� 30��, ������Ʈ �� 30�� ȸ���� ��
//               ���� �����ϸ� �Ѵ� ȸ������ ���� ������� ǥ���ȴ�.
//			4. ���� �ΰ��� �׷��� ������ �ϳ��� ���� �¾�ó�� ��������� ������ �� ����. ������ ���� ���� ������ ���� ���ư��� �ȴ�.
//          5. �־��� �޴��� ���� �������͸� �Ѱų� �� �� �ִ�.
//          6. �������� �� ���� Z���� 0���� �����Ǿ� �ִ�.  
//			7. ���� ��ȭ�ϴ� ��ġ�� ���������� �����ϱ� ��ƴ�. ������ ���� �׷� �뷫���� ���� ��ġ�� �׷� ���ظ� ���ϰ� �����Ͽ���.
//			8. �� ���� ��ġ�� �������� ���ظ� ���� ���� �Ѱ�����, ��Ȯ�� ���� ��ġ�� �ƴϴ�.			- 20146847 ��ȣ��-
//--------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <gl/glut.h>
#include<gl/gl.H>
using namespace std;

void InitGraphics();
///////////////////////  �� ����, ���� ����, ���� �����ϱ� ���� ��� ����.//////////////////////////////////////////////////
GLfloat light0_pos[] = { 0.0, 0.0f, 3.0f, 1.0 };// ������ �� �ִ� ���� ��ġ.
GLfloat diffuse0[] = { 0.6, 0.6f, 0.6f, 1.0 };   //
GLfloat ambient0[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //
GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat direction0[] = { 0.0,0.0,5.0,1.0 };		//������ �� �ִ� ���� ��������.

GLfloat Sunpos[] = { 3.0, 3.0f, 3.0f, 1.0 };		//������ �� ���� �⺻������ ����ִ� ���� ��ġ
GLfloat Sundiffuse[] = { 0.1f, 0.1f, 0.1f, 1.0 };   //�л걤
GLfloat Sunambient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //�ֺ���
GLfloat Sunspecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat Sundirection[] = { 0.0,0.0,5.0,1.0 };		//������ �� ���� �⺻������ ����ִ� ���� ��������


GLfloat emission[] = { 0.1, 0.0, 0.3, 1.0 };
GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shine[] = { 1.0, 1.0,1.0,1.0 };						//���� ������ ���� ��������.

GLfloat color[] = { 1.0, 0.0, 1.0, 1.0 };
GLfloat color1[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat color2[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat color3[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat color4[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat color5[] = { 1.0, 0.0, 0.0, 1.0 };						//�� ����� �� ������ ���� ���

GLfloat Black[] = { 0.0,0.0,0.0,1.0 };
GLfloat White[] = { 1.0,1.0,1.0,1.0 };							//����� �������� ǥ���ϱ� ���� ���
GLfloat Sun[] = { 1.0,1.0,0.0,1.0 };							//	������� ���Ǹ����� �׷��� ���� ��ġ�� ǥ���� Sphere�� ��.
////////////////////////////////////////////////////////////////////////////

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
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // ������Ʈ�� ȸ������ ������ ���
GLfloat TM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // M�� ������� ������ ���
GLfloat AM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // ���� ȸ������ ������ ���
GLfloat TAM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // AM�� ������� ������ ���
GLfloat ObjM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // ������Ʈ�� �׸��µ� ����� ���
GLfloat AxisM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // ���� �׸��µ� ����� ���
GLfloat LightM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // ���� �����ϴµ������ ���

GLfloat slope, dx, dy;
bool FNDraw = false;
bool VNDraw = false;
int RotAxis = -1;

GLfloat fcenterx, fcentery, fcenterz;
GLfloat bcenterx, bcentery, bcenterz;
GLfloat Ecenterx, Ecentery, Ecenterz;
GLfloat Wcenterx, Wcentery, Wcenterz;
GLfloat Ucenterx, Ucentery, Ucenterz;
GLfloat Dcenterx, Dcentery, Dcenterz;											// ����ü 6���� �����߽� ���� ���� ������.


GLfloat FrontNormal[3];														//�ո��� �븻����
GLfloat BackNormal[3];														//�޸��� �븻����
GLfloat ENormal[3];																//���� ������ �븻����
GLfloat WNormal[3];															//���� ������ �븻����
GLfloat UNormal[3];															//���� ���� �븻����
GLfloat DNormal[3];															//�Ʒ��� ���� �븻����

GLfloat VertexNormal[8][3];											//���� �븻����.

GLfloat temppos[4];															//�ӽ������� ���� ����

float A1, A2, A3, B1, B2, B3;											//��������� �Ҷ� �ʿ��� �ӽú���.


void init(void)														//�� ����, �ʱ�ȭ	0������ �츮�� �����̴� ��, 7������ �¾��ó�� ��Ƴ��� ��. 
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);										//�� ���
	glEnable(GL_LIGHT0);											//0�� �� ���
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100.0f);                  
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);                 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);									//0������ �Ӽ��� ����,

	glEnable(GL_LIGHT7);
	glLightfv(GL_LIGHT7, GL_POSITION, Sunpos);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Sundiffuse);
	glLightfv(GL_LIGHT7, GL_AMBIENT, Sunambient);
	glLightfv(GL_LIGHT7, GL_SPECULAR, Sunspecular);									//7�� ���� �Ӽ��� ����.

	glLightf(GL_LIGHT0, GL_SHININESS, 190.0f);
	glEnable(GL_DEPTH_TEST);
}

void DrawCenterline()									// ������Ʈ�� �߽ɰ� ������ �մ� �Լ�.
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glPopMatrix();													//�����߽��� ���������� ������ �����̸� �ȵǱ� ������ Push,Pop�� �̿��ؼ� �׷��ش�.
	glVertex3f(centerx, centery, centerz);
	glEnd();
}

void FaceNormal(GLfloat Vertex[][3], GLfloat *FrontNormal)				//�� , �޸��� �븻�� ���ϴ� �Լ�
{
	float length;

	float A1 = Vertex[1][0] - Vertex[0][0];
	float A2 = Vertex[1][1] - Vertex[0][1];
	float A3 = Vertex[1][2] - Vertex[0][2];

	float B1 = Vertex[3][0] - Vertex[0][0];
	float B2 = Vertex[3][1] - Vertex[0][1];
	float B3 = Vertex[3][2] - Vertex[0][2];												//������ �ϱ����� ���Ͱ����� ������

	FrontNormal[0] = A2 * B3 - A3 * B2;
	FrontNormal[1] = A3 * B1 - A1 * B3;
	FrontNormal[2] = A1 * B2 - A2 * B1;															//���� ����
	length = sqrt(FrontNormal[0] * FrontNormal[0] + FrontNormal[1] * FrontNormal[1] + FrontNormal[2] * FrontNormal[2]);
	for (int i = 0; i < 3; i++)
		FrontNormal[i] /= (length * 2);																		//������ ũ��� ����

}

void VNormal(GLfloat *Pivot, GLfloat *P1, GLfloat *P2, GLfloat *P3, GLfloat *result)				// Vertex�븻�� ���ϴ� �Լ�,
{
	float n1[3];
	float n2[3];
	float n3[3];

	float A1 = P1[0] - Pivot[0];
	float A2 = P1[1] - Pivot[1];
	float A3 = P1[2] - Pivot[2];

	float B1 = P2[0] - Pivot[0];
	float B2 = P2[1] - Pivot[1];
	float B3 = P2[2] - Pivot[2];

	float C1 = P3[0] - Pivot[0];
	float C2 = P3[1] - Pivot[1];
	float C3 = P3[2] - Pivot[2];

	n1[0] = B2 * A3 - B3 * A2;
	n1[1] = B3 * A1 - B1 * A3;
	n1[2] = B1 * A2 - B2 * A1;

	n2[0] = C2 * B3 - C3 * B2;
	n2[1] = C3 * B1 - C1 * B3;
	n2[2] = C1 * B2 - C2 * B1;

	n3[0] = A2 * C3 - A3 * C2;
	n3[1] = A3 * C1 - A1 * C3;
	n3[2] = A1 * C2 - A2 * C1;																	//���� �����Ͽ� ���� ��

	float length1, length2, length3;
	length1 = sqrt(n1[0] * n1[0] + n1[1] * n1[1] + n1[2] * n1[2]);
	length2 = sqrt(n2[0] * n2[0] + n2[1] * n2[1] + n2[2] * n2[2]);
	length3 = sqrt(n3[0] * n3[0] + n3[1] * n3[1] + n3[2] * n3[2]);

	for (int i = 0; i < 3; i++)
	{
		n1[i] /= (length1 * 2);
		n2[i] /= (length2 * 2);
		n3[i] /= (length3 * 2);
	}																					//������ ũ�� ����

	result[0] = (n1[0] + n2[0] + n3[0]) / 0.8f;										
	result[1] = (n1[1] + n2[1] + n3[1]) / 0.8f;
	result[2] = (n1[2] + n2[2] + n3[2]) / 0.8f;											//������ �� ���� �� ������ ũ��� ����
}
		
void DrawFaceNormal()																// ���� �븻�� �׸��� �Լ�
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);													//�븻�� ������ ����.
	glBegin(GL_LINES);
	glVertex3f(fcenterx, fcentery, fcenterz);
	glVertex3f(FrontNormal[0] * 0.7 + fcenterx, FrontNormal[1] * 0.7 + fcentery, FrontNormal[2] * 0.7 + fcenterz);					//������ ũ��� �׷���.
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(bcenterx, bcentery, bcenterz);
	glVertex3f(BackNormal[0] * 0.7 + bcenterx, BackNormal[1] * 0.7 + bcentery, BackNormal[2] * 0.7 + bcenterz);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Wcenterx, Wcentery, Wcenterz);
	glVertex3f(WNormal[0] * 2 + Wcenterx, WNormal[1] * 2 + Wcentery, WNormal[2] * 2 + Wcenterz);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Ecenterx, Ecentery, Ecenterz);
	glVertex3f(ENormal[0] * 2 + Ecenterx, ENormal[1] * 2 + Ecentery, ENormal[2] * 2 + Ecenterz);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Ucenterx, Ucentery, Ucenterz);
	glVertex3f(UNormal[0] * 2 + Ucenterx, UNormal[1] * 2 + Ucentery, UNormal[2] * 2 + Ucenterz);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Dcenterx, Dcentery, Dcenterz);
	glVertex3f(DNormal[0] * 1.3 + Dcenterx, DNormal[1] * 1.3 + Dcentery, DNormal[2] * 1.3 + Dcenterz);
	glEnd();																										//���� �븻�� �׷���


}

void DrawVertexNormal()																						//Vertex�븻�� �׷��ִ� �Լ�
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);													//������� ���� ����.
	glBegin(GL_LINES);
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glVertex3f(Vertex[0][0] + VertexNormal[0][0] * 0.3, Vertex[0][1] + VertexNormal[0][1] * 0.3, Vertex[0][2] + VertexNormal[0][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glVertex3f(VertexB[0][0] + VertexNormal[1][0] * 0.3, VertexB[0][1] + VertexNormal[1][1] * 0.3, VertexB[0][2] + VertexNormal[1][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glVertex3f(VertexB[3][0] + VertexNormal[2][0] * 0.3, VertexB[3][1] + VertexNormal[2][1] * 0.3, VertexB[3][2] + VertexNormal[2][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glVertex3f(Vertex[3][0] + VertexNormal[3][0] * 0.3, Vertex[3][1] + VertexNormal[3][1] * 0.3, Vertex[3][2] + VertexNormal[3][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glVertex3f(Vertex[2][0] + VertexNormal[4][0] * 0.3, Vertex[2][1] + VertexNormal[4][1] * 0.3, Vertex[2][2] + VertexNormal[4][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glVertex3f(Vertex[1][0] + VertexNormal[5][0] * 0.3, Vertex[1][1] + VertexNormal[5][1] * 0.3, Vertex[1][2] + VertexNormal[5][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glVertex3f(VertexB[1][0] + VertexNormal[6][0] * 0.3, VertexB[1][1] + VertexNormal[6][1] * 0.3, VertexB[1][2] + VertexNormal[6][2] * 0.3);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glBegin(GL_LINES);
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glVertex3f(VertexB[2][0] + VertexNormal[7][0] * 0.3, VertexB[2][1] + VertexNormal[7][1] * 0.3, VertexB[2][2] + VertexNormal[7][2] * 0.3);
	glEnd();																											//���� ������ ũ��� �����Ͽ� �׷��ش�.
}

void DrawPolygon()																						//�������� �׷��ִ� �Լ�.
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);								//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(Vertex[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);								//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(Vertex[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[1]);
	glVertex3fv(Vertex[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[2]);
	glVertex3fv(Vertex[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[0]);
	glVertex3fv(VertexB[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[0]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[1]);
	glVertex3fv(VertexB[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[2]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(VertexB[0]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[1]);
	glVertex3fv(VertexB[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[2]);
	glVertex3fv(VertexB[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);					//������ �ۿ� ������ ������ �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[3]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glFrontFace(GL_CW);																						//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[1]);																				//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glNormal3fv(VertexNormal[6]);																				//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glNormal3fv(VertexNormal[7]);																				//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[2]);																				//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);											//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color1);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[5]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[6]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glNormal3fv(VertexNormal[1]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);													//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color2);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[1]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glNormal3fv(VertexNormal[2]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glNormal3fv(VertexNormal[3]);																					//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glEnd();


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);														//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color3);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[3]);																						//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glNormal3fv(VertexNormal[4]);																						//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[7]);																						//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[2]);																						//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular0);						//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color4);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[5]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[4]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[7]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[6]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);							//�������� ���� ������ ����, ��������� ������ �����Ͽ� �׷���
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color5);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[5]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[4]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[3]);																//�� ȿ���� ���� ���� �׸��� ���� �븻�� �����Ѵ�.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glEnd();


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(centerx, centery, centerz);

	glEnd();

}

void DrawAxis()																						//���� �׸��� �Լ�.
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();

}

void TransPoseMatrix(GLfloat *start, GLfloat *destination)      // ȸ������� ������� ������ �Լ�
{                                                         //  ȸ������� ������� Tanspose �ѰͰ� ���� ���� 
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

void ClearAll()                  // �����츦 �ʱ���·� Ŭ���� ���ִ� �Լ�.
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

}                           // ��� ������ �ʱ⿡ �����ƴ� ������ �ʱ�ȭ�Ѵ�.

void ResetObj()               // ������Ʈ�� �������·� �ʱ�ȭ ���� �Լ�.
{
	TransPoseMatrix(M, TM);               // ���ȴ� ������Ʈ�� ���� ��� ������ �׸�ŭ�� ���� ������� ȸ���� ǥ���� �־���Ѵ�.
										  //   ������Ʈ�� 30�� �������� ���� -30�� �����Ͱ� �����Ƿ� ���ݱ����� ������Ʈ�� ȸ������ �������
	glMatrixMode(GL_MODELVIEW);         // ���� ȸ������ �����־���Ѵ�. ������� Transpose�ѰͰ� �����Ƿ� Transpose�Ͽ� ���� ȸ������ ������Ʈ ȸ������ �� * ���� ȸ�������� �ٲ��ش�.
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glMultMatrixf(TM);
	glMultMatrixf(AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);         //���� ȸ������ ������Ʈ ȸ������ ���� �����ִ� ����.
	glLoadMatrixf(AxisM);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	AM[12] = 0;
	AM[13] = 0;
	AM[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAxis()                                       //���� ������Ʈ�� Reset�ϴ� ������ �����ϸ� ��, ������Ʈ�� ���常 �ٲپ� �Ȱ��� ������ �����Ѵ�.            
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
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);               //���� ȸ������ ���� ���� ������Ʈ�� ȸ������ �����ִ� ���� ����.
	glLoadMatrixf(AxisM);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);				//������ �� �ִ� ���� ��� �Բ� ���ư��� �����ؾ� �ϹǷ� ���� �׸��� ���� �� ��ġ�� ������ �ش�.
	M[12] = 0;
	M[13] = 0;
	M[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAll()                                    // ��, ������Ʈ�� ���� ��Ű�°��� �ƴ� �ΰ� ��� �ʱ��� ���·� �����ش� ( �����츦 Ŭ�����ϴ°��� �ƴϴ�.)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);
	glLoadMatrixf(AxisM);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();

}

void AddInput(int button, int state, int x, int y) {			//���콺 Ŭ�� �ݹ��Լ�.

	mx = (x - 350.) / 350.;
	my = (350. - y) / 350.;

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)      //���� ������
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
		glPushMatrix();
		glLoadMatrixf(ObjM);
		glGetFloatv(GL_MODELVIEW_MATRIX, M);  //������Ʈ ����ȸ���� ������Ʈ����ȸ����Ŀ� ����
		M[12] = 0;
		M[13] = 0;
		M[14] = 0;
		glPopMatrix();
	}
	else if (AddInputMode == 3 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)   //���� �� ������Ʈ ����
	{
		glPushMatrix();
		glLoadMatrixf(AxisM);
		glGetFloatv(GL_MODELVIEW_MATRIX, AM);// �� ����ȸ����Ŀ� ����
		AM[12] = 0;
		AM[13] = 0;
		AM[14] = 0;
		glPopMatrix();
	}
	glutPostRedisplay();

}

void MouseDrag(int x, int y) {
	if (AddInputMode != 1)  //����� ��尡 �ƴϰ�, ������Ʈ ȸ���϶�
	{
		GLfloat centertx, centerty;

		mdx = (x - 350.) / 350.;
		mdy = (350. - y) / 350.;
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
			glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);               // ������Ʈ�� ���� ȸ������ ����ȸ������ ���Ͽ� ������Ʈ�� ǥ���Ҷ� ���� ��Ŀ� �������ش�.
		}
		else if (RotAxis == 1) //��ȸ���϶�
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(AM);   //���� ȸ��
			glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);               // ���� ���� ȸ������ ���� ȸ������ ���Ͽ� ���� ȸ���Ҷ� ���� ��Ŀ� ������ �ش�.
			glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);				// �� ȸ���� �Բ� ���� ���ư��� �ϹǷ� ��ȸ����, �� ��ġ�� ���� �� �ش�.
		}
		glutPostRedisplay();
	}
}

void InitGraphics(void)
{
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glShadeModel(GL_SMOOTH);
	glPointSize(5.0);

	glMatrixMode(GL_PROJECTION);                  //���� ��Ʈ������带  GL_PROJECTION���� ��ȯ
	glLoadIdentity();
	if (ProjectionMode) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0);         // parallel ���� ��ȯ
		RotAxis = -1;
	}
	else {
		gluPerspective(22.0f, 1.0, 0.1, 100.0);         // perspective ���� ��ȯ
		RotAxis = -1;
	}
	glutPostRedisplay();
}

void Display()
{
	int i;
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//------------------------------����� �κ�---------------------------------------//
	if (AddInputMode == 1) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
	}
	//----------------------------------------------------------------------------------//
	else {
		// ������Ʈ, ���� �׸����� ������  ȸ������ ���ο��� ������ �ָ� �ȵǱ� ������  Push, Pop�� �̿��� ���������� �׷������Ѵ�.
		glPushMatrix();
		glLoadIdentity();
		glLightfv(GL_LIGHT7, GL_POSITION, Sunpos);				//�����ϼ� ����  Sunlight ����.
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		glLoadMatrixf(ObjM);
		DrawCenterline();
		DrawPolygon();
		if (FNDraw)																			//��ư�� ���� normal���� �׸��ų� , �ȱ׸��ų� �����ϴ� �κ�
			DrawFaceNormal();
		if (VNDraw)
			DrawVertexNormal();
		glPopMatrix();

		glPushMatrix();                           // ������Ʈ ȸ�� ��忡�� ���� �׿� ������� ���������� �׷����� �ϹǷ�  push
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(AxisM);                     // ���ݱ��� �ٲ�� ���� ȸ������ �ҷ��ͼ� �׷���� �ϹǷ� ���� �׸��� ���� AxisM����� ���� �𵨺信 �ҷ���.
		DrawAxis();
		glPushMatrix();
		glTranslatef(0.0, 0.0, 1.5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Sun);					//���Ǽ��� ���� ������ ��ġ ��.
		glutWireSphere(0.05, 20, 30);																	//����ڰ� ���� ���ϰ� �ϱ����� ������ ��ġ�� ��Ȯ�ϰԴ� �ƴ����� �뷫 �׷���.
		glPopMatrix();
		glPopMatrix();                     //�� �׸��� �ٽ� pop���� �������� �����´�.
		glLoadIdentity();

		glFlush();
	}

	glutSwapBuffers();
}

void MyMenu(int value)
{
	int i;

	switch (value) {
	case 1:                              //������ �׸���.
		AddInputMode = 0;
		centerx = 0.;
		centery = 0.;
		centerz = -(abs(bx_up - bx_lo) + abs(by_up - by_lo)) / 4.0;
		bcenterx = 0;
		bcentery = 0;
		bcenterz = 0;
		for (i = 0; i < NumVertex; i++) {
			centerx += Vertex[i][0];
			centery += Vertex[i][1];

			fcenterx += Vertex[i][0];
			fcentery += Vertex[i][1];
			fcenterz += Vertex[i][2];

			bcenterx += VertexB[i][0];
			bcentery += VertexB[i][1];


			VertexB[i][2] = centerz * 2.;
			bcenterz += VertexB[i][2];
		}
		/////////////////////////////// ������ �׸��� ��ư�� �ԷµǸ� �� ���� �����߽��� ���Ѵ�.
		Wcenterx = Vertex[0][0] + Vertex[1][0] + VertexB[0][0] + VertexB[1][0];
		Wcenterx /= 4;

		Wcentery = Vertex[0][1] + Vertex[1][1] + VertexB[0][1] + VertexB[1][1];
		Wcentery /= 4;

		Wcenterz = Vertex[0][2] + Vertex[1][2] + VertexB[0][2] + VertexB[1][2];
		Wcenterz /= 4;
		/////////////////////////////////////
		Ecenterx = Vertex[3][0] + Vertex[2][0] + VertexB[3][0] + VertexB[2][0];
		Ecenterx /= 4;

		Ecentery = Vertex[3][1] + Vertex[2][1] + VertexB[3][1] + VertexB[2][1];
		Ecentery /= 4;

		Ecenterz = Vertex[3][2] + Vertex[2][2] + VertexB[3][2] + VertexB[2][2];
		Ecenterz /= 4;
		//////////////////////////////////////
		Ucenterx = Vertex[0][0] + Vertex[3][0] + VertexB[0][0] + VertexB[3][0];
		Ucenterx /= 4;

		Ucentery = Vertex[0][1] + Vertex[3][1] + VertexB[0][1] + VertexB[3][1];
		Ucentery /= 4;

		Ucenterz = Vertex[0][2] + Vertex[3][2] + VertexB[0][2] + VertexB[3][2];
		Ucenterz /= 4;
		//////////////////////////////////////////
		Dcenterx = Vertex[1][0] + Vertex[2][0] + VertexB[1][0] + VertexB[2][0];
		Dcenterx /= 4;

		Dcentery = Vertex[1][1] + Vertex[2][1] + VertexB[1][1] + VertexB[2][1];
		Dcentery /= 4;

		Dcenterz = Vertex[1][2] + Vertex[2][2] + VertexB[1][2] + VertexB[2][2];
		Dcenterz /= 4;
		//////////////////////////////////////////////�����߽��� ���ϴ� ����.

		centerx /= NumVertex;
		centery /= NumVertex;


		fcenterx /= NumVertex;
		fcentery /= NumVertex;
		fcenterz /= NumVertex;

		bcenterx /= NumVertex;
		bcentery /= NumVertex;
		bcenterz /= NumVertex;


		FaceNormal(Vertex, FrontNormal);							
		FaceNormal(VertexB, BackNormal);										//��, �޸��� �븻���� ���ϴ� ���� FaceNormal �Լ� �̿�

		BackNormal[2] *= -1;															//�� ����.

		VNormal(Vertex[0], VertexB[0], Vertex[3], Vertex[1], VertexNormal[0]);										//���� Vertex���� �븻�� ���ϴ°���
		VNormal(VertexB[0], VertexB[3], Vertex[0], VertexB[1], VertexNormal[1]);
		VNormal(VertexB[3], Vertex[3], VertexB[0], VertexB[2], VertexNormal[2]);
		VNormal(Vertex[3], Vertex[0], VertexB[3], Vertex[2], VertexNormal[3]);

		VNormal(Vertex[2], VertexB[2], Vertex[1], Vertex[3], VertexNormal[4]);
		VNormal(Vertex[1], Vertex[2], VertexB[1], Vertex[0], VertexNormal[5]);
		VNormal(VertexB[1], Vertex[1], VertexB[2], VertexB[0], VertexNormal[6]);
		VNormal(VertexB[2], VertexB[1], Vertex[2], VertexB[3], VertexNormal[7]);									//���� Vertex���� �븻�� ���ϴ°���
		
		//////////////��, �Ʒ�, ������ �븻�� ���ϴ� ����/////////////
		A1 = Vertex[0][0] - VertexB[0][0];
		A2 = Vertex[0][1] - VertexB[0][1];
		A3 = Vertex[0][2] - VertexB[0][2];

		B1 = Vertex[0][0] - Vertex[1][0];
		B2 = Vertex[0][1] - Vertex[1][1];
		B3 = Vertex[0][2] - Vertex[1][2];

		WNormal[0] = A2 * B3 - A3 * B2;
		WNormal[1] = A3 * B1 - A1 * B3;
		WNormal[2] = A1 * B2 - A2 * B1;

		A1 = Vertex[3][0] - VertexB[3][0];
		A2 = Vertex[3][1] - VertexB[3][1];
		A3 = Vertex[3][2] - VertexB[3][2];

		B1 = Vertex[3][0] - Vertex[2][0];
		B2 = Vertex[3][1] - Vertex[2][1];
		B3 = Vertex[3][2] - Vertex[2][2];

		ENormal[0] = B2 * A3 - B3 * A2;
		ENormal[1] = B3 * A1 - B1 * A3;
		ENormal[2] = B1 * A2 - B2 * A1;

		A1 = Vertex[3][0] - VertexB[3][0];
		A2 = Vertex[3][1] - VertexB[3][1];
		A3 = Vertex[3][2] - VertexB[3][2];

		B1 = Vertex[3][0] - Vertex[0][0];
		B2 = Vertex[3][1] - Vertex[0][1];
		B3 = Vertex[3][2] - Vertex[0][2];

		UNormal[0] = A2 * B3 - A3 * B2;
		UNormal[1] = A3 * B1 - A1 * B3;
		UNormal[2] = A1 * B2 - A2 * B1;

		A1 = Vertex[2][0] - Vertex[1][0];
		A2 = Vertex[2][1] - Vertex[1][1];
		A3 = Vertex[2][2] - Vertex[1][2];

		B1 = Vertex[2][0] - VertexB[2][0];
		B2 = Vertex[2][1] - VertexB[2][1];
		B3 = Vertex[2][2] - VertexB[2][2];

		DNormal[0] = A2 * B3 - A3 * B2;
		DNormal[1] = A3 * B1 - A1 * B3;
		DNormal[2] = A1 * B2 - A2 * B1;
		//////////////��, �Ʒ�, ������ �븻�� ���ϴ� ����/////////////
		break;
	case 2:                  // ������Ʈ ȸ��
		AddInputMode = 2;
		break;
	case 3:                  //��ȸ�� (���� ȸ��)
		AddInputMode = 3;
		break;
	case 4:
		ProjectionMode = !ProjectionMode;   //Projection ��� ��ȯ
		InitGraphics();
		break;
	case 5:										//���͸� �׸���, �ȱ׸��� ����
		FNDraw = !FNDraw;
		break;
	case 6:										//���͸� �׸���, �ȱ׸��� ����
		VNDraw = !VNDraw;
		break;
	case 7:                           //������Ʈ ����
		ResetObj();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 8:                        // �� ����
		ResetAxis();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 9:                  // �Ѵ� ����.
		ResetAll();
		break;
	case 10:                  //ȭ�� Ŭ����
		ClearAll();
		break;
	case 11:               //���α׷� ����
		exit(0);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// GLUT Window Initialization:

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("20146847_JHY");

	// Initialize OpenGL graphics state

	InitGraphics();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                 // �����׸������� ��İ� ������Ʈ�� �׸������� ����� View����Ʈ�� �����Ͽ� �� ����� �ʱ�ȭ ��.
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);
	init();
	// Register callbacks:
	glutDisplayFunc(Display);
	glutMouseFunc(AddInput);
	glutMotionFunc(MouseDrag);

	// Create our popup menu
	glutCreateMenu(MyMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("RotateObjects", 2);
	glutAddMenuEntry("RoatAxis(Rotate Light)", 3);
	glutAddMenuEntry("Orthographic/Perspective", 4);
	glutAddMenuEntry("Draw Face Normals / Undo", 5);
	glutAddMenuEntry("Draw Vertex Normals / Undo", 6);
	glutAddMenuEntry("ResetObjects", 7);
	glutAddMenuEntry("ResetAxis", 8);
	glutAddMenuEntry("ResetAll", 9);
	glutAddMenuEntry("Clear", 10);
	glutAddMenuEntry("Exit", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}