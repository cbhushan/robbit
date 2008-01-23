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
*	FrameUpdate.h  v 3.0 , 2007-12-05, 11:47:00 IST
*
*	Function of the Class ' frame'
*	Reades form the ASCII log file for the current location
*	 Creats the current frame for the simulation
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void frame::update(int mode = 0)
		// mode -
		// 0: frame_update_mode
		// 1: read whole file at beginning simulation to get the max coordinates
{
	char string[1000];	// buffer string to store the data line temporarily
	int i=0;			// simple counters
	int st_pos;			// position of file pointer
	float temp_float;	// temporary float buffer
	
	if(!input_data_file.eof())
	{
		input_data_file.getline(string, 1000);

		if(string[0]!='%')
		{
			// Reads the iteration number
			iter_no=atoi(string);
			st_pos=4;
			
			// neglects the 2nd column of data
			temp_float=next_no(string,st_pos);
		
			// Sets the current time and time step for sleep function
			temp_float=next_no(string,st_pos);
			this->time_step = temp_float - this->time;
			this->time = current_time = temp_float;
			
			for(i=0; i<no_of_bots; ++i)
			{
				// Reads the current robots location, orientation
				this->bot_x[i]		=next_no(string,st_pos);
				this->bot_y[i]		=next_no(string,st_pos);
				this->bot_orient[i]	=next_no(string,st_pos);
				temp_float			=next_no(string,st_pos);
				temp_float			=next_no(string,st_pos);

				// Calculates the maximum and minimum coordinates of arena depending on the log file
				if(mode == 1)
				{
					if(max_x < this->bot_x[i])
						max_x = this->bot_x[i];
					if(max_y < this->bot_y[i])
						max_y = this->bot_y[i];
					if(min_x > this->bot_x[i])
						min_x = this->bot_x[i];
					if(min_y > this->bot_y[i])
						min_y = this->bot_y[i];
				}
			}

			// Reads the current velocity wise components
			for(i=0; i<no_of_bots; ++i)
			{
				this->bot_vx[i] =next_no(string,st_pos);
				this->bot_vy[i] =next_no(string,st_pos);
				this->bot_vorient[i]=atan2((double)this->bot_vx[i],(double)this->bot_vy[i]);
			}

			// Reads the current ball location
			this->ball_x=next_no(string,st_pos);
			this->ball_y=next_no(string,st_pos);
			
			// Calculates the maximum and minimum coordinates of arena depending on the log file
			if(mode == 1)
			{
				if(max_x < this->ball_x)
					max_x = this->ball_x;
				if(max_y < this->ball_y)
					max_y = this->ball_y;
				if(min_x > this->ball_x)
					min_x = this->ball_x;
				if(min_y > this->ball_y)
					min_y = this->ball_y;
			}
		}
		else	// lines starting with 
		{
			// neglects all the blank lines and  line starting with % sign
			while(string[0]=='%' || string[0]=='\n')
			{
				input_data_file.getline(string, 1000);
				current_time=0.0;
				this->time=0.0;
			}
		}
	}
	else	// End of the input file
	{
		end_of_input_file = true;
	}
}
