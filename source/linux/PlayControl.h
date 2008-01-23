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
*	PlayControl.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	controls the animation (speed, begin & end)
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void play_control(void)
{
	// defines hold time between the frames depending on the animation speed
	sleep_for = (int)(current.time_step * default_sleep_time / render_speed);
	SleepMilli(sleep_for);
	
	// determines the start & end of animation
	if( end_animation || end_of_input_file )
	{
		kill_animation();
	}
	else // Running animation
	{
		if(!is_paused)
		{
			if(update_frame_mode != 1)
				{
					current.update();
				}
				else
				{
					current = get_next_frame();
				}
		}
	}
	
	// updates position for on board view in each frame
	if(camera_on_bot!=-1)
	{
		reshape(width, height);
	}
	
	glutSetWindow (winIdMain);	// Sets the main window
	glutPostRedisplay ();
	glutSetWindow (winIdSub);	// Sets the sub-window
	glutPostRedisplay ();
}
