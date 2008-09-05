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

//! Actual Capture screen routine
/*! Captures OpenGL render buffer. Creates a PNG file, writes header info, image data, and closes it.
*/
void CaptureScreen(char *filename)
{
  long bitsize;
  long width;
  GLint viewport[4];
  void *bits; // RGB bits

  // Grab the current viewport
  glGetIntegerv(GL_VIEWPORT, viewport);

  width = viewport[2] * 3; // Real width of scanline
  width = (width + 3) & ~3; // Aligned to 4 bytes
  bitsize = width * viewport[3]; //  Size of bitmap, aligned

  if ((bits = (void *)calloc(bitsize, sizeof(GLubyte))) == NULL) {
    fl_message(" Couldn't allocate memory for screenshot ");
  }
  else {
    // Read pixels from the framebuffer
    //glFinish(); // Finish all OpenGL commands
    glPixelStorei(GL_PACK_ALIGNMENT, 4); // Force 4-byte alignment
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, bits);

    PNGImage screenshot(filename, (int)viewport[2], (int)viewport[3]);
    screenshot.openFileWrite();
    screenshot.initWriteStructs();
    screenshot.writeHeader();
    screenshot.writeImage(bits);
    screenshot.writeEnd();
    free(bits);
  }
}
