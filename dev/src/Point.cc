#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Point.h>

ActualPoint::ActualPoint(const Space &space_, std::istream &is)
	: ActualGeomObj(space_)
{
	is >> color;
	if (!is)
		color = Color::FOREGROUND;
	coords = new float[space().dim()];
	float *coord = coords;
	for (int i = 0; i < space().dim(); i++)
		is >> *coord++;
}

ActualPoint::ActualPoint(const ActualPoint &actual_point)
	: ActualGeomObj(actual_point.space()),
	  color(actual_point.color)
{
	int size = space().dim();
	coords = new float[size];
	for (int i = 0; i < size; i++)
		coords[i] = actual_point.coords[i];
}

void
ActualPoint::draw(Prims &prims) const
{
//	prims.marker_color(color);
	CoordsArray coords_array(space().dim(), 1, coords);
	prims.multimarker(coords_array);
}

void
ActualPoint::print(std::ostream &os) const
{
	os << Point::name << " " << color << "\n";
	int lim = space().dim() - 1;
	float *coord = coords;
	for (int i = 0; i < lim; i++)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const char * const Point::name = "#Point";
