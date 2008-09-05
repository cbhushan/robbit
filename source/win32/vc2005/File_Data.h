// ------------------------------------------------------------------------------------//
//
//	This file is part of 3-D Simulator ' Robbit '
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

//! Class to store file data
/*! This record may be one from a log-file.
It includes methods to build an index, to get based on the index, etc.
*/
class File_Data
{
 protected:
  typedef std::size_t pos_type;
  std::vector<pos_type> file_index;
  std::ifstream input;

 public:
  int BuildFileIndex();									// read the file and bulids the index of the file content
  int SetFileInput(const char *fname);					// opens the file and calls buildFileIndex()
  int IndexSize() const { return file_index.size(); }	// returns the size of the index
  int GetData(int i, Frame_Data &data);					// get the data from index created
};
