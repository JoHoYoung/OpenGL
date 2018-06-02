//--------------------------------------------------------------User's Guide---------------------------------------------------------------
//				
//						**본 프로그램은 4개의 점만 입력해야하며 시계반대방향 순서로 입력해 주어야 올바른 폴리곤이 형성된다.***
//						**  본 프로그램은 두개의 빛을 사용하며 움직일수 있는 빛의 초기위치는 0,0,3 이며 깔려있는 빛은 3,3,3에 설정되어있다.
//
//          1. 오른쪽 마우스의 메뉴를 따라 1. 폴리곤 그리기 2. 물체 회전 3. 빛 회전 4. 프로젝션 모드 변환 5. 면 법선벡터 그리기
//               6. Vertex법선벡터 그리기 7. 오브젝트 리셋 8. 축(빛) 리셋 9. 전체리셋 10. 클리어 11.종료 등의 기능을 수행할 수 있다.
//			2. 도형은 사각형만 그릴 수 있으며 점은 시계반대방향 순서로 입력해야 한다. 그렇지않으면 원하는 결과를 얻을 수 없다.
//          3. 축, 오브젝트 리셋시 축, 오브젝트 간의 상대적인 회전을 고려하여 리셋된다. 예를들어 축을 30도, 오브젝트 를 30도 회전한 후
//               축을 리셋하면 둘다 회전값이 없는 모양으로 표현된다.
//			4. 빛은 두개가 그려져 있으며 하나의 빛은 태양처럼 깔려있으며 움직일 수 없다. 나머지 빛은 축을 돌리면 같이 돌아가게 된다.
//          5. 주어진 메뉴를 통해 법선벡터를 켜거나 끌 수 있다.
//          6. 폴리곤의 앞 면의 Z값은 0으로 설정되어 있다.  
//			7. 빛의 변화하는 위치를 직관적으로 이해하기 어렵다. 때문에 구를 그려 대략적인 빛의 위치를 그려 이해를 편하게 구현하였다.
//			8. 단 빛의 위치는 직관적인 이해를 위해 구현 한것으로, 정확한 빛의 위치는 아니다.			- 20146847 조호영-
//--------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <gl/glut.h>
#include<gl/gl.H>
using namespace std;

void InitGraphics();
///////////////////////  빛 설정, 면의 재질, 색을 설정하기 위한 행렬 값들.//////////////////////////////////////////////////
GLfloat light0_pos[] = { 0.0, 0.0f, 3.0f, 1.0 };// 움직일 수 있는 빛의 위치.
GLfloat diffuse0[] = { 0.6, 0.6f, 0.6f, 1.0 };   //
GLfloat ambient0[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //
GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat direction0[] = { 0.0,0.0,5.0,1.0 };		//움직일 수 있는 빛의 설정값들.

GLfloat Sunpos[] = { 3.0, 3.0f, 3.0f, 1.0 };		//움직일 수 없고 기본적으로 깔려있는 빛의 위치
GLfloat Sundiffuse[] = { 0.1f, 0.1f, 0.1f, 1.0 };   //분산광
GLfloat Sunambient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //주변광
GLfloat Sunspecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat Sundirection[] = { 0.0,0.0,5.0,1.0 };		//움직일 수 없고 기본적으로 깔려있는 빛의 설정값들


GLfloat emission[] = { 0.1, 0.0, 0.3, 1.0 };
GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shine[] = { 1.0, 1.0,1.0,1.0 };						//재질 설정을 위한 설정값들.

GLfloat color[] = { 1.0, 0.0, 1.0, 1.0 };
GLfloat color1[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat color2[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat color3[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat color4[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat color5[] = { 1.0, 0.0, 0.0, 1.0 };						//각 면들의 색 설정을 위한 행렬

GLfloat Black[] = { 0.0,0.0,0.0,1.0 };
GLfloat White[] = { 1.0,1.0,1.0,1.0 };							//흰색과 검정색을 표현하기 위한 행렬
GLfloat Sun[] = { 1.0,1.0,0.0,1.0 };							//	사용자의 편의를위해 그려줄 빛의 위치를 표현할 Sphere의 색.
////////////////////////////////////////////////////////////////////////////

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
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // 오브젝트의 회전값을 저장할 행렬
GLfloat TM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // M의 역행렬을 저장할 행렬
GLfloat AM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };            // 축의 회전값을 저장할 행렬
GLfloat TAM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // AM의 역행렬을 저장할 행렬
GLfloat ObjM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // 오브젝트를 그리는데 사용할 행렬
GLfloat AxisM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // 축을 그리는데 사용할 행렬
GLfloat LightM[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };         // 빛을 조절하는데사용할 행렬

GLfloat slope, dx, dy;
bool FNDraw = false;
bool VNDraw = false;
int RotAxis = -1;

GLfloat fcenterx, fcentery, fcenterz;
GLfloat bcenterx, bcentery, bcenterz;
GLfloat Ecenterx, Ecentery, Ecenterz;
GLfloat Wcenterx, Wcentery, Wcenterz;
GLfloat Ucenterx, Ucentery, Ucenterz;
GLfloat Dcenterx, Dcentery, Dcenterz;											// 육면체 6면의 무게중심 값을 위한 변수들.


GLfloat FrontNormal[3];														//앞면의 노말벡터
GLfloat BackNormal[3];														//뒷면의 노말벡터
GLfloat ENormal[3];																//동쪽 옆면의 노말벡터
GLfloat WNormal[3];															//서쪽 옆면의 노말벡터
GLfloat UNormal[3];															//위쪽 면의 노말벡터
GLfloat DNormal[3];															//아랫쪽 면의 노말벡터

GLfloat VertexNormal[8][3];											//선의 노말벡터.

GLfloat temppos[4];															//임시저장을 위한 변수

float A1, A2, A3, B1, B2, B3;											//외적계산을 할때 필요한 임시변수.


void init(void)														//빛 생성, 초기화	0번빛은 우리가 움직이는 빛, 7번빛은 태양빛처럼 깔아놓은 빛. 
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);										//빛 사용
	glEnable(GL_LIGHT0);											//0번 빛 사용
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100.0f);                  
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);                 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);									//0번빛의 속성값 설정,

	glEnable(GL_LIGHT7);
	glLightfv(GL_LIGHT7, GL_POSITION, Sunpos);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Sundiffuse);
	glLightfv(GL_LIGHT7, GL_AMBIENT, Sunambient);
	glLightfv(GL_LIGHT7, GL_SPECULAR, Sunspecular);									//7번 빛의 속성값 설정.

	glLightf(GL_LIGHT0, GL_SHININESS, 190.0f);
	glEnable(GL_DEPTH_TEST);
}

void DrawCenterline()									// 오브젝트의 중심과 원점을 잇는 함수.
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glPopMatrix();													//무게중심은 움직이지만 원점은 움직이면 안되기 때문에 Push,Pop을 이용해서 그려준다.
	glVertex3f(centerx, centery, centerz);
	glEnd();
}

void FaceNormal(GLfloat Vertex[][3], GLfloat *FrontNormal)				//앞 , 뒷면의 노말을 구하는 함수
{
	float length;

	float A1 = Vertex[1][0] - Vertex[0][0];
	float A2 = Vertex[1][1] - Vertex[0][1];
	float A3 = Vertex[1][2] - Vertex[0][2];

	float B1 = Vertex[3][0] - Vertex[0][0];
	float B2 = Vertex[3][1] - Vertex[0][1];
	float B3 = Vertex[3][2] - Vertex[0][2];												//외적을 하기위한 벡터값들을 가져옴

	FrontNormal[0] = A2 * B3 - A3 * B2;
	FrontNormal[1] = A3 * B1 - A1 * B3;
	FrontNormal[2] = A1 * B2 - A2 * B1;															//외적 과정
	length = sqrt(FrontNormal[0] * FrontNormal[0] + FrontNormal[1] * FrontNormal[1] + FrontNormal[2] * FrontNormal[2]);
	for (int i = 0; i < 3; i++)
		FrontNormal[i] /= (length * 2);																		//적당한 크기로 설정

}

void VNormal(GLfloat *Pivot, GLfloat *P1, GLfloat *P2, GLfloat *P3, GLfloat *result)				// Vertex노말을 구하는 함수,
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
	n3[2] = A1 * C2 - A2 * C1;																	//각각 외적하여 구한 후

	float length1, length2, length3;
	length1 = sqrt(n1[0] * n1[0] + n1[1] * n1[1] + n1[2] * n1[2]);
	length2 = sqrt(n2[0] * n2[0] + n2[1] * n2[1] + n2[2] * n2[2]);
	length3 = sqrt(n3[0] * n3[0] + n3[1] * n3[1] + n3[2] * n3[2]);

	for (int i = 0; i < 3; i++)
	{
		n1[i] /= (length1 * 2);
		n2[i] /= (length2 * 2);
		n3[i] /= (length3 * 2);
	}																					//적당한 크기 설정

	result[0] = (n1[0] + n2[0] + n3[0]) / 0.8f;										
	result[1] = (n1[1] + n2[1] + n3[1]) / 0.8f;
	result[2] = (n1[2] + n2[2] + n3[2]) / 0.8f;											//구해진 값 저장 후 적당한 크기로 설정
}
		
void DrawFaceNormal()																// 면의 노말을 그리는 함수
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);													//노말의 재질을 설정.
	glBegin(GL_LINES);
	glVertex3f(fcenterx, fcentery, fcenterz);
	glVertex3f(FrontNormal[0] * 0.7 + fcenterx, FrontNormal[1] * 0.7 + fcentery, FrontNormal[2] * 0.7 + fcenterz);					//적당한 크기로 그려줌.
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
	glEnd();																										//면의 노말을 그려줌


}

void DrawVertexNormal()																						//Vertex노말을 그려주는 함수
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, White);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, White);													//흰색으로 재질 설정.
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
	glEnd();																											//각각 적당한 크기로 설정하여 그려준다.
}

void DrawPolygon()																						//폴리곤을 그려주는 함수.
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);								//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(Vertex[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);								//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(Vertex[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[1]);
	glVertex3fv(Vertex[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[2]);
	glVertex3fv(Vertex[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[0]);
	glVertex3fv(VertexB[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[0]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[1]);
	glVertex3fv(VertexB[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);						//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(VertexB[2]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[0]);
	glVertex3fv(VertexB[0]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[1]);
	glVertex3fv(VertexB[1]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);							//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[2]);
	glVertex3fv(VertexB[2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Black);					//폴리곤 밖에 검은색 엣지를 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3fv(Vertex[3]);
	glVertex3fv(VertexB[3]);
	glEnd();

	glFrontFace(GL_CW);																						//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[1]);																				//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glNormal3fv(VertexNormal[6]);																				//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glNormal3fv(VertexNormal[7]);																				//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[2]);																				//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);											//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color1);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[5]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[6]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glNormal3fv(VertexNormal[1]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);													//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color2);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[1]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
	glNormal3fv(VertexNormal[2]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glNormal3fv(VertexNormal[3]);																					//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glEnd();


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);														//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color3);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[3]);																						//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glNormal3fv(VertexNormal[4]);																						//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[7]);																						//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[2]);																						//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[3][0], VertexB[3][1], VertexB[3][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular0);						//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color4);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[5]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[4]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[7]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[2][0], VertexB[2][1], VertexB[2][2]);
	glNormal3fv(VertexNormal[6]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(VertexB[1][0], VertexB[1][1], VertexB[1][2]);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);							//폴리곤을 각각 지정된 색깔, 설정값들로 재질을 결정하여 그려줌
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color5);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glNormal3fv(VertexNormal[0]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
	glNormal3fv(VertexNormal[5]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[1][0], Vertex[1][1], Vertex[1][2]);
	glNormal3fv(VertexNormal[4]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[2][0], Vertex[2][1], Vertex[2][2]);
	glNormal3fv(VertexNormal[3]);																//빛 효과를 위해 점을 그릴때 각각 노말을 적용한다.
	glVertex3f(Vertex[3][0], Vertex[3][1], Vertex[3][2]);
	glEnd();


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(centerx, centery, centerz);

	glEnd();

}

void DrawAxis()																						//축을 그리는 함수.
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

void TransPoseMatrix(GLfloat *start, GLfloat *destination)      // 회전행렬의 역행렬을 구해줄 함수
{                                                         //  회전행렬의 역행렬은 Tanspose 한것과 같기 때문 
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

void ClearAll()                  // 윈도우를 초기상태로 클리어 해주는 함수.
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

}                           // 모든 변수를 초기에 설정됐던 값으로 초기화한다.

void ResetObj()               // 오브젝트만 원래상태로 초기화 해줄 함수.
{
	TransPoseMatrix(M, TM);               // 돌렸던 오브젝트를 원래 대로 돌릴때 그만큼의 축의 상대적인 회전도 표현해 주어야한다.
										  //   오브젝트를 30도 돌린것은 축을 -30도 돌린것과 같으므로 지금까지의 오브젝트의 회전값의 역행렬을
	glMatrixMode(GL_MODELVIEW);         // 축의 회전값에 곱해주어야한다. 역행렬은 Transpose한것과 같으므로 Transpose하여 축의 회전값을 오브젝트 회전값의 역 * 축의 회전값으로 바꿔준다.
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);
	glMultMatrixf(TM);
	glMultMatrixf(AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AM);
	glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);         //축의 회전값에 오브젝트 회전값의 역을 더해주는 과정.
	glLoadMatrixf(AxisM);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	AM[12] = 0;
	AM[13] = 0;
	AM[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAxis()                                       //위의 오브젝트를 Reset하는 과정과 동일하며 축, 오브젝트의 입장만 바꾸어 똑같은 과정을 수행한다.            
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
	glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);               //축의 회전값의 역을 현재 오브젝트의 회전값에 곱해주는 과정 수행.
	glLoadMatrixf(AxisM);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);				//움직일 수 있는 빛은 축과 함께 돌아가게 구현해야 하므로 축을 그릴때 같이 빛 위치를 설정해 준다.
	M[12] = 0;
	M[13] = 0;
	M[14] = 0;

	RotAxis = -1;
	glLoadIdentity();
	glutPostRedisplay();
}

void ResetAll()                                    // 축, 오브젝트만 리셋 시키는것이 아닌 두개 모두 초기의 상태로 돌려준다 ( 윈도우를 클리어하는것이 아니다.)
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

void AddInput(int button, int state, int x, int y) {			//마우스 클릭 콜백함수.

	mx = (x - 350.) / 350.;
	my = (350. - y) / 350.;

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)      //점을 찍을때
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
		glPushMatrix();
		glLoadMatrixf(ObjM);
		glGetFloatv(GL_MODELVIEW_MATRIX, M);  //오브젝트 누적회전을 오브젝트누적회전행렬에 저장
		M[12] = 0;
		M[13] = 0;
		M[14] = 0;
		glPopMatrix();
	}
	else if (AddInputMode == 3 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)   //누적 축 로테이트 저장
	{
		glPushMatrix();
		glLoadMatrixf(AxisM);
		glGetFloatv(GL_MODELVIEW_MATRIX, AM);// 축 누적회전행렬에 저장
		AM[12] = 0;
		AM[13] = 0;
		AM[14] = 0;
		glPopMatrix();
	}
	glutPostRedisplay();

}

void MouseDrag(int x, int y) {
	if (AddInputMode != 1)  //점찍는 모드가 아니고, 오브젝트 회전일때
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
			glGetFloatv(GL_MODELVIEW_MATRIX, ObjM);               // 오브젝트의 현재 회전값과 누적회전값을 곱하여 오브젝트를 표현할때 쓰는 행렬에 저장해준다.
		}
		else if (RotAxis == 1) //축회전일때
		{
			glRotatef(theta, 0., 0., 1.);
			glRotatef(angle, 1., 0., 0.);
			glRotatef(-theta, 0., 0., 1.);
			glMultMatrixf(AM);   //누적 회전
			glGetFloatv(GL_MODELVIEW_MATRIX, AxisM);               // 축의 현재 회전값과 누적 회전값을 곱하여 축을 회전할때 쓰는 행렬에 저장해 준다.
			glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);				// 축 회전과 함께 빛이 돌아가야 하므로 축회전후, 빛 위치를 설정 해 준다.
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

	glMatrixMode(GL_PROJECTION);                  //현재 매트릭스모드를  GL_PROJECTION으로 변환
	glLoadIdentity();
	if (ProjectionMode) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0);         // parallel 모드로 변환
		RotAxis = -1;
	}
	else {
		gluPerspective(22.0f, 1.0, 0.1, 100.0);         // perspective 모드로 변환
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
	//------------------------------점찍는 부분---------------------------------------//
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
		// 오브젝트, 축을 그릴때는 각각의  회전값이 서로에게 영향을 주면 안되기 때문에  Push, Pop을 이용해 독립적으로 그려지게한다.
		glPushMatrix();
		glLoadIdentity();
		glLightfv(GL_LIGHT7, GL_POSITION, Sunpos);				//움직일수 없는  Sunlight 설정.
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		glLoadMatrixf(ObjM);
		DrawCenterline();
		DrawPolygon();
		if (FNDraw)																			//버튼에 따라 normal들을 그리거나 , 안그리거나 결정하는 부분
			DrawFaceNormal();
		if (VNDraw)
			DrawVertexNormal();
		glPopMatrix();

		glPushMatrix();                           // 오브젝트 회전 모드에서 축은 그에 관계없이 독립적으로 그려져야 하므로  push
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(AxisM);                     // 지금까지 바꿨던 축의 회전등을 불러와서 그려줘야 하므로 축을 그릴때 쓰는 AxisM행렬을 현재 모델뷰에 불러옴.
		DrawAxis();
		glPushMatrix();
		glTranslatef(0.0, 0.0, 1.5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Sun);					//편의성을 위한 조명의 위치 색.
		glutWireSphere(0.05, 20, 30);																	//사용자가 보기 편하게 하기위해 조명의 위치를 정확하게는 아니지만 대략 그려줌.
		glPopMatrix();
		glPopMatrix();                     //다 그리면 다시 pop으로 원래것을 가져온다.
		glLoadIdentity();

		glFlush();
	}

	glutSwapBuffers();
}

void MyMenu(int value)
{
	int i;

	switch (value) {
	case 1:                              //폴리곤 그리기.
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
		/////////////////////////////// 폴리곤 그리기 버튼이 입력되면 각 면의 무게중심을 구한다.
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
		//////////////////////////////////////////////무게중심을 구하는 과정.

		centerx /= NumVertex;
		centery /= NumVertex;


		fcenterx /= NumVertex;
		fcentery /= NumVertex;
		fcenterz /= NumVertex;

		bcenterx /= NumVertex;
		bcentery /= NumVertex;
		bcenterz /= NumVertex;


		FaceNormal(Vertex, FrontNormal);							
		FaceNormal(VertexB, BackNormal);										//앞, 뒷면의 노말벡터 구하는 과정 FaceNormal 함수 이용

		BackNormal[2] *= -1;															//값 설정.

		VNormal(Vertex[0], VertexB[0], Vertex[3], Vertex[1], VertexNormal[0]);										//각각 Vertex들의 노말을 구하는과정
		VNormal(VertexB[0], VertexB[3], Vertex[0], VertexB[1], VertexNormal[1]);
		VNormal(VertexB[3], Vertex[3], VertexB[0], VertexB[2], VertexNormal[2]);
		VNormal(Vertex[3], Vertex[0], VertexB[3], Vertex[2], VertexNormal[3]);

		VNormal(Vertex[2], VertexB[2], Vertex[1], Vertex[3], VertexNormal[4]);
		VNormal(Vertex[1], Vertex[2], VertexB[1], Vertex[0], VertexNormal[5]);
		VNormal(VertexB[1], Vertex[1], VertexB[2], VertexB[0], VertexNormal[6]);
		VNormal(VertexB[2], VertexB[1], Vertex[2], VertexB[3], VertexNormal[7]);									//각각 Vertex들의 노말을 구하는과정
		
		//////////////윗, 아래, 옆면의 노말을 구하는 과정/////////////
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
		//////////////윗, 아래, 옆면의 노말을 구하는 과정/////////////
		break;
	case 2:                  // 오브젝트 회전
		AddInputMode = 2;
		break;
	case 3:                  //축회전 (광원 회전)
		AddInputMode = 3;
		break;
	case 4:
		ProjectionMode = !ProjectionMode;   //Projection 모드 변환
		InitGraphics();
		break;
	case 5:										//벡터를 그릴지, 안그릴지 결정
		FNDraw = !FNDraw;
		break;
	case 6:										//벡터를 그릴지, 안그릴지 결정
		VNDraw = !VNDraw;
		break;
	case 7:                           //오브젝트 리셋
		ResetObj();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 8:                        // 축 리셋
		ResetAxis();
		RotAxis = -1;
		glutPostRedisplay();
		break;
	case 9:                  // 둘다 리셋.
		ResetAll();
		break;
	case 10:                  //화면 클리어
		ClearAll();
		break;
	case 11:               //프로그램 종료
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
	glLoadIdentity();                                 // 축을그리기위한 행렬과 오브젝트를 그리기위한 행렬을 View포인트를 설정하여 그 값들로 초기화 함.
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