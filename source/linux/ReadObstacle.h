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
*	ReadObstacle  v 3.0 , 2007-12-05, 11:03:00 IST
*
*	Reads the Obstacle File - ' Obstacle.txt '
*	Updates the corresponding Obstacle parameters
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



void ReadObstacle()
{
	char temp_string[5];	// Temporary String
	char string[1000];		// Saves wholw line from the file
	int st_pos;				// Indicates the current location in string
	int end_file=0;			// indicated end of file when non-zero

	// reads a line from the file
	obstacle_data_file.getline(string, 1000);
	
	// neglect all the lines starting from % sign
	while(string[0]=='%')
	{
		obstacle_data_file.getline(string, 1000);
	}

	while(!end_file)
	{
		if(string[0]!='%')
		{
			// Copies first two letters to identify type of the obstacle
			strncpy (temp_string,string,2);
			temp_string[2]='\0';
			st_pos=3;
			
			// Updates the 2D Obstacle
			if(strcmp(temp_string,"2D")==0)
			{
				obs_2D[obs_2D_counter][0]=next_no(string,st_pos);
				obs_2D[obs_2D_counter][1]=next_no(string,st_pos);
				obs_2D_counter++;
			}
			
			// Updates the Wall Obstacle
			else if(strcmp(temp_string,"WL")==0)
			{
				obs_WL[WL_counter][1]=next_no(string,st_pos);
				obs_WL[WL_counter][2]=next_no(string,st_pos);
				obs_WL[WL_counter][3]=next_no(string,st_pos);
				obs_WL[WL_counter][4]=next_no(string,st_pos);
				obs_WL[WL_counter][0]=next_no(string,st_pos);
				WL_counter++;
			}
			
			// Updates the Cube Obstacle
			else if(strcmp(temp_string,"CB")==0)
			{
				obs_CB[CB_counter][1]=next_no(string,st_pos);
				obs_CB[CB_counter][2]=next_no(string,st_pos);
				obs_CB[CB_counter][0]=next_no(string,st_pos);
				CB_counter++;
			}
			
			// Updates the Sphere Obstacle
			else if(strcmp(temp_string,"SP")==0)
			{
				obs_SP[SP_counter][1]=next_no(string,st_pos);
				obs_SP[SP_counter][2]=next_no(string,st_pos);
				obs_SP[SP_counter][0]=next_no(string,st_pos);
				SP_counter++;
			}
			
			// Throws an error and neglects the input, if given in wrong format
			else
			{
				cout<<"Obstacle NOT provided in correct format.\nNeglecting the given Obstacle"<<endl;
			}
		}
		
		// Takes the next line from ASCII file, if there is any or end the loop
		if(!obstacle_data_file.eof())
			obstacle_data_file.getline(string, 1000);
		else
			end_file=1;
	}
	cout<<"\nFinished reading the Obstacle Data File"<<endl;
}
