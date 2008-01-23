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
*	Definitions.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Animation parameter definitions & includes
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */




//-----------------------------------------Includes--------------------------------------//
#include<fstream.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<GL/glaux.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "cv.h"
#include "highgui.h"



//-------------------------------------Function declaration-------------------------------//

//Functions of Robot_Class.h
void display_data();						// displays the data
//void get_data();							// read the data from input 
float next_no(char *string, int &st_pos);	// finds the next number, reading from the 
											// string and updates the string pointer position


//Functions of Robot_Animation.h
void position_khepera2(float pos_x,float pos_y,double orient,int colour);
												// Displays the robot(Khepara II) at their positions
void position_khepera3(float pos_x,float pos_y,double orient,int colour);
												// Displays the robot(Khepara III) at their positions
void init(void);								// Initializes GL-display
void display(void);								// Displays the environment and calls 
												// position_khepera2() or position_khepera3()
void play_control(void);						// controls the animation(speed, end, begining)
void mouse(int button,int state,int x,int y);	// Mouse event Handler
void reshape(int w, int h);						// Handler for window resize
void key_event_handler(unsigned char key, int x, int y);// Handler for keyboard events
void menuSelect(int value);						// Menu Funtions
void motion(int x, int y);						// Handles the Motion of mouse
void outputCharacter(float x, float y, float z, char *string);	// Draws the string at any point
void reshape(int w, int h);						// Determines the Eye location
int  kill_animation(void);						// Stops the animation
void WindowDump(int dump_mode);					// Takes the screenshot
void video_dump(int);							// Records a video
void drawString (char *s);						// Draws the string in sub-window (2D text)
void subReshape (int w, int h);					// reshape for sub-window(info-box)
void draw_floor();								// Draws the floor on which robots are moving
void draw_right_click_menu();					// Draws the right-click menu on the main window
void ReadObstacle();							// Reads the obstacle ASCII file
void DrawObstacle();							// Draws the Obstacle
void draw_trails();								// Draws the trails of robots
void DetectObstacleCollision(int bot_no);			// Detects the collision with the given obstacles (if any)

//--------------------------------------Parameter definitions--------------------------------//


//light 0 parameters
const GLfloat light0_ambient[]  = {0.7, 0.8, 0.7, 1.0};		// ambience
const GLfloat light0_diffuse[]  = {1.0, 1.0, 1.0, 1.0};		// diffuse
const GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};		// specular	

//light 1 parameters
const GLfloat light1_ambient[]  = {0.7, 0.8, 0.7, 1.0};		// ambience
const GLfloat light1_diffuse[]  = {1.0, 1.0, 1.0, 1.0};		// diffuse
const GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0};		// specular

//light 2 parameters
const GLfloat light2_ambient[]  = {0.7, 0.8, 0.7, 1.0};		// ambience
const GLfloat light2_diffuse[]  = {1.0, 1.0, 1.0, 1.0};		// diffuse
const GLfloat light2_specular[] = {1.0, 1.0, 1.0, 1.0};		// specular	

//light 3 parameters
const GLfloat light3_ambient[]  = {0.7, 0.8, 0.7, 1.0};		// ambience
const GLfloat light3_diffuse[]  = {1.0, 1.0, 1.0, 1.0};		// diffuse
const GLfloat light3_specular[] = {1.0, 1.0, 1.0, 1.0};		// specular	

//material characteristics for cylindrical part of robot
const GLfloat cyl_shininess  = {1};							// shininess
const GLfloat cyl_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat cyl_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat cyl_k2_specular[4][4] = {{0.5, 0.5, 0.5, 1.0},{1.0, 0.0, 0.0, 1.0},{0.0, 1.0, 0.0, 1.0},{0.0, 1.0, 0.0, 1.0}};// specular for Khepara II
const GLfloat cyl_k3_specular[4][4] = {{0.9, 0.9, 0.9, 1.0},{1.0, 0.0, 0.0, 1.0},{0.0, 1.0, 0.0, 1.0},{0.0, 1.0, 0.0, 1.0}};// specular for Khepara III	

//material characteristics for Middle Disk(disk0) of robot
const GLfloat disk0_shininess={1};
const GLfloat disk0_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat disk0_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat disk0_specular[] = {0.18, 0.41, 0.18, 1.0};	// specular

//material characteristics for Top Disk(disk1) of robot
const GLfloat disk1_shininess={50};
const GLfloat disk1_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat disk1_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat disk1_specular[3][4] = {{0.0, 0.0, 0.0, 1.0},{0.8, 0.0, 0.0, 1.0},{0.0, 0.8, 0.0, 1.0}};		// specular

//material characteristics for Orientation Disk(disk2) of robot
const GLfloat disk2_shininess={1};
const GLfloat disk2_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat disk2_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat disk2_specular[] = {1.0, 1.0, 0.0, 1.0};		// specular

//material characteristics for centroid of robot
const GLfloat disk_center_shininess={1};
const GLfloat disk_center_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat disk_center_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat disk_center_specular[] = {0.0, 0.0, 0.0, 1.0};		// specular

//material characteristics for text (for numbering of bots)
const GLfloat text_shininess={1};
const GLfloat text_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat text_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat text_specular[] = {1.0, 0.0, 0.0, 1.0};		// specular


//material characteristics for ball
const GLfloat ball_shininess={1};
const GLfloat ball_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat ball_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat ball_specular[] = {1.0, 1.0, 0.0, 1.0};		// specular

//material characteristics for plane of motion
const GLfloat plane_shininess  = {1};						// shininess
const GLfloat plane_specular[] = {0.3, 0.3, 0.9, 1.0};		// specular 

const GLfloat floor_shininess={1};
const GLfloat floor_specular[] = {0.8, 0.8, 0.8, 1.0};		// specular


//material characteristics for 2D Obstacle
const GLfloat disk_2D_obstacle_shininess={1};
const GLfloat disk_2D_obstacle_specular[] = {1.0, 0.0, 0.0, 1.0};		// specular






//-----------------------------------constants--------------------------------------//


#define no_of_bots 6						// number of robots
#define radius_of_orient_disk 1.0			// radius of disk (orientation)
#define height_obstacle 10.0				// height of obstacle
#define radius_ball 3.5						// radius of ball (spherical)
#define no_of_trail_data 40					// number of steps for which position is stored
											// to draw the trail of ball and bots
#define coloured_steps 35					// No of steps in which the bot is coloured
#define PI 3.1415926535

const double radianFactor = 2 * PI / 360; // radian factor for calulations
void *font = GLUT_BITMAP_8_BY_13;			// font for writing in the animation

ifstream input_data_file;	// file pointer to the input data-file
ifstream obstacle_data_file;


//-------------------------------------Variables------------------------------------//

// for size of the rectangular platform
float max_x=-20000;				// max value of x in datafile
float max_y=-20000;				// max value of y in datafile
float min_x=20000;				// min value of x in datafile
float min_y=20000;				// min value of y in datafile

int iter_no;					// stores the iteration number of current iteration
float radius_of_robot;			// radius of the robot(cylindrical)
float height_robot;				// height of the robot(cylindrical)
int bot_slices; 				// number of slices for Cylinder & Disk	
int bot_stacks=4;				// number of stacks for Cylinder & Disk
int bot_selected;				// identifies the type of robot selected, 1 for KheparaII, 2 for KeparaIII
int small_disk_slices=6;		// nukber of slices for centriod and 2D obstacle
int small_disk_stacks=1;		// nukber of stacks for centriod and 2D obstacle

// instantaneous data of robots, balls
float ball_pos_x;				// current x-coordinate of ball
float ball_pos_y;				// current y-coordinate of ball
float bot_pos_x[no_of_bots];	// current x-coordinate of i'th robot
float bot_pos_y[no_of_bots];	// current y-coordinate of i'th robot
float bot_vel_x[no_of_bots];	// current x-velocity of i'th robot
float bot_vel_y[no_of_bots];	// current y-velocity of i'th robot
float bot_orient[no_of_bots];	// current orientation  of i'th robot
float bot_vel_orient[no_of_bots];
float bot_center_x;				// current x-coordinate of centroid of the robots
float bot_center_y;				// current y-coordinate of centroid of the robots
int is_bot_hit[no_of_bots][2];	// stores non-zero in 1st column if the robot has been hit,
								//                  1 : hit by another robot
								//                  2 : hit by ball
								//                  3 : hit by obstacle
								// stores value in seconds in 2nd column (used to colour robot for limited time)

// arrays to store the data to produce the trail for robots and ball
float bot_trail[no_of_trail_data][no_of_bots][2];
float ball_trail[no_of_trail_data][2];

// speed control
float render_speed	= 1.0;		// speed of rendering graphics in linear scale;
								// 1 = normal; 2 = double speed, etc.
float current_time	= 0.0;		// current animation time
float time_step		= 0.0;		// time between cuurent time and previous iteration time
int sleep_for		= 0;		// time to sleep (in milliseconds) before going to next iteration
int default_sleep_time = 1000;	// sleep time at render_speed = 1


// main animation parameters
static GLUquadric* quad;		// GLUquadric object used for creating cylinder and disk
int width=800, height = 600;	// width and height of the animation window
int sub_height = 60;			// height of sub-window(info-box)
int winIdSub,winIdMain;			// defining the main and sub-window(info-b0x)

// animation event handler states
bool is_paused = true;			// tag to identify if paused or not
bool end_animation = false;		// tag to identify end of animation
bool end_of_input_file = false;	// tag to identify end of input file
bool read_file_mode = true;		// tag to identify read mode of file
bool number_bots = false;		// tag to identify if bots are to be numbered or not
bool info_box = true;			// tag to identify if info box is ON or OFF


// mouse handler 
int	ani_speed_menu;				// takes input for animation speed menu
int light_menu;					// takes input for no of light menu
int robot_menu;					// takes input for robot to be selected
int moving = 0;					// identifies if mouse is moving or not, 0:not moving, 1:moving
int startx, starty;				// stores starting points of a mouse drag (with left click)

// eye/camera position parameters
float radius_camera_movement = 300.0;	// distance of viewing eye from the bots
float theta =45;				// stores theta value of camera position (polar parameters)
float phi = 45;					// stores phi value of camera position (polar parameters)
float eyeX,eyeY,eyeZ;			// stores the current position of camera in cartesian coordinate 
								//   system, derived from theta, phi
float centerX=0,centerY=0,centerZ=0;	//stores the position to which the camera is directed
float upX=0, upY=0, upZ=1.0f;	// stores the normal vector parameters of camera
float ratio;
int camera_on_bot = -1;			// identifies if camera is mounted on any robot, 1: mounted, -1:not mounted
int is_topview = -1;				// identifies if top view is selected or not, 1:selected, 0 not selected
int delta_zoom = 5;				// the amount by which 'radius_camera_movement' changes on zoom in/out
int no_of_lights = 2;			// number of lights currently

// Picture parameters (snapshot)
IplImage *capture=0, *img=0;	// Image pointers for saving the snapshot
int capture_height, capture_width;	// Stores the height, Width of the saved picture
int capture_step, capture_channels;	// stores the openCV step & channel of saved picture
uchar* capture_data;			// openCV data pointer of the capured image
int saved_true;					// tag to identify if picture or video is saved, 1:saved, 0:notsaved
	

// video 
bool video_record_on = false;
int total_frames_video = 0;
int fps     = 25;				// or 30
int frameW  = 800;				//  = width; 	// 744 for firewire cameras
int frameH	= 600;				//  = height;	// 480 for firewire cameras
int isColor = 1;	
char img_save_name[] = "capture.png";
char video_save_name[] = "capture.avi";
CvVideoWriter *writer;//cvCreateVideoWriter(video_save_name,CV_FOURCC('M','J','P','G'),fps,cvSize(frameW,frameH),isColor);;

// string variables 
char s[100];					// General string 
char string[1000];				// Large string
char info_string[1000];			// Large string for display in info box
int info_refresh_count = 100; 	// counter for no. of frames( for displaying the message for only few frames)
float size_square=20;			// half the size of the squares on the board

// obstacle related variables
//int place_obstacle = 1;	// shows/hides obstacle, 0 - hide, 1 - show
float obs_2D[20][2];			// saves 2D obstacle location, [x][y] 
float obs_WL[20][5];			// saves wall type Obstacle location [height][x1][y1][x2][y2]
float obs_CB[20][3];			// saves cube type Obstacle location [side length][x][y]
float obs_SP[20][3];			// saves sphere type Obstacle location [side length][x][y]

int obs_2D_counter=0;			// saves no. of 2D obstacle
int WL_counter=0;				// saves no. of wall type obstacle
int CB_counter=0;				// saves no. of cube type obstacle
int SP_counter=0;				// saves no. of sphere type obstacle

bool show_obstacle=true;
bool show_trails=true;

int update_frame_mode=-1;		// mode for frame update
							// 0: use existing output_pos.log file
							// 1: generate frame at runtime
							// 2: generate new output_pos.log and then use for simulation