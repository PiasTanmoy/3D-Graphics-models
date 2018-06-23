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



double eyeX = 0;
double eyeY = 0;
double eyeZ = 80;


double lookX = 0;
double lookY = 0;
double lookZ = 0;

double upX = 0;
double upY = 1;
double upZ = 0;


struct position
{
    double x, y, z;
};

struct position pos;

struct left
{
    double x, y, z;
};

struct left l;

struct right
{
    double x, y, z;
};

struct right r;

struct up
{
    double x, y, z;
};

struct up u;

void initCam()
{

    pos.x = 100;
    pos.y = 100;
    pos.z = 0;


    r.x = -1*sqrt(2);
    r.y = 1*sqrt(2);
    r.z = 0;

    l.x = -1*sqrt(2);
    l.y = -1*sqrt(2);
    l.z = 0;

    u.x = 0;
    u.y = 0;
    u.z = 1;


}

struct square
{
    double x,y,z;
};

struct point
{
	double x,y,z;
};


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

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}




void drawSphere(double radius,int slices,int stacks, double s_x, double s_y, double s_z)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	/**
        i = Slack (Vertical line)
        j = slice (Horizontal line)
        for a particular point on slack
        generate all points on the slice
    */
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x= s_x +  r*cos(((double)j/(double)slices)*0.5*pi);
			points[i][j].y= s_y + r*sin(((double)j/(double)slices)*0.5*pi);
			points[i][j].z= s_z + h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        glColor3f(1,0,0);
		for(j=0;j<slices;j++)
		{
		    /**
                Make a rectangle using 2 points on a slack
                and 2 points from the next slack
		    */
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
				*/
			}glEnd();
		}
	}
}





void drawCylinder(double radius,double height, int slices,int stacks, double s_x, double s_y, double s_z)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	h = (height/2);
	r = radius;
	//generate points
	/**
        i = Slack (Vertical line)
        j = slice (Horizontal line)
        for a particular point on slack
        generate all points on the slice
    */
	for(i=0;i<2;i++)
	{
		for(j=0;j<=slices;j++)
		{
			points[i][j].x= s_x +  r*cos(((double)j/(double)slices)*0.5*pi);
			points[i][j].y= s_y + r*sin(((double)j/(double)slices)*0.5*pi);
			points[i][j].z= s_z + h;
		}
		h -= (height);
	}
	//draw quads using generated points
	for(i=0;i<2;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        glColor3f(0,1,0);
		for(j=0;j<slices;j++)
		{
		    /**
                Make a rectangle using 2 points on a slack
                and 2 points from the next slack
		    */
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
				*/
			}glEnd();
		}
	}
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


    drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);

    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);
        glRotatef(90,0,1,0);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);
        glRotatef(90,0,1,0);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);

    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);
        glRotatef(-90,0,0,1);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);
        glRotatef(180,0,0,1);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);
        glRotatef(90,0,0,1);
        drawSphere( s_r, 10, 50, squareLen,squareLen,squareLen);

    }
    glPopMatrix();



    //drawSquare(squr.squareLen);

    //drawSphere(50, 50, 30);
    //drawSquare(100);
}


void drawMyTest()
{
    drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
        glRotatef(90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,1,0,0);
        glRotatef(-90,0,0,1);
        glRotatef(-90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(-90,1,0,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(180,1,0,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
        glRotatef(-90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(-90,0,1,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
        glRotatef(-90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(180,0,1,0);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(-90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(180,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(-180,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90,0,0,1);
        glRotatef(90,0,0,1);
        drawCylinder(s_r, 2*squareLen, 50, 50, squr.x + squareLen, squr.y + squareLen, 0);
    }
    glPopMatrix();
}


double A = 0.1;



double tx;
double ty;
double tz;


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '2':
			lookX++;
            tx = l.x*cos(A) + r.x*sin(A);
            ty = l.y*cos(A) + r.y*sin(A);
            tz = l.z*cos(A) + r.z*sin(A);

            r.x = r.x*cos(A) - l.x*sin(A);
            r.y = r.y*cos(A) - l.y*sin(A);
            r.z = r.z*cos(A) - l.z*sin(A);

            l.x = tx;
            l.y = ty;
            l.z = tz;

			break;
        case '1':
            A = A*(-1);

            tx = l.x*cos(A) + r.x*sin(A);
            ty = l.y*cos(A) + r.y*sin(A);
            tz = l.z*cos(A) + r.z*sin(A);

            r.x = r.x*cos(A) - l.x*sin(A);
            r.y = r.y*cos(A) - l.y*sin(A);
            r.z = r.z*cos(A) - l.z*sin(A);

            l.x = tx;
            l.y = ty;
            l.z = tz;

            A = A*(-1);
            lookX--;

			break;
        case '3':
            tx = l.x*cos(A) + u.x*sin(A);
            ty = l.y*cos(A) + u.y*sin(A);
            tz = l.z*cos(A) + u.z*sin(A);

            u.x = u.x*cos(A) - l.x*sin(A);
            u.y = u.y*cos(A) - l.y*sin(A);
            u.z = u.z*cos(A) + l.z*sin(A);

            l.x = tx;
            l.y = ty;
            l.z = tz;

			lookY++;

			break;
        case '4':
            A = -1*A;
            tx = l.x*cos(A) + u.x*sin(A);
            ty = l.y*cos(A) + u.y*sin(A);
            tz = l.z*cos(A) + u.z*sin(A);

            u.x = u.x*cos(A) - l.x*sin(A);
            u.y = u.y*cos(A) - l.y*sin(A);
            u.z = u.z*cos(A) + l.z*sin(A);

            l.x = tx;
            l.y = ty;
            l.z = tz;
            A = -1*A;

			break;
        case '6':

            tx = r.x*cos(A) + u.x*sin(A);
            ty = r.y*cos(A) + u.y*sin(A);
            tz = r.z*cos(A) + u.z*sin(A);

            u.x = u.x*cos(A) - r.x*sin(A);
            u.y = u.y*cos(A) - r.y*sin(A);
            u.z = u.z*cos(A) - r.z*sin(A);

            r.x = tx;
            r.y = ty;
            r.z = tz;
			break;
        case '5':
            A = -1*A;
            tx = r.x*cos(A) + u.x*sin(A);
            ty = r.y*cos(A) + u.y*sin(A);
            tz = r.z*cos(A) + u.z*sin(A);

            u.x = u.x*cos(A) - r.x*sin(A);
            u.y = u.y*cos(A) - r.y*sin(A);
            u.z = u.z*cos(A) - r.z*sin(A);

            r.x = tx;
            r.y = ty;
            r.z = tz;
            A = -1*A;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			pos.x-= 2*l.x;
			pos.y-= 2*l.y;
			pos.z-= 2*l.z;

			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			pos.x+= 2*l.x;
			pos.y+= 2*l.y;
			pos.z+= 2*l.z;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;

			pos.x+= 2*r.x;
			pos.y+= 2*r.y;
			pos.z+= 2*r.z;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;

			pos.x-= 2*r.x;
            pos.y-= 2*r.y;
            pos.z-= 2*r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+= 2*u.x;
			pos.y+= 2*u.y;
			pos.z+= 2*u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    pos.x-= 2*u.x;
			pos.y-= 2*u.y;
			pos.z-= 2*u.z;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    if(squareLen<21 && squareLen>0) {
                squareLen-=1;
                s_r++;
		    }
			break;
		case GLUT_KEY_END:
		    if(squareLen<20 && squareLen>-1) {
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
	gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x , pos.y+l.y, pos.z+l.z,	u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    //glColor3f(0,1,0);
    //drawSquare(50);

    //drawSS();

    drawMY();
    drawMyTest();

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
	initCam();
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
