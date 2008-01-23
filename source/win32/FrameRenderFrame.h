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
*	FrameRenderFrame.h  v 3.0 , 2007-12-05, 10:56:00 IST
*
*	Function of the Class 'frame'
*	 Intializes the main simulation window & its parameters
*	Read the Input & Obstacle ASCII files 
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


frame::render_frame()
{
	int i;		// Local counter

	// Initializes the center of the robots to be zero
	this->bot_center_x=this->bot_center_y=0;
	
	// Render robots according to selected robots
	for(i=0;i<no_of_bots; ++i)
	{
		if(bot_selected==1)
			position_khepera2(this->bot_x[i],this->bot_y[i],(double)(this->bot_orient[i]),this->bot_hit[i][0]);
		else if(bot_selected==2)
			position_khepera3(this->bot_x[i],this->bot_y[i],(double)(this->bot_orient[i]),this->bot_hit[i][0]);
			
		this->bot_center_x+=this->bot_x[i];			// compute sum of x-cor position of all the bots
		this->bot_center_y+=this->bot_y[i];			// compute sum of y-cor position of all the bots
		
		// Numbers the robots dependin on the mode
		if(number_bots)
		{
			sprintf(s,"%d", i+1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, text_specular);
			outputCharacter(this->bot_x[i],this->bot_y[i]+7, (height_robot+0.5), s);
		}
	}
	
	// Calculates the centoid of the Robots
	this->bot_center_x/=no_of_bots;
	this->bot_center_y/=no_of_bots;

	// Render robot centeriod
	glPushMatrix();
	glTranslatef(bot_center_x,bot_center_y,0.05);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_center_specular);
	gluDisk(quad, 0.0, 1.0, bot_slices, bot_stacks);
	glPopMatrix();
	
	// Renders the floor of the animation
	draw_floor();
		
	// Render the robot trails and ball trails is show_trails is true
	if(show_trails)
		draw_trails();
	
	// Renders the ball
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ball_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ball_shininess);
	glTranslatef(this->ball_x,this->ball_y,4);
	glutSolidSphere(radius_ball,8,8);
	glPopMatrix();

	// Renders the obstacle depending on the mode if show_obstacle is true
	if(show_obstacle)
		DrawObstacle();

	glutSwapBuffers();
}
