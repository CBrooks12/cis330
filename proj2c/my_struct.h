/* This file should contain your struct definitions for Circle, Triangle, and 
   Rectangle */

typedef struct{
	double minX;
	double maxX;
	double minY;
	double maxY;
}Rectangle;

typedef struct{
	double minY;
	double maxY;
	double pt1X;
	double pt2X;
}Triangle;

typedef struct{
	double origin;
	double originY;
	double radius;
}Circle;
