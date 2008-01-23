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
*	Reshape.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Determines the Eye/camera location
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void reshape(int w, int h)
{
	width = w;
    height = h;

    //prevent a divide by zero, when window is too short
    if(h == 0) h = 1;
    ratio = 1.0 * w / h;

    // reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// no transformations
    
    // set the viewport to be the entire window
    glViewport(0, 0, w, h);

	upX = upY = 0;
	upZ = 1.0f;
	
    // set the view.
	gluPerspective(45,ratio,1,1000);
	if(camera_on_bot==-1)	// Sets the camera to look at the centroid of the robots
	{
		centerX = 0;
		centerY = 0;
		centerZ = 0;

		for(int i=0;i<no_of_bots; ++i)
		{
			centerX += current.bot_x[i];
			centerY += current.bot_y[i];
		}

		centerX /=no_of_bots;
		centerY /=no_of_bots;

		if(is_topview==1)	// If top-view, set the camera vertically above the centroid of the robots
		{
			eyeX = centerX;
			eyeY = centerY;
			eyeZ = radius_camera_movement;

			upX = upZ = 0;
			upY = 1.0f;
		}
		else	// general view
		{
			eyeX = centerX + (radius_camera_movement * sin(theta * radianFactor) * cos(phi * radianFactor));
			eyeY = centerY + (radius_camera_movement * sin(theta * radianFactor) * sin(phi * radianFactor));
			eyeZ = radius_camera_movement * cos(radianFactor * theta);
		}
	}
	else		//sets the onboard view of a robot, Sets the camera over specified robot
	{
		eyeX = current.bot_x[camera_on_bot];
		eyeY = current.bot_y[camera_on_bot];
		eyeZ = height_robot * 2;
		
		centerX = eyeX + (radius_of_robot) * cos(current.bot_orient[camera_on_bot]);
		centerY = eyeY + (radius_of_robot) * sin(current.bot_orient[camera_on_bot]);
		centerZ = eyeZ;
	}

	gluLookAt(eyeX, eyeY, eyeZ,centerX, centerY, centerZ, upX, upY, upZ); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// calls the refresh of the sub-window
	glutSetWindow (winIdSub);
	glutReshapeWindow (width-10, sub_height);
	glutPositionWindow (5, 5);
	glutSetWindow (winIdMain);
}
