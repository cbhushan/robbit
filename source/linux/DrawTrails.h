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
*	DrawTrails.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws trails of robots and ball
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void draw_trails()
{
	int i,j;		// Simple counter for 'for' loops
	
	// save the current location in the history array for location
	// removes the oldest data and shifs the other data
	for(i=1; i<no_of_trail_data; i++)  
	{
		for(j=0; j<no_of_bots; j++)
		{
			bot_trail[i-1][j][0]=bot_trail[i][j][0];
			bot_trail[i-1][j][1]=bot_trail[i][j][1];
		}

		ball_trail[i-1][0]=ball_trail[i][0];
		ball_trail[i-1][1]=ball_trail[i][1];
	}

	for(j=0; j<no_of_bots; j++)
	{
		bot_trail[no_of_trail_data-1][j][0]=current.bot_x[j];
		bot_trail[no_of_trail_data-1][j][1]=current.bot_y[j];
	}

	ball_trail[no_of_trail_data-1][0]=current.ball_x;
	ball_trail[no_of_trail_data-1][1]=current.ball_y;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_center_specular);

	// Draws the line joining the all the points for robots
	for(j=0; j<no_of_bots; j++)
	{
		i=(iter_no<no_of_trail_data)?(no_of_trail_data-iter_no):0;
		glBegin(GL_LINE_STRIP);
		for(; i<no_of_trail_data; i++)
			glVertex3f(bot_trail[i][j][0],bot_trail[i][j][1],0.1);
		glEnd ();
	}

	// Draws the line joining the all the points for ball
	i=(iter_no<no_of_trail_data)?(no_of_trail_data-iter_no):0;
	glBegin(GL_LINE_STRIP);
		for(; i<no_of_trail_data; i++)
			glVertex3f(ball_trail[i][0],ball_trail[i][1],0.1);
	glEnd ();

	glFinish();
}
