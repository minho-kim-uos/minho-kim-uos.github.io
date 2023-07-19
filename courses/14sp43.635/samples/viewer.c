#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <GL/glut.h>

#define	MIN(x,y)	((x)<(y)?(x):(y))
#define	MAX(x,y)	((x)>(y)?(x):(y))
#define	SET_VEC3(v,x,y,z)	(v[0]=x,v[1]=y,v[2]=z);
#define	SET_VEC4(v,x,y,z,w)	(v[0]=x,v[1]=y,v[2]=z,v[3]=w);
#define	INC_VEC3(x,y)		(x[0]+=y[0],x[1]+=y[1],x[2]+=y[2]);
#define	SET_IDENTITY4(m)		\
{								\
	SET_VEC4(m[0], 1, 0, 0, 0);	\
	SET_VEC4(m[1], 0, 1, 0, 0);	\
	SET_VEC4(m[2], 0, 0, 1, 0);	\
	SET_VEC4(m[3], 0, 0, 0, 1);	\
}
#define	LEN2(x)			sqrt(x[0]*x[0]+x[1]*x[1])

#define	MODE_NONE			0
#define	MODE_ROTATE			1
#define	MODE_TRANSLATE		2
#define	MODE_ZOOM			3
#define	MODE_ROTATE_OBJ		4
#define	MODE_TRANSLATE_OBJ	5

struct
{
	GLint	width, height;		// current window size
	GLint	x, y;				// latest mouse position (in window coords)
	GLint	mode;				// current interaction mode
	GLint	id_sel;				// currently selected object id (0 if nothing selected)
	GLdouble	position[3];	// current translation
	GLdouble	mat_rot[4][4];	// current rotation
} GUI;

typedef struct
{
	GLint		id;								// object id (used for picking)
	GLdouble	position[3];					// current position
	GLdouble	mat_rot[4][4];					// current rotation
	void		(*proc_render)(GLint, void*);	// rendering procedure
} TObject;

struct
{
	GLfloat	fovy;
	GLfloat	near, far;
} camera;

TObject	objects[3];
int		num_obj = 3;

void render_axes(void)
{
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
}

void proc_render_sphere(GLint mode, void *pobj)
{
	if(mode == GL_RENDER)
	{
		render_axes();
		glColor3f(1,1,1);
		glutWireSphere(1,32,32);
		glColor3f(0,.5,.5);
	}
	glutSolidSphere(1,32,32);
}

void proc_render_cube(GLint mode, void* pobj)
{
	if(mode == GL_RENDER)
	{
		render_axes();
		glColor3f(1,1,1);
		glutWireCube(1);
		glColor3f(.5,.5,0);
	}
	glutSolidCube(1);
}

void proc_render_teapot(GLint mode, void* pobj)
{
	if(mode == GL_RENDER)
	{
		render_axes();
		glColor3f(1,1,1);
		glutWireTeapot(1);
		glColor3f(.5,0,.5);
	}
	glutSolidTeapot(1);
}


void render_scene(GLint mode)
{
	int	i;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(GUI.position[0], GUI.position[1], GUI.position[2]);
	glMultMatrixd((GLdouble*)GUI.mat_rot);

	if(mode == GL_RENDER)	render_axes();

	for(i = 0 ; i < num_obj ; i++)	// render each object in the list
	{
		glPushMatrix();
			glTranslated(objects[i].position[0],
						objects[i].position[1],
						objects[i].position[2]);
			glMultMatrixd((GLdouble*)objects[i].mat_rot);
			if(mode == GL_SELECT)	glPushName(objects[i].id);
			objects[i].proc_render(mode, &objects[i]);
			if(mode == GL_SELECT)	glPopName();
		glPopMatrix();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_scene(GL_RENDER);
	glutSwapBuffers();
}
GLint process_hits(GLint hits, GLuint buffer[])
{
	GLuint	names;
	GLuint	i, j;
	GLuint	*ptr;
	GLint	nearest = -1;
	GLfloat	z_min;
	GLfloat	min_depth = FLT_MAX;

//	printf("-------------------------\n");
//	printf("# of hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	for(i = 0 ; i < hits ; i++)
	{
		names = *ptr;
//		printf("# of names for this hit = %d\n", names);
		ptr++;
//		printf("min depth=%g\n", (float)*ptr/0x7fffffff);
		z_min = *ptr;	// minimum depth of the current hit
		ptr++;
//		printf("max depth=%g\n", (float)*ptr/0x7fffffff);
		ptr++;
//		printf("names are...");
		for (j = 0; j < names; j++)
		{ 
			if(z_min < min_depth)
			{
				min_depth = z_min;
				nearest = *ptr;
			}
//			printf(":%d:", *ptr);
			ptr++;
		}
//		printf("\n");
	}
//	printf("%d selected\n", nearest);
	return nearest;
}


#define	BUFSIZE	512
GLuint check_pick(int x, int y)
{
	GLuint	selectBuf[BUFSIZE];
	GLint	hits;
	GLint	viewport[4];
	GLuint	nearest = -1;
	
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	glSelectBuffer(BUFSIZE, selectBuf);
	(void) glRenderMode(GL_SELECT);
	
	glInitNames();
//	glLoadName(0);
//	glPushName(0);
	
	glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			// Re-defines the projection matrix for picking
			gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 
					1.0, 1.0, viewport);
			gluPerspective(camera.fovy, (GLfloat)GUI.width/(GLfloat)GUI.height,
					camera.near, camera.far);
			render_scene(GL_SELECT);	
			// At this point, the matrix mode might have changed to 
			// GL_MODELVIEW, therefore we need to change it again.
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	glPopAttrib();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if(hits > 0)	nearest = process_hits(hits, selectBuf);
	return nearest;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		switch(state)
		{
			case GLUT_DOWN:
				GUI.id_sel = check_pick(x,y);
				if(GUI.id_sel >= 0)
					GUI.mode = MODE_ROTATE_OBJ;
				else
					GUI.mode = MODE_ROTATE;
				GUI.x = x;
				GUI.y = y;
				break;
			case GLUT_UP:
				GUI.mode = MODE_NONE;
				break;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		switch(state)
		{
			case GLUT_DOWN:
				GUI.id_sel = check_pick(x, y);
				if(GUI.id_sel >= 0)
					GUI.mode = MODE_TRANSLATE_OBJ;
				else
					GUI.mode = MODE_TRANSLATE;
				GUI.x = x;
				GUI.y = y;
				break;
			case GLUT_UP:
				GUI.mode = MODE_NONE;
				break;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		switch(state)
		{
			case GLUT_DOWN:
				GUI.mode = MODE_ZOOM;
				GUI.x = x;
				GUI.y = y;
				break;
			case GLUT_UP:
				GUI.mode = MODE_NONE;
				break;
		}
	}
}

void reshape(int w, int h)
{
	GUI.width = w;
	GUI.height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera.fovy, (GLfloat)w/(GLfloat)h,
			camera.near, camera.far);
}

void unproject_vector(GLdouble vec_win[2], GLdouble vec[3], GLdouble mat_mv[4][4])
{
	GLdouble	org_win[3];
	GLdouble	mat_proj[4*4];
	GLint		viewport[4];

	glGetDoublev(GL_PROJECTION_MATRIX, mat_proj);
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Projects the origin (0,0,0) to get its window coords.
	gluProject(0, 0, 0,
			(GLdouble*)mat_mv, 
			mat_proj, viewport,
			&org_win[0], &org_win[1], &org_win[2]);

	// Unprojects the vector onto the world coords.
	gluUnProject(vec_win[0]+org_win[0], vec_win[1]+org_win[1], org_win[2],
			(GLdouble*)mat_mv, 
			mat_proj, viewport,
			&vec[0], &vec[1], &vec[2]);
}

void motion(int x, int y)
{
	GLdouble	offset[2];
	offset[0] = x - GUI.x;
	offset[1] = y - GUI.y;
	GUI.x = x;
	GUI.y = y;
	switch(GUI.mode)
	{
		case MODE_ROTATE:
		{
			glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
					glRotated(LEN2(offset), offset[1], offset[0], 0);
					glMultMatrixd((GLdouble*)GUI.mat_rot);
					glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*)GUI.mat_rot);
				glPopMatrix();
			glPopAttrib();
			break;
		}
		case MODE_ROTATE_OBJ:
		{
			GLdouble	axis[3];
			GLdouble	axis_win[2] = {offset[1], offset[0]};
			GLdouble	mat_mv[4][4];
			TObject		*pobj = &objects[GUI.id_sel];
			glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
					glTranslated(GUI.position[0], GUI.position[1], GUI.position[2]);
					glMultMatrixd((GLdouble*)GUI.mat_rot);
					glTranslated(pobj->position[0], pobj->position[1], pobj->position[2]);
					glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*)mat_mv);
				glPopMatrix();
			glPopAttrib();
			unproject_vector(axis_win, axis, mat_mv);
			glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
					glRotated(LEN2(axis_win), axis[0], axis[1], axis[2]);
					glMultMatrixd((GLdouble*)pobj->mat_rot);
					glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*)pobj->mat_rot);
				glPopMatrix();
			glPopAttrib();
			break;
		}
		case MODE_ZOOM:
		{
			camera.fovy = MIN(90, MAX(0, camera.fovy+offset[1]));
			reshape(GUI.width, GUI.height);
			break;
		}
		case MODE_TRANSLATE:
		{
			GLdouble	offset_world[3];
			GLdouble	mat_mv[4][4];
			glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
					glTranslated(GUI.position[0], GUI.position[1], GUI.position[2]);
					glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*)mat_mv);
				glPopMatrix();
			glPopAttrib();
			offset[1] *= -1.0;
			unproject_vector(offset, offset_world, mat_mv);
			INC_VEC3(GUI.position, offset_world);
			break;
		}
		case MODE_TRANSLATE_OBJ:
		{
			GLdouble	offset_world[3];
			GLdouble	mat_mv[4][4];
			TObject		*pobj = &objects[GUI.id_sel];
			offset[1] *= -1.0;

			glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
					glTranslated(GUI.position[0], GUI.position[1], GUI.position[2]);
					glMultMatrixd((GLdouble*)GUI.mat_rot);
					glTranslated(pobj->position[0], pobj->position[1], pobj->position[2]);
					glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*)mat_mv);
				glPopMatrix();
			glPopAttrib();

			unproject_vector(offset, offset_world, mat_mv);

			INC_VEC3(pobj->position, offset_world);
			break;
		}
	}
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q':
		case 'Q':
		case 27:
			exit(0);
	}
}
void init(void)
{
	camera.fovy = 45;
	camera.near = 1;
	camera.far = 20;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1,1);

	GUI.id_sel = -1;
	GUI.mode = MODE_ROTATE;

	SET_IDENTITY4(GUI.mat_rot);
	SET_VEC3(GUI.position, 0, 0, -10);

	{
		int	i;
		for(i = 0 ; i < num_obj ; i++)
		{
			objects[i].id = i;
			SET_IDENTITY4(objects[i].mat_rot);
		}
		SET_VEC3(objects[0].position, 1, 1, 1);
		objects[0].proc_render = proc_render_sphere;

		SET_VEC3(objects[1].position, -1, -1, -1);
		objects[1].proc_render = proc_render_cube;

		SET_VEC3(objects[2].position, 1, -1, -1);
		objects[2].proc_render = proc_render_teapot;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("viewer");
	glClearColor(0.0, 0.0, 0.0, 0.0);

	init();

	glutDisplayFunc(display); 
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}
