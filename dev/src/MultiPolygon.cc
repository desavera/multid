#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <ColorArray.h>
#include <CoordsArray.h>
#include <Prims.h>
#include <MultiPolygon.h>

ActualMultiPolygon::ActualMultiPolygon(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  modified(1),
	  coords_array(0),
	  color_array(0)
{
	const int MAX = 80;
	char buf[MAX];

	is >> color;
	if (!is)
		color = Color::FOREGROUND;
	for ( ; ; ) {
		is >> buf;
		if (!is) return;
		if (strncmp(buf, Polygon::name, MAX) == 0) {
			Polygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, "#end", MAX) == 0) {
			is.getline(buf, MAX);
			return;
		}
		else {
			is.clear( std::ios::badbit | is.rdstate() );
			return;
		}
	}
}

ActualMultiPolygon::~ActualMultiPolygon(void)
{
	delete color_array;
	delete [] coords_array;
}

void
ActualMultiPolygon::draw(Prims &prims) const
{
//	prims.edge_color(color);
	if (modified)
		((ActualMultiPolygon * const) this)->update();
	if (! list.null())
		prims.multipolygon(list.n_geom_objs(),
			coords_array, *color_array);
}

void
ActualMultiPolygon::print(std::ostream &os) const
{
	os << MultiPolygon::name << " " << color << "\n";
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).print(os);
	os << "#end of MultiPolygon\n";
}

void
ActualMultiPolygon::update(void)
{
	modified = 0;
	delete [] coords_array;
	coords_array = 0;
	delete color_array;
	color_array = 0;

	if (list.null())
		return;

	coords_array = new CoordsArray[list.n_geom_objs()];
	color_array = new ColorArray(list.n_geom_objs());

	CoordsArray *ca = coords_array;
	int i = 0;
	for (Pix p = list.first(); p != 0; list.next(p), ca++, i++) {
		const Polygon &pgon = (Polygon &) list(p);
		ca->init(pgon.space().dim(), pgon.n_points(), pgon.coords());
		color_array->set(i, pgon.color());
	}
}

const char * const MultiPolygon::name = "#MultiPolygon";

void
MultiPolygon::empty(void)
{
	make_actual();
	actual_multi_polygon()->list.empty();
	actual_multi_polygon()->modified = 1;
}
