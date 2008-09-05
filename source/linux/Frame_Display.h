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


//! Class to store data required for running of simulation and GUI
/*! Stores data required to render a frame. It also has all the data for running and handling the events from GUI. On update of values of Frame_Data object, the data here must be updated.
*/
class Frame_Display : public Fl_Gl_Window {
 private:
  int bot_selected;	// type of robot selected, 1 for KheparaII, 2 for KeparaIII

  bool number_bots;	  // tag to identify if bots are to be numbered or not
  bool show_obstacle;
  bool show_trails;
  bool topview;
  bool autoview;

  float obs_2D[20][2];	// saves 2D obstacle location, [x][y] 
  float obs_WL[20][5];	// saves wall type Obstacle location [height][x1][y1][x2][y2]
  float obs_CB[20][3];	// saves cube type Obstacle location [side length][x][y]
  float obs_SP[20][3];	// saves sphere type Obstacle location [side length][x][y]

  int obs_2D_counter;	// saves no. of 2D obstacle
  int WL_counter;	// saves no. of wall type obstacle
  int CB_counter;	// saves no. of cube type obstacle
  int SP_counter;	// saves no. of sphere type obstacle
  float radius_ball;	// radius of ball (spherical)
  int no_of_trail_data;	// number of steps for which position is stored
			// to draw the trail of ball and bots
  int coloured_steps;	// No of steps in which the bot is coloured

  // arrays to store the data to produce the trail for robots and ball
  std::deque<float> bot_trail[no_of_bots][2];
  std::deque<float> ball_trail[2];

  // eye/camera position parameters
  float radius_camera_movement;// distance of viewing eye from the bots
  float theta;		// stores theta value of camera position (polar parameters)
  float phi;			// stores phi value of camera position (polar parameters)
  float eyeX,eyeY,eyeZ;		// stores the current position of camera in cartesian coordinate 
				//   system, derived from theta, phi
 
  float upX, upY, upZ;	// stores the normal vector parameters of camera
  float aspect;
  float Near, Far;
  int camera_on_bot;// identifies if camera is mounted on any robot; 0 -> general
  int delta_zoom;// the amount by which 'radius_camera_movement' changes on zoom in/out
  int no_of_lights;	// number of lights currently
  float mouseX0,mouseY0;
  bool mousePushValid;

  float radius_of_robot;// radius of the robot(cylindrical)
  float height_robot;	// height of the robot(cylindrical)
  int bot_slices; 	// number of slices for Cylinder & Disk	
  int bot_stacks;	// number of stacks for Cylinder & Disk
  int small_disk_slices;// nukber of slices for centriod and 2D obstacle
  int small_disk_stacks;// nukber of stacks for centriod and 2D obstacle

  Frame_Data data; // object of data class

  XY LineStart, LineEnd, Point;

 public:

  Frame_Display(int x, int y, int w, int h);

  bool is_paused;         // tag to identify if paused or not
  float render_speed;   // speed of rendering graphics
  int current_index;
  float view_centerX,view_centerY,view_centerZ; //stores the position to which the camera is directed

  int handle(int event);
  void UpdateFrame(Frame_Data _data); // Updates the current frame to display
  void draw();  	// Draws the current frame
  void DrawFloor();	// Draws the floor on which robots are moving
  void ReadObstacle();	// Reads the obstacle ASCII file
  void DrawObstacle();	// Draws the Obstacle
  void DrawTrails();	// Draws the trails of robots
  void BotHit();
  void CaptureScreenshot();

  // Detects the collision with the given obstacles (if any)
  void DetectObstacleCollision(int bot_no);

  // Displays the robot(Khepara II) at their positions
  void position_khepera2(float pos_x,float pos_y,double orient,int colour);

  // Displays the robot(Khepara III) at their positions
  void position_khepera3(float pos_x,float pos_y,double orient,int colour);
  void PositionCustomRobot(float pos_x,float pos_y,double orient,int colour);

  void inline AutoUpdateEye();

  void init(void); // Initializes GL-display
  void reshape(int w, int h); // Handler for window resize
  void setIndex(int val) { current_index=val; redraw(); }
  void outputCharacter(float x, float y, float z, char *string);

  void setPlayPause();

  //! Shows confirmation box before exit
  void setExit() { if(fl_choice("Do you really want to exit?",NULL,"Yes","No")==1) exit(0); }
  void setStop();

  //! Resets all the settings to default
  void setReset() { setDefaults();  redraw(); }

  //! Toggles the numbering of bot
  /*!
    \param val value of the numbering bot (GUI)
  */
  void setBotNumbering(bool val) { number_bots=val;  redraw(); }
  // void setInformation(bool val) { show_info=val;  }
  void setTrails(bool val);

  //! Toggles the displaying of the Obstacles
  /*! If set to display obstacle then reads obstacle from ascii file
    \param val value of the show obstacle option (GUI)
  */
  void setObstacles(bool val) {
    show_obstacle=val;
    if(show_obstacle)
      ReadObstacle();
    redraw();
  }

  //! Toggles the top view mode
  /*! 
    \param val value of the top view mode (GUI)
  */
  void setTopView(bool val) { topview=val;  redraw(); }

  //! Toggles the Auto-rotate mode
  /*! 
    \param val value of the auto-rotate mode (GUI)
  */
  void setAutoView(bool val) { autoview=val;  redraw(); }
  void selectBot(int val);

  //! Set no of lights to be used
  /*! 
    \param val no of lights (GUI)
  */
  void setLights(int val) { no_of_lights=val; redraw(); }

  //! Sets the rendering speed
  /*! 
    \param val value rendring speed in form of nX (GUI); 0: denotes maximum possible speed
  */
  void setRenderSpeed(float val) { render_speed=val; }
  void setDefaults();

  //! Sets dimension of Custom Robot (Cylindrical)
  /*! Also set the robot to be displayed to be Custom Robot
    \param height height of Custom Robot (GUI)
    \param radius radius of Custom Robot (GUI)
  */
  void setCustomRobot(float height, float radius){
    height_robot=height;
    radius_of_robot=radius;
    selectBot(3);
  }

  //! Sets Arena coordinates
  /*!
    \param maxx maximum x coordinate (GUI)
    \param minx minimum x coordinate (GUI)
    \param maxy maximum y coordinate (GUI)
    \param miny minimum y coordinate (GUI)
  */
  void setArena(float maxx,float minx,float maxy,float miny) {
    max_x=maxx;    max_y=maxy;    min_x=minx;   min_y=miny; 
  }

  //! Sets radius of ball
  /*!
    \param val radius of ball (GUI)
  */
  void setBallRadius(float val) { radius_ball=val;}

  //! Sets no of trail data to keep
  /*!
    \param val number of trail data (GUI)
  */
  void setTrailPoints(float val) { no_of_trail_data=val;}

  //! Sets no of coloured steps (in case of any collision)
  /*!
    \param val number of coloured steps (GUI)
  */
  void setColouredSteps(float val) { coloured_steps=val;}
  void initAdvWindow();

  //! Sets graphic quality of objects rendered
  /*!
    \param slices number of slices
    \param stacks number of stacks
  */
  void setGraphicsQuality(int slices, int stacks) {
    bot_stacks=stacks;
    bot_slices=slices;
  }
};

