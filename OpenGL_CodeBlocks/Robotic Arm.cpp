#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;


double displace_sqr = 20;
double squareLen = 20.0;
double squareLen_max = 20.0;
double squareLen_min = 0;
double angle_sqr = 90;
int drawbox = 1;

double lookx = 40;
double looky = -100;
double lookz = 100;

struct square
{
    double x,y,z;
};

struct point
{
	double x,y,z;
};

struct vect
{
	double x,y;
};

struct vect v;

struct pos
{
	double x,y;
};

struct pos p;

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


double arrowTri = 10;
double arrowLen = 20;


double s_r = 0;
struct square squr;


double rotateBig = 0.03*(3.1416/180);
double rotateBig2 = 0.03*(3.1416/180);
double rotateM = 0.03*(3.1416/180);
double rotateT = 0.03*(3.1416/180);
double rotateS1 = 0.03*(3.1416/180);
double rotateS2 = 0.03*(3.1416/180);

void drawArm()
{
    double s1 = 5;
    double s2 = 4;
    double r1 = 5;
    double r2 = 3;

    glRotatef(rotateBig, 1, 0, 0);
    glRotatef(rotateBig2, 0, 0, 1);


    glPushMatrix();
    {
        glTranslatef(0,-1*s1*r1,0);
        glRotatef(90,1,0,0);
        glScaled(1, 1, s1);
        glutWireSphere(r1, 10, 10);
    }
    glPopMatrix();

    double start2 = -1*(2*s1*r1 + s2*r2);

    glTranslatef(0,1*start2 ,0);
    glTranslatef(0,s2*r2 ,0);
    glRotatef(rotateM, 1, 0, 0);
    glTranslatef(0,-1*s2*r2 ,0);




    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        glScaled(1, 1, s2);
        glutWireSphere(r2, 8, 8);
    }
    glPopMatrix();

    double start3 = - s2*r2;
    double size3 = 5;

    glRotatef(rotateT,0,1,0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0,start3,0);
        glVertex3f(0,start3-size3,size3);
        glVertex3f(0,start3-size3,-1*size3);
    }
    glEnd();

    double start4;
    double start5;

    glPushMatrix();
    {
        glTranslatef(0, 0, 4);
        glRotatef(rotateS1,0,1,0);
        glTranslatef(0, start3-8, 0);
        glRotatef(90,1,0,0);
        glScaled(1, 1, 2);
        glutWireSphere(1.5, 5, 5);
    }
    glPopMatrix();

    //glRotatef(-90,1,0,0);
    //glTranslatef(0, start3-8, 0);
    glPushMatrix();
    {

    }
    glPopMatrix();


    glTranslatef(0, -78, -4);
    glTranslatef(0, +62, 0);
    glRotatef(rotateS2,0,0,1);
    glTranslatef(0, -3, 0);


    glRotatef(90,1,0,0);
    glScaled(1, 1, 2);
    //glTranslatef(0, -4, 0);
    glutWireSphere(1.5, 5, 5);



}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			//drawgrid=1-drawgrid;
			if(rotateBig <= 45)
                rotateBig+=1;
			break;
        case '2':
            if(rotateBig >= -45)
                rotateBig-=1;
            break;
        case '3':
            if(rotateM <= 90)
                rotateM+=1;
            break;


        case '4':
            if(rotateM >= 0)
                rotateM-=1;
            break;


        case '5':
            if(rotateT <= 60)
                rotateT+=4;

            break;

        case '6':
            if(rotateT >= -60)
                rotateT-=4;
            break;

        case '7':
            if(rotateS1 <= 60)
                rotateS1+=3;
            break;

        case '8':
            if(rotateS1 >= -60)
                rotateS1-=3;
            break;

        case '9':
            if(rotateS2 <= 90)
                rotateS2+=3;
            break;
        case '0':
            if(rotateS2 >= 3)
                rotateS2-=3;
            break;

        case 'q':
            if(rotateBig2 <= 90)
                rotateBig2+=1;
            break;

        case 'w':
            if(rotateBig2 >= 0)
                rotateBig2-=1;
            break;



		default:
			break;
	}
}

double a=2*(3.1416/180.0);
double r = 100;

void specialKeyListener(int key, int x,int y){
    double vx;
    double vy;
    double vpx;
    double vpy;


	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			looky--;


			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			looky++;

			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			a+=0.02;
            lookx = r*cos(a);
            lookz = r*sin(a);


			break;
		case GLUT_KEY_LEFT:
		    a-=0.02;
            lookx = r*cos(a);
            lookz = r*sin(a);

			cameraAngle -= 0.03;

			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    if(squareLen<22 && squareLen>0) {
                squareLen-=1;
                s_r++;
		    }
			break;
		case GLUT_KEY_END:
		    if(squareLen<21 && squareLen>-1) {
                squareLen+=1;
                s_r--;
		    }
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(lookx,looky,lookz,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

	drawArm();
	//drawEmni();

	//arrow();
	//arrow();

    //glColor3f(0,1,0);
    //drawSquare(50);

    //drawSS();

    //drawMY();
    //drawMyTest();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){


	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization


	lookx = r*cos(a);
	lookz = r*sin(a);

	/**
        if 1, draw grid
        else no grid
    */
	drawgrid=0;

	/**
        if 1, draw axis
        else no axis
    */
	drawaxes=1;

	/**
        Camera location
    */
	cameraHeight=50.0;
	cameraAngle=10.0;

    /**
        Don't know
    */
	angle=50;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
    // Default
	glutInit(&argc,argv);
	// set up window size
	glutInitWindowSize(500, 500);
	// Where openGL window is created on the monitor screen
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Window Name");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
