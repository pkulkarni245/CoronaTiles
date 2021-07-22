#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>
//#include<dos.h>
//#include<conio.h>
//#include<windows.h>

float bspd=0.2; // block dx value
char name[25];
float b1x=50.0,b1y=0;//block 1 init position
float hm=0.0;//copter moving dy value
int myTempVar=0,sci=1;float scf=1; // for increment score score_int score_flag
char scs[20],slevel[20];
//to store score_string using itoa() and level as well
int level=1,lflag=1,windowNumber=1; //level_flag & welcome_flag init w/ 1
//Coordinates to be used to determine intersection
float perx,pery,perw,perh,covx,covy,covw,covh;//person center x,y,width,height;virus center x,y,width,height
int intersectionFlag=0;


void updateIntersectionFlag();
void init(void){
	srand(time(0));
	b1y=(rand()%61)+20;//b/w 20 and 80
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , .0);
}

void renderBitmapString(float x,float y,float z,void *font,char*string){
	char *c;
	glRasterPos3f(x, y,z);
	for(c=string; *c != '\0'; c++)
	glutBitmapCharacter(font, *c);
}



void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//GameOver Checking  !!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	if(intersectionFlag==1){///////INTERSECTION CONDITION HERE, REPLACE SCF>=20 WITH INTERSECTION CONDITION//
		windowNumber=3;
		glColor3f(0.0,0.0,1.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(1.0,0.0,0.0);
		renderBitmapString(40,70,0,GLUT_BITMAP_HELVETICA_18,"GAME OVER!!!");
		glColor3f(1.0,1.0,1.0);
		renderBitmapString(25,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"You survived for ");
		renderBitmapString(59,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		renderBitmapString(65,58,0,GLUT_BITMAP_TIMES_ROMAN_24," days.");
		glutSwapBuffers();
		glFlush();
	}else if(windowNumber==1){//Welcome Screen
		windowNumber=2;
		glColor3f(0.3,0.6,0.3);
		glRectf(0.0,0.0,100.0,10.0);//ceil
		glRectf(0.0,100.0,100.0,90.0);//floor
		glColor3f(1.0,1.0,0.0);
		renderBitmapString(45.5,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		glColor3f(1.0,0.0,0.0);
		renderBitmapString(40,45,0,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome, ");
		renderBitmapString(65,45,0,GLUT_BITMAP_TIMES_ROMAN_24,name);
		renderBitmapString(43,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");
		renderBitmapString(17,24,0,GLUT_BITMAP_9_BY_15,"Use left mouse button/'w'&'m' keys to play.");
		glColor3f(0.0,0.0,0.0);
		drawPerson();
		glutSwapBuffers();
		glFlush();
	}else if(windowNumber==2){
		//on every increase by 50 in score in each level
		if(sci%50==0&&lflag==1){
			lflag=0; //make level_flag=0
			level++;//increase level by 1
			bspd+=0.05;//increase block_dx_speed by 0.01
		}
		else if(sci%50!=0&&lflag!=1){//within every level make level_flag=1
			lflag=1;
		}
		glPushMatrix();
		glColor3f(0.3,0.6,0.3);
		glRectf(0.0,0.0,100.0,10.0); //ceil
		glRectf(0.0,100.0,100.0,90.0); //floor
		glColor3f(1.0,1.0,1.0);
		renderBitmapString(35,93,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		glColor3f(0.0,0.0,0.0); //score
		renderBitmapString(1,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Days Survived:");
		sprintf(slevel,"%d",level); //level
		renderBitmapString(80,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Wave:");
		renderBitmapString(93,3,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);
		scf+=0.025; //so less as program run very fast
		sci=(int)scf;
		sprintf(scs,"%d",sci);
		//from int to char convertion to display score
		renderBitmapString(30,3,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glTranslatef(0.0,hm,0.0);
		// hm(=dy) changes occur by mouse func
		drawPerson();
		updateIntersectionFlag();
		//code for helicopter//if wall move towards left & get out of projection volume
		if(b1x<=-50){
			covx=b1x=50; //total width is 50
			b1y=(rand()%61)+20;
			//10 for selling+10 for giving enough space
			// block bottom limit 0+20 & top limit 24+20=44
		}
		else{
			covx=b1x-=bspd;
		}
		//within the projection volume dec its x value by block_speed
		glTranslatef(b1x,-hm,0.0);
		glColor3f(1.0,0.0,0.0);
		if(scf>=30)
			drawObstacle(1);
		else
			drawObstacle(0);
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}else if(windowNumber==3){//windowNumber=3

	}
}







void moveHeliU(void){
	hm+=0.2;
	myTempVar++;
	glutPostRedisplay();
}
void moveHeliD(){
	hm-=0.2;
	myTempVar--;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y){
	switch (button){
		case GLUT_LEFT_BUTTON:	if (state == GLUT_DOWN)	glutIdleFunc(moveHeliU);	else if (state == GLUT_UP)	glutIdleFunc(moveHeliD);	break;
		default:	break;
	}
}
void keys(unsigned char key,int x,int y){
	if(key=='w')	glutIdleFunc(moveHeliU);
	if(key=='m')	glutIdleFunc(moveHeliD);
	if(key=='s')	intersectionFlag=1;
}
int main(int argc, char** argv){
	printf("Enter your name to play: ");
	scanf("%s",name);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Corona Tiles");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutMainLoop();
	return 0;
}

void updateIntersectionFlag(){

}

void drawPerson(){
	float xa=8,ya=43,xb,yb;
	float angle;
	double radius=3;
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xa,ya);
		for (angle=1.0f;angle<361.0f;angle+=0.2)
		{
			xb = xa+sin(angle)*radius;
			yb = ya+cos(angle)*radius;
			glVertex2f(xb,yb);
		}
	glEnd();
	glColor3f(0.5,0.7,0.7);
	glRectf(4,28.9,12,39.9);//body
	glColor3f(0.7,0.8,1.0);
	glRectf(2,32,3.9,39.9);//left hand
	glRectf(12.2,32,14.1,39.9);//right hand
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(3,31);
		for (angle=1.0f;angle<361.0f;angle+=0.2)
		{
			xb = 3+sin(angle)*1;
			yb = 31+cos(angle)*1;
			glVertex2f(xb,yb);
		}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(13,31);
		for (angle=1.0f;angle<361.0f;angle+=0.2)
		{
			xb = 13+sin(angle)*1;
			yb = 31+cos(angle)*1;
			glVertex2f(xb,yb);
		}
	glEnd();
	glColor3f(0.2,0.2,0.6);
	glRectf(4.5,18,7.5,28.5);//left leg
	glRectf(8.5,18,11.5,28.5);//right leg
	glColor3f(0.7,0.0,0.7);
	glRectf(5,16.8,7,17.9);//right leg
	glRectf(9,16.8,11,17.9);//right leg
	glFlush();
}
void drawObstacle(int annihilate){
	float xa=b1x,ya=b1y,xb,yb;
	if(windowNumber==3)
		annihilate=1;
	if(annihilate==1){
		ya=(rand()%61)+20;
	}

	float angle;
	double radius=5;
	glColor3f(0.3,0.6,0.3);
	glBegin(GL_POLYGON);
		glVertex2f(xa,ya);
		for (angle=1.0f;angle<361.0f;angle+=0.2)
		{
			xb = xa+sin(angle)*radius;
			yb = ya+cos(angle)*radius;
			glVertex2f(xb,yb);
		}
	glEnd();
	glColor3f(1,0.6,0.2);
	glBegin(GL_TRIANGLES);
	glVertex2f(xa-2,(ya+5));
	glVertex2f(xa,(ya+7));
	glVertex2f(xa+2,(ya+5));//end up
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
	glBegin(GL_LINES);
	glVertex2f(b1x,0);
	glVertex2f(b1x,100);
	glVertex2f(0,b1y);
	glVertex2f(100,b1y);
	glEnd();

}