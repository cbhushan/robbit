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
*	KeyEventHandler.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Monitors the keyboard input
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void key_event_handler(unsigned char key, int x, int y)
{
	info_refresh_count = 0;
	switch (key)
	{
	case ' ':					// Play/Pause Animation
		is_paused = !is_paused;
		sprintf(info_string, "Space Bar");
		break;

	case '0':					// Select or return to Isometric View
		camera_on_bot=-1;
		reshape(width, height);
		sprintf(info_string, "Isometric View");
		break;

	case 't':					// Top View
	case 'T':
		camera_on_bot=-1;
		is_topview*=-1;
		if(is_topview==1)
			sprintf(info_string, "Top View");
		else
			sprintf(info_string, "Isometric View");
		reshape(width, height);
		break;

	case 's':					// Screen Shot
	case 'S':
		sprintf(info_string, "Screen Shot Taken");
		WindowDump(0);
		break;

	case 'v':					// Video record
	case 'V':
		if(video_record_on)
		{
			video_dump(3);	
			sprintf(info_string, "End Video recording");
		}
		else 
		{
			video_dump(1);
			sprintf(info_string, "Start Video recording");
		}
		video_record_on = !video_record_on;
		break;

	case 27:					// Stop Animation on Esc
		sprintf(info_string, "Stop Animation");
		kill_animation();
		break;

	case '+':					// Zoom In 
		radius_camera_movement -= delta_zoom;
		sprintf(info_string, "Zoom In");
		reshape(width, height);
		break;

	case '-':					// Zoom Out
		radius_camera_movement += delta_zoom;
		sprintf(info_string, "Zoom Out");
		reshape(width, height);
		break;
	case 'n':					// Number Robots
	case 'N':
		number_bots=!number_bots;
		if(number_bots)
			sprintf(info_string, "Number bots = ON");
		else 
			sprintf(info_string, "Number bots = OFF");
		reshape(width, height);
		break;

	case 'r':					// Replay Animation
	case 'R':
		sprintf(info_string, "Replay Animation");
		input_data_file.clear();
		input_data_file.seekg(0);
		// get_data();get_data();
		current.update(1);current.update(1);
		glutIdleFunc(play_control);
		break;

	case 'i':					// show/hide info box 
    case 'I':
		if (info_box)
		{
			glutSetWindow (winIdSub);
			glutHideWindow ();
		}
		else
		{
			sprintf(info_string, "Press i to hide this INFO BOX");
			glutSetWindow (winIdSub);
			glutShowWindow ();
			glutPostRedisplay ();
		}
		info_box = !info_box;
		break;
	
	case 'o':					// show/hide Obstacles
    case 'O':
		show_obstacle=!show_obstacle;
		sprintf(info_string, "Show/Hide Obstacles");
		break;

	default:					// Selection of bot for onboard view
		if(((int)key-48)<=no_of_bots && ((int)key-48)>0)
		{
			camera_on_bot=((int)key-49);
			sprintf(info_string, "On board view of Bot %d",camera_on_bot+1);
			reshape(width, height);
		}
		else
		{
			sprintf(info_string, "Invalid key");
		}
	}

	if(is_paused)
	{
		glutSetWindow (winIdSub);
		glutPostRedisplay();
	}
	else 
		glutIdleFunc(play_control);
}
