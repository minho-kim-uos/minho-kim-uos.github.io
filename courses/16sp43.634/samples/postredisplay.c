#include <GL/glut.h>
#include <stdio.h>

int	color = 0;

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	if(color)	glColor3f(1,1,1);
	else		glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f (0.25, 0.25, 0.0);
		glVertex3f (0.75, 0.25, 0.0);
		glVertex3f (0.75, 0.75, 0.0);
		glVertex3f (0.25, 0.75, 0.0);
	glEnd();

	glFlush ();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case ' ':
			color = (color+1)&0x01;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (250, 250); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	glClearColor (0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
