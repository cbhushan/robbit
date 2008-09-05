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


//-----------------------------------------Includes--------------------------------------//
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<deque>
#include<math.h>
#include<time.h> 
#include<windows.h>

#include "Fl/Fl.H"
#include "Fl/Fl_Gl_Window.H"
#include "FL/gl.h"
#include "FL/glu.h"
#include "Fl/fl_draw.H"
#include <GL/glut.h>
#include <FL/fl_message.H>
#include <FL/Fl_File_Chooser.H>


void outputCharacter(float x, float y, float z, char *string);	// Draws the string at any point

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
const GLfloat cyl_shininess  = {1};				// shininess
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
const GLfloat disk1_specular[3][4] = {{0.0, 0.0, 0.0, 1.0},{0.8, 0.0, 0.0, 1.0},{0.0, 0.8, 0.0, 1.0}}; // specular

//material characteristics for Orientation Disk(disk2) of robot
const GLfloat disk2_shininess={1};
const GLfloat disk2_ambient[]  = {1.0, 0.0, 0.0, 1.0};		// ambience
const GLfloat disk2_diffuse[]  = {1.0, 0.0, 0.0, 1.0};		// diffuse
const GLfloat disk2_specular[] = {1.0, 1.0, 0.0, 1.0};		// specular

//material characteristics for centroid of robot
const GLfloat disk_center_shininess={1};
const GLfloat disk_center_ambient[] = {1.0, 0.0, 0.0, 1.0};	// ambience
const GLfloat disk_center_diffuse[] = {1.0, 0.0, 0.0, 1.0};	// diffuse
const GLfloat disk_center_specular[]= {0.0, 0.0, 0.0, 1.0};	// specular

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
const GLfloat plane_shininess  = {1};				// shininess
const GLfloat plane_specular[] = {0.3, 0.3, 0.9, 1.0};		// specular 

const GLfloat floor_shininess={1};
const GLfloat floor_specular[] = {0.8, 0.8, 0.8, 1.0};		// specular

//material characteristics for 2D Obstacle
const GLfloat disk_2D_obstacle_shininess={1};
const GLfloat disk_2D_obstacle_specular[] = {1.0, 0.0, 0.0, 1.0}; // specular

GLfloat light0_pos[4] ;// position 
GLfloat light1_pos[4] ;// position
GLfloat light2_pos[4] ;// position 
GLfloat light3_pos[4] ;// position 


//-----------------------------------constants--------------------------------------//


#define no_of_bots 6				// number of robots
#define radius_of_orient_disk 1.0	// radius of disk (orientation)
#define height_obstacle 10.0		// height of obstacle


#define PI 3.1415926535

const double radianFactor = 2 * PI / 360; // radian factor for calulations
void *font = GLUT_BITMAP_8_BY_13;	// font for writing in the animation

//-------------------------------------Variables------------------------------------//

// for size of the rectangular platform
float max_x=-20000;	// max value of x in datafile
float max_y=-20000;	// max value of y in datafile
float min_x=20000;	// min value of x in datafile
float min_y=20000;	// min value of y in datafile

//int iter_no;		// stores the iteration number of current iteration


int default_sleep_time = 1000;				// sleep time at render_speed = 1
// main animation parameters
static GLUquadric* quad;					// GLUquadric object used for creating cylinder and disk

int info_refresh_count = 100;				// counter for no. of frames( for displaying the message for only few frames)

int update_frame_mode=-1;					// mode for frame update
											// 0: use existing output_pos.log file
											// 1: generate frame at runtime
											// 2: generate new output_pos.log and then use for simulation
clock_t start_time;
