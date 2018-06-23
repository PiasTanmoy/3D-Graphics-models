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

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}


void drawBox()
{
	if(drawbox==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
		    glVertex3f( 100,100,0);
			glVertex3f(-100,100,0);

			glVertex3f( 100,-100,0);
			glVertex3f(-100,-100,0);

			glVertex3f(-100,-100,0);
			glVertex3f(-100, 100,0);

			glVertex3f(100,-100,0);
			glVertex3f(100, 100,0);

		}glEnd();
	}
}


double arrowTri = 10;
double arrowLen = 20;

void drawArrow()
{

    double angle = atan(v.y / v.x);
    double x1 = p.x;
    double y1 = p.y;

    double x2 = p.x + arrowLen*cos(angle);
    double y2 = p.y + arrowLen*sin(angle);

    double r = 5;
    double tx = (2.0*(x2) + x1)/3.0;
    double ty = (2.0*(y2) + y1)/3.0;

    /**
        Change the arrow head to the other end point
    */
    if(v.x<0) {
        tx = (2.0*(x1) + x2)/3.0;
        ty = (2.0*(y1) + y2)/3.0;

    }

    double ax1 = tx + r*cos(asin(1) + angle);
    double ay1 = ty + r*sin(asin(1) + angle);

    double ax2 = tx - r*cos(asin(1) + angle);
    double ay2 = ty - r*sin(asin(1) + angle);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f(x1, y1, 0);
        glVertex3f( x2,  y2, 0);
    }glEnd();

    if(v.x<0) {
        x2 = x1;
        y2 = y1;
    }

    glColor3f(1.0, 0, 0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(x2, y2, 0);
        glVertex3f(ax1, ay1 ,0);
        glVertex3f(ax2, ay2 ,0);
    }
    glEnd();
}




double s_r = 0;
struct square squr;

void drawMY()
{


    glColor3f(1, 1, 1);
    glTranslatef(squr.x,squr.y,squr.z+displace_sqr);
    drawSquare(squareLen);

    glPushMatrix();
    {
        //glRotatef(45,1,0,0);
        glTranslatef(squr.x,squr.y,squr.z - displace_sqr*2);
        drawSquare(squareLen);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        glTranslatef(squr.x,squr.y,squr.z - displace_sqr);
        glTranslatef(squr.x,squr.y - displace_sqr,squr.z);
        drawSquare(squareLen);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        glTranslatef(squr.x,squr.y,squr.z - displace_sqr);
        glTranslatef(squr.x,squr.y - displace_sqr,squr.z);
        drawSquare(squareLen);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        glTranslatef(squr.x,squr.y,squr.z + displace_sqr);
        glTranslatef(squr.x,squr.y - displace_sqr,squr.z);
        drawSquare(squareLen);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        glTranslatef(squr.x + displace_sqr,squr.y,squr.z );
        glTranslatef(squr.x,squr.y ,squr.z+ displace_sqr);
        drawSquare(squareLen);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        glTranslatef(squr.x + displace_sqr,squr.y,squr.z );
        glTranslatef(squr.x,squr.y ,squr.z - displace_sqr);
        drawSquare(squareLen);
    }
    glPopMatrix();

    //glRotatef(90,0,1,0);
    glTranslatef(squr.x,squr.y,squr.z-displace_sqr);

    //drawSquare(squr.squareLen);

    //drawSphere(50, 50, 30);
    //drawSquare(100);
}



void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
    double vx;
    double vy;
    double vpx;
    double vpy;
    double a=2*(3.1416/180.0);

	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;


			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;

			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			vx = v.x*cos(a);
            vy = v.y*cos(a);

            vpx = v.y*sin(a);
            vpy = -v.x*sin(a);

            v.x = vx+vpx;
            v.y = vy+vpy;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			vx = v.x*cos(a);
            vy = v.y*cos(a);

            vpx = -v.y*sin(a);
            vpy = v.x*sin(a);

            v.x = vx+vpx;
            v.y = vy+vpy;
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

void reflection()
{
    double rx;
    double ry;
    double tx;
    double ty;
    double nx=0;
    double ny=0;



    if(p.x>100 ){
        nx = -1;
        ny = 0;
    }

    else if(p.y>100 ){
        nx = 0;
        ny = -1;
    }

    else if(p.x<-100 ){
        nx = 1;
        ny = 0;
    }

    else if(p.y<-100 ){
        nx = 0;
        ny = 1;
    }

    tx = 2*(v.x * nx)*nx;
    ty = 2*(v.y * ny)*ny;

    v.x = v.x - tx;
    v.y = v.y - ty;

}



void arrow()
{
    drawBox();
    drawArrow();

    reflection();
    p.x += v.x;
    p.y += v.y;
    //drawSquare(10);
    //glTranslatef(30,60,0);
    //drawSquare(10);

}



void arrowInit()
{

    p.x = 10;
    p.y = 10;

    v.x = 0.03;
    v.y = 0.02;

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
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

	arrow();

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
	arrowInit();

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
