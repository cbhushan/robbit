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

typedef std::vector<float> FloatVec;
typedef std::vector<int> IntVec;

//! Class to store frame data
/*! Stores data for a frame that is to be rendered. On extraction of a record from log-file, or when the 
custom algorithm updates the coordinate data, etc. the data here must be stored here.
*/
class Frame_Data
{
 public:
  FloatVec bot_x;	// x-coordinate of the robots' position [cm]
  FloatVec bot_y;	// y-coordinate of the robots' position [cm]
  FloatVec bot_vx;	// x-component of the robots' velocity [cm/sec]
  FloatVec bot_vy;	// y-component of the robots' velocity [cm/sec]
  FloatVec bot_orient;	// orientation of the robots [rad]
  FloatVec bot_vorient; // angular velocity [rad/sec]
  IntVec   bot_hit[2];	// [ bot number ] [1: hit (1)/not hit (0)
                        //                 2: time of hit ]
  int bot_design;	//      1: Khepera II; 2: Khepera III
  float time;		//	current time of the frame
	
  float ball_x;		// x-coordinate of the balls' position [cm]
  float ball_y;		// y-coordinate of the balls' position [cm]
  float ball_vx;	// x-component of the balls' velocity [cm/sec]
  float ball_vy;	// y-component of the balls' velocity [cm/sec]
  float bot_center_x;	// x-coordinate of current cetroid of the robots
  float bot_center_y;	// y-coordinate of current cetroid of the robots
  float time_step;	// current delay time (for sleep functions)
};
