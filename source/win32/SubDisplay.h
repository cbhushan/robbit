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
*	SubDisplay.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws the sub-window(info-bar)
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void subDisplay()
{
	// Clear subwindow
	glutSetWindow (winIdSub);
	glClearColor (0.3, 0.3, 0.3, 0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw border
	glColor3f (0.4F, 0.4F, 0.4F);
	glBegin (GL_LINE_LOOP);
	glVertex2f (0.0F, 0.0F);
	glVertex2f (0.0F, 0.99F);
	glVertex2f (0.999F, 0.99F);
	glVertex2f (0.999F, 0.0F);
	glEnd ();

	// Leftmost part of sub-window
	glColor3f (1.0F, 1.0F, 1.0F);			// sets color to white 

	// displayes the time
	sprintf (s, "time");
	glRasterPos2f (0.03F, 0.7F);
	drawString (s);
	sprintf (s, "= %6.2f sec", current.time);
	glRasterPos2f (0.08F, 0.7F);
	drawString (s);

	// displayes the theta
	sprintf (s, "theta");
	glRasterPos2f (0.03F, 0.45F);
	drawString (s);
	sprintf (s, "= %6.2f deg", theta);
	glRasterPos2f (0.08F, 0.45F);
	drawString (s);

	// displayes the phi
	sprintf (s, "phi");
	glRasterPos2f (0.03F, 0.2F);
	drawString (s);
	sprintf (s, "= %6.2f deg", phi);
	glRasterPos2f (0.08F, 0.2F);
	drawString (s);

	
	// Middle part of sub-table
	glColor3f (0.0F, 1.0F, 0.2F);
	glRasterPos2f (0.47F, 0.70F);
	drawString ("INFO BOX");

	// states play/pause status
	if(is_paused)
	{
		sprintf (s, " Paused");
		glRasterPos2f (0.48F, 0.35F);
		drawString (s);
	}


	// Rightmost part of the sub-window,  prints the keypress
	if(info_string != "" && info_refresh_count < 15)
	{
		glColor3f (1.0F, 0.5F, 0.5F);
		glRasterPos2f (0.77F, 0.55F);
		drawString (info_string);
		if(camera_on_bot == -1 && is_topview !=1)
		{
			if(info_refresh_count == 14)
				info_refresh_count = 100;
			else 
				info_refresh_count ++;
		}
		else
		{
			glRasterPos2f (0.75F, 0.27F);
			if(is_topview==1)
				drawString ("Press t to return to Isometric view");
			else
				drawString ("Press 0 to return to Isometric view");
		}
	}
	glutSwapBuffers ();
}

