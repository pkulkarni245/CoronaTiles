#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
//#include<dos.h>
//#include<conio.h>
//#include<windows.h>

float bspd=0.1; //obstacle dx value
float b1x=50.0,b1y=0;//obstacle 1 init position
float hm=0.0;//obstacle movement dy value
int i=0,sci=1;float scf=1; // for increment score score_int score_flag
char scs[20],slevel[20];
int level=1,lflag=1,wflag=1; //level_flag & welcome_flag init w/ 1
float angle;
double radius=3;
int menu;
static GLfloat theta[] = {0.0,0.0,0.0};


void menuFunction(int n){
	switch(n){
		case 0: exit(0); break;
	}
}

void drawSquare(double x1, double y1, double sidelength){
    double halfside = sidelength / 2;
    glBegin(GL_POLYGON);
    glColor3f(0.3,0.6,0.3);
    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);
    glEnd();
}

void drawRotatedSquare(double x1, double y1, double sidelength){
    double halfside = sidelength / 2; 
    double cmn = 6.2;
    glColor3f(0.3,0.6,0.3);
    glBegin(GL_POLYGON);	
    glVertex2d(x1 + cmn, y1);
    glVertex2d(x1, y1 -cmn);
    glVertex2d(x1 -cmn, y1);
    glVertex2d(x1, y1 + cmn);
    glEnd();
 }


void drawObstacle(int annihilate){
	float xa=b1x+2.5,ya=b1y+17.5,xb,yb;
	//*
	//annihilation
	if(level>=3)
		annihilate=1;
	if(annihilate==1)
		ya=(rand()%81)+5;
		//*/
	drawSquare(xa,ya,8.8);
	drawRotatedSquare(xa,ya,13);
	float angle;
	double radius=5;
	glColor3f(0.3,0.5,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(xa,ya);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
		xb = xa+sin(angle)*radius;
		yb = ya+cos(angle)*radius;
		glVertex2f(xb,yb);
	}
	glEnd();
}

void init(void){
	srand(time(0));
	b1y=(rand()%61)+20;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , .0);
}

void drawPerson(){
	float xa=8,ya=43,xb,yb;
	float angle;
	double radius=3;
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xa,ya);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
		xb = xa+sin(angle)*radius;
		yb = ya+cos(angle)*radius;
		glVertex2f(xb,yb);
	}
	glEnd();
	glBegin(GL_QUADS); 
	glColor3f(  0.0f,  0.0f, 0.0f);	
	glVertex2f(4,28.9);
	glColor3f(  0.0f,  0.0f, 0.0f);
	glVertex2f(12,28.9);
	glColor3f(0.5,0.7,0.7);
	  glVertex2f(12, 39.9);
	glColor3f(0.5,0.7,0.7);
	  glVertex2f(4,39.9 );
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(2,32);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(3.9,32);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(3.9, 39.9);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(2,39.9 );
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(12.1,32);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(13.9,32);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(13.9, 39.9);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(12.1,39.9 );
	glEnd();
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(3,31);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
		xb = 3+sin(angle)*1;
		yb = 31+cos(angle)*1;
		glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(13,31);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
		xb = 13+sin(angle)*1;
		yb = 31+cos(angle)*1;
		glVertex2f(xb,yb);
	}
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(4.5,18);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(7.5,18);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(7.5, 28.5);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(4.5,28.5);
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(8.5,18);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(11.5,18);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(11.5, 28.5);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(8.5,28.5);
	glEnd();
	glColor3f(0.7,0.0,0.7);
	glRectf(5,16.8,7,17.9);//right foot
	glRectf(9,16.8,11,17.9);//right foot
	glFlush();
}
void drawProtocolPerson(){
	float angle;
	double radius=3;
	float xb,yb,xa=8,ya=43;
	glColor3f(1.0,1.0,0.6);//Head
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(8,43);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
	    xb = xa+sin(angle)*radius;
	    yb = ya+cos(angle)*radius;
	    glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glRectf(5.6,40.3,10.4,43.2);//mask
	glColor3f(0.7,1.0,1.0);
	glRectf(4,28.5,12,39.9);//body
	glColor3f(0.7,1.0,1.0);
	glRectf(2,32,3.9,39.9);//left arm
	glRectf(3.4,30.8,3.8,31.9);//right glove thumb
	glRectf(2.1,29,3.4,31.9);//right glove fingers
	glColor3f(0.7,1.0,1.0);
	glRectf(12.1,32,14,39.9);//right arm
	glRectf(12.1,30.8,12.6,31.9);//right glove thumb
	glRectf(12.6,29,13.9,31.9);//right glove fingers
	glColor3f(0.7,1.0,1.0);
	glRectf(4.5,18,7.7,28.8);//left leg
	glRectf(8.3,18,11.5,28.8);//right leg
	glColor3f(0.7,0.0,0.7);
	glRectf(5,16.8,7,17.9);//right leg
	glRectf(9,16.8,11,17.9);//right leg
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(6,45.3);
	glVertex2f(10,45.3);
	glVertex2f(12,41);
	glVertex2f(4,41);
	glEnd();
	glFlush();
}

void drawSalutePerson(){
	float xa=8,ya=43,xb,yb;
	float angle;
	double radius=3;
	glColor3f(1.0,1.0,0.6);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xa,ya);
	for (angle=1.0f;angle<361.0f;angle+=0.2){
		xb = xa+sin(angle)*radius;
		yb = ya+cos(angle)*radius;
		glVertex2f(xb,yb);
	}
	glEnd();
	glColor3f(0.7,1.0,1.0);
	glRectf(5.6,40.3,10.4,43.2);//mask
	glBegin(GL_QUADS); 
	glColor3f(  0.0f,  0.0f, 0.0f);	
	glVertex2f(4,28.9);
	glColor3f(  0.0f,  0.0f, 0.0f);
	glVertex2f(12,28.9);
	glColor3f(0.5,0.7,0.7);
	  glVertex2f(12, 39.9);
	glColor3f(0.5,0.7,0.7);
	  glVertex2f(4,39.9 );
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(2,32);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(3.9,32);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(3.9, 39.9);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(2,39.9 );
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(12.1,32);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(13.9,32);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(13.9, 39.9);
	glColor3f(0.7,0.8,1.0);
	  glVertex2f(12.1,39.9 );
	glEnd();	
	glColor3f(0.7,1.0,1.0);
	glRectf(3.4,30.8,3.8,31.9);//left glove thumb
	glRectf(2.1,29,3.4,31.9);//left glove fingers
	glRectf(12.1,30.8,12.6,31.9);//right glove thumb
	glRectf(12.6,29,13.9,31.9);//right glove fingers
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(4.5,18);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(7.5,18);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(7.5, 28.5);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(4.5,28.5);
	glEnd();
	glBegin(GL_QUADS);	  
	glColor3f(  0.0f,  0.0f, 0.0f);	
	  glVertex2f(8.5,18);
	glColor3f(  0.0f,  0.0f, 0.0f);
	  glVertex2f(11.5,18);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(11.5, 28.5);
	glColor3f(0.2,0.2,0.6);
	  glVertex2f(8.5,28.5);
	glEnd();
	glColor3f(0.7,0.0,0.7);
	glRectf(5,16.8,7,17.9);//right foot
	glRectf(9,16.8,11,17.9);//right foot
	glFlush();
}

void renderBitmapString(float x,float y,float z,void *font,char*string){
	char *c;
	glRasterPos3f(x, y,z);
	for(c=string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//GameOver Checking
	if(
	(i==330||i==-80)
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
	&&(int)b1y<18+(int)hm&&(int)b1y+14>18+(int)hm))
	//legs checking
	{//endgame screen: score display
		wflag=-1;
		int flashcheck=0;
		for(flashcheck=0;flashcheck<3;flashcheck++){
			if(flashcheck%2==0){
				glColor3f(1,0,0);
				glRectf(0,0,100,100);
			}else{
				glColor3f(0,0,0);
				glRectf(0,0,100,100);
			}
			glColor3f(227/255.0,229/255.0,47/255.0);
			glRectf(0.0,0.0,100.0,10.0);//floor
			glRectf(0.0,100.0,100.0,90.0);//ceil
			glColor3f(0,0,0);
			renderBitmapString(40,95,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
			glutSwapBuffers();
			glFlush();
			sleep(1);
		}
		glColor3f(0.0,0.0,0.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(1.0,0.0,0.0);
		glColor3f(1,0,0);
		renderBitmapString(43,70,0,GLUT_BITMAP_HELVETICA_18,"GAME OVER");
		glColor3f(227/255.0,229/255.0,47/255.0);
		glRectf(0.0,0.0,100.0,10.0);//floor
		glRectf(0.0,100.0,100.0,90.0);//ceil
		renderBitmapString(37,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"Days Survived:");
		renderBitmapString(60,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glColor3f(0.0,0.0,0.0);
		renderBitmapString(39,5,0,GLUT_BITMAP_HELVETICA_10,"PRESS SPACEBAR TO CONTINUE");
		renderBitmapString(40,95,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		glutSwapBuffers();
		glFlush();
	}
	else if(wflag==1){//Welcome Screen
		wflag=0;
		char prof[4][20]={"Prof MS Bhargavi","Prof Shruthiba A","Prof N Thanuja","Prof Anjini L"};int slide;
		glColor3f(227/255.0,229/255.0,47/255.0);
		glRectf(0.0,0.0,100.0,10.0);//floor
		glRectf(0.0,100.0,100.0,90.0);//ceil
		for(slide=0;slide<5;slide++){
			glColor3f(0,0,0);
			glRectf(0,10,100,90);
			glColor3f(227/255.0,229/255.0,47/255.0);
			if(slide==0)
				renderBitmapString(23,60,0,GLUT_BITMAP_TIMES_ROMAN_24,"A Bangalore Institute of Technology Production...");
			else if(slide==1||slide==2){
				renderBitmapString(31,65,0,GLUT_BITMAP_TIMES_ROMAN_24,"Under the able guidance of");
				renderBitmapString(27,43,0,GLUT_BITMAP_HELVETICA_12,"Asst Prof");
				renderBitmapString(27,40,0,GLUT_BITMAP_HELVETICA_12,"Dept of CS&E");
				renderBitmapString(60,43,0,GLUT_BITMAP_HELVETICA_12,"Asst Prof");
				renderBitmapString(60,40,0,GLUT_BITMAP_HELVETICA_12,"Dept of CS&E");
				int arrInd=(slide-1)*2;
				renderBitmapString(27,46,0,GLUT_BITMAP_HELVETICA_18,prof[arrInd]);
				renderBitmapString(60,46,0,GLUT_BITMAP_HELVETICA_18,prof[(arrInd+1)]);
			}
			if(slide==3){
				renderBitmapString(31,65,0,GLUT_BITMAP_TIMES_ROMAN_24,"Under the able guidance of");
				renderBitmapString(39,46,0,GLUT_BITMAP_HELVETICA_18,"Bhanushree KJ");
				renderBitmapString(39,43,0,GLUT_BITMAP_HELVETICA_12,"Asst Prof");
				renderBitmapString(39,40,0,GLUT_BITMAP_HELVETICA_12,"Dept of CS&E");

			}
			if(slide==4){
				glColor3f(0,0,0);
				glRectf(0,0,100,100);
			}
			glutSwapBuffers();
			glFlush();
			sleep(2);
		}


		glColor3f(227/255.0,229/255.0,47/255.0);
		glRectf(0.0,0.0,100.0,10.0);//floor
		glRectf(0.0,100.0,100.0,90.0);//ceil
		renderBitmapString(40,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		renderBitmapString(36,11,0,GLUT_BITMAP_HELVETICA_12,"Pavan Kulkarni    -    Pulkit Vaish");
		glColor3f(0.0,0.0,0.0);
		renderBitmapString(43,5,0,GLUT_BITMAP_HELVETICA_10,"CLICK TO PLAY");
		glutSwapBuffers();
		glFlush();
	}
	else if(wflag==2){//message screen
		glColor3f(0,0,0);
		glRectf(0,0,100,100);
		glColor3f(227/255.0,229/255.0,47/255.0);
		glRectf(0.0,0.0,100.0,10.0);//floor
		glRectf(0.0,100.0,100.0,90.0);//ceil
		glColor3f(0.0,0.0,0.0);
		renderBitmapString(40,95,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		glColor3f(1.0,1.0,0.6);
		renderBitmapString(30,70,0,GLUT_BITMAP_HELVETICA_18,"PRECAUTIONS AND GUIDELINES");
		renderBitmapString(32,60,0,GLUT_BITMAP_HELVETICA_18,"-Wear mask at all the times");
		renderBitmapString(32,55,0,GLUT_BITMAP_HELVETICA_18,"-Maintain social distancing when in a crowd.");
		renderBitmapString(32,50,0,GLUT_BITMAP_HELVETICA_18,"-Always wash your hands before consuming edibles.");
		renderBitmapString(32,45,0,GLUT_BITMAP_HELVETICA_18,"-Cover your mouth when you cough or sneeze.");
		glColor3f(0.0,0.0,0.0);
		renderBitmapString(32,5,0,GLUT_BITMAP_HELVETICA_18,"Pavan Kulkarni    -    Pulkit Vaish");
		drawProtocolPerson();
		glPushMatrix();
		glTranslatef(30.0,5,0);
		glScalef(.7,.7,0);
		drawSalutePerson();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(50.0,5,0);
		glScalef(.7,.7,0);
		drawSalutePerson();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(70.0,5,0);
		glScalef(.7,.7,0);
		drawSalutePerson();
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
	else if(wflag==0){
		//on every increase by 50 in score in each level
		if(sci%50==0&&lflag==1){
			lflag=0; //make level_flag=0
			level++;//increase level by 1
			bspd+=0.01;//increase block_dx_speed by 0.01
		}
		//within every level make level_flag=1
		else if(sci%50!=0&&lflag!=1){
			lflag=1;
		}
		glPushMatrix();
		glColor3f(227/255.0,229/255.0,47/255.0);
		glRectf(0.0,0.0,100.0,5.0);    //floor
		glRectf(0.0,100.0,100.0,95.0); //ceil
		glColor3f(0.0,0.0,0.0);
		renderBitmapString(40,96,0,GLUT_BITMAP_TIMES_ROMAN_24,"Corona Tiles");
		renderBitmapString(1,1,0,GLUT_BITMAP_TIMES_ROMAN_24,"Days Survived:");
		sprintf(slevel,"%d",level); //level
		renderBitmapString(80,1,0,GLUT_BITMAP_TIMES_ROMAN_24,"Wave:");
		renderBitmapString(90,1,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);
		scf+=0.025;//increase speed at each wave
		sci=(int)scf;
		sprintf(scs,"%d",sci);
		//from int to char conversion to display score
		renderBitmapString(20,1,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glTranslatef(0.0,hm,0.0);
		drawPerson();
		if(b1x<-10){
			b1x=50;         //total width is 50
			b1y=(rand()%25)+20;
			//10 for selling+10 for giving enough space
			// block bottom limit 0+20 & top limit 24+20=44
		}
		else
			b1x-=bspd;
		//within the projection volume dec its x value by block_speed
		glTranslatef(b1x,-hm,0.0);
		/*
		//Crosshairs through virus for testing purposes
		glBegin(GL_LINES);
		glVertex2f(b1x+2,0);
		glVertex2f(b1x+2,100);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(0,b1y+17);
		glVertex2f(100,b1y+17);
		glEnd();
		//*/
		drawObstacle(0);
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
}


void movePersonUp(void){
	hm+=0.15;
	i++;
	if(wflag!=-1)
		glutPostRedisplay();
}


void movePersonDown(){
	hm-=0.15;
	i--;
	if(wflag!=-1)
		glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	
	switch (button){
		case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		glutIdleFunc(movePersonUp);
		else if (state == GLUT_UP)
		glutIdleFunc(movePersonDown);
		break;
		default: break;
	}
}


void keys(unsigned char key,int x,int y){
	if(key=='w') glutIdleFunc(movePersonUp);
	if(key=='m') glutIdleFunc(movePersonDown);
	if(key=='s') if(wflag==0) wflag=-1;
	if(key==32) if(wflag==-1) wflag=2;
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Corona Tiles");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	menu=glutCreateMenu(menuFunction);
	glutCreateMenu(menuFunction);
	glutAddMenuEntry("-----MENU-----",-1);
	glutAddMenuEntry("Exit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
 }
