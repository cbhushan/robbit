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
*	DetectObstacleCollision.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Detects the collision beteween any robot and any obstacle
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void DetectObstacleCollision(int bot_no)
{
	float bot_distance;
	int local_counter=0;
	float local_float;
	
	// detects the collision with 2D obstacle
	while(local_counter<obs_2D_counter)
	{
		bot_distance=pow((current.bot_x[bot_no]-obs_2D[local_counter][0]),2)+pow((current.bot_y[bot_no]-obs_2D[local_counter][1]),2);
		if(bot_distance <= pow((radius_of_robot),2))
		{
			current.bot_hit[bot_no][0]=3;		// sets to switch to blue colour(robot-obstacle collision)
			current.bot_hit[bot_no][1]=info_refresh_count=0;
			sprintf(info_string, "Bot %d hit by 2D Obstacle",bot_no+1);
			break;
		}
		local_counter++;
	}

	local_counter=0;
	// detects the collision with Cube Obstacle
	while(local_counter<CB_counter)
	{
		local_float=(obs_CB[local_counter][0]/2)+radius_of_robot;
		if( current.bot_x[bot_no]<=(obs_CB[local_counter][1]+local_float) &&
			current.bot_x[bot_no]>=(obs_CB[local_counter][1]-local_float) &&
			current.bot_y[bot_no]<=(obs_CB[local_counter][2]+local_float) &&
			current.bot_y[bot_no]>=(obs_CB[local_counter][2]-local_float) )
		{
			current.bot_hit[bot_no][0]=3;		// sets to switch to green colour(robot-obstacle collision)
			current.bot_hit[bot_no][1]=info_refresh_count=0;
			sprintf(info_string, "Bot %d hit by Cube Obstacle",bot_no+1);
			break;
		}
		local_counter++;
	}

	local_counter=0;
	// detects the collision with Sphere Obstacle
	while(local_counter<SP_counter)
	{
		bot_distance=pow((current.bot_x[bot_no]-obs_SP[local_counter][1]),2)+pow((current.bot_y[bot_no]-obs_SP[local_counter][2]),2);
		local_float=(float)sqrt((2*obs_SP[local_counter][0]-height_robot)*height_robot)+radius_of_robot;
		if(bot_distance <= pow(local_float,2))
		{
			current.bot_hit[bot_no][0]=3;		// sets to switch to green colour(robot-obstacle collision)
			current.bot_hit[bot_no][1]=info_refresh_count=0;
			sprintf(info_string, "Bot %d hit by Sphere Obstacle",bot_no+1);
			break;
		}
		local_counter++;
	}

	local_counter=0;
	// detects the collision with Wall Obstacle
	while(local_counter<WL_counter)
	{
		XY LineStart, LineEnd, Point;

		LineStart.X = obs_WL[local_counter][1]; LineStart.Y = obs_WL[local_counter][2];
		LineEnd.X = obs_WL[local_counter][3]; LineEnd.Y = obs_WL[local_counter][4];
		Point.X = current.bot_x[bot_no]; Point.Y = current.bot_y[bot_no];

		if(DistancePointLine( &Point, &LineStart, &LineEnd ))
		{
			current.bot_hit[bot_no][0]=3;		// sets to switch to green colour(robot-obstacle collision)
			current.bot_hit[bot_no][1]=info_refresh_count=0;
			sprintf(info_string, "Bot %d hit by Wall Obstacle",bot_no+1);
			return;
		}
		local_counter++;
	}
}
