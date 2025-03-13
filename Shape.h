#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <optional>
#include "Hit.h"
#include "Ray.h"
#include "Material.h"
#include "Shape.h"
#include "Image.h"
#include "utils.h"
using namespace std;


/*
* Superclass of all types of shapes. Contains various methods common to all shapes
*/
class Shape 
{
protected:
	Color color;
	Image* texture = nullptr;		// represent a texture for texture mapping 
	Material mat;
	Image* mask = nullptr;			// represent mask for shape (what part of surface to be visible)
	Image* bumpMap = nullptr;		// represent bump map for shape
public:
	/*
	* Abstract method for finding an intersection between a shape and a given ray (if there exists one).
	* Each subclass will handle this method differently
	*/
	virtual optional<Hit> intersect(const Ray& ray) const = 0;

	/*
	* Method that reads the apperance properties of a shape.
	* This is the same for every subclass of shape
	*/
	void readApperance(istream& is);

	/*
	* Method that solves a quadratic equation, given an 'a', 'b', or 'c'.
	* This method returns both roots (ignoring the case of a single root), if they exist
	* or returns negative 'dummy' values when there is no real solution or only one solution.
	*/
	pair<float, float> quadratic(double a, double b, double c) const;

	/*
	* Method that takes a given 't' value and checks whether or not it represents
	* a viable hit, and returns said hit. Otherwise returns nullopt.
	* Each subclass has slightly different way of handling
	*/
	virtual optional<Hit> viableT(float t, const Ray& ray) const = 0;

	/*
	* Converts (x,y,z) coordinates of the point to (u,v) parameters (in the range [0..1])
	* based on the range of the corresponding shape's coordinates for the given point.
	* Each subclass will handle this differently
	*/
	virtual pair<float, float> texel_uv(const Point& pt) const = 0;

	/*
	* Given (u,v) coordinates of a hit point on the shape, selects what color to assign.
	* If no color map was loaded, returns solid color of shape, otherwise returns color from color map
	*/
	virtual Color selectColor(float u, float v) const = 0;

	/*
	* Given coordinates (u,v) of the hit point, computes if the point is visible or not.
	*/
	virtual bool isVisible(float u, float v) const  = 0;

	/*
	* Given hit point and it's normal this method alters the normal slightly 
	* for bump mapping purposes.
	*/
	virtual Unit bumpNormal(const Point& pt, const Unit& N, float u, float v) const = 0;
};

#endif