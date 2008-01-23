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
*	DrawString.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws 2D-text in the window
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



void  drawString (char *s)
{
	unsigned int i;
	for (i = 0; i < (int)strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, s[i]);
}
