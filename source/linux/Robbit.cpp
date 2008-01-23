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
*	Robot_Animation.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Starts the main - code
*	 Intializes the main simulation window & its parameters
*	Read the Input & Obstacle ASCII files 
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Robot_Class.h"
#include "FrameUpdate.h"
#include "FrameRenderFrame.h"

frame current;			// object of the class frame

#include "SleepMilli.h"
#include "WriteInputFile.h"
#include "GetNextFrame.h"
#include "NextNo.h"
#include "ReadObstacle.h"
#include "DrawObstacle.h"
#include "OutputCharacter.h"
#include "DrawString.h"
#include "KillAnimation.h"
#include "DrawFloor.h"
#include "DrawTrails.h"
#include "SubDisplay.h"
#include "DistancePointLine.h"
#include "DetectObstacleCollision.h"
#include "BotHit.h"
#include "PositionKhepera3.h"
#include "PositionKhepera2.h"
#include "Display.h"
#include "WindowDump.h"
#include "VideoDump.h"
#include "PlayControl.h"
#include "Mouse.h"
#include "Motion.h"
#include "Reshape.h"
#include "KeyEventHandler.h"
#include "MenuSelect.h"
#include "DrawRightClickMenu.h"
#include "SubReshape.h"
#include "Init.h"


int main(int argc, char** argv)
{
	// Initializes the simulation window
	glutInit(&argc, argv);
	glClearColor (0.1, 0.1, 0.1, 0.0);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   	glutInitWindowSize (width,height);
	glutInitWindowPosition (10, 10);
	winIdMain=glutCreateWindow (argv[0]);
	
	// file pointer to the input data-file
	input_data_file.open("output_pos2.log");	
	
	// File pointer to Obstacle file
	obstacle_data_file.open("Obstacle.txt");

	// Select frame data input mode update_frame_mode
	do
	{
		cout<<"\nWhich of the following do you want to do\n";
		cout<<"\t1\tuse existing output_pos.log file\n";
		cout<<"\t2\tgenerate frame at runtime\n";
		cout<<"\t3\tgenerate new output_pos.log and then use for simulation\n";
		cout<<"\n\nEnter your choice : ";
		cin>>update_frame_mode;
		if(update_frame_mode>3 || update_frame_mode<1)
		{
			cout<<"Invalid choice, Press any key to enter your choice again...\n";
			getchar();
		}
	}while(update_frame_mode>4 || update_frame_mode<1); 
	
	update_frame_mode--;

	// sets the maximum limits when 2nd option is taken 
	if(update_frame_mode == 1)
	{
		current = get_next_frame();
		max_x = +100.0;
		max_y = +100.0;
		min_x = -100.0;
		min_y = -100.0;
	}
	else
	{
		if(update_frame_mode == 2)
		{
			write_input_file(/* args */);
			end_of_input_file	= false;
			end_animation		= false;
			read_file_mode		= false;
			input_data_file.clear();
			input_data_file.seekg(0);
		}

		// Read whole data file for max & min value of X & Y
		cout<<"\n\nReading Input File..............."<<endl;

		while(!input_data_file.eof() || !end_of_input_file)
			current.update(1);
		
		cout<<"Done"<<endl;
	}

	// Read obstacle data file for obstacle
	cout<<"\n\nReading Obstacle Data File..............."<<endl;
	ReadObstacle();
		
	// Initializes the simulation window parameters
	init();
		
	// Takes input to select the robot
	do
	{
		cout<<"\nWhich Robot do you want for animation ?\n(you can also change the robots during animation)\n\n1. Khepara II\n2. Khepara III";
		cout<<"\n\nEnter your choice : ";
		cin>>bot_selected;
		if(bot_selected>2 || bot_selected<1)
		{
			cout<<"Wrong choice, Press any key to enter your choice again.\n"<<endl;
			getchar();
		}
	}while(bot_selected>2 || bot_selected<1);

	current.bot_design = bot_selected;
		
	// Sets the radius, height and slics of the Robots according to the type of robot selected
	if(bot_selected==1)
	{
		height_robot=5;
		radius_of_robot=3.5;
		bot_slices=10;
	}
	else if(bot_selected==2)
	{
		height_robot=7;
		radius_of_robot=6.5;
		bot_slices=15;
	}

	cout<<"\n\n\tPlease refer the manual for detailed list of shortcuts.\n\n\tRight click in animation window for MENU.\n\tLeft-click & drag to change the viewing position.\n\n\tPress any Key to Start Animation."<<endl;
	getchar();

	if(update_frame_mode != 1)
	{
		// sets the tags for normal reading & locates the file pointer to begining 
		end_of_input_file	= false;
		end_animation		= false;
		read_file_mode		= false;
		input_data_file.clear();
		input_data_file.seekg(0);
			
		// Reads the 1st set of positions for the simulation
		current.update();
		current.update();
	}
	
	// intializes the main window with standard basic function
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key_event_handler);
	
	// Draws the right click menu
	draw_right_click_menu();

	glutMainLoop();
	return 0;
}
