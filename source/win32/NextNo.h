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
*	NextNo.h  v 3.0 , 2007-12-05, 11:00:00 IST
*
*	Takes a string and current string pointer as arguments
*	Finds the next number, reading from a string
*	numbers shold be seperated by space or comma
*	[ used to read the numbers form the input files ]
*	Updates the string pointer position
*	Returns the found number(float)
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



float next_no(char *string, int &st_pos)
{
	char temp_string[20]="a";	// Temporary string
	int num_found=0;			// 1 if number is found, 0 if not found
	int counter=0;				// Simple local counter

	while(((string[st_pos]!=' ' && string[st_pos]!=',' && string[st_pos]!=')') || !num_found) && string[st_pos]!='/0')
	{
		if(string[st_pos]!=',' && string[st_pos]!=')')
		{
			temp_string[counter]=string[st_pos];
			counter++;
		}
		
		if(string[st_pos]!=' ' && string[st_pos]!=',' && string[st_pos]!=')')
		{
			num_found=1;
		}
		st_pos++;
	}
	return(atof(temp_string));
}
