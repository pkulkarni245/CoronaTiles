#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
//#include<dos.h>
#include<stdio.h>
//#include<conio.h>
//#include<windows.h>

/* CHANGES MADE TO THE ORIGINAL HELICOPTER CODE PROVIDED IN THE PDF
* drawObstacle primitive now uses 2 squares instead of triangles.
* Center : x= xa+2.5 and y=ya+17.5
* drawSquare and drawRotatedSquare were added.
* THIS IS NOT THE FILE CURRENT PRESENTLY UNDER THE NAME coronatiles.c but an extension/modification to the original code we copied.	
**/

float bspd=0.1; // block dx value
char name[25];
float b1x=50.0,b1y=0;//block 1 init position
float hm=0.0;//copter moving dy value
int i=0,sci=1;float scf=1; // for increment score score_int score_flag
char scs[20],slevel[20];
//to store score_string using itoa() and level as well
int level=1,lflag=1,wflag=1; //level_flag & welcome_flag init w/ 1

float angle;
double radius=3;

void drawSquare(double x1, double y1, double sidelength)
{
    double halfside = sidelength / 2;

   //glColor3f(0.36,0.65,0.36);
    glBegin(GL_POLYGON);
    glColor3f(0.3,0.6,0.3);
    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

void drawRotatedSquare(double x1, double y1, double sidelength)
{

    double halfside = sidelength / 2; 
    //x1=xa;y1=ya;
    //xa+2.83,
    double cmn = 6.2;
    glColor3f(0.3,0.6,0.3);
    //glColor3f(.23,0.49,0.23);
    glBegin(GL_POLYGON);	
    glVertex2d(x1 + cmn, y1);
    glVertex2d(x1, y1 -cmn);
    glVertex2d(x1 -cmn, y1);
    glVertex2d(x1, y1 + cmn);
    glEnd();
 
}


void drawObstacle(int annihilate){
	float xa=b1x+2.5,ya=b1y+17.5,xb,yb;
	//if(windowNumber==3)
		//annihilate=1;
	//if(annihilate==1){
		//ya=(rand()%61)+20;
	//}
	drawSquare(xa,ya,8.8);
	drawRotatedSquare(xa,ya,13);
	float angle;
	double radius=5;
	glColor3f(0.3,0.5,0.3);
	glBegin(GL_POLYGON);
		glVertex2f(xa,ya);
		for (angle=1.0f;angle<361.0f;angle+=0.2)
		{
			xb = xa+sin(angle)*radius;
			yb = ya+cos(angle)*radius;
			glVertex2f(xb,yb);
		}
	glEnd();
	/**
	glColor3f(1,0.6,0.2);
	glBegin(GL_TRIANGLES);
	glVertex2f(xa-2,(ya+5));
	glVertex2f(xa,(ya+7));
	glVertex2f(xa+2,(ya+5));//end up	
	
	float rectX = (xa+5)/1.414;
	float rectY = (ya+5)/1.414;
	glRectf(rectX,rectY,(xa+7),(ya+7));
	
	////////2ND TRIANGLE/////////
	glVertex2f(xa+5,(ya+2));
	glVertex2f(xa+5,(ya-2));
	glVertex2f(xa+7,ya);//end right
	glVertex2f(xa-2,(ya-5));
	glVertex2f(xa+2,(ya-5));
	glVertex2f(xa,(ya-7));//end down
	glVertex2f(xa-5,(ya+2));
	glVertex2f(xa-5,(ya-2));
	glVertex2f(xa-7,ya);//end left
	glEnd();
	**/
}

void init(void)
{
	srand(time(0));
	b1y=(rand()%45)+10;//b/w 10 to 44
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , .0);
}


void drawPerson(){
	float xa=8,ya=43,xb,yb;
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xa,ya);//xa=8 and ya=43
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    xb = xa+sin(angle)*radius;
	    yb = ya+cos(angle)*radius;
	    glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glRectf(4,28.9,12,39.9);//body
	glColor3f(0.7,1.0,1.0);
	glRectf(2,32,3.9,39.9);//left arm
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(3,31);//left hand
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    xb = 3+sin(angle)*1;
	    yb = 31+cos(angle)*1;
	    glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glRectf(12.1,32,14,39.9);//right arm
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(13,31);//right hand
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    xb = 13+sin(angle)*1;
	    yb = 31+cos(angle)*1;
	    glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glRectf(4.5,18,7.5,28.8);//left leg
	glRectf(8.5,18,11.5,28.8);//right leg
	glColor3f(0.7,0.0,0.7);
	glRectf(5,16.8,7,17.9);//left boot
	glRectf(9,16.8,11,17.9);//right boot
	glFlush();
}


void renderBitmapString(float x,float y,float z,void *font,char*string)
{
	char *c;
	glRasterPos3f(x, y,z);
	for(c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//GameOver Checking
	if(
	//(i==730||i==-700)
	(i==300||i==-50)
	//top and bottom wall check
	||
	( ((int)b1x==8) && (int)b1y<30+(int)hm&&(int)b1y+16>30+(int)hm)
		//body checking
	||
	( ((int)b1x==4)
	&&(int)b1y<43+(int)hm&&(int)b1y+14>43+(int)hm)
		 // Head checking
	||
	( ((int)b1x==7||(int)b1x==1)
	//||(int)b1x==6) 
	//&&(int)b1y<45+(int)hm&&(int)b1y+35>45+(int)hm)
	&&(int)b1y<18+(int)hm&&(int)b1y+14>18+(int)hm))
	//legs checking
	{
		glColor3f(0.0,0.0,1.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(1.0,0.0,0.0);
		renderBitmapString(40,70,0,GLUT_BITMAP_HELVETICA_18,"GAME OVER!!!");
		glColor3f(1.0,1.0,1.0);
		renderBitmapString(25,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"You");
		renderBitmapString(45,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"scored:");
		renderBitmapString(70,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glutSwapBuffers();
		glFlush();
		printf("\nGAME OVER\n\n");
		printf("%s You scored %s" ,name,scs);
		printf("\n\nClose the console window to exit...\n");
		//getch();
		exit(0);
	}
	else if(wflag==1)//Welcome Screen
	{
		wflag=0;
		glColor3f(0.0,0.5,0.7);
		glRectf(0.0,0.0,100.0,10.0);//ceil
		glRectf(0.0,100.0,100.0,90.0);//floor
		glColor3f(1.0,1.0,1.0);
		renderBitmapString(35,85,0,GLUT_BITMAP_HELVETICA_18,"CITY ENGINEERING COLLEGE");
		renderBitmapString(41,80,0,GLUT_BITMAP_HELVETICA_12,"Bangalore, Karnataka-560 062");
		glColor3f(1.0,1.0,0.0);
		renderBitmapString(20,65,0,GLUT_BITMAP_8_BY_13,"a mini project for Computer Graphics & Visualization Laboratery");
		renderBitmapString(45.5,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"Helicopter");
		glColor3f(1.0,0.0,0.0);
		renderBitmapString(40,45,0,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome");
		renderBitmapString(53,45,0,GLUT_BITMAP_TIMES_ROMAN_24,name);
		renderBitmapString(43,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");
		renderBitmapString(17,24,0,GLUT_BITMAP_9_BY_15,"CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP RELEASE TO GO DOWN");
		glColor3f(0.0,0.0,0.0);
		drawPerson();
		glutSwapBuffers();
		glFlush();
	}
	else
	{
		//on every increase by 50 in score in each level
		if(sci%50==0&&lflag==1)
		{
			lflag=0; //make level_flag=0
			level++;//increase level by 1
			bspd+=0.01;//increase block_dx_speed by 0.01
		}
		//within every level make level_flag=1
		else if(sci%50!=0&&lflag!=1)
		{
			lflag=1;
		}
		glPushMatrix();
		glColor3f(0.0,0.5,0.7);
		glRectf(0.0,0.0,100.0,10.0);    //ceil
		glRectf(0.0,100.0,100.0,90.0); //floor
		glColor3f(0.0,0.0,0.0); //score
		renderBitmapString(1,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Distance:");
		//glColor3f(0.7,0.7,0.7);
		sprintf(slevel,"%d",level); //level
		renderBitmapString(80,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Level:");
		renderBitmapString(93,3,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);
		scf+=0.025;         //so less as program run very fast
		sci=(int)scf;
		sprintf(scs,"%d",sci);
		//from int to char convertion to display score
		renderBitmapString(20,3,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glTranslatef(0.0,hm,0.0);
		// hm(=dy) changes occur by mouse func
		drawPerson();
		//code for helicopter
		//if wall move towards left & get out of projection volume
		if(b1x<-10)
		{
			b1x=50;         //total width is 50
			b1y=(rand()%25)+20;
			//10 for selling+10 for giving enough space
			// block bottom limit 0+20 & top limit 24+20=44
		}
		else
			b1x-=bspd;
		//within the projection volume dec its x value by block_speed
		glBegin(GL_LINES);
		glVertex2f(0,i);
		glVertex2f(100,i);
		glEnd();
		glTranslatef(b1x,-hm,0.0);
		glBegin(GL_LINES);
		glVertex2f(b1x+2,0);
		glVertex2f(b1x+2,100);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(0,b1y+17);
		glVertex2f(100,b1y+17);
		glEnd();
		drawObstacle(0);
		//glRectf(b1x,b1y,b1x+5,b1y+35);//block 1
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
}


void moveHeliU(void)
{
	hm+=0.15;
	i++;
	glutPostRedisplay();
}


void moveHeliD()
{
	hm-=0.15;
	i--;
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
	{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		glutIdleFunc(moveHeliU);
		else if (state == GLUT_UP)
		glutIdleFunc(moveHeliD);
		break;
		default: break;
	}
}


void keys(unsigned char key,int x,int y)
{
	if(key=='w') glutIdleFunc(moveHeliU);
	if(key=='m') glutIdleFunc(moveHeliD);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Corona Tiles");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutMainLoop();
	return 0;
 }

 
