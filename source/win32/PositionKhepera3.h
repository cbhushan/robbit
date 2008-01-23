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
*	Robot_Class.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws the KheperaIII Robots with all the specifications
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void position_khepera3(float pos_x,float pos_y,double orient,int colour) 
{
	// setting properties of the material of cylinders
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k3_specular[colour]);
	
	// body cylinder 0
	glPushMatrix();
	glTranslatef(pos_x,pos_y,0);
	gluCylinder(quad,(radius_of_robot),(radius_of_robot),3.5,bot_slices,bot_stacks);
	glPopMatrix();
  
	// body cylinder 1
	glPushMatrix();
	glTranslatef(pos_x,pos_y,3.5);
	gluCylinder(quad,(radius_of_robot),(radius_of_robot-1),0.5,bot_slices,bot_stacks);
	glPopMatrix();
  
	// body cylinder 2
	const GLfloat cyl_spe[] = {0.0, 0.0, 0.0, 1.0};		// specular
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_spe);
	glPushMatrix();
	glTranslatef(pos_x,pos_y,4.0);
	gluCylinder(quad,(radius_of_robot-1),(radius_of_robot-1),1.0,bot_slices,bot_stacks);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k3_specular[colour]);

	// body cylinder 3
	glPushMatrix();
	glTranslatef(pos_x,pos_y,5.0);
	gluCylinder(quad,(radius_of_robot),(radius_of_robot),1.5,bot_slices,bot_stacks);
	glPopMatrix();

	// body cylinder 4
	glPushMatrix();
	glTranslatef(pos_x,pos_y,6.5);
	gluCylinder(quad,(radius_of_robot),(radius_of_robot-0.5),0.5,bot_slices,bot_stacks);
	glPopMatrix();

	// top disk
	glPushMatrix();
	glTranslatef(pos_x,pos_y,height_robot);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk1_specular[colour]);
	gluDisk(quad,0.0,(radius_of_robot-0.5),bot_slices,bot_stacks);
	glPopMatrix();

	// orientation disk - shows the orientation of the bot
	glPushMatrix();
	glTranslatef((pos_x+(radius_of_robot-radius_of_orient_disk-0.5)*cos(orient)),(pos_y+(radius_of_robot-radius_of_orient_disk-0.5)*sin(orient)),(height_robot+0.05));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk2_specular);
	gluDisk(quad,0.0,radius_of_orient_disk,bot_slices,bot_stacks);
	glPopMatrix();
}

