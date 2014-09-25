#ifndef _MultiPoint_h
#define _MultiPoint_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Space.h>
#include <Map.h>
#include <GeomObj.h>

class ActualMultiPoint
	: public ActualGeomObj
{
protected:
	ActualMultiPoint(const Space &space_, int n_points_);
	ActualMultiPoint(const Space &space_, std::istream &is);
	ActualMultiPoint(const ActualMultiPoint &actual_multi_point);
	ActualMultiPoint(const Map &map,
		const ActualMultiPoint &actual_multi_point);
	~ActualMultiPoint(void);

	virtual ActualGeomObj *image(const Map &map) const;
	virtual void draw(Prims &prims) const;
	virtual void print(std::ostream &os) const;

	class IncompatibleMapDomain : public std::exception { };

private:
	Color color;
	int n_points;
	float *coords;		// single subscript for efficiency

	friend class MultiPoint;
	friend class ActualPolygon;
	friend class Polygon;
	friend class ActualPolyline;
	friend class Polyline;
};

inline
ActualMultiPoint::ActualMultiPoint(const Space &space_, int n_points_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  n_points(n_points_)
{
	coords = new float[n_points*space().dim()];
}

inline
ActualMultiPoint::ActualMultiPoint(const Map &map,
	const ActualMultiPoint &actual_multi_point)
	: ActualGeomObj(map.codomain()),
	  color(actual_multi_point.color),
	  n_points(actual_multi_point.n_points)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_multi_point.space())
		throw IncompatibleMapDomain();
#endif
	int n = actual_multi_point.space().dim(), m = space().dim();
	coords = new float[n_points*m];
	for (int j = 0; j < n_points; j++)
		map.apply(actual_multi_point.coords + j*n, coords + j*m);
}

inline
ActualMultiPoint::~ActualMultiPoint(void)
{
	delete [] coords;
}

inline ActualGeomObj *
ActualMultiPoint::image(const Map &map) const
{
	ActualMultiPoint *mapped = new ActualMultiPoint(map, *this);
	return (ActualGeomObj *) mapped;
}

class MultiPoint
	: public GeomObj
{
public:
	MultiPoint(const Space &space_, int n_points);
	MultiPoint(const Space &space_, std::istream &is);
	MultiPoint(const MultiPoint &multi_point);
	MultiPoint(const Map &map, const MultiPoint &multi_point);
	~MultiPoint(void);

	Color color(void) const;
	Color &color(void);

	const int n_points(void) const;

	const float * operator[](int index) const;
	float * operator[](int index);

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualMultiPoint * const actual_multi_point(void) const;
	void make_actual(void);
};

inline
MultiPoint::MultiPoint(const Space &space_, int n_points_)
	: GeomObj(new ActualMultiPoint(space_, n_points_))
{
}

inline
MultiPoint::MultiPoint(const Space &space_, std::istream &is)
	: GeomObj(new ActualMultiPoint(space_, is))
{
}

inline
MultiPoint::MultiPoint(const MultiPoint &multi_point)
	: GeomObj(multi_point)
{
}

inline
MultiPoint::MultiPoint(const Map &map, const MultiPoint &multi_point)
	: GeomObj(map, multi_point)
{
}

inline
MultiPoint::~MultiPoint(void)
{
}

inline ActualMultiPoint * const
MultiPoint::actual_multi_point(void) const
{
	return (ActualMultiPoint *) actual;
}

inline void
MultiPoint::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualMultiPoint(*actual_multi_point());
	}
}

inline Color
MultiPoint::color(void) const
{
	return actual_multi_point()->color;
}

inline Color &
MultiPoint::color(void)
{
	make_actual();
	return actual_multi_point()->color;
}

inline const int
MultiPoint::n_points(void) const
{
	return actual_multi_point()->n_points;
}

inline const float *
MultiPoint::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	return actual_multi_point()->coords + index*space().dim();
}

inline float *
MultiPoint::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= n_points())
		throw RangeViolation();
#endif
	make_actual();
	return actual_multi_point()->coords + index*space().dim();
}

#endif
