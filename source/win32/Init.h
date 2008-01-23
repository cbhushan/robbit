// ------------------------------------------------------------------------------------//
//
//	This program is part of 3-D Simulator ' Robbit '
//	visit:   http://webuser.unicas.it/robbit/  for details
//	
//	This program is free software published  under the terms of 
//	the GNU General Public License, Free Software Foundation, Inc.
//	visit:  http://www.gnu.org/licenses/gpl.html for details
//
//	Developers(alphabetical list) : 
//	* Antonelli Gianluca
//	* Arrichiello Filippo
//	* Bhushan Chitresh
//	* Prakash Chander
//	* Purkayasth Sayandeep
//	
//	 Groups(alphbetical) :
//	* KRAIG, Indian Institute of Technology, Kharagpur, India
//	* LAI, Università degli Studi di Cassino, Italy
//	
// ------------------------------------------------------------------------------------//

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	
*	init.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Initilization of the main window
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void init(void) 
{
	glClearColor (0.5, 0.5, 0.5, 0.0);
	glEnable(GL_LIGHTING); 

	glutSetWindowTitle("Robot Simulator");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	const GLfloat light0_pos[]		= {max_x+60, min_y+(max_y-min_y)/2, 10, 1.0};			// position 
	const GLfloat light1_pos[]		= {min_x-60, min_y+(max_y-min_y)/2, 10, 1.0};			// position
	const GLfloat light2_pos[]		= {min_x+(max_x-min_x)/2, max_y+60, 10, 1.0};			// position 
	const GLfloat light3_pos[]		= {min_x+(max_x-min_x)/2, min_y-60, 10, 1.0};			// position 

	// Light source 0
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);				// set  specular light 
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);					// set infinite light source 
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glEnable(GL_LIGHT0);   
	
	// Light source 1
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);				// set  specular light 
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);					// set infinite light source 
	glEnable(GL_LIGHT1); 

	// Light source 2
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);				// set  specular light 
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);					// set infinite light source 

	// Light source 3
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);				// set  specular light 
	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);					// set infinite light source 

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cyl_shininess);	// material property for shineness
	glEnable(GL_DEPTH_TEST);

	quad = gluNewQuadric();
}
