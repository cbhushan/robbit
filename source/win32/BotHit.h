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
*	BotHit.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Function to determine which robot has been hit and mark it
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void bot_hit()
{
	int i,j;					// simple counter
	double bot_distance;		// stores the instantaneous distance of a robots 
								// from ball, obstacle or another robot

	for(i=0; i<no_of_bots; i++)
	{
		if(current.bot_hit[i][1]>coloured_steps)
		{
			current.bot_hit[i][0]=0;		// sets to switch badk to normal color
		}
		else
		{
			current.bot_hit[i][1]++;
		}
			// detects the collision with other robots
			for(j=i+1; j<no_of_bots; j++)
			{
				bot_distance=pow((current.bot_x[i]-current.bot_x[j]),2)+pow((current.bot_y[i]-current.bot_y[j]),2);
				if(bot_distance <= pow((2*radius_of_robot),2))
				{
					current.bot_hit[i][0]=current.bot_hit[j][0]=1;	// sets to switch to red colour(robot-robot collision
					current.bot_hit[i][1]=current.bot_hit[j][1]=info_refresh_count=0;
					sprintf(info_string, "Bot %d hit by Bot %d",i+1,j+1);
				}
			}
		
			// detects the collision with the ball
			bot_distance=pow((current.bot_x[i]-current.ball_x),2)+pow((current.bot_y[i]-current.ball_y),2);
			if(bot_distance <= pow((radius_of_robot+radius_ball),2))
			{
				current.bot_hit[i][0]=2;		// sets to switch to green colour(robot-ball collision
				current.bot_hit[i][1]=info_refresh_count=0;
				sprintf(info_string, "Bot %d hit by Ball",i+1);
			}

			//  detects collision with obstacles
			if(show_obstacle)
			DetectObstacleCollision(i);
	}
}


