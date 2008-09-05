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

#include <stdio.h>
#include <PNG/png.h>

//! Class to store information of a PNG image
/*! It contains operations for opening/closing PNG files, reading/writing structs,
headers, writing image data, and other miscellaneous operations.
*/
class PNGImage {
public:
  PNGImage() : fp(NULL) {}
  PNGImage(char* _filename, int _width, int _height) 
    : filename(_filename), 
      fp(NULL),
      png_ptr(NULL), info_ptr(NULL),
      width(_width), height(_height) {}
  ~PNGImage();
	
  bool openFileRead();
  bool openFileWrite();
  bool isPNG(int bytesToCheck);
  bool initReadStructs();
  bool initWriteStructs();
  bool writeHeader();
  bool writeImage(void *bits);
  bool writeEnd();

private:
  char *filename;
  FILE* fp;
  png_structp png_ptr;
  png_infop info_ptr;
  long width, height;	
  png_byte* row;
  int bytes_per_pixel;
  long i,j;
  GLubyte *rgb;
  long width_para; // Real width of scanline
};

//! PNGImage Destructor
PNGImage::~PNGImage() {
  if (fp!=NULL) fclose(fp);
}

//! Open PNG file for read
/*! 
\return false, if already open, or due to other error; true, if file opened successfully
*/
bool PNGImage::openFileRead() {
  if (fp!=NULL) {
    printf("file already opened\n");
    return false;	// can't open an already opened file
  }
	
  fp = fopen(filename, "rb");
  if (!fp) {
    printf("couldn't open file %s for reading\n", filename);
    return false;			// couldn't open file
  }
  //  printf("opened file %s\n", filename);      
  return true;
}

//! Open PNG file for write
/*! 
\return false, if already open, or due to other error; true, if file opened successfully
*/
bool PNGImage::openFileWrite() {
  if (fp!=NULL) {
    printf("file already opened\n");
    return false;	// can't open an already opened file
  }
	
  fp = fopen(filename, "wb");	
  if (!fp) {
    printf("couldn't open file %s for writing\n", filename);
    return false;			// couldn't open file
  }	
  //  printf("opened file %s\n", filename);	
  return true;
}

//! Query if file is open and PNG
/*! 
\param bytesToCheck = 8, initial checkbytes for valid PNG file.
\return true, if file is a valid PNG file; false, if invalid, or due to other error;
*/
bool PNGImage::isPNG(int bytesToCheck = 8) {
  if (fp==NULL) {
    if (openFileRead() == false) return false;
  }
	
  if (bytesToCheck > 8) {
    bytesToCheck=8;
    printf("bytesToCheck set to 8.  It cannot be more than 8.\n");
  }
  else if (bytesToCheck < 1) {
    bytesToCheck=1;
    printf("bytesToCheck set to 1.  It cannot be less than 1.\n");
  }
	
  // todo: check that fp is at start of file.
	
  char header[8];	// 8 is than maximum size that can be checked.
	
  int retValue = fread(header, 1, bytesToCheck, fp);
  if (retValue != bytesToCheck) {
    printf("couldn't read %d bytes from file.\n", bytesToCheck);
  }
	
  // use library to check if it's a valid PNG file
  bool valid;
  valid = ( png_sig_cmp((png_byte*)header, 0, bytesToCheck) == 0);
	
  return valid;
}

//! Reads PNG structs
bool PNGImage::initReadStructs(){ 
  // initialise png_ptr
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,    // from png.h
				   NULL, // ptr to struct for user error funct.
				   NULL, // ptr to user error function
				   NULL);// ptr to usr warning function

  if (png_ptr == NULL) {
    printf("initReadStructs: png_ptr was not able to be initialised\n");
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    return false;
  }

  // initialise info_ptr
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    printf("initReadStructs: info_ptr was not able to be initialised\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    return false;
  }

  // note: there is no end_info variable because I don't know what
  // it's for yet.  But if we need one then it's memory allocation
  // should happen here (once a variable has been declared in the
  // class).

  return true;
}

//! Writes PNG structs
bool PNGImage::initWriteStructs() {
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
				    NULL, // ptr to user error struct
				    NULL, // ptr to user error function
				    NULL);// ptr to user warning function

  if (!png_ptr) {
    printf("initWriteStructs: failed to init png_ptr\n");
    png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
    return false;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    printf("initWriteStructs: failed to init info_ptr\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }

  // prepare for errors.  Can't call setjmp() before png_ptr has been
  // allocated because the data inside png_ptr is access by png_jmpbuf!
  if (setjmp(png_jmpbuf(png_ptr))) {  // png_jmpbuf is a macro in pngconf.h
    printf("initReadStructs: setjmp returned non-zero (i.e. an error occured.)\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }

  png_init_io(png_ptr, fp);
  return true;
}

//! Writes PNG header data
bool PNGImage::writeHeader() {
  // prepare for errors.
  if (setjmp(png_jmpbuf(png_ptr))) {  // png_jmpbuf is a macro in pngconf.h
    printf("writeHeader: setjmp returned non-zero (i.e. an error occured.)\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height,
	       8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
	       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);
  return true;
}

//! Writes PNG image data
bool PNGImage::writeImage( void *bits ) {

  // prepare for errors.
  if (setjmp(png_jmpbuf(png_ptr))) {  // png_jmpbuf is a macro in pngconf.h
    printf("writeImage: setjmp returned non-zero (i.e. an error occured.)\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }

  bytes_per_pixel = 3;
  width_para = width * 3; // Real width of scanline
  width_para = (width_para + 3) & ~3; // Aligned to 4 bytes

  row= (png_byte*) malloc(width*3*sizeof(png_byte));
  
  for (i=0; i<height; i++) {
    for (j=0, rgb=((GLubyte *)bits)+(height-i-1)*width_para; j<width; j++, rgb+=3) {
      row[j*3+0]=(int)rgb[0]; // red
      row[j*3+1]=(int)rgb[1]; // green
      row[j*3+2]=(int)rgb[2]; // blue
    }
    png_write_row(png_ptr, row);
  }
  free(row);
  return true;
}

//! Finish writing PNG file
bool PNGImage::writeEnd() {

  // prepare for errors.
  if (setjmp(png_jmpbuf(png_ptr))) {  // png_jmpbuf is a macro in pngconf.h
    printf("writeEnd: setjmp returned non-zero (i.e. an error occured.)\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }

  png_write_end(png_ptr, NULL);  // NULL because we don't need to
				 // write any comments, etc.

  png_destroy_write_struct(&png_ptr, &info_ptr);
  return true;
}
