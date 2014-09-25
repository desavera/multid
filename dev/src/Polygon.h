#ifndef _Polygon_h
#define _Polygon_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <MultiPoint.h>

class ActualPolygon
	: public ActualMultiPoint
{
protected:
	ActualPolygon(const Space &space_, int n_points_);
	ActualPolygon(const Space &space_, std::istream &is);
	ActualPolygon(const ActualPolygon &actual_polygon);
	ActualPolygon(const Map &map, const ActualPolygon &actual_polygon);
	~ActualPolygon(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	friend class Polygon;
};

inline
ActualPolygon::ActualPolygon(const Space &space_, int n_points_)
	: ActualMultiPoint(space_, n_points_)
{
}

inline
ActualPolygon::ActualPolygon(const Space &space_, std::istream &is)
	: ActualMultiPoint(space_, is)
{
}

inline
ActualPolygon::ActualPolygon(const ActualPolygon &actual_polygon)
	: ActualMultiPoint(actual_polygon)
{
}

inline
ActualPolygon::ActualPolygon(const Map &map,
	const ActualPolygon &actual_polygon)
	: ActualMultiPoint(map, actual_polygon)
{
}

inline
ActualPolygon::~ActualPolygon(void)
{
}

inline ActualGeomObj *
ActualPolygon::image(const Map &map) const
{
	ActualPolygon *mapped = new ActualPolygon(map, *this);
	return (ActualGeomObj *) mapped;
}

class Polygon
	: public GeomObj
{
public:
	Polygon(const Space &space_, int n_points);
	Polygon(const Space &space_, std::istream &is);
	Polygon(const Polygon &polygon);
	Polygon(const Map &map, const Polygon &polygon);
	~Polygon(void);

	Color color(void) const;
	Color &color(void);

	const int n_points(void) const;

	const float * operator[](int index) const;
	float * operator[](int index);

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualPolygon * const actual_polygon(void) const;
	void make_actual(void);

	friend class ActualMultiPolygon;
	const float * coords(void) const;
};

inline
Polygon::Polygon(const Space &space_, int n_points_)
	: GeomObj(new ActualPolygon(space_, n_points_))
{
}

inline
Polygon::Polygon(const Space &space_, std::istream &is)
	: GeomObj(new ActualPolygon(space_, is))
{
}

inline
Polygon::Polygon(const Polygon &polygon)
	: GeomObj(polygon)
{
}

inline
Polygon::Polygon(const Map &map, const Polygon &polygon)
	: GeomObj(map, polygon)
{
}

inline
Polygon::~Polygon(void)
{
}

inline ActualPolygon * const
Polygon::actual_polygon(void) const
{
	return (ActualPolygon *) actual;
}

inline void
Polygon::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualPolygon(*actual_polygon());
	}
}

inline Color
Polygon::color(void) const
{
	return actual_polygon()->color;
}

inline Color &
Polygon::color(void)
{
	make_actual();
	return actual_polygon()->color;
}

inline const int
Polygon::n_points(void) const
{
	return actual_polygon()->n_points;
}

inline const float *
Polygon::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	return actual_polygon()->coords + index*space().dim();
}

inline float *
Polygon::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	make_actual();
	return actual_polygon()->coords + index*space().dim();
}

inline const float *
Polygon::coords(void) const
{
	return actual_polygon()->coords;
}

#endif
