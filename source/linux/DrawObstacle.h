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
*	DrawObstacle.h  v 3.0 , 2007-12-05, 11:17:00 IST
*
*	Renders the Obstacle given in the ASCII file after reading from the corresponding variable
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void DrawObstacle()
{
	int local_counter=0;		// local counter for this function

	// Renders 2D Obstacles
	while(local_counter < obs_2D_counter)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,disk_2D_obstacle_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
		glPushMatrix();
			glTranslatef(obs_2D[local_counter][0],obs_2D[local_counter][1],0.05);
			gluDisk(quad, 0.0, 1.0, small_disk_slices, small_disk_stacks);
		glPopMatrix();
		local_counter++;
	}

	// Renders Cube type Obstacles
	local_counter=0;
	while(local_counter < CB_counter)
	{
		glPushMatrix ();
			glTranslated (obs_CB[local_counter][1],obs_CB[local_counter][2],obs_CB[local_counter][0]/2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_2D_obstacle_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
			glutSolidCube (obs_CB[local_counter][0]);
		glPopMatrix();
		local_counter++;
	}

	// Renders wall type Obstacles
	local_counter=0;
	while(local_counter < WL_counter)
	{
		glBegin(GL_POLYGON);
			glVertex3f (obs_WL[local_counter][1], obs_WL[local_counter][2], 0.0);
			glVertex3f (obs_WL[local_counter][3], obs_WL[local_counter][4], 0.0);
			glVertex3f (obs_WL[local_counter][3], obs_WL[local_counter][4], obs_WL[local_counter][0]);
			glVertex3f (obs_WL[local_counter][1], obs_WL[local_counter][2], obs_WL[local_counter][0]);
		glEnd();
		glFlush ();
		local_counter++;
	}

	// Renders Sphere type Obstacles
	local_counter=0;
	while(local_counter < SP_counter)
	{
		glPushMatrix ();
			glTranslated (obs_SP[local_counter][1],obs_SP[local_counter][2],obs_SP[local_counter][0]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_2D_obstacle_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
			glutSolidSphere (obs_SP[local_counter][0],8,8);
		glPopMatrix();
		local_counter++;
	}

	glFinish();
}
