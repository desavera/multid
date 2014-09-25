#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <mathutil.h>
#include <CoordsArray.h>
#include <Prims.h>
#include <Bond.h>

ActualBond::ActualBond(const Space &space_, std::istream &is)
	: ActualGeomObj(space_)
{
	is >> color;
	if (!is)
		color = Color::FOREGROUND;
	coords = new float[2*space().dim()];
	float *coord = coords;
	for (int i = 0; i < 2*space().dim(); i++)
		is >> *coord++;
}

ActualBond::ActualBond(const ActualBond &actual_bond)
	: ActualGeomObj(actual_bond.space()),
	  color(actual_bond.color)
{
	int size = 2*space().dim();
	coords = new float[size];
	for (int i = 0; i < size; i++)
		coords[i] = actual_bond.coords[i];
}

void
ActualBond::draw(Prims &prims) const
{
//	prims.line_color(color);
	CoordsArray coords_array(space().dim(), 2, coords);
	prims.polyline(coords_array);
}

void
ActualBond::print(std::ostream &os) const
{
	os << Bond::name << " " << color << "\n";
	int i, lim = 2*space().dim() - 1;
	float *coord = coords;
	for (i = 0; i < lim; i++)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const char * const Bond::name = "#Bond";

float
Bond::length(void) const
{
	float dist = 0.;
	int dim = space().dim();
	float *coords = actual_bond()->coords;
	for (int i = 0; i < dim; i++)
		dist += sqr(coords[dim + i] - coords[i]);
	return sqrt(dist);
}

Point
Bond::midpoint(void) const
{
	Point middle(space());
	int dim = space().dim();
	float *coords = actual_bond()->coords;
	for (int i = 0; i < dim; i++)
		middle[i] = .5*(coords[i] + coords[dim + i]);
	return middle;
}

Point
Bond::interpolant(float fraction) const
{
	Point interp(space());
	int dim = space().dim();
	float *coords = actual_bond()->coords;
	for (int i = 0; i < dim; i++)
		interp[i] = (1.-fraction)*coords[i] + fraction*coords[dim + i];
	return interp;
}
