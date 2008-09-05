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

#include "Definitions.h"
#include "DistancePointLine.h"

#include "WritePNG.h"
#include "CaptureScreen.h"

#include "Frame_Data.h"

#include "File_Data.h"
#include "File_Data.c"

#include "Frame_Display.h"
#include "Frame_Display.c"

#include "robbitGUI.h"
#include "robbitGUI.cxx"

#include "GetNextFrame.h"
// #include "WriteInputFile.h"

RobbitUI robbit_gui;

void FileIdleProc(void *); // idle function when reading from file,
void FunctionIdleProc(void *); // idle function when displaying in real time
void WriteInputFile();

//! Main function 
/*! Displays splash screen, asks mode of operation (log file, custom algorithm, etc., starts simulation)

\param argc number of commandline arguments
\param argv array of commandline arguments
\return 0, except in case of error
*/
int main(int argc, char** argv) {
  glutInit(&argc,argv);

  start_time = clock();
  robbit_gui.SplashWindow->show();
  robbit_gui.htmlSplash->load("splash.html");

  // hide splash screen after 3 seconds
  while(robbit_gui.htmlSplash->visible() && (clock()-start_time)/CLOCKS_PER_SEC < 3.0)
    Fl::check();
  robbit_gui.SplashWindow->hide();

  update_frame_mode=fl_choice("Choose simulation  mode:\n1. Read from log file.\n2. Generate data at runtime.\n3. Generate log file then run simulation"," 1 ","2"," 3 ");

  if(update_frame_mode==0) {
    // read from log file
	  
    robbit_gui.display->mode(FL_DOUBLE|FL_RGB|FL_DEPTH|FL_ALPHA);
    robbit_gui.display->setDefaults(); 
    robbit_gui.show();
    
    Fl::add_idle(FileIdleProc);
    Fl::run();
  }
  else if(update_frame_mode == 1) {
    // get frame data from function
    
    robbit_gui.display->mode(FL_DOUBLE|FL_RGB|FL_DEPTH|FL_ALPHA);
    robbit_gui.display->setDefaults(); 
    robbit_gui.show();   

    Fl::add_idle(FunctionIdleProc);
    Fl::run(); 
  }
  else {
    // creat the log file then read from it
    WriteInputFile(/* args */);
    
    robbit_gui.display->mode(FL_DOUBLE|FL_RGB|FL_DEPTH|FL_ALPHA);
    robbit_gui.display->setDefaults(); 
    robbit_gui.show();
    
    Fl::add_idle(FileIdleProc);
    Fl::run();
  }

  return 0;
}

//! Idle function operating in log file mode
/*! When the simlation is run by reading data from pre-existing log file, this function handles the data handling and updating.
It also sets the positions of the various light sources, numbered 0 through 3.
It sets the floor size by reading through the data file once, and getting the maximum and minimum coordinates of the objects present in the arena.
Sets the initial look-at coordinate. Updates the sleep time between frame renders.
Also controls play/pause actions.
*/
void FileIdleProc(void *) {

  File_Data file_data;
  Frame_Data data;
  int scan_counter; // loop counters
  int sleep_for;
  char *file_name = fl_file_chooser("Choose Log File", "*.log", "");
  int num_records = file_data.SetFileInput(file_name);
  
  light0_pos[0] = max_x+60; light0_pos[1] =  min_y+(max_y-min_y)/2; // position 
  light1_pos[0] = min_x-60; light1_pos[1] = min_y+(max_y-min_y)/2;  // position
  light2_pos[0] = min_x+(max_x-min_x)/2; light2_pos[1] = max_y+60;  // position 
  light3_pos[0] = min_x+(max_x-min_x)/2; light3_pos[1] = min_y-60;  // position 
  light0_pos[2] = light2_pos[2] = light3_pos[2] = light1_pos[2] = 10;
  light0_pos[3] = light1_pos[3] = light2_pos[3] = light3_pos[3] = 1.0;

  robbit_gui.display->view_centerX=(max_x+min_x)/2; 
  robbit_gui.display->view_centerY=(max_y+min_y)/2; 
  robbit_gui.display->view_centerZ=0;

  robbit_gui.indexSlider->bounds(0,num_records-1);
  robbit_gui.indexSlider->step(1);
  robbit_gui.indexSlider->activate();
  robbit_gui.RenderSpeedMenu->activate();
  
  for(scan_counter=0; scan_counter<num_records; scan_counter++) {

    robbit_gui.indexSlider->value(scan_counter);    
    Fl::check(); // keeps GUI alive

    // delay between the frames according to animation speed
    if(robbit_gui.display->render_speed!=0.0) {
      sleep_for = (int)(data.time_step*default_sleep_time/robbit_gui.display->render_speed);
	  if(scan_counter==0 || sleep_for>300 || sleep_for <0) sleep_for=60;
      Sleep(sleep_for);
    }

    if(!robbit_gui.display->is_paused) {
      file_data.GetData(scan_counter, data);
      robbit_gui.display->UpdateFrame(data);
    }
    else {
      scan_counter--;
    }
    scan_counter=robbit_gui.display->current_index;
  }

  robbit_gui.display->setStop();
}

//! Idle function operating in custom algorithm mode
/*! When the simlation is run by creating coordinate data using a custom algorithm, this function is used.
Algorithm writers may use the above function, void FileIdleProc (void *) as reference while writing this function.
*/
void FunctionIdleProc(void *) {
  // sets the maximum limits when 2nd option is taken 
  max_x = +100.0;
  max_y = +100.0;
  min_x = -100.0;
  min_y = -100.0;

  Frame_Data data;
  
  light0_pos[0] = max_x+60; light0_pos[1] =  min_y+(max_y-min_y)/2; // position 
  light1_pos[0] = min_x-60; light1_pos[1] = min_y+(max_y-min_y)/2;  // position
  light2_pos[0] = min_x+(max_x-min_x)/2; light2_pos[1] = max_y+60;  // position 
  light3_pos[0] = min_x+(max_x-min_x)/2; light3_pos[1] = min_y-60;  // position 
  light0_pos[2] = light2_pos[2] = light3_pos[2] = light1_pos[2] = 10;
  light0_pos[3] = light1_pos[3] = light2_pos[3] = light3_pos[3] = 1.0;

  robbit_gui.display->view_centerX=(max_x+min_x)/2; 
  robbit_gui.display->view_centerY=(max_y+min_y)/2; 
  robbit_gui.display->view_centerZ=0;
  
  while(1) {
    Fl::check();

    Sleep(100);   
    
    if(!robbit_gui.display->is_paused) {
      data=GetNextFrame();
      robbit_gui.display->UpdateFrame(data);
    }
  }
}

//! Writes log file in specified format
/*! Writes frame data including x & y coordinates, x & y velocities, orientation (\f$\theta\f$),
 direction of velocity and other details for each object in the arena in a given format.

Any line starting with '%' is treated as comment and is skipped while reading the log.

Each line contains the data for all the robots at a particular time. Following pseduo code expains the format.
\code
fprintf(LogFile,"%4d %3.1f  ",iteration_number,tfly); // tfly: time between successive iterations
fprintf(LogFile,"%7.3f",current_time);

for i=0 to i<no_of_robots {
  fprintf(LogFile,"%7.2f %7.2f %6.3f %5.1f %5.1f ",x_pos_Robot[i],y_pos_Robot[i],orientation_Robot[i],Linear_Speed_Robot[i],Angular_velocity_Robots[i]);
}
	
fori=0 to i<NoofRobots { 
  fprintf(LogFile,"%5.1f %5.1f ",x_velocity_Robots[i],y_velocity_Robots[i]);
}
	
fprintf(LogFile,"%5.1f %5.1f ",x_pos_ball,y_pos_ball);
fprintf(LogFile,"\n"); // end of current line
\endcode
*/
void WriteInputFile() {


  // code goes here
  // note format of input file must be strictly as discussed
}

/** \mainpage Robbit
 
  \section Robbit What is Robbit ?
 
  Robbit is a open-source software which provide 3D simulation environment for multiple robot system. Current version of Robbit is 4.0.0 (for both windows and linux). At the moment, Robbit supports modules for mobile robots only. However, in the future the scope should expand and, of course, contributions are most welcome.

 Robbit has been developed thinking in researchers, students, roboticists and hobbyists who want to design, test and simulate mobile robots and research topics like autonomous navigation techniques, obstacle avoidance, artificial intelligence etc.

 Robbit is open source and is distributed under the GNU General Public License, published by the Free Software Foundation (version 3 of the License, or any later version).
 
 <hr size="1">
 
 \section c Contributors
 (alphabetical)

 <b>Antonelli Gianluca</b>,
 Dipartimento di Automazione, Elettromagnetismo,
 Ingegneria dell'Informazione e Matematica Industriale,
 Universita degli Studi di Cassino, Italy

 <b>Arrichiello Filippo</b>,
 Laboratory of Industrial Automation-Robotics Research group,
 Dipartimento di Automazione, Elettromagnetismo,
 Universita degli Studi di Cassino, Italy
   
 <b>Bhushan Chitresh</b>,
 Department of Electronics &amp; Electrical Communication Engineering
 Indian Institute of Technology Kharagpur, India

 <b>Prakash Chander</b>,
 Department of Computer Science Engineering
 Indian Institute of Technology Guwahati, India

 <b>Purkayasth Sayandeep</b>,
 Department of Electronics &amp; Electrical Communication Engineering
 Indian Institute of Technology Kharagpur, India
*/

/** \page Installation
\section Installation
All the dependencies must be fulfilled prior to installation. see \ref Dependencies in Related Pages.
\subsection Linux

All the structures and classes are available in .h files, and the methods/functions are available in .c files. To complie Robbit go to source directory and run: \code $> cmake .  \endcode then \code $> make \endcode To execute run: \code $> ./Robbit \endcode Note: Configuration settings can be modified in the file "CMakeLists.txt" before starting the installation.

\subsection win32 Windows 32-/64-Bit
 
Open Microsoft Visual Studio 2005 Solution robbit.sln, which can be found in vc2005 directory. Build the solution. <b>robbit.exe</b> will be created in the same directory.
<br><br>
The dependencies are included in the include/ folder which contain FLTK and PNG includes and libraries. These will be used directly by the build process. Make sure OpenGL libraries (static and dynamic) and include files are present your system.
<br>
The following libraries are to be used for linking. 
\code 
opengl32.lib wsock32.lib comctl32.lib glaux.lib glu32.lib fltk.lib fltkgl.lib libpng.lib
\endcode
While distributing, note that the project is built with FLTK and STL headers and libs, so only opengl32.dll will be required apart from the executable, and optional log-file and/or Obstacle files. 
\page Dependencies
\section Dependencies
    <ul>
    <li>C/C++ compiler: (<a href="http://msdn2.microsoft.com/hi-in/visualc/default.aspx">Windows</a>), (<a href="http://gcc.gnu.org/">Linux</a>)</li>
    <li>openGL v 3.7.6: (<a href="http://www.opengl.org/resources/libraries/glut/">Windows</a>), freeglut v 2.4.0 (<a href="http://freeglut.sourceforge.net/">Linux</a>)</li>
    <li>FLTK with FLUID v 1.1.9: (<a href="http://www.fltk.org/">Windows & Linux</a>)</li>
    <li>libpng v 1.2.31: (<a href="http://www.libpng.org/pub/png/libpng.html">Windows & Linux</a>)</li>
    <li>make v 3.81: (<a href="http://www.gnu.org/software/make/">Linux</a>)</li>
    <li>cmake v 2.6.1: (<a href="http://www.cmake.org/">Linux</a>)</li>
    <li>Standard Template Library (<a href="http://www.sgi.com/tech/stl/index.html">Windows & Linux</a>)</li>
    <li>openCV Library: (<a href="http://sourceforge.net/project/showfiles.php?group_id=22870">Windows & Linux</a>) [NOT required for Robbit 4.0.0]</li>
    <li>Doxygen: (<a href="http://www.stack.nl/~dimitri/doxygen/">Windows & Linux</a>) [For Documentation]</li>
    </ul>
 */
 
/** \page Usage
    \section KeyMap Keyboard mappings
<br><br>
<div align="center"><table>
<tr><td>t/T</td><td>Toggle Top View</td></tr>
<tr><td>l/L</td><td>Toggle Trails</td></tr>
<tr><td>a/A</td><td>About Window</td></tr>
<tr><td>d/D</td><td>Advanced Settings</td></tr>
<tr><td>s/S</td><td>Take Sreenshot</td></tr>
<tr><td>Escape</td><td>Quit simulator</td></tr>
<tr><td>n/N</td><td>Toggle Bot Numbering</td></tr>
<tr><td>o/O</td><td>Toggle Obstacles</td></tr>
<tr><td>u/U</td><td>Toggle Auto-rotating view</td></tr>
<tr><td>1,2,... 6</td><td>Onboard view of respective bot</td></tr>
<tr><td>+/-</td><td>Zoom in/out</td></tr>
</table></div>

	\section mouseMaps Mouse mappings
	Pan, zoom and rotate features have been mapped to mouse keys followed by drag, as follows.
		<br><br>
		<div align="center"><table>
		<tr><td>Left key press and drag</td><td>Panaromic rotate</td></tr>
		<tr><td>Right key press and drag</td><td>Pan</td></tr>
		<tr><td>Mouse scroll</td><td>Zoom in/out</td></tr>
		</table></div>

    \section advSettings Advanced settings
	Options have been provided to modify the arena's dimension, number of trail points, radius of ball, number of frames till which a collision is marked colored after the collision has actually ended,
	and render quality.

	\subsection obstacles Obstacles
	The position of obstacles, size and dimensions are to be placed in the Obstacles.txt. The format to be followed for the different types of simplistic obstacles are given within the same.
	As a sample an example of each is also provided. Another file following the same format may be used instead of this file (at runtime, an option for file selection is provided).

	\section customAlgo Custom algorithms
	One may write his own algorithm to generate coordinates of the objects, and other details. This must be written within the user function
	GetNextFrame.h. 
 */

/** \page Features
Comprehensive feature list:
<ul> <li>3D panaromic view through mouse control
</li><li>Lighting control - upto four lights
</li><li>Chessboard floor
</li><li>Numbering the robots
</li><li>Onboard View of robots
</li><li>Saving snapshots
</li><li>Animation speed control
</li><li>Centroid of the robots
</li><li>Motion trails
</li><li>Show/Hide trails
</li><li>Placing obstacle (by reading from ASCII file)
</li><li>Show/Hide obstacle
</li><li>Collision detection by changing colour
</li><li>Media Player style play/pause/stop/seek of animation
</li><li>3D view of robots of different types including two built-in KheperaII and KheperaIII, and support for custom robot (limited).
</li><li>Customizable Robots
</li><li>Customizable Arena
</li><li>Pan view
</li><li>Auto-rotating view
</li><li>Simulating from the given motion algorithm (in form of code)
</li></ul>
<br><br>
External Libraries used:
<ul> <li>GUI using FLTK
</li><li>libPNG for screenshots (earlier use of OpenCV has been discontinued)
</li><li>Standard Template Library for dynamic implementation
</li></ul>
*/
