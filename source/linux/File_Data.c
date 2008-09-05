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

using namespace std;

//! Opens the log file and calls BuildFileIndex()
/*!
\param fname string :  name of the log file to be opened
*/
int File_Data::SetFileInput(const char *fname) {
  this->input.open(fname);
  if (!this->input.is_open()) {
    fl_message("Cannot open file %s",fname);
    return -1;
  }

  int num = this->BuildFileIndex();
  fl_message("Indexed %d valid entries.",num);
  return num;
}


//! Builds index for quick reference within log file
/*! Stores the positions of get pointers to valid records in the log file, in a vector.
This way, the file does not need to be traversed in serial fashion, and allows for quicker
and random access to file data. 
*/
int File_Data::BuildFileIndex()
{
  char string[1000];	// local string
  char *str_end;
  float temp_float;
  int i;

  if (!this->input.is_open()) 
    return -1;

  this->input.seekg(pos_type(0)); // rewind to the begining
  this->file_index.clear();

  while (!this->input.eof()) {

    // skip all lines starting with '%'
    while( this->input.peek()=='%' && !input.eof()) {
      this->input.getline(string, 1000);
    }

    this->file_index.push_back( input.tellg() );
    
    // Calculates the maximum and minimum coordinates of arena depending on the log file
    this->input.getline(string, 1000);

    temp_float=(float)strtod(string, &str_end);
    //    st_pos=4;

    temp_float=(float)strtod(str_end, &str_end);
    temp_float=(float)strtod(str_end, &str_end);

    for(i=0; i<no_of_bots; ++i) {
      temp_float=(float)strtod(str_end, &str_end);
      if(max_x < temp_float)
	max_x = temp_float;
      if(min_x > temp_float)
	min_x = temp_float;

      temp_float=(float)strtod(str_end, &str_end);
      if(max_y < temp_float)
	max_y = temp_float;
      if(min_y > temp_float)
	min_y = temp_float;

      temp_float=(float)strtod(str_end, &str_end);
      temp_float=(float)strtod(str_end, &str_end);
      temp_float=(float)strtod(str_end, &str_end);
    }

    for(i=0; i<no_of_bots; ++i) {
      temp_float = (float)strtod(str_end, &str_end);
      temp_float = (float)strtod(str_end, &str_end);
    }

      temp_float=(float)strtod(str_end, &str_end);
      if(max_x < temp_float)
	max_x = temp_float;
      if(min_x > temp_float)
	min_x = temp_float;

      temp_float=(float)strtod(str_end, &str_end);
      if(max_y < temp_float)
	max_y = temp_float;
      if(min_y > temp_float)
	min_y = temp_float;

  }
  return this->file_index.size();
}

//! Get data from file index
/*! Reads each line pointed to by the get pointer locations stored in the index.
Breaks each line into the required fields, and stores the fields into the object 'data' of class 'Frame_Data'.

\param ind current record number / index
\param data object 'data' of class 'Frame_Data'
\return 0 always
*/
int File_Data::GetData(int ind, Frame_Data &data)
{
  if (ind < 0 || ind>= this->file_index.size()) { 
    return 0;
  }
  
  // make sure any error bits are cleared
  this->input.clear();

  // seek to the current line
  this->input.seekg( this->file_index[ind], ios::beg );

  char string[1000]; // buffer string to store the data line temporarily
  char *str_end;
  int i=0;	 // simple counters
  float temp_float; // temporary float buffer	

  data.bot_x.resize(no_of_bots);
  data.bot_y.resize(no_of_bots);
  data.bot_vx.resize(no_of_bots);
  data.bot_vy.resize(no_of_bots);
  data.bot_orient.resize(no_of_bots);
  data.bot_vorient.resize(no_of_bots);
  data.bot_hit[0].resize(no_of_bots);
  data.bot_hit[1].resize(no_of_bots);

  this->input.getline(string, 1000);

  // Reads the iteration number
  temp_float=(float)strtod(string, &str_end);
  //  iter_no=atoi(string);
  //  st_pos=4;
			
  // neglects the 2nd column of data
  temp_float=(float)strtod(str_end, &str_end);
		
  // Sets the current time and time step for sleep function
  temp_float=(float)strtod(str_end, &str_end);
  data.time_step = temp_float - data.time;
  data.time = temp_float;
			
  for(i=0; i<no_of_bots; i++) {
    // Reads the current robots location, orientation
    data.bot_x[i] = (float)strtod(str_end, &str_end);
    data.bot_y[i] = (float)strtod(str_end, &str_end);
    data.bot_orient[i] = (float)strtod(str_end, &str_end);
    temp_float = (float)strtod(str_end, &str_end);
    temp_float = (float)strtod(str_end, &str_end);
  }

  // Reads the current velocity wise components
  for(i=0; i<no_of_bots; ++i) {
    data.bot_vx[i] = (float)strtod(str_end, &str_end);
    data.bot_vy[i] = (float)strtod(str_end, &str_end);
    data.bot_vorient[i] = atan2((double)data.bot_vx[i],(double)data.bot_vy[i]);
  }

  // Reads the current ball location
  data.ball_x=(float)strtod(str_end, &str_end);
  data.ball_y=(float)strtod(str_end, &str_end);			
}
