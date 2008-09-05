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

//! Contains x, y coordinates of a generic point. 
/*!
*/
typedef struct tagXY
{
    float X, Y;
}
XY;

//! Distance between two points 
/*!
\param Point1 XY point
\param Point2 XY point
\return Distance between two points as float
*/
float Magnitude( XY *Point1, XY *Point2 )
{
    XY Vector;
    Vector.X = Point2->X - Point1->X;
    Vector.Y = Point2->Y - Point1->Y;
    return (float)sqrt( Vector.X * Vector.X + Vector.Y * Vector.Y );
}

//! Evaluates if a bot lies on a line given by two points
/*!
\param Point XY point, center of robot
\param LineStart XY point, marks a point on the line
\param LineEnd XY point, marks a second point on the line
\return 0, if bot is not on the line; 1, if it is.
*/
int DistancePointLine( XY *Point, XY *LineStart, XY *LineEnd, float radius_of_robot )
{
    float LineMag,x1,x2,y1,y2;
    float U;
 
    LineMag = Magnitude( LineEnd, LineStart );
 
    U = ( ( ( Point->Y - LineStart->Y ) * ( LineEnd->X - LineStart->X ) ) -
        ( ( Point->X - LineStart->X ) * ( LineEnd->Y - LineStart->Y ) ) ) /LineMag ;
 
	x1= ((LineStart->X > LineEnd->X)?LineStart->X:LineEnd->X)+radius_of_robot;
	x2= ((LineStart->X < LineEnd->X)?LineStart->X:LineEnd->X)-radius_of_robot;
	y1= ((LineStart->Y > LineEnd->Y)?LineStart->Y:LineEnd->Y)+radius_of_robot;
	y2= ((LineStart->Y < LineEnd->Y)?LineStart->Y:LineEnd->Y)-radius_of_robot;

	if(U<0)
		U= (-1)*U;

	if( (U<radius_of_robot) &&
		(Point->X < x1) && (Point->X > x2) &&
		(Point->Y < y1) && (Point->Y > y2))
		return 1;
	else
		return 0;
}
