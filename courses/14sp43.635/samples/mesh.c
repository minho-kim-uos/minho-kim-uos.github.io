/*

	mesh

	keyboard control
	left/right: rotates around the y-axis of the cube
	up/down: rotates around the x-axis of the cube
	TAB: switches the mesh rendering method
	q/Q/ESC: quit

 */
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

// view frustum
struct
{
	GLfloat	left;
	GLfloat	right;
	GLfloat	bottom;
	GLfloat	top;
	GLfloat	near;
	GLfloat	far;
} frustum =
{
	-1,1,-1,1,1,5
};

GLfloat	rotx = 0;
GLfloat	roty = 0;

GLint	method = 0;

GLuint	vboid_v1;
GLuint	vboid_v2;
GLuint	vboid_i;

void textout(GLfloat x, GLfloat y, GLfloat z, const char* text)
{
	glColor3f(1,1,1);
	glRasterPos3f(x,y,z);
	for(int i=0 ; i<strlen(text) ; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void render_tet(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1,1,1);
	textout(1,-1,-1,"(1,-1,-1)");
	textout(-1,1,-1,"(-1,1,-1)");
	textout(-1,-1,1,"(-1,-1,1)");
	textout(1,1,1,"(1,1,1)");
	switch(method)
	{
		case 0:
		{	
			GLfloat	vertices[4][3][3] =
			{
				{
					{ 1,-1,-1},{-1, 1,-1},{ 1, 1, 1},
				},
				{
					{ 1,-1,-1},{-1,-1, 1},{-1, 1,-1},
				},
				{
					{ 1,-1,-1},{ 1, 1, 1},{-1,-1, 1},
				},
				{
					{ 1, 1, 1},{-1, 1,-1},{-1,-1, 1},
				},
			};
			glColor3f(0,1,1);
			glBegin(GL_TRIANGLES);
				for(int i=0 ; i<4 ; i++)
				{
					for(int j=0 ; j<3 ; j++)
					{
						glVertex3fv(vertices[i][j]);
					}
				}
			glEnd();
			break;
		}
		case 1:
		{
			GLfloat	vertices[4][3] =
			{
				{ 1, 1, 1},
				{ 1,-1,-1},
				{-1, 1,-1},
				{-1,-1, 1},
			};
			GLint	indices[4][4] =
			{
				{1,2,0},
				{1,3,2},
				{1,0,3},
				{0,2,3},
			};
			glColor3f(1,0,1);
			glBegin(GL_TRIANGLES);
				for(int i=0 ; i<4 ; i++)
				{
					for(int j=0 ; j<3 ; j++)
					{
						glVertex3fv(vertices[indices[i][j]]);
					}
				}
			glEnd();
			break;
		}
		case 2:
		{
			// vertices
			// For more details, see http://www.songho.ca/opengl/gl_vertexarray.html
			GLfloat	vertices[12][3] =
			{
				{ 1,-1,-1},{-1, 1,-1},{ 1, 1, 1},
				{ 1,-1,-1},{-1,-1, 1},{-1, 1,-1},
				{ 1,-1,-1},{ 1, 1, 1},{-1,-1, 1},
				{ 1, 1, 1},{-1, 1,-1},{-1,-1, 1},
			};
			glEnableClientState(GL_VERTEX_ARRAY);
			glColor3f(1,1,0);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawArrays(GL_TRIANGLES, 0, 12);
			glDisableClientState(GL_VERTEX_ARRAY);

			break;
		}
		case 3:
		{
			// vertices + indices
			// For more details, see http://www.songho.ca/opengl/gl_vertexarray.html
			GLfloat	vertices[4][3] =
			{
				{ 1, 1, 1},
				{ 1,-1,-1},
				{-1, 1,-1},
				{-1,-1, 1},
			};
			GLuint	indices[12] =
			{
				1,2,0,
				1,3,2,
				1,0,3,
				0,2,3,
			};
			glColor3f(.5,0,0);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, indices);
			glDisableClientState(GL_VERTEX_ARRAY);
			break;
		}
		case 4:
		{
			// VBO: vertices only
			// For more details, see http://www.songho.ca/opengl/gl_vbo.html
			glBindBuffer(GL_ARRAY_BUFFER, vboid_v1);
			glEnableClientState(GL_VERTEX_ARRAY);
			glColor3f(0,.5,0);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 12);
			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		}
		case 5:
		{
			// VBO: vertices + indices
			// For more details, see http://www.songho.ca/opengl/gl_vbo.html
			glBindBuffer(GL_ARRAY_BUFFER, vboid_v2);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboid_i);
			glEnableClientState(GL_VERTEX_ARRAY);
			glColor3f(0,0,.5);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			break;
		}
	}
}

// "display" callback function.
// This function is called whenever the window needs to be updated (redrawn).
void display(void)
{
	// Clears the "color buffer". See what happens if you 
	// comment out this call.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// translates objects such that they are inside of the frustum
	glTranslatef(0, 0, -(frustum.near + frustum.far)/2.0);
	glRotatef(roty, 0, 1, 0);
	glRotatef(rotx, 1, 0, 0);

	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(2,0,0);
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,2,0);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,2);
	glEnd();

	render_tet();
//	glColor3f(1,1,1);
//	glutWireCube(1);
//
//	glColor4f(.5,.5,.5,0.9);
//	glutSolidCube(1);

	glutSwapBuffers ();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '\t':
			method = (method+1)%6;
			break;
		case 'q':
		case 'Q':
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}

void rotate(GLfloat *angle, GLfloat theta)
{
	*angle += theta;
	if(theta > 0 && *angle > 360)	*angle -= 360;
	else if(*angle < 0)	*angle += 360;
}

#define	STEP	10
void special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			rotate(&roty, -STEP);
			break;
		case GLUT_KEY_RIGHT:
			rotate(&roty, STEP);
			break;
		case GLUT_KEY_UP:
			rotate(&rotx, -STEP);
			break;
		case GLUT_KEY_DOWN:
			rotate(&rotx, STEP);
			break;
	}
	glutPostRedisplay();
}

void init_vbo(void)
{
	{
		GLfloat	vertices[12][3] =
		{
			{ 1,-1,-1},{-1, 1,-1},{ 1, 1, 1},
			{ 1,-1,-1},{-1,-1, 1},{-1, 1,-1},
			{ 1,-1,-1},{ 1, 1, 1},{-1,-1, 1},
			{ 1, 1, 1},{-1, 1,-1},{-1,-1, 1},
		};
		glGenBuffers(1,&vboid_v1);
		glBindBuffer(GL_ARRAY_BUFFER, vboid_v1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	{
		GLfloat	vertices[4][3] =
		{
			{ 1, 1, 1},
			{ 1,-1,-1},
			{-1, 1,-1},
			{-1,-1, 1},
		};
		GLuint	indices[12] =
		{
			1,2,0,
			1,3,2,
			1,0,3,
			0,2,3,
		};
		glGenBuffers(1,&vboid_v2);
		glGenBuffers(1,&vboid_i);

		glBindBuffer(GL_ARRAY_BUFFER, vboid_v2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboid_i);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}


void cleanup(void)
{
	printf("Clearning up...\n");
	glDeleteBuffers(1, &vboid_v1);
	glDeleteBuffers(1, &vboid_v2);
	glDeleteBuffers(1, &vboid_i);
}

int main(int argc, char** argv)
{

	// Initializes GLUT library. Should be called at the beginning
	// before any GLUT function is called.
	glutInit(&argc, argv);	

	// Specifies the type of the color buffer. 
	// A single buffer with RGB type.
	// See the reference for more details.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Creates the window with given title bar text.
	glutCreateWindow("sample05: perspective projection");

	glewInit();

	// Registers the "display" callback function.
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glClearColor (0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	// for transparent color
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// to remove "stitching" artifacts
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(frustum.left,
				frustum.right,
				frustum.bottom,
				frustum.top,
				frustum.near,
				frustum.far);

	// Go into the infinite event loop.

	init_vbo();

	atexit(cleanup);

	glutMainLoop();


	return 0;
}



