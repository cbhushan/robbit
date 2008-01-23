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
*	DistancePointLine.h  v 3.0 , 2007-12-05, 10:47:00 IST
*
*	Returns 1 if the any robot has collided to a wall 
*	[ calculates the distance between center of the robot and wall ]
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef struct tagXY
{
    float X, Y;
}
XY;

float Magnitude( XY *Point1, XY *Point2 )
{
    XY Vector;
    Vector.X = Point2->X - Point1->X;
    Vector.Y = Point2->Y - Point1->Y;
    return (float)sqrt( Vector.X * Vector.X + Vector.Y * Vector.Y );
}

int DistancePointLine( XY *Point, XY *LineStart, XY *LineEnd )
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

