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
//	* LAI, UniversitÓ degli Studi di Cassino, Italy
//	
// ------------------------------------------------------------------------------------/
//! CLass to build the whole GUI
// /*! This class is created with FLUID (Fast Light User-Interface Designer). It also monitors all the events and callback
// */
// generated by Fast Light User Interface Designer (fluid) version 1.0109

#ifndef robbitGUI_h
#define robbitGUI_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Help_View.H>
#include<time.h>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Output.H>

class RobbitUI {
public:
  RobbitUI();
  Fl_Double_Window *RobbitMainWindow;
private:
  void cb_RobbitMainWindow_i(Fl_Double_Window*, void*);
  static void cb_RobbitMainWindow(Fl_Double_Window*, void*);
public:
  Fl_Value_Slider *indexSlider;
private:
  void cb_indexSlider_i(Fl_Value_Slider*, void*);
  static void cb_indexSlider(Fl_Value_Slider*, void*);
public:
  Frame_Display *display;
  Fl_Button *ButtonAbout;
private:
  void cb_ButtonAbout_i(Fl_Button*, void*);
  static void cb_ButtonAbout(Fl_Button*, void*);
public:
  Fl_Light_Button *ToggleAutoView;
private:
  void cb_ToggleAutoView_i(Fl_Light_Button*, void*);
  static void cb_ToggleAutoView(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *ToggleTopView;
private:
  void cb_ToggleTopView_i(Fl_Light_Button*, void*);
  static void cb_ToggleTopView(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *ToggleTrails;
private:
  void cb_ToggleTrails_i(Fl_Light_Button*, void*);
  static void cb_ToggleTrails(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *ToggleObstacles;
private:
  void cb_ToggleObstacles_i(Fl_Light_Button*, void*);
  static void cb_ToggleObstacles(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *ToggleBotNumbering;
private:
  void cb_ToggleBotNumbering_i(Fl_Light_Button*, void*);
  static void cb_ToggleBotNumbering(Fl_Light_Button*, void*);
public:
  Fl_Button *ButtonAdvSettings;
private:
  void cb_ButtonAdvSettings_i(Fl_Button*, void*);
  static void cb_ButtonAdvSettings(Fl_Button*, void*);
public:
  Fl_Button *ButtonScrrenshot;
private:
  void cb_ButtonScrrenshot_i(Fl_Button*, void*);
  static void cb_ButtonScrrenshot(Fl_Button*, void*);
public:
  Fl_Choice *RenderSpeedMenu;
  static Fl_Menu_Item menu_RenderSpeedMenu[];
private:
  void cb_0_i(Fl_Menu_*, void*);
  static void cb_0(Fl_Menu_*, void*);
  void cb_1X_i(Fl_Menu_*, void*);
  static void cb_1X(Fl_Menu_*, void*);
  void cb_2X_i(Fl_Menu_*, void*);
  static void cb_2X(Fl_Menu_*, void*);
  void cb_5X_i(Fl_Menu_*, void*);
  static void cb_5X(Fl_Menu_*, void*);
  void cb_10X_i(Fl_Menu_*, void*);
  static void cb_10X(Fl_Menu_*, void*);
  void cb_MAX_i(Fl_Menu_*, void*);
  static void cb_MAX(Fl_Menu_*, void*);
public:
  Fl_Choice *BotMenu;
  static Fl_Menu_Item menu_BotMenu[];
  static Fl_Menu_Item *KheperaII;
private:
  void cb_KheperaII_i(Fl_Menu_*, void*);
  static void cb_KheperaII(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *KheperaIII;
private:
  void cb_KheperaIII_i(Fl_Menu_*, void*);
  static void cb_KheperaIII(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *Custom;
private:
  void cb_Custom_i(Fl_Menu_*, void*);
  static void cb_Custom(Fl_Menu_*, void*);
public:
  Fl_Choice *LightMenu;
  static Fl_Menu_Item menu_LightMenu[];
  static Fl_Menu_Item *Light1;
private:
  void cb_Light1_i(Fl_Menu_*, void*);
  static void cb_Light1(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *Light2;
private:
  void cb_Light2_i(Fl_Menu_*, void*);
  static void cb_Light2(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *Light3;
private:
  void cb_Light3_i(Fl_Menu_*, void*);
  static void cb_Light3(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *Light4;
private:
  void cb_Light4_i(Fl_Menu_*, void*);
  static void cb_Light4(Fl_Menu_*, void*);
public:
  Fl_Button *ButtonReset;
private:
  void cb_ButtonReset_i(Fl_Button*, void*);
  static void cb_ButtonReset(Fl_Button*, void*);
public:
  Fl_Button *ButtonPlayPause;
private:
  void cb_ButtonPlayPause_i(Fl_Button*, void*);
  static void cb_ButtonPlayPause(Fl_Button*, void*);
public:
  Fl_Button *ButtonStop;
private:
  void cb_ButtonStop_i(Fl_Button*, void*);
  static void cb_ButtonStop(Fl_Button*, void*);
public:
  Fl_Double_Window *AboutWindow;
  Fl_Help_View *textrobbit;
  Fl_Double_Window *SplashWindow;
  Fl_Help_View *htmlSplash;
private:
  void cb_About_i(Fl_Button*, void*);
  static void cb_About(Fl_Button*, void*);
  void cb_Close_i(Fl_Return_Button*, void*);
  static void cb_Close(Fl_Return_Button*, void*);
public:
  Fl_Double_Window *custom_robot_window;
  Fl_Input *height;
  Fl_Input *radius;
private:
  void cb_OK_i(Fl_Return_Button*, void*);
  static void cb_OK(Fl_Return_Button*, void*);
public:
  Fl_Double_Window *AdvSettingsWindow;
  Fl_Input *maxy;
private:
  void cb_maxy_i(Fl_Input*, void*);
  static void cb_maxy(Fl_Input*, void*);
public:
  Fl_Input *miny;
private:
  void cb_miny_i(Fl_Input*, void*);
  static void cb_miny(Fl_Input*, void*);
public:
  Fl_Input *maxx;
private:
  void cb_maxx_i(Fl_Input*, void*);
  static void cb_maxx(Fl_Input*, void*);
public:
  Fl_Input *minx;
private:
  void cb_minx_i(Fl_Input*, void*);
  static void cb_minx(Fl_Input*, void*);
public:
  Fl_Input *ball_radius;
private:
  void cb_ball_radius_i(Fl_Input*, void*);
  static void cb_ball_radius(Fl_Input*, void*);
public:
  Fl_Input *trail_points;
private:
  void cb_trail_points_i(Fl_Input*, void*);
  static void cb_trail_points(Fl_Input*, void*);
public:
  Fl_Input *coloured_steps;
private:
  void cb_coloured_steps_i(Fl_Input*, void*);
  static void cb_coloured_steps(Fl_Input*, void*);
public:
  Fl_Slider *graphics_quality;
private:
  void cb_graphics_quality_i(Fl_Slider*, void*);
  static void cb_graphics_quality(Fl_Slider*, void*);
  void cb_OK1_i(Fl_Return_Button*, void*);
  static void cb_OK1(Fl_Return_Button*, void*);
public:
  void show();
};
#endif
