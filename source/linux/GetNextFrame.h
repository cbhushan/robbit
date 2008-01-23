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
*	GetNextFrame.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Creates the object for the next frame and returns the object
*	Contains the userdefined algorith for algo check 
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


frame get_next_frame()
{
	frame next = current;
	int bot_count = 0;

	/* algorithm for next frame data STARTS here */
	
	/* for example - comment out example and substitute by user defined algorithm */
	//no_of_bots=4;					// enter number of robots
	next.ball_x = 70.0;
	next.ball_y = 70.0;
	next.time = current.time + 0.08;
	next.time_step = 0.08;
	for (bot_count = 0; bot_count < no_of_bots; ++bot_count)
	{
		next.bot_x[bot_count] = 60.0 - 0.1*(current.time / 0.08)*(bot_count);
		next.bot_y[bot_count] = 60.0 - 0.1*(current.time / 0.08)*(bot_count);
		next.bot_orient[bot_count] =   60.0*(current.time / 0.08)*(bot_count);
	}
	
	/* algorithm for next frame data ENDS here */

	return (next);
}
