#include <GL/glut.h>
#include <stdio.h>

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f (0.25, 0.25, 0.0);
		glVertex3f (0.75, 0.25, 0.0);
		glVertex3f (0.75, 0.75, 0.0);
		glVertex3f (0.25, 0.75, 0.0);
	glEnd();

	glFlush ();
}

void special(int key, int x, int y)
{
	char	keystr[32];
	int		modifiers;
	char	mod[128];
	switch(key)
	{
	case GLUT_KEY_F1:
	case GLUT_KEY_F2:
	case GLUT_KEY_F3:
	case GLUT_KEY_F4:
	case GLUT_KEY_F5:
	case GLUT_KEY_F6:
	case GLUT_KEY_F7:
	case GLUT_KEY_F8:
	case GLUT_KEY_F9:
	case GLUT_KEY_F10:
	case GLUT_KEY_F11:
	case GLUT_KEY_F12:
		sprintf(keystr, "F%d", key-GLUT_KEY_F1+1);
		break;
	case GLUT_KEY_LEFT:
		strcpy(keystr, "left arrow");
		break;
	case GLUT_KEY_UP:
		strcpy(keystr, "up arrow");
		break;
	case GLUT_KEY_RIGHT:
		strcpy(keystr, "right arrow");
		break;
	case GLUT_KEY_DOWN:
		strcpy(keystr, "down arrow");
		break;
	case GLUT_KEY_PAGE_UP:
		strcpy(keystr, "page up");
		break;
	case GLUT_KEY_PAGE_DOWN:
		strcpy(keystr, "page down");
		break;
	case GLUT_KEY_HOME:
		strcpy(keystr, "home");
		break;
	case GLUT_KEY_END:
		strcpy(keystr, "end");
		break;
	case GLUT_KEY_INSERT:
		strcpy(keystr, "insert");
		break;
	}

	modifiers = glutGetModifiers();
	if(modifiers)
	{
		strcpy(mod, " while [");
		if(modifiers & GLUT_ACTIVE_SHIFT)	sprintf(mod, "%s Shift(or Capslock)", mod);
		if(modifiers & GLUT_ACTIVE_CTRL)	sprintf(mod, "%s Ctrl", mod);
		if(modifiers & GLUT_ACTIVE_ALT)		sprintf(mod, "%s Alt", mod);
		sprintf(mod, "%s] is pressed", mod);
	}
	else
	{
		strcpy(mod, "");
	}
	printf("The %s key is pressed at (%d,%d)%s.\n", keystr, x, y, mod);
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
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
