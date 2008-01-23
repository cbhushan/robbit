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
*	DrawRightClickMenu.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Draws the right click menu 
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void draw_right_click_menu()
{
	// creat sub-menu for animation speed
	ani_speed_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Real Time",1);
	glutAddMenuEntry("2X",2);
	glutAddMenuEntry("4X",4);
	glutAddMenuEntry("6X",6);
	glutAddMenuEntry("10X",10);
	glutAddMenuEntry("15X",15);
	glutAddMenuEntry("25X",25);

	// create sub-menu for no. of lights
	light_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Switch off Light",100);
	glutAddMenuEntry("1 Light",101);
	glutAddMenuEntry("2 Light",102);
	glutAddMenuEntry("3 Light",103);
	glutAddMenuEntry("4 Light",104);

	// create sub-menu to select the robot
	robot_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Khepara II",200);
	glutAddMenuEntry("Khepara III",201);

	// create a pop-up menu on right click
	glutCreateMenu(menuSelect);
	glutAddMenuEntry("Show/Hide Info Box",1010);
	glutAddMenuEntry("Show/Hide Trails",1011);
	glutAddMenuEntry("Show/Hide Obstacle",1012);
	glutAddMenuEntry("Zoom In",1007);
	glutAddMenuEntry("Zoom Out",1008);
	glutAddMenuEntry("Pause/Play",1001);
	glutAddMenuEntry("Stop Animation",1003);
	glutAddMenuEntry("Replay Animation",1009);
	glutAddMenuEntry("Top View",1004);
	glutAddMenuEntry("Screen Shot",1005);
	glutAddMenuEntry("Record Video",1006);
	glutAddMenuEntry("Number Robots",1002);
	glutAddSubMenu("Select Robot", robot_menu);
	glutAddSubMenu("Animation Speed", ani_speed_menu);
	glutAddSubMenu("No. of Light", light_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// intializes the sub window
	winIdSub = glutCreateSubWindow (winIdMain, 5, 5, width-10, sub_height);
	glutDisplayFunc (subDisplay);
	glutReshapeFunc (subReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key_event_handler);

	// creat sub-menu for animation speed
	ani_speed_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Real Time",1);
	glutAddMenuEntry("2X",2);
	glutAddMenuEntry("4X",4);
	glutAddMenuEntry("6X",6);
	glutAddMenuEntry("10X",10);
	glutAddMenuEntry("15X",15);
	glutAddMenuEntry("25X",25);

	// create sub-menu for no. of lights
	light_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Switch off Light",100);
	glutAddMenuEntry("1 Light",101);
	glutAddMenuEntry("2 Light",102);
	glutAddMenuEntry("3 Light",103);
	glutAddMenuEntry("4 Light",104);

	// create sub-menu to select the robot
	robot_menu = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Khepara II",200);
	glutAddMenuEntry("Khepara III",201);

	// create a pop-up menu on right click
	glutCreateMenu(menuSelect);
	glutAddMenuEntry("Show/Hide Info Box",1010);
	glutAddMenuEntry("Show/Hide Trails",1011);
	glutAddMenuEntry("Show/Hide Obstacle",1012);
	glutAddMenuEntry("Zoom In",1007);
	glutAddMenuEntry("Zoom Out",1008);
	glutAddMenuEntry("Pause/Play",1001);
	glutAddMenuEntry("Stop Animation",1003);
	glutAddMenuEntry("Replay Animation",1009);
	glutAddMenuEntry("Top View",1004);
	glutAddMenuEntry("Screen Shot",1005);
	glutAddMenuEntry("Record Video",1006);
	glutAddMenuEntry("Number Robots",1002);
	glutAddSubMenu("Select Robot", robot_menu);
	glutAddSubMenu("Animation Speed", ani_speed_menu);
	glutAddSubMenu("No. of Light", light_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
