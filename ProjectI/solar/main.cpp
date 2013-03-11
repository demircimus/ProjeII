#include <iostream>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL.h>

using namespace std;
GLfloat angleSun = 0.0f;
GLfloat angleEarth = 0.0f;
GLfloat angleMoon = 0.0f;

GLint LoadGLTexture(char *, int , int );

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

GLuint textureEarth, textureSun,textureMoon, background, textureMercury; 

void initRendering() 
{	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	background = LoadGLTexture("/Users/demircimus/Documents/Visual Studio 2010/Projects/ProjectI/solar/BackgroundTexture.bmp", 512, 512);
	textureSun = LoadGLTexture("/Users/demircimus/Documents/Visual Studio 2010/Projects/ProjectI/solar/SunTexture.bmp", 256, 256);
	textureEarth = LoadGLTexture("/Users/demircimus/Documents/Visual Studio 2010/Projects/ProjectI/solar/EarthTexture.bmp", 256, 256);
	textureMoon = LoadGLTexture("/Users/demircimus/Documents/Visual Studio 2010/Projects/ProjectI/solar/MoonTexture.bmp", 256, 256);
	textureMercury = LoadGLTexture("/Users/demircimus/Documents/Visual Studio 2010/Projects/ProjectI/solar/MercuryTexture.bmp", 256, 256);
}

 void drawBackground() 
 {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(0, 1, 0, 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glDepthMask( false );

	glBindTexture(GL_TEXTURE_2D, background);
	glBegin(GL_QUADS ); {
	  glTexCoord2f( 0.f, 0.f );
	  glVertex2f( 0.f, 0.f );
	  glTexCoord2f( 0.f, 1.f );
	  glVertex2f( 0.f, 1.f );
	  glTexCoord2f( 1.f, 1.f );
	  glVertex2f( 1.f, 1.f );
	  glTexCoord2f( 1.f, 0.f );
	  glVertex2f( 1.f, 0.f );
	} 
	glEnd();

	glDepthMask( true );

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawBackground() ;
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	//Light operations
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	//

	GLUquadric *quadEarth = gluNewQuadric();
	GLUquadric *quadSun = gluNewQuadric();
	GLUquadric *quadMoon = gluNewQuadric();
	//gluQuadricDrawStyle(quadEarth, GLU_FILL);
	
	gluQuadricNormals(quadEarth, GLU_SMOOTH);

	glTranslatef(0.0f, 0.0f, -20.0f);
	//glRotatef(90, 1.0f, 0.0f, 0.0f);

	//Texture operations
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureSun);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Draw Sun
							
	//glRotatef(angleSun, 0.0f, 0.0f, 1.0f);						//Rotate on its own axis
	gluQuadricTexture(quadSun,1);
	gluSphere(quadSun, 1.5, 20, 20);
	gluDeleteQuadric(quadSun); 
    

	//Texture operations
	glBindTexture(GL_TEXTURE_2D, textureEarth);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Draw Earth
	glPushMatrix();		
	    glRotatef(angleEarth, 0.0f, 0.0f, 1.0f);
	    glTranslatef(6.0f, 0.0f, 0.0f);
		glRotatef(angleEarth, 0.0f, 0.0f, 1.0f);						//Rotate on its own axis
	glPushMatrix();
		gluQuadricTexture(quadEarth,1);
		gluSphere(quadEarth, 1.0, 20, 20);
	glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, textureMoon);
		glRotatef(angleEarth, 0.0f, 0.0f, 1.0f);						//Rotate on its own axis
	    glTranslatef(2.0f, 0.0f, 0.0f);		
		gluQuadricTexture(quadMoon,1);
		gluSphere(quadMoon, 0.5, 20, 20);
		gluDeleteQuadric(quadMoon); 
    glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, textureMercury);
	    glRotatef(-angleEarth, 0.0f, 0.0f, 1.0f);
	    glTranslatef(2.75f, 0.0f, 0.0f);
		glRotatef(-angleEarth, 0.0f, 0.0f, 1.0f);						//Rotate on its own axis
	glPushMatrix();
		gluQuadricTexture(quadEarth,1);
		gluSphere(quadEarth, 0.75, 20, 20);
		gluDeleteQuadric(quadEarth); 
	glPopMatrix();

    //glDisable(GL_TEXTURE_2D); 
	
	glFlush();
	glutSwapBuffers();
}

static void timerCallback (int value)
{
	angleSun+=2.0f;
	angleEarth+=2.0f;
	angleMoon+24.0f;

    if(angleSun>360.f)
    {
        angleSun-=360;
    }

    if(angleEarth>360.f)
    {
        angleEarth-=360;
    }    
	
	if(angleMoon>360.f)
    {
        angleMoon-=360;
    }

    glutPostRedisplay();
    glutTimerFunc(25,timerCallback,0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1300, 700);
	
	glutCreateWindow("Project I");
	initRendering();
	
	glutTimerFunc(25,timerCallback,0);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}

GLint LoadGLTexture(char *filename, int width, int height)
{
    GLuint _texture;
    
    _texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
     );
    
    // check for an error during the load process 
    if(_texture == 0)
    {
	    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
	
    
    glBindTexture(GL_TEXTURE_2D, _texture); // select our current texture
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return _texture;
}





