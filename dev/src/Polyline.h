#ifndef _Polyline_h
#define _Polyline_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <MultiPoint.h>

class ActualPolyline
	: public ActualMultiPoint
{
protected:
	ActualPolyline(const Space &space_, int n_points_);
	ActualPolyline(const Space &space_, std::istream &is);
	ActualPolyline(const ActualPolyline &actual_polyline);
	ActualPolyline(const Map &map, const ActualPolyline &actual_polyline);
	~ActualPolyline(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	friend class Polyline;
};

inline
ActualPolyline::ActualPolyline(const Space &space_, int n_points_)
	: ActualMultiPoint(space_, n_points_)
{
}

inline
ActualPolyline::ActualPolyline(const Space &space_, std::istream &is)
	: ActualMultiPoint(space_, is)
{
}

inline
ActualPolyline::ActualPolyline(const ActualPolyline &actual_polyline)
	: ActualMultiPoint(actual_polyline)
{
}

inline
ActualPolyline::ActualPolyline(const Map &map,
	const ActualPolyline &actual_polyline)
	: ActualMultiPoint(map, actual_polyline)
{
}

inline
ActualPolyline::~ActualPolyline(void)
{
}

inline ActualGeomObj *
ActualPolyline::image(const Map &map) const
{
	ActualPolyline *mapped = new ActualPolyline(map, *this);
	return (ActualGeomObj *) mapped;
}

class Polyline
	: public GeomObj
{
public:
	Polyline(const Space &space_, int n_points);
	Polyline(const Space &space_, std::istream &is);
	Polyline(const Polyline &polyline);
	Polyline(const Map &map, const Polyline &polyline);
	~Polyline(void);

	Color color(void) const;
	Color &color(void);

	const int n_points(void) const;

	const float * operator[](int index) const;
	float * operator[](int index);

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualPolyline * const actual_polyline(void) const;
	void make_actual(void);

	friend class ActualMultiPolyline;
	const float * coords(void) const;
};

inline
Polyline::Polyline(const Space &space_, int n_points_)
	: GeomObj(new ActualPolyline(space_, n_points_))
{
}

inline
Polyline::Polyline(const Space &space_, std::istream &is)
	: GeomObj(new ActualPolyline(space_, is))
{
}

inline
Polyline::Polyline(const Polyline &polyline)
	: GeomObj(polyline)
{
}

inline
Polyline::Polyline(const Map &map, const Polyline &polyline)
	: GeomObj(map, polyline)
{
}

inline
Polyline::~Polyline(void)
{
}

inline ActualPolyline * const
Polyline::actual_polyline(void) const
{
	return (ActualPolyline *) actual;
}

inline void
Polyline::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualPolyline(*actual_polyline());
	}
}

inline Color
Polyline::color(void) const
{
	return actual_polyline()->color;
}

inline Color &
Polyline::color(void)
{
	make_actual();
	return actual_polyline()->color;
}

inline const int
Polyline::n_points(void) const
{
	return actual_polyline()->n_points;
}

inline const float *
Polyline::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	return actual_polyline()->coords + index*space().dim();
}

inline float *
Polyline::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	make_actual();
	return actual_polyline()->coords + index*space().dim();
}

inline const float *
Polyline::coords(void) const
{
	return actual_polyline()->coords;
}

#endif
