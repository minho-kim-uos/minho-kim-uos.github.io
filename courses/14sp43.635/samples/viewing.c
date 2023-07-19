/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#include <GL/glut.h>
#include <stdlib.h>

void render_cube(void)
{
	// x axis
	glColor3f(.5,0,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(2,0,0);
	glEnd();
	// y axis
	glColor3f(0,.5,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,2,0);
	glEnd();
	// z axis
	glColor3f(0,0,.5);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,2);
	glEnd();

	glColor3f(1,0,0);	//(+x) red
	glBegin(GL_QUADS);
		glVertex3f(1,-1,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,1,1);
		glVertex3f(1,-1,1);
	glEnd();
			
	glColor3f(0,1,1);	//(-x) cyan
	glBegin(GL_QUADS);
		glVertex3f(-1,-1,-1);
		glVertex3f(-1,-1,1);
		glVertex3f(-1,1,1);
		glVertex3f(-1,1,-1);
	glEnd();

	glColor3f(0,1,0);	//(+y) green
	glBegin(GL_QUADS);
		glVertex3f(-1,1,-1);
		glVertex3f(-1,1,1);
		glVertex3f(1,1,1);
		glVertex3f(1,1,-1);
	glEnd();

	glColor3f(1,0,1);	//(-y) violet
	glBegin(GL_QUADS);
		glVertex3f(-1,-1,-1);
		glVertex3f(1,-1,-1);
		glVertex3f(1,-1,1);
		glVertex3f(-1,-1,1);
	glEnd();

	glColor3f(0,0,1);	//(+z) blue
	glBegin(GL_QUADS);
		glVertex3f(-1,-1,1);
		glVertex3f(1,-1,1);
		glVertex3f(1,1,1);
		glVertex3f(-1,1,1);
	glEnd();

	glColor3f(1,1,0);	//(-z) yellow
	glBegin(GL_QUADS);
		glVertex3f(-1,-1,-1);
		glVertex3f(-1,1,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,-1,-1);
	glEnd();
}

void display(void)
{
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glRotatef(90, 1, 0, 0);
	gluLookAt(1,1,1,0,0,0,0,1,0);

	render_cube();

	glutSwapBuffers ();
}

void init (void) 
{
/* select clearing color 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-3.0, 3.0, -2.0, 2.0, 1.0, 10.0);

//      glColor3f (1.0, 1.0, 0.0);

	glEnable(GL_DEPTH);
	glEnable(GL_CULL_FACE);

}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
	case 'q':
	case 'Q':
		exit(0);
		break;
	}
}

/* 
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
