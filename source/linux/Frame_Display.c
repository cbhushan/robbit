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

#include "robbitGUI.h"
extern RobbitUI robbit_gui;

//! Changes view angle during autoview
/*! Decrements the angle made by the line connecting the camera location
and the look-at position, with the X axis, projected on the floor.
*/
void Frame_Display::AutoUpdateEye() {

  float dx;
  if(render_speed==0) {
    dx=0.075;
  }
  else {
    dx=1/render_speed;
  }

  phi = phi - dx;
  if(phi > 360) 
    phi = 0.1;
  if(phi < 0)
    phi = 359.9;
}

//! Clears trail data
/*! If show_trails is set, it clears the trail data.
\param val value of the Show trails option (GUI)
*/
void Frame_Display::setTrails(bool val) {
  show_trails=val;
  if(!show_trails) {
    for(int j=0; j<no_of_bots; j++) {
      bot_trail[j][0].clear();
      bot_trail[j][1].clear();
    }
    ball_trail[0].clear();
    ball_trail[1].clear();
  }
  redraw();
}


//! Stops simulation
/*! Clears file record index, repositions slider to 0, pauses the animation.
*/
void Frame_Display::setStop() { 
  current_index=-1;
  robbit_gui.indexSlider->value(0);
  is_paused = true;
  robbit_gui.ButtonPlayPause->label("@>");
  redraw();
}

//! Swaps Play and Pause symbols in GUI Play/Pause button, on click
void Frame_Display::setPlayPause() {
  is_paused=!is_paused;
  if(is_paused) { robbit_gui.ButtonPlayPause->label("@>"); }
  else { robbit_gui.ButtonPlayPause->label("@||"); }
}


//! Creates GL rendering widget in main window
/*! 
\param x x coordinate of top-left pixel of widget
\param y y coordinate of top-left pixel of widget
\param w width of widget
\param h height of widget
*/
Frame_Display::Frame_Display(int x, int y, int w, int h)
: Fl_Gl_Window(x,y,w,h)
{
  end();
  mode(FL_RGB | FL_DOUBLE | FL_ALPHA | FL_DEPTH);
}


//! Sets bot structure variables
/*! 
\param val type of bot: 1 = KheperaII; 2 = KheperaIII; 3 = Custom Robot
*/
void Frame_Display:: selectBot(int val) { 
  bot_selected=val;

  if(bot_selected==1) {
    height_robot=5;
    radius_of_robot=3.5;
    bot_slices=10;
  }
  else if(bot_selected==2) {
    height_robot=7;
    radius_of_robot=6.5;
    bot_slices=15;
  }
  redraw();
}

//! Sets default values of variables
/*! Developers may change them to their requirements.
*/
void Frame_Display::setDefaults() {

  data.bot_x.resize(no_of_bots);
  data.bot_y.resize(no_of_bots);
  data.bot_vx.resize(no_of_bots);
  data.bot_vy.resize(no_of_bots);
  data.bot_orient.resize(no_of_bots);
  data.bot_vorient.resize(no_of_bots);
  data.bot_hit[0].resize(no_of_bots);
  data.bot_hit[1].resize(no_of_bots);

  this->number_bots=false;
  this->show_obstacle=false;
  this->show_trails=false;
  this->topview = false;
  this->autoview = false;
  this->camera_on_bot=0;
  this->is_paused=false;

  this->view_centerX=(max_x+min_x)/2; 
  this->view_centerY=(max_y+min_y)/2; 
  this->view_centerZ=0;

  this->upX=0;
  this->upY=0;
  this->upZ=1.0f;

  this->radius_camera_movement = 300.0;
  this->theta = 45;
  this->phi = 45;

  this->radius_ball = 3.5;
  this->no_of_trail_data = 40;
  this->coloured_steps = 35;

  this->Near=1;
  this->Far=1000;

  this->delta_zoom = 5;
  this->no_of_lights = 1;

  this->bot_selected=1;
  this->height_robot=5;
  this->radius_of_robot=3.5;
  this->bot_slices=20;
  this->bot_stacks=6;
  this->small_disk_slices=6;
  this->small_disk_stacks=1;

  this->render_speed=1;
  this->current_index=-1;

  robbit_gui.ToggleBotNumbering->value(this->number_bots);
  robbit_gui.ToggleTrails->value(this->show_trails);
  robbit_gui.ToggleObstacles->value(this->show_obstacle);
  robbit_gui.ToggleTopView->value(this->topview);
  robbit_gui.RenderSpeedMenu->value(1);
  robbit_gui.BotMenu->value(0);
  robbit_gui.LightMenu->value(0);
  robbit_gui.ButtonPlayPause->label("@||");
}

//! Sets configuration of Advanced Settings menu elements
void Frame_Display::initAdvWindow() {
  char temp_string[20];
  sprintf(temp_string,"%.2f",max_x);
  robbit_gui.maxx->value(temp_string);
  sprintf(temp_string,"%.2f",max_y);
  robbit_gui.maxy->value(temp_string);
  sprintf(temp_string,"%.2f",min_x);
  robbit_gui.minx->value(temp_string);
  sprintf(temp_string,"%.2f",min_y);
  robbit_gui.miny->value(temp_string);

  sprintf(temp_string,"%.2f",radius_ball);
  robbit_gui.ball_radius->value(temp_string);

  sprintf(temp_string,"%d",no_of_trail_data);
  robbit_gui.trail_points->value(temp_string);

  sprintf(temp_string,"%d",coloured_steps);
  robbit_gui.coloured_steps->value(temp_string);
  robbit_gui.graphics_quality->value((int)(bot_slices/10));
}

//! Renders the current frame
/*! Draws the centroid of the robots, the robots, bot numbering, trails, and the ball.
Also, if the robots and/or the ball or obstacles collide, then it marks them and
sets highlight colors as required. Calls functions to render the obstacles, and the floor.
*/
void Frame_Display::draw()
{   

  init();
  
  reshape(w(), h());

  int i; // Local counter
  char s[100];	// Local string 

  BotHit();

  // Initializes the center of the robots to be zero
  data.bot_center_x=data.bot_center_y=0;
	
  // Render robots according to selected robots
  for(i=0;i<no_of_bots; ++i) {
    if(this->bot_selected==1) {
      position_khepera2(data.bot_x[i],data.bot_y[i],(double)(data.bot_orient[i]),data.bot_hit[0][i]);
    }
    else if(this->bot_selected==2) {
      position_khepera3(data.bot_x[i],data.bot_y[i],(double)(data.bot_orient[i]),data.bot_hit[0][i]);
    }
    else if(this->bot_selected==3) {
      PositionCustomRobot(data.bot_x[i],data.bot_y[i],(double)(data.bot_orient[i]),data.bot_hit[0][i]);
    }

    data.bot_center_x+=data.bot_x[i];	// compute sum of x-cor position of all the bots
    data.bot_center_y+=data.bot_y[i];	// compute sum of y-cor position of all the bots
    
    // Numbers the robots dependin on the mode
    if(this->number_bots) {
      sprintf(s,"%d", i+1);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, text_specular);
      outputCharacter(data.bot_x[i],data.bot_y[i]+7, (height_robot+0.5), s);
    }
  }
	
  // Calculates the centoid of the Robots
  data.bot_center_x/=no_of_bots;
  data.bot_center_y/=no_of_bots;

  // Render robot centeriod
  glPushMatrix();
  glTranslatef(data.bot_center_x,data.bot_center_y,0.05);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_center_specular);
  gluDisk(quad, 0.0, 1.0, bot_slices, bot_stacks);
  glPopMatrix();
	
  // Renders the floor of the animation
  DrawFloor();
		
  // Render the robot trails and ball trails is show_trails is true
  if(this->show_trails) {
    DrawTrails();
  }
  // Renders the ball
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ball_specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ball_shininess);
  glTranslatef(data.ball_x,data.ball_y,radius_ball);
  glutSolidSphere(radius_ball,bot_slices,bot_slices);
  glPopMatrix();

  // Renders the obstacle depending on the mode if show_obstacle is true
  if(this->show_obstacle) {
    DrawObstacle();
  }
}


//! Updates the current frame data
/*! Updates the object data to be rendered to mirror those most recently read
from the file/custom algorithm.
*/
void Frame_Display::UpdateFrame(Frame_Data _data) {
  data= _data;
  current_index++;
  redraw();
}

//! Resizes the simulation
/*! In case of resizing window, the OpenGL rendering is also resized to w times h pixel rectangle.
\param w new width of rendering
\param h new hight of rendering
*/
void Frame_Display::reshape(int w, int h) {
  //prevent a divide by zero, when window is too short
  if(h == 0) { h = 1; }
  aspect = 1.0 * w / h;

  // reset the coordinate system before modifying
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();	// no transformations

  // set the viewport to be the entire window
  glViewport(0, 0, w, h);

  upX = upY = 0;
  upZ = 1.0f;
	
  // set the view.
  gluPerspective(45,aspect,this->Near,this->Far);

  // Sets the camera to look at the centroid of the robots
  if(!camera_on_bot) {

    // If top-view, set the camera vertically above center
    if(topview) {
      eyeX = view_centerX;
      eyeY = view_centerY;
      eyeZ = radius_camera_movement;

      upX = upZ = 0;
      upY = 1.0f;
    }
    else {
      // general view
      if(this->autoview) {
	AutoUpdateEye();
      }

      eyeX = view_centerX + (radius_camera_movement*sin(theta*radianFactor) * cos(phi*radianFactor));
      eyeY = view_centerY + (radius_camera_movement*sin(theta*radianFactor) * sin(phi*radianFactor));
      eyeZ = radius_camera_movement * cos(radianFactor*theta);
    }
  }
  //sets the onboard view of a robot, Sets the camera over specified robot
  else {
    eyeX = data.bot_x[camera_on_bot-1];
    eyeY = data.bot_y[camera_on_bot-1];
    eyeZ = height_robot * 2;
		
    view_centerX = eyeX + (radius_of_robot) * cos(data.bot_orient[camera_on_bot-1]);
    view_centerY = eyeY + (radius_of_robot) * sin(data.bot_orient[camera_on_bot-1]);
    view_centerZ = eyeZ;
  }

  gluLookAt(eyeX, eyeY, eyeZ, view_centerX, view_centerY, view_centerZ, upX, upY, upZ); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


//! Reads obstacle data file
/*! Reads and parses the obstacle data file and stores the obstacle details, provided they are
given in a particular format, into an array. Presently, supported types of obstacles are 
Cube, Sphere, Wall and a Pole.
*/
void Frame_Display::ReadObstacle()
{
  char temp_string[5];	// Temporary String
  char string[1000];	// Saves wholw line from the file
  int st_pos;		// Indicates the current location in string
  int end_file=0;	// indicated end of file when non-zero
  char *fname = fl_file_chooser("Choose Obsctacle ASCII File", "*", "");
  std::ifstream obstacle_data_file;
  obstacle_data_file.open(fname);

  obs_2D_counter = 0;
  WL_counter = 0;
  CB_counter = 0;
  SP_counter = 0;

  if (!obstacle_data_file.is_open()) {
    fl_message("Cannot open file %s !",fname);
    this->show_obstacle=false;
  }
  else {

    // reads a line from the file
    obstacle_data_file.getline(string, 1000);
	
    // neglect all the lines starting from % sign
    while(string[0]=='%') {
      obstacle_data_file.getline(string, 1000);
    }

    while(!end_file) {
      if(string[0]!='%') {
	// Copies first two letters to identify type of the obstacle
	strncpy (temp_string,string,2);
	temp_string[2]='\0';
	st_pos=3;
			
	// Updates the 2D Obstacle
	if(strcmp(temp_string,"2D")==0)	{
	  obs_2D[obs_2D_counter][0]=next_no(string,st_pos);
	  obs_2D[obs_2D_counter][1]=next_no(string,st_pos);
	  obs_2D_counter++;
	}
			
	// Updates the Wall Obstacle
	else if(strcmp(temp_string,"WL")==0) {
	  obs_WL[WL_counter][1]=next_no(string,st_pos);
	  obs_WL[WL_counter][2]=next_no(string,st_pos);
	  obs_WL[WL_counter][3]=next_no(string,st_pos);
	  obs_WL[WL_counter][4]=next_no(string,st_pos);
	  obs_WL[WL_counter][0]=next_no(string,st_pos);
	  WL_counter++;
	}
			
	// Updates the Cube Obstacle
	else if(strcmp(temp_string,"CB")==0) {
	  obs_CB[CB_counter][1]=next_no(string,st_pos);
	  obs_CB[CB_counter][2]=next_no(string,st_pos);
	  obs_CB[CB_counter][0]=next_no(string,st_pos);
	  CB_counter++;
	}
			
	// Updates the Sphere Obstacle
	else if(strcmp(temp_string,"SP")==0) {
	  obs_SP[SP_counter][1]=next_no(string,st_pos);
	  obs_SP[SP_counter][2]=next_no(string,st_pos);
	  obs_SP[SP_counter][0]=next_no(string,st_pos);
	  SP_counter++;
	}
			
	// Throws an error and neglects the input, if given in wrong format
	else {
	  fl_message("Obstacle NOT provided in correct format.\nNeglecting the given Obstacle File.");
	}
      }
		
      // Takes the next line from ASCII file, if there is any or end the loop
      if(!obstacle_data_file.eof()) {
	obstacle_data_file.getline(string, 1000);
      }
      else {
	end_file=1;
      }
    }
  }
  obstacle_data_file.close();
}

//! Renders obstacle
/*! Takes details stored by ReadObstacle and renders some supported types of obstacles.
Note that the pole is represented purely as a point on the floor. It has no rendering of its
exected structure to prevent obstruction in viewing.
*/
void Frame_Display::DrawObstacle()
{
  int local_counter=0; // local counter

  // Renders 2D Obstacles
  while(local_counter < obs_2D_counter) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,disk_2D_obstacle_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
    glPushMatrix();
    glTranslatef(obs_2D[local_counter][0],obs_2D[local_counter][1],0.05);
    gluDisk(quad, 0.0, 1.0, small_disk_slices, small_disk_stacks);
    glPopMatrix();
    local_counter++;
  }

  // Renders Cube type Obstacles
  local_counter=0;
  while(local_counter < CB_counter) {
    glPushMatrix ();
    glTranslated (obs_CB[local_counter][1],obs_CB[local_counter][2],obs_CB[local_counter][0]/2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_2D_obstacle_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
    glutSolidCube (obs_CB[local_counter][0]);
    glPopMatrix();
    local_counter++;
  }

  // Renders wall type Obstacles
  local_counter=0;
  while(local_counter < WL_counter) {
    glBegin(GL_POLYGON);
    glVertex3f (obs_WL[local_counter][1], obs_WL[local_counter][2], 0.0);
    glVertex3f (obs_WL[local_counter][3], obs_WL[local_counter][4], 0.0);
    glVertex3f (obs_WL[local_counter][3], obs_WL[local_counter][4], obs_WL[local_counter][0]);
    glVertex3f (obs_WL[local_counter][1], obs_WL[local_counter][2], obs_WL[local_counter][0]);
    glEnd();
    glFlush ();
    local_counter++;
  }

  // Renders Sphere type Obstacles
  local_counter=0;
  while(local_counter < SP_counter) {
    glPushMatrix ();
    glTranslated (obs_SP[local_counter][1],obs_SP[local_counter][2],obs_SP[local_counter][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_2D_obstacle_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, disk_2D_obstacle_shininess);
    glutSolidSphere (obs_SP[local_counter][0],bot_slices,bot_slices);
    glPopMatrix();
    local_counter++;
  }

  glFinish();
}

//! Renders the floor
/*! The floor is presently a checkerboard of blue and white. 
*/
void Frame_Display::DrawFloor()
{
  float size_square=20;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular);

  int i,j;

  for(i=min_x-30; i<max_x+50; i+=80)
    for(j=min_y-30; j<max_y+50; j+=80)
      glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

  for(i=min_x+11; i<max_x+50; i+=80)
    for(j=min_y+10; j<max_y+50; j+=80)
      glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);
	
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, plane_specular);

  for(i=min_x-30; i<max_x+50; i+=80)
    for(j=min_y+10; j<max_y+50; j+=80)
      glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

  for(i=min_x+11; i<max_x+50; i+=80)
    for(j=min_y-30; j<max_y+50; j+=80)
      glRectf(size_square+i, size_square+j, -size_square+i, -size_square+j);

  glFinish();
}

//! Renders the trails
/*! The trails are stored as a finite length vector. On change of frame data, the 
oldest points belonging to it are popped from the front and new points are pushed 
at the back.
*/
void Frame_Display::DrawTrails()
{
  int i,j; // Simple counter for 'for' loops
	
  // save the current location in the history array for location
  // removes the oldest data

  for(int j=0; j<no_of_bots; j++) {
    if(bot_trail[j][0].size()>no_of_trail_data) {
      bot_trail[j][0].pop_front();
      bot_trail[j][1].pop_front();
    }
    bot_trail[j][0].push_back(data.bot_x[j]);
    bot_trail[j][1].push_back(data.bot_y[j]);
  }

  if(ball_trail[0].size()>no_of_trail_data) {
    ball_trail[0].pop_front();
    ball_trail[1].pop_front();
  }
  ball_trail[0].push_back(data.ball_x);
  ball_trail[1].push_back(data.ball_y);

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk_center_specular);

  // Draws the line joining the all the points for robots
  for(j=0; j<no_of_bots; j++)
    {
      glBegin(GL_LINE_STRIP);
      for(i=0; i<bot_trail[j][0].size(); i++)
	glVertex3f(bot_trail[j][0][i],bot_trail[j][1][i],0.1);
      glEnd ();
    }

  // Draws the line joining the all the points for ball
  glBegin(GL_LINE_STRIP);
  for(i=0; i<ball_trail[0].size(); i++)
    glVertex3f(ball_trail[0][i],ball_trail[1][i],0.1);
  glEnd ();

  glFinish();
}

//! Detects collision between an object and any obstacle
/*! 
\param bot_no number of the bot whose collision is being evaluated
*/
void Frame_Display::DetectObstacleCollision(int bot_no)
{
  float bot_distance;
  int local_counter=0;
  float local_float;
	
  // detects the collision with 2D obstacle
  while(local_counter<obs_2D_counter) {
    bot_distance=pow((data.bot_x[bot_no]-obs_2D[local_counter][0]),2)+pow((data.bot_y[bot_no]-obs_2D[local_counter][1]),2);
    if(bot_distance <= pow((radius_of_robot),2)) {
      data.bot_hit[0][bot_no]=3; // sets to switch to blue colour(robot-obstacle collision)
      data.bot_hit[1][bot_no]=info_refresh_count=0;
      break;
    }
    local_counter++;
  }

  local_counter=0;
  // detects the collision with Cube Obstacle
  while(local_counter<CB_counter)	{
    local_float=(obs_CB[local_counter][0]/2)+radius_of_robot;
    if( data.bot_x[bot_no]<=(obs_CB[local_counter][1]+local_float) &&
	data.bot_x[bot_no]>=(obs_CB[local_counter][1]-local_float) &&
	data.bot_y[bot_no]<=(obs_CB[local_counter][2]+local_float) &&
	data.bot_y[bot_no]>=(obs_CB[local_counter][2]-local_float) )	{
      data.bot_hit[0][bot_no]=3; // sets to switch to green colour(robot-obstacle collision)
      data.bot_hit[1][bot_no]=info_refresh_count=0;
      break;
    }
    local_counter++;
  }

  local_counter=0;
  // detects the collision with Sphere Obstacle
  while(local_counter<SP_counter) {
    bot_distance=pow((data.bot_x[bot_no]-obs_SP[local_counter][1]),2)+pow((data.bot_y[bot_no]-obs_SP[local_counter][2]),2);
    local_float=(float)sqrt((2*obs_SP[local_counter][0]-height_robot)*height_robot)+radius_of_robot;
    if(bot_distance <= pow(local_float,2)) {
      data.bot_hit[0][bot_no]=3; // sets to switch to green colour(robot-obstacle collision)
      data.bot_hit[1][bot_no]=info_refresh_count=0;
      break;
    }
    local_counter++;
  }

  local_counter=0;
  // detects the collision with Wall Obstacle
  while(local_counter<WL_counter)	{
    //    XY LineStart, LineEnd, Point;

    LineStart.X = obs_WL[local_counter][1]; LineStart.Y = obs_WL[local_counter][2];
    LineEnd.X = obs_WL[local_counter][3]; LineEnd.Y = obs_WL[local_counter][4];
    Point.X = data.bot_x[bot_no]; Point.Y = data.bot_y[bot_no];

    if(DistancePointLine( &Point, &LineStart, &LineEnd, radius_of_robot )) {
      data.bot_hit[0][bot_no]=3; // sets to switch to green colour(robot-obstacle collision)
      data.bot_hit[1][bot_no]=info_refresh_count=0;
      return;
    }
    local_counter++;
  }
}

//! Renders KheperaII bots
/*! Renders the 3D structure of the KheperaII robots, which is contained herein.
\param pos_x x coordinate
\param pos_y y coordinate
\param orient orientation (direction it faces)
\param color non-default color when collision occurs
*/
void Frame_Display::position_khepera2(float pos_x,float pos_y,double orient,int colour) 
{
  // setting properties of the material of cylinders
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k2_specular[colour]);
	
  // body cylinder 0
  glPushMatrix();
  glTranslatef(pos_x,pos_y,0);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot),0.6,bot_slices,bot_stacks);
  glPopMatrix();
  
  // body cylinder 1
  glPushMatrix();
  glTranslatef(pos_x,pos_y,0.6);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot-0.5),0.4,bot_slices,bot_stacks);
  glPopMatrix();

  // body cylinder 2
  glPushMatrix();
  glTranslatef(pos_x,pos_y,1.0);
  gluCylinder(quad,(radius_of_robot-0.5),(radius_of_robot-0.5),2.0,bot_slices,bot_stacks);
  glPopMatrix();

  // middle disk
  glPushMatrix();
  glTranslatef(pos_x,pos_y,3.0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk0_specular);
  gluDisk(quad,0.0,(radius_of_robot-0.5),bot_slices,bot_stacks);
  glPopMatrix(); 
  
  // top disk
  glPushMatrix();
  glTranslatef(pos_x,pos_y,height_robot);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk1_specular[colour]);
  gluDisk(quad,0.0,radius_of_robot,bot_slices,bot_stacks);
  glPopMatrix();

  // orientation disk - shows the orientation of the bot
  glPushMatrix();
  glTranslatef((pos_x+(radius_of_robot-radius_of_orient_disk)*cos(orient)),(pos_y+(radius_of_robot-radius_of_orient_disk)*sin(orient)),(height_robot+0.05));
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk2_specular);
  gluDisk(quad,0.0,radius_of_orient_disk,bot_slices,bot_stacks);
  glPopMatrix();
}

//! Renders KheperaIII bots
/*! Renders the 3D structure of the KheperaIII robots, which is contained herein.
\param pos_x x coordinate
\param pos_y y coordinate
\param orient orientation (direction it faces)
\param color non-default color when collision occurs
*/
void Frame_Display::position_khepera3(float pos_x,float pos_y,double orient,int colour) {
  // setting properties of the material of cylinders
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_of_lights);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k3_specular[colour]);
	
  // body cylinder 0
  glPushMatrix();
  glTranslatef(pos_x,pos_y,0);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot),3.5,bot_slices,bot_stacks);
  glPopMatrix();
  
  // body cylinder 1
  glPushMatrix();
  glTranslatef(pos_x,pos_y,3.5);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot-1),0.5,bot_slices,bot_stacks);
  glPopMatrix();
  
  // body cylinder 2
  const GLfloat cyl_spe[] = {0.0, 0.0, 0.0, 1.0};		// specular
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_spe);
  glPushMatrix();
  glTranslatef(pos_x,pos_y,4.0);
  gluCylinder(quad,(radius_of_robot-1),(radius_of_robot-1),1.0,bot_slices,bot_stacks);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k3_specular[colour]);

  // body cylinder 3
  glPushMatrix();
  glTranslatef(pos_x,pos_y,5.0);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot),1.5,bot_slices,bot_stacks);
  glPopMatrix();

  // body cylinder 4
  glPushMatrix();
  glTranslatef(pos_x,pos_y,6.5);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot-0.5),0.5,bot_slices,bot_stacks);
  glPopMatrix();

  // top disk
  glPushMatrix();
  glTranslatef(pos_x,pos_y,height_robot);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk1_specular[colour]);
  gluDisk(quad,0.0,(radius_of_robot-0.5),bot_slices,bot_stacks);
  glPopMatrix();

  // orientation disk - shows the orientation of the bot
  glPushMatrix();
  glTranslatef((pos_x+(radius_of_robot-radius_of_orient_disk-0.5)*cos(orient)),(pos_y+(radius_of_robot-radius_of_orient_disk-0.5)*sin(orient)),(height_robot+0.05));
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk2_specular);
  gluDisk(quad,0.0,radius_of_orient_disk,bot_slices,bot_stacks);
  glPopMatrix();
}

//! Renders custom bots
/*! Renders the 3D structure of user customizable robots. Presently, this is a simplistic cylinder with a 
disk to show the direction it faces.
\param pos_x x coordinate
\param pos_y y coordinate
\param orient orientation (direction it faces)
\param color non-default color when collision occurs
*/
void Frame_Display::PositionCustomRobot(float pos_x,float pos_y,double orient,int colour) {
  // setting properties of the material of cylinders
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyl_k2_specular[colour]);
	
  // body cylinder 0
  glPushMatrix();
  glTranslatef(pos_x,pos_y,0);
  gluCylinder(quad,(radius_of_robot),(radius_of_robot),height_robot,bot_slices,bot_stacks);
  glPopMatrix();

  // top disk
  glPushMatrix();
  glTranslatef(pos_x,pos_y,height_robot);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk1_specular[colour]);
  gluDisk(quad,0.0,radius_of_robot,bot_slices,bot_stacks);
  glPopMatrix();
  
  // orientation disk - shows the orientation of the bot
  glPushMatrix();
  glTranslatef((pos_x+(radius_of_robot-radius_of_orient_disk)*cos(orient)),(pos_y+(radius_of_robot-radius_of_orient_disk)*sin(orient)),(height_robot+0.05));
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disk2_specular);
  gluDisk(quad,0.0,radius_of_orient_disk,bot_slices,bot_stacks);
  glPopMatrix();
}


//! Initializes OpenGL simulation startup settings
/*! Contains settings for light sources (positions, etc.). Eliminates hidden surfaces.
Also enables fog effect.
*/
void Frame_Display::init(void) {

  glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // no transformations
  glPushMatrix();

  glClearColor (0.5, 0.5, 0.5, 0.0);
  glEnable(GL_LIGHTING); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);

  // Light source 0
  if(no_of_lights>0) {
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	// set  specular light 
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);	// set infinite light source 
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHT0);   
  }

  // Light source 1
  if(no_of_lights>1) {
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);	// set  specular light 
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);	// set infinite light source 
    glEnable(GL_LIGHT1);
  } 

  // Light source 2
  if(no_of_lights>2) {
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);	// set  specular light 
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);	// set infinite light source 
  }

  // Light source 3
  if(no_of_lights>3) {
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);	// set  specular light 
    glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);	// set infinite light source 
  }

  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cyl_shininess); // material property for shineness

  // Use depth buffering for hidden surface elimination
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  quad = gluNewQuadric();

  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogf(GL_FOG_DENSITY, 1.0);
  glFogf(GL_FOG_START, this->Far*0.8);
  glFogf(GL_FOG_END, this->Far);

}


//! Detects collisions between any of the bots and/or the ball and/or obstacles.
/*! The collision of any bot with a obstacle is handled through DetectObstacleCollision(<bot number>).
*/
void Frame_Display::BotHit() {
  int i,j; // simple counter
  double bot_distance;	// stores the instantaneous distance of a robots from ball, obstacle or another robot

  for(i=0; i<no_of_bots; i++) {
    if(data.bot_hit[1][i]>coloured_steps) {
      data.bot_hit[0][i]=0; // sets to switch badk to normal color
    }
    else {
      data.bot_hit[1][i]++;
    }

    // detects the collision with other robots
    for(j=i+1; j<no_of_bots; j++) {
      bot_distance=pow((data.bot_x[i]-data.bot_x[j]),2)+pow((data.bot_y[i]-data.bot_y[j]),2);
      if(bot_distance <= pow((2*radius_of_robot),2)) {
	data.bot_hit[0][i]=data.bot_hit[0][j]=1; // sets to switch to red colour(robot-robot collision
	data.bot_hit[1][i]=data.bot_hit[1][j]=info_refresh_count=0;
      }
    }
		
    // detects the collision with the ball
    bot_distance=pow((data.bot_x[i]-data.ball_x),2)+pow((data.bot_y[i]-data.ball_y),2);
    if(bot_distance <= pow((radius_of_robot+radius_ball),2))	{
      data.bot_hit[0][i]=2; // sets to switch to green colour(robot-ball collision)
      data.bot_hit[1][i]=info_refresh_count=0;
    }

    //  detects collision with obstacles
    if(show_obstacle) { 
      DetectObstacleCollision(i);
    }
  }
}


//! Event handler
/*! Any event in the FLTK window called this event handler with a event handle.
Handles both keystrokes (shortcuts), mouse gestures.
\param event event handle number
*/
int Frame_Display::handle(int event) {
  switch(event) {
  case FL_MOUSEWHEEL:
    radius_camera_movement += (delta_zoom*Fl::event_dy());
    redraw();
    return 1;
    
  case FL_PUSH:
    this->mouseX0 = Fl::event_x();
    this->mouseY0 = Fl::event_y();
    this->mousePushValid = true;
    return 1;

  case FL_DRAG: {
    float dx = (Fl::event_x() - this->mouseX0);
    float dy = (Fl::event_y() - this->mouseY0);
    this->mouseX0 = Fl::event_x();
    this->mouseY0 = Fl::event_y();
      
    if (Fl::event_button() == 1 && this->mousePushValid && !this->topview && !camera_on_bot) {
      theta = theta - dy;
      if(theta >= 180) 
	theta = 179.9;
      if(theta <= 0) 
	theta = 0.1;
	
      phi = phi - dx;
      if(phi > 360) 
	phi = 1;
      if(phi < 0)
	phi = 359;
	
      redraw();
    }
    if (Fl::event_button() == 3 && this->mousePushValid && !camera_on_bot) {
      if(!this->topview) {
	view_centerX+=(dx*sin(phi*radianFactor)-dy*cos(phi*radianFactor));
	view_centerY-=(dx*cos(phi*radianFactor)+dy*sin(phi*radianFactor));
      }
      else {
	view_centerX-=dx;
	view_centerY+=dy;
      }
      redraw();
    }
    return 1;    
  }

  case FL_RELEASE:   
    this->mousePushValid = false;
    return 1;

  case FL_FOCUS :
  case FL_UNFOCUS :
    return 1;

  case FL_KEYBOARD:
    return Fl_Gl_Window::handle(event);

  case FL_SHORTCUT:
    switch ((char)Fl::event_key()) {
    case ' ': // Play/Pause Animation
      setPlayPause();
      return 1;

    case 't': // Top View
    case 'T':
      if(!this->autoview) {
	robbit_gui.ToggleTopView->value(!this->topview);
	if(!this->topview) {
	  robbit_gui.ToggleAutoView->deactivate();
	}
	else {
	  robbit_gui.ToggleAutoView->activate();
	}
	setTopView(!this->topview);
      }
      return 1;

    case 'l': // Trails
    case 'L':
      robbit_gui.ToggleTrails->value(!this->show_trails);
      setTrails(!this->show_trails);
      return 1;

    case 'a': // About Window
    case 'A':
      robbit_gui.AboutWindow->show();
      robbit_gui.textrobbit->load("index.html");
      return 1;

    case 'd': // Advanced Settings
    case 'D':
      initAdvWindow();
      robbit_gui.AdvSettingsWindow->show();
      return 1;

    case 's': // Screen Shot
    case 'S':
      CaptureScreenshot();
      return 1;

    case 27: // Stop Animation on Esc	      
      setExit();
      return 1;

    case 'n': // Number Robots
    case 'N':
      robbit_gui.ToggleBotNumbering->value(!this->number_bots);
      setBotNumbering(!this->number_bots);
      return 1;
	
    case 'o': // show/hide Obstacles
    case 'O':
      robbit_gui.ToggleObstacles->value(!this->show_obstacle);
      setObstacles(!this->show_obstacle);
      return 1;

    case 'u': // auto view
    case 'U':
      if(!this->topview) {
	robbit_gui.ToggleAutoView->value(!this->autoview);
	if(!this->autoview) {
	  robbit_gui.ToggleTopView->deactivate();
	}
	else {
	  robbit_gui.ToggleTopView->activate();
	}
	setAutoView(!this->autoview);
      }
      return 1;

    default:
       //  Selection of bot for onboard view
      if( ( (Fl::event_key()-48)<=no_of_bots) && ((Fl::event_key()-48)>0) ) {
	camera_on_bot=Fl::event_key()-48;
	fl_message("On board view of robot %d",camera_on_bot);
	return 1;
	}
      else if(Fl::event_key()== 65451) { // Zoom In 
	radius_camera_movement -= delta_zoom;
	redraw();
	return 1;
      }
      else if(Fl::event_key()== 65453) { // Zoom Out
	radius_camera_movement += delta_zoom;
	redraw();
	return 1;
      }
      else {
	camera_on_bot=0;
	view_centerX=(max_x+min_x)/2; 
	view_centerY=(max_y+min_y)/2; 
	view_centerZ=0;
	return Fl_Gl_Window::handle(event);
      }
    }

  case FL_MOVE:
    this->mousePushValid = false;
    return 1;

  default:
    // pass other events to the base class...
    return Fl_Gl_Window::handle(event);
  }
}


//! Renders a character at a specific location
/*! 
\param x x coordinate of string to be rendered
\param y y coordinate of string to be rendered
\param z z coordinate of string to be rendered
\param string string to be rendered
*/
void Frame_Display::outputCharacter(float x, float y, float z, char *string) {
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

//! Captures a screenshot as a PNG
/*! Saves a screenshot with a generated filename in Portable Network Graphics format.
The filename contains details like the time, and view angles, \f$\theta\f$ and \f$\phi\f$.
*/
void Frame_Display::CaptureScreenshot() {
  char img_file_name[200];
  sprintf(img_file_name, "screenshots/capture_%08d_%d_%d.png", (int)(data.time*100), (int)theta, (int)phi);
  CaptureScreen(img_file_name);
  fl_message("\nSaved '%s'",img_file_name);
}

