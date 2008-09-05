// ------------------------------------------------------------------------------------//
//
//	This file is part of 3-D Simulator ' Robbit '
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

//! User defined function to generate next frame data
/*! A user may define his algorithm to generate the data in Frame_data here.
*/
Frame_Data GetNextFrame()
{
  Frame_Data next_frame;

  next_frame.bot_x.resize(no_of_bots);
  next_frame.bot_y.resize(no_of_bots);
  next_frame.bot_vx.resize(no_of_bots);
  next_frame.bot_vy.resize(no_of_bots);
  next_frame.bot_orient.resize(no_of_bots);
  next_frame.bot_vorient.resize(no_of_bots);
  next_frame.bot_hit[0].resize(no_of_bots);
  next_frame.bot_hit[1].resize(no_of_bots);

  int bot_count = 0;
  /*********************************************
   * algorithm for next frame data below here *
   *********************************************/


  /* for example - comment out example and substitute by user defined algorithm */
  //no_of_bots=4;					// enter number of robots
  next_frame.ball_x = 70.0;
  next_frame.ball_y = 70.0;
  next_frame.time = 100;
  next_frame.time_step = 0.08;
  for (bot_count = 0; bot_count < no_of_bots; ++bot_count)
    {
      next_frame.bot_x[bot_count] = 60.0 /*- 0.1*(current.time / 0.08)*/*(bot_count);
      next_frame.bot_y[bot_count] = 60.0 /*- 0.1*(current.time / 0.08)*/*(bot_count);
      next_frame.bot_orient[bot_count] = 60.0/*(current.time / 0.08)*/*(bot_count);
    }
	
  /* algorithm for next frame data ENDS here */

  return (next_frame);
}
