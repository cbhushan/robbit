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
*	MenuSelect.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Monitors the right click menu Select
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void menuSelect(int value)
{
	info_refresh_count = 0;
	switch (value) 
	{
	case 1:						// Animation speed : Real Time
		sprintf(info_string, "1X animation speed");
		render_speed=1;
		break;
	case 2:						// Animation speed : 2X
		sprintf(info_string, "2X animation speed");
		render_speed=2;
		break;
	case 4:						// Animation speed : 4X
		sprintf(info_string, "4X animation speed");
		render_speed=4;
		break;
	case 6:						// Animation speed : 6X
		sprintf(info_string, "6X animation speed");
		render_speed=6;
		break;
	case 10:					// Animation speed : 10X
		sprintf(info_string, "10X animation speed");
		render_speed=10;
		break;
	case 15:					// Animation speed : 15X
		sprintf(info_string, "15X animation speed");
		render_speed=15;
		break;
	case 25:					// Animation speed : 25X
		sprintf(info_string, "25X animation speed");
		render_speed=25;
		break;

	case 100:					// Lighting : switch OFF
		sprintf(info_string, "Lighs Switched OFF");
		glDisable(GL_LIGHTING);
		break;
	case 101:					// Lighting : 1 Light
		sprintf(info_string, "No of light: 1");
		no_of_lights=1;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		break;
	case 102:					// Lighting : 2 Light
		sprintf(info_string, "No of lights: 2");
		no_of_lights=2;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		break;
	case 103:					// Lighting : 3 Light
		sprintf(info_string, "No of lights: 3");
		no_of_lights=3;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		break;
	case 104:					// Lighting : 4 Light
		sprintf(info_string, "No of lights: 4");
		no_of_lights=4;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		break;

	case 200:					// Selecting Khepara II
		sprintf(info_string, "Khepara II selected");
		height_robot=5;
		radius_of_robot=3.5;
		bot_selected=1;
		bot_slices=10;
		break;
	case 201:					// Selecting Khepara III
		sprintf(info_string, "Khepara III selected");
		height_robot=7;
		radius_of_robot=6.5;
		bot_selected=2;
		bot_slices=15;
		break;

	case 1001:					// Play / Pause Animation
		is_paused = !is_paused;
		sprintf(info_string, "Paused");
		if(is_paused)
		{
			glutSetWindow (winIdSub);
			glutPostRedisplay();
			//glutIdleFunc(NULL);
		}
		else 
			sprintf(info_string, "Play");
		//	glutIdleFunc(play_control);
		break;

	case 1002:					// Number Robots
		number_bots=!number_bots;
		if(number_bots) 
			sprintf(info_string, "Number bots = ON");
		else 
			sprintf(info_string, "Number bots = OFF");
		reshape(width, height);
		break;

	case 1003:					// Stop Animation
		sprintf(info_string, "Animation Stopped");
		kill_animation();
		break;

	case 1004:					// Top View of Animation
		camera_on_bot=-1;
		is_topview*=-1;
			if(is_topview==1)
			sprintf(info_string, "Top View");
		else
			sprintf(info_string, "Isometric View");
		reshape(width, height);
		break;

	case 1005:					// Screenshot of Animation
		sprintf(info_string, "Screenshot Taken");
		WindowDump(0);
		break;

	case 1006:					// video recording od Animation
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

	case 1007:					// Zoom In 
		sprintf(info_string, "Zoom In");
		radius_camera_movement -= delta_zoom;
		reshape(width, height);
		break;

	case 1008:					// Zoom Out
		sprintf(info_string, "Zoom Out");
		radius_camera_movement += delta_zoom;
		reshape(width, height);
		break;

	case 1009:					// Replay Animation
		sprintf(info_string, "Replay Animation");
		input_data_file.clear();
		input_data_file.seekg(0);
		//get_data();get_data();
		current.update(1);current.update(1);
		glutIdleFunc(play_control);
		break;

	case 1010:					// info box 
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
		}
		info_box = !info_box;
		break;
	case 1011:					// Show/Hide Trails
		show_trails=!show_trails;
		break;
	case 1012:					// Show/Hide Obstacles
		show_obstacle=!show_obstacle;
		break;
  }
	glutIdleFunc(play_control);
}
