//------------------------------------------------------------ User Guide -------------------------------------------------------------------------------------------------
//
//      1. To Draw Polygon  : Decide coordinates with Mouse Left Button click -> Menu -> Draw
//      2. Default Mode Setting is Orthogonal.
//      3. At Menu, You can select Projection Mode ( Orthogonal, Perspective )
//      4. To Change View Point, Select at Menu then you can change view point with mouse drag.
//      5. With View point reset button, you can back to view point at first.  
//      
//		* Clear Window, ViewPoint and Projection Mode Set default( Default Projection Mode is Orthogonal )
//		* To draw Polygon, choose at least 3 points
//		* Users can't draw polygon that has more than 100points
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>                                                                        //Standard Library
#include <windows.h>                                                                   // Library to get Window
#include <stdio.h>                                                                       // Standard I.O Library
#include <glut.h>                                                                        // Library to use OpenGL

#define WINDOW_ROW 500
#define WINDOW_COL 500                                                         // Define Size of Window

float upperx;
float uppery;																			// Variables for get change of mouse's points
float xpos, ypos;																		//	Variables for get change of mouse's points
float Viewx = 0;	
float Viewy = 0;																		//	Variables for View point.  View points are X=0, Y=0 
float TempChangeX = 0;
float TempChangeY = 0;																// Variable for stack changes of X pos Y pos, without these variable, Changes of X pos, Ypos are initailized at every loop
float ChangeStackX = 0;
float ChangeStackY = 0;																// these variable do same thing with TempChange X,Y
float depth;																				// for setting depth of 3D object. depth is setted average of X range and Y range
bool PersMode = 0;

float Matrix[100][3];                                                                       // 2*100 Matrix to store X,Y
float Matrix2[100][3];																		// 2*100 Matrix for opposite side of polygon 
int INDEX = 0;                                                                             // INDEX
bool IsDrawed = false;                                                                   // Variable for controlling unwanted input.
int WhatToDo = 0;																		// Variable for control flow of program
void MyMainMenu(int entryID)                                                       // Call-Back function to control menu
{
	if (entryID == 1)                                                                              // Draw
	{
		WhatToDo = 1;
		IsDrawed = true;                                                    // After draw, there must be no inputs. With this Variable, control input.
		float xMAX = INT_MIN;
		float yMAX = INT_MIN;   
		float xMIN = INT_MAX;
		float yMIN = INT_MAX;											// With initailize these variable to these values, these variables are used to get Min, Max Value of x,y Position
		for (int i = 0; i < INDEX; i++) {									// For loop to get MAX, MIN Value of x,y position
			if (xMAX < Matrix[i][0])              
				xMAX = Matrix[i][0];

			if (yMAX < Matrix[i][1])              
				yMAX = Matrix[i][1];

			if (xMIN > Matrix[i][0])          
				xMIN = Matrix[i][0];

			if (yMIN > Matrix[i][1])      
				yMIN = Matrix[i][1];										// get Max, Min Value of X, Y to Get Range of X, Y
		}
		if ((xMAX - xMIN) > (yMAX - yMIN))
			depth = (xMAX - xMIN);
		else
			depth = (yMAX - yMIN);			//	    Set depth with The bigger of (xMAX - xMIN) and  (yMAX - yMIN)
	
		for (int i = 0; i < INDEX; i++)
			Matrix2[i][2] = -depth;			//		with depth, set z value of opposite polygon
	}
	if (entryID == 2)                                                     // Change View Point X, Y
	{
		WhatToDo = 2;
	}
	if (entryID == 3)													  // Change Perspective to Orthogonal
	{
		WhatToDo = -1;
		glMatrixMode(GL_PROJECTION);								// Load GL_PROJECTION Matrix Mode
		glLoadIdentity();													// initailize
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);							// Set Mode Orthogonal with glOrtho. 
	}
	if (entryID == 4)
	{	
		WhatToDo = -1;
		glMatrixMode(GL_PROJECTION);								// Load GL_PROJECTION Matrix Mode
		glLoadIdentity();													// initailize
		gluPerspective(28.0f, 1.0, 0.1f, 20.0f);							// set projection mode perspective with gluPerspective
		glMatrixMode(GL_MODELVIEW);                              // Load GL_MODELVIEW Matrix Mode
		glLoadIdentity();													// initialize
		gluLookAt(Viewx, Viewy, 4, 0, 0, 0, 0.0f, 1.0f, 0.0f);			// Set ViewPoint , When Mode Changed. 
	}
	if (entryID == 5)                                                   // Reset View Point X, Y
	{
		Viewx = 0;
		Viewy = 0;
		TempChangeX = 0;
		TempChangeY = 0;
		ChangeStackX = 0;
		ChangeStackY = 0;											//	Initailize Variables To Reset
		glMatrixMode(GL_MODELVIEW);                            // Load GL_MODELVIEW Maxtrix Mode
		glLoadIdentity();												// Initialize
		gluLookAt(Viewx, Viewy, 4, 0, 0, 0, 0.0f, 1.0f, 0.0f);		//  Initailize View Point with Initailized Viewx, Viewy
	}
	if (entryID == 6)													// Clear Window
	{
		 INDEX = 0;
		 Viewx = 0;
		 Viewy = 0;
		 TempChangeX = 0;
		 TempChangeY = 0;
		 ChangeStackX = 0;
		 ChangeStackY = 0;
		 PersMode = 0;
		 IsDrawed = false;
		 WhatToDo = 0;													// To Clear Window, Intailize Variables
		 glMatrixMode(GL_MODELVIEW);                              //	Load Matrix MODELVIEW 
		 glLoadIdentity();												// Initialize 
		 gluLookAt(Viewx, Viewy, 4, 0, 0, 0, 0.0f, 1.0f, 0.0f);				//To Clear Window, Reset View Point with initialized Viewx, Viewy
		 glMatrixMode(GL_PROJECTION);									// Load GL_PROJECT
		 glLoadIdentity();														//initialize
		 glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);												// To Clear Window, Set ProjectionMode Default Mode Orthogonal
	}
	if (entryID == 7)												// Exit
		exit(1);

	glutPostRedisplay();
}

void GetMousePoint(int button, int state, int x, int y)                                  // Function to get x,ypos from user's mouse click
{
	if (IsDrawed&&button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)            // Loop for saving position of X,Y in state of Drawed ( for Caculating interval of currnet x,ypos with upper pos used scale, transpose, rotate)
	{
		upperx = ((float)x - (float)WINDOW_ROW / 2.0) / ((float)WINDOW_ROW / 2);
		uppery = ((float)y - (float)WINDOW_COL / 2.0) / ((float)WINDOW_COL / 2);            // Process To Get Position used at Window

	}
	if (IsDrawed&&button == GLUT_LEFT_BUTTON && state == GLUT_UP)            // Loop for saving position of X,Y in state of Drawed ( for Caculating interval of currnet x,ypos with upper pos used scale, transpose, rotate)
	{
		ChangeStackX += TempChangeX;
		ChangeStackY += TempChangeY;
	}

	if (!IsDrawed&&button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)              // If mouse's left button clicked and polygon is not drawed
	{
		xpos = WINDOW_ROW;
		ypos = WINDOW_COL;

		xpos = ((float)x - (float)xpos / 2.0) / ((float)xpos / 2);
		ypos = ((float)y - (float)ypos / 2.0) / ((float)ypos / 2);                     // Process To Get Position used in glVertex2f, glVertex3f function
		Matrix[INDEX][0] = xpos;
		Matrix[INDEX][1] = -ypos;	//Input User's Position To get Polygon
		Matrix[INDEX][2] = 0.0f;		// set first poygon set Z value 0, Another polygon Z value is decided with Range of X, Range of Y.
		Matrix2[INDEX][0] = xpos;
		Matrix2[INDEX++][1] = -ypos;	//Input User's Po ion To get Polygon and Increase INDEX
		
	}
	glutPostRedisplay();
}


void MouseDrag(int x, int y)                                 // Call-Back Function used at glutMotionFunc
{
	float xpos, ypos;

	xpos = ((float)x - (float)WINDOW_ROW / 2.0) / ((float)WINDOW_ROW / 2);
	ypos = ((float)y - (float)WINDOW_COL / 2.0) / ((float)WINDOW_COL / 2);

	if (WhatToDo == 2)                                          // if Mode is Change View Point
	{
		Viewx = ChangeStackX - upperx + xpos;
		Viewy = ChangeStackY - (ypos - uppery);            // Set ViewX, View Y with Difference of Mouse's x,y Position
		printf(" ViewPoint X : %f\n", Viewx);
		printf(" ViewPoint Y : %f\n", Viewy);
		TempChangeX = -upperx + xpos;
		TempChangeY = -(ypos - uppery);						// To Stack Chage of X, Y
		glMatrixMode(GL_MODELVIEW);                              //	Load Matrix MODELVIEW 
		glLoadIdentity();												// Initialize
		gluLookAt(Viewx, Viewy, 4, 0, 0, 0, 0.0f, 1.0f, 0.0f);				//Set View point of x, y with Difference of Mouse's X,Y Position
	}
	glutPostRedisplay();                                           // Restarting display() Function
}
void display()                                               //   Function to decide what to draw at window
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear Window with Delete Buffer For Color
	glShadeModel(GL_FLAT);                                //	With One Color  
	glEnable(GL_DEPTH_TEST);									// For Expression of Depth
	glViewport(0, 0, 500, 500);									// Set Viewport Size equal to size of Window
	if (WhatToDo == 0)											// if not polygon mode, default, draw points
	{
		glPointSize(5.0f);												// point size is 5.0f
		glBegin(GL_POINTS);											// draw points
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0f);
		for (int i = 0; i < INDEX; i++)
		{
			glVertex2f(Matrix[i][0], Matrix[i][1]);
		}																				//	when draw points, we can draw points At 2D ,there is no problem to see Because We Can't see 3D without
		glEnd();																		//	Change of ViewPoint, At Drawing points, draw at 2D. It doesn't matter if you change the polygon to 3D when drawing it.
		glFlush();																		//	The point is drawn in 2D and then in 3D when the polygon is drawn, then we can see 3D with change of Viewpoint.
	}
	else {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < INDEX; i++)
		{
			glVertex3f(Matrix[i][0], Matrix[i][1], Matrix[i][2]);

		}
		glEnd();																								// Draw Polygon at 3D, it's Z-value is 0.

		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 0; i < INDEX; i++)
		{
			glBegin(GL_LINES);
			glVertex3f(Matrix[i][0], Matrix[i][1], Matrix[i][2]);
			glVertex3f(Matrix2[i][0], Matrix2[i][1], Matrix2[i][2]);
			glEnd();
		}																										// Draw Lines Between Two Polygon  to create a three-dimensional effect.
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		for (int i = 0; i < INDEX; i++)
		{
			glVertex3f(Matrix2[i][0], Matrix2[i][1], Matrix2[i][2]);

		}
		glEnd();																						// Draw another side of Polygon at 3D, it's Z-value is dicided by average of X-Range and Y-range
		glFlush();
	}
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);                                                                     
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_ROW, WINDOW_COL);                           // Setting Window 
	glutInitWindowPosition(100, 100);                                                    // Setting Window Position
	glutCreateWindow(argv[0]);                                                            // Creat Window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);													// Set Default Mode Orthogonal
	glutDisplayFunc(display);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);                        // Creat Menu
	glutMouseFunc(GetMousePoint);                                                     // Does mouse click happen, call GetMousePoint Function 
	glutAddMenuEntry("Draw Polygon", 1);
	glutAddMenuEntry("Change View Points", 2);
	glutAddMenuEntry("Orthogonal", 3);
	glutAddMenuEntry("Perspective", 4);
	glutAddMenuEntry("ResetViewPoints", 5);
	glutAddMenuEntry("Clear Window", 6);
	glutAddMenuEntry("Exit", 7);
	glutMotionFunc(MouseDrag);                                                            // Catch Mouse Drag Action With Call Back Function "MouseDrag"
	glutAttachMenu(GLUT_RIGHT_BUTTON);                                              // IF users click mouse right button, show menu.
	glutMainLoop();
	return 0;
}
