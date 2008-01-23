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
*	Motion.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Rotate the scene in 3D with the left mouse button
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void motion(int x, int y)
{
	if (moving) 
	{
		theta = theta + ((y - starty)/2);
		if(theta > 360) 
			theta = 1;
		if(theta < 0) 
			theta = 359;
		
		phi = phi + ((x - startx)/2);
		if(phi > 360) 
			phi = 1;
		if(phi < 0)
			phi = 359;
		
		startx = x;
		starty = y;
		reshape(width, height);
	}
}