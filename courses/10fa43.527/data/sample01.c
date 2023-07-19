#include <GL/glut.h>

// "display" callback function.
// This function is called whenever the window needs to be updated (redrawn).
void display(void)
{
	// Clears the "color buffer". See what happens if you 
	// comment out this call.
	glClear(GL_COLOR_BUFFER_BIT);	

	// Specifies the "current color" status.
	// All the primitives will be colored in this color from not on.
	// Try other colors yourself.
	glColor3f(1.0, 0.0, 0.0);

	// Draws a quad (quadrilateral) by specifying
	// the potisions of four corner vertices.
	glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f( 0.5, -0.5);
		glVertex2f( 0.5,  0.5);
		glVertex2f(-0.5,  0.5);
	glEnd();

	// Forces all the previous OpenGL commands actually "executed" immediately.
	// See what happens if you comment out this call.
	glFlush ();
}

int main(int argc, char** argv)
{
	// Initializes GLUT library. Should be called at the beginning
	// before any GLUT function is called.
	glutInit(&argc, argv);	

	// Specifies the type of the color buffer. 
	// A single buffer with RGB type.
	// See the reference for more details.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

//glutInitWindowSize (250, 250); 
//   glutInitWindowPosition (100, 100);

	// Creates the window with given title bar text.
	glutCreateWindow("sample01: red square");

   glClearColor (0.0, 0.0, 0.0, 0.0);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	// Registers the "display" callback function.
	glutDisplayFunc(display); 

	// Go into the infinite event loop.
	glutMainLoop();

	return 0;
}
/*
	Try yourself:
 
	- How can you change the default window size?
	- How can you change the initial position of the window?
	- How can you change the color used to clear the buffer?
 */



