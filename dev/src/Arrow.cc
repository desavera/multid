#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Arrow.h>

const double sqrt3over10 = 0.17320508075688772935;

ActualArrow::ActualArrow(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  origin(space_)
{
	is >> color;
	if (!is)
		color = Color::FOREGROUND;
	const int MAX = 80;
	char buf[MAX];
	is >> buf;	// Point::name
	Point org(space_, is);
	origin = org;
	coords = new float[space().dim()];
	float *coord = coords;
	for (int i = 0; i < space().dim(); i++)
		is >> *coord++;
}

void
ActualArrow::draw(Prims &prims) const
{
//	prims.line_color(color);
	if (space().dim() == 2) {
		float c[10];

		c[0] = origin[0];
		c[1] = origin[1];
		c[2] = c[0] + coords[0];
		c[3] = c[1] + coords[1];
		c[4] = c[2] - sqrt3over10 * coords[0] + 0.1	    * coords[1];
		c[5] = c[3] - 0.1	  * coords[0] - sqrt3over10 * coords[1];
		c[6] = c[2] - sqrt3over10 * coords[0] - 0.1	    * coords[1];
		c[7] = c[3] + 0.1	  * coords[0] - sqrt3over10 * coords[1];
		c[8] = c[2];
		c[9] = c[3];

		CoordsArray coords_array(2, 5, c);
		prims.polyline(coords_array);
	}
	else if (space().dim() == 3) {
		float c[15];

		c[0]  = origin[0];
		c[1]  = origin[1];
		c[2]  = origin[2];
		c[3]  = c[0] + coords[0];
		c[4]  = c[1] + coords[1];
		c[5]  = c[2] + coords[2];
		c[6]  = c[3] - sqrt3over10 * coords[0] + 0.1	     * coords[1];
		c[7]  = c[4] - 0.1	   * coords[0] - sqrt3over10 * coords[1];
		c[8]  = c[5] - 0.1*coords[2];
		c[9]  = c[3] - sqrt3over10 * coords[0] - 0.1	     * coords[1];
		c[10] = c[4] + 0.1	   * coords[0] - sqrt3over10 * coords[1];
		c[11] = c[5] - 0.1*coords[2];
		c[12] = c[3];
		c[13] = c[4];
		c[14] = c[5];

		CoordsArray coords_array(3, 5, c);
		prims.polyline(coords_array);
	}
	else
		throw InappropriateDimension();
}

void
ActualArrow::print(std::ostream &os) const
{
	os << Arrow::name << " " << color << "\n";
	os << origin;
	int i, lim = space().dim() - 1;
	float *coord = coords;
	for (i = 0; i < lim; i++)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const char * const Arrow::name = "#Arrow";
