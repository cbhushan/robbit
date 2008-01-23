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
*	Contains the definitions of class ' frame '
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Definitions.h"

class frame
{
public:
	frame();
	update(int mode, ifstream fp);		// Updates the current positions for each frame
	render_frame();						// Renders the current frame

	float bot_x			[no_of_bots];	// x-coordinate of the robots' position [cm]
	float bot_y			[no_of_bots];	// y-coordinate of the robots' position [cm]
	float bot_vx		[no_of_bots];	// x-component of the robots' velocity [cm/sec]
	float bot_vy		[no_of_bots];	// y-component of the robots' velocity [cm/sec]
	float bot_orient	[no_of_bots];	// orientation of the robots [rad]
	float bot_vorient	[no_of_bots];	// angular velocity [rad/sec]
	int   bot_hit		[no_of_bots][2];	// [ bot number ] [	1: hit (1)/not hit (0);
											// 2: time of hit ]
	int bot_design;			//	1: Khepera II; 2: Khepera III
	float time;				//	current time of the frame
	
	float ball_x;			// x-coordinate of the balls' position [cm]
	float ball_y;			// y-coordinate of the balls' position [cm]
	float ball_vx;			// x-component of the balls' velocity [cm/sec]
	float ball_vy;			// y-component of the balls' velocity [cm/sec]
	float bot_center_x;		// x-coordinate of current cetroid of the robots
	float bot_center_y;		// y-coordinate of current cetroid of the robots
	float time_step;		// current delay time (for sleep functions)
};

frame::frame() {}
