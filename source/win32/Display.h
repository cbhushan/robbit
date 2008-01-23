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
*	Display.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Main function which draws all the things in main window
*	by calling different functions
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void display()
{
	glutSetWindow (winIdMain);
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();					// no transformations
	glPushMatrix();

	// Calls function to find if it has hit any thing or not
	bot_hit();
	
	// Renders the current frame
	current.render_frame();
	
	// Video recording
	if(video_record_on)
	{
		video_dump(2);
	}
}
