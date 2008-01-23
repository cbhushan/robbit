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
*	VideoDump.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Saves the current running simulation as video in AVI format
*	[ Currently unstable ]
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void video_dump(int mode)		// Records a video
							// mode == 1,2,3 => start,record,stop respectively
{
   unsigned char *image;
   int cv_i;
   int cv_j;
   int i;

   /* Allocate our buffer for the image */
   if ((image = (unsigned char*)malloc(3*width*height*sizeof(char))) == NULL)
   {
   	cout<<"Failed to allocate memory for image\nCould not save image!\n";
   }

   glPixelStorei(GL_PACK_ALIGNMENT,1);

   /* Copy the image into our buffer */
   glReadBuffer(GL_FRONT);
   glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,image);

   capture = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 4);

	capture_height		= capture->height;
	capture_width		= capture->width;
	capture_step		= capture->widthStep;
	capture_channels	= capture->nChannels;
	capture_data		= (uchar *)capture->imageData;

	for(cv_i=0;cv_i<capture_height;cv_i++)
	for(cv_j=0;cv_j<capture_width ;cv_j++)
	{
		capture_data[cv_i*capture_step+cv_j*capture_channels+2] = image[3*(capture_height-cv_i)*width+3*cv_j+0];
		capture_data[cv_i*capture_step+cv_j*capture_channels+1] = image[3*(capture_height-cv_i)*width+3*cv_j+1];
		capture_data[cv_i*capture_step+cv_j*capture_channels+0] = image[3*(capture_height-cv_i)*width+3*cv_j+2];
	}

	switch(mode)
	{
	case 1:
		sprintf(video_save_name, "capture_%d_%d_%d.avi", (int)(current.time), (int)theta, (int)phi);
		cout<<video_save_name<<endl;
		writer = cvCreateVideoWriter(video_save_name,-1,fps,cvSize(frameW,frameH));
		break;
	case 2:
		for(i = 0; i < 10; ++i)
			cvWriteFrame(writer,capture);
		break;
	case 3:
		cvWriteFrame(writer,capture);
		cvReleaseVideoWriter(&writer);
		cout<<"\n......video recorded"<<endl;
		break;
	}
}
