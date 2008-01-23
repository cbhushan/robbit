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
*	Robot_Class.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	 Kills the animation at any time as required
*	And dislpays the Thankyou message
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


int kill_animation(void)
{
	input_data_file.close();
	cout<<endl<<"Input data file closed..\n";
	cout<<endl<<"\n\n\n\n\t Thankyou for using this program.\n\n\tProgram developed by:\n\n\t Antonelli Gianluca\n\tArrichiello Filippo\n\tBhushan Chitresh\n\tPrakash Chander\n\tPurkayasth Sayandeep\n\n\n"<<endl;
	exit(0);
}