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
*	DrawFloor.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws the floor on which robots are moving
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void draw_floor()
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular);

	for(int i=min_x-30; i<max_x+50; i+=80)
		for(int j=min_y-30; j<max_y+50; j+=80)
			glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

	for(i=min_x+11; i<max_x+50; i+=80)
		for(int j=min_y+10; j<max_y+50; j+=80)
			glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);
	
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, plane_specular);

	for(i=min_x-30; i<max_x+50; i+=80)
		for(int j=min_y+10; j<max_y+50; j+=80)
			glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

	for(i=min_x+11; i<max_x+50; i+=80)
		for(int j=min_y-30; j<max_y+50; j+=80)
			glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

	glFinish();
}