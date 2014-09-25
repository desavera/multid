#ifndef _Arrow_h
#define _Arrow_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Space.h>
#include <Map.h>
#include <GeomObj.h>
#include <Point.h>

class ActualArrow
	: public ActualGeomObj
{
protected:
	ActualArrow(const Point &origin_);
	ActualArrow(const Space &space_, std::istream &is);
	ActualArrow(const ActualArrow &actual_arrow);
	ActualArrow(const Map &map, const ActualArrow &actual_arrow);
	~ActualArrow(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain : public std::exception { };
	class InappropriateDimension : public std::exception { };

private:
	Point origin;
	Color color;
	float *coords;		// single subscript for efficiency

	friend class Arrow;
};

inline
ActualArrow::ActualArrow(const Point &origin_)
	: ActualGeomObj(origin_.space()),
	  origin(origin_),
	  color(Color::FOREGROUND)
{
	coords = new float[space().dim()];
}

inline
ActualArrow::ActualArrow(const ActualArrow &actual_arrow)
	: ActualGeomObj(actual_arrow.space()),
	  origin(actual_arrow.origin),
	  color(actual_arrow.color)
{
	int size = space().dim();
	coords = new float[size];
	for (int i = 0; i < size; i++)
		coords[i] = actual_arrow.coords[i];
}

inline
ActualArrow::ActualArrow(const Map &map, const ActualArrow &actual_arrow)
	: ActualGeomObj(map.codomain()),
	  origin(map, actual_arrow.origin),
	  color(actual_arrow.color)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_arrow.space())
		throw IncompatibleMapDomain();
#endif
	coords = new float[space().dim()];
	map.apply_derivative(actual_arrow.origin, actual_arrow.coords, coords);
}

inline
ActualArrow::~ActualArrow(void)
{
	delete [] coords;
}

inline ActualGeomObj *
ActualArrow::image(const Map &map) const
{
	ActualArrow *mapped = new ActualArrow(map, *this);
	return (ActualGeomObj *) mapped;
}

class Arrow
	: public GeomObj
{
public:
	Arrow(const Point &origin);
	Arrow(const Space &space_, std::istream &is);
	Arrow(const Arrow &arrow);
	Arrow(const Map &map, const Arrow &arrow);
	~Arrow(void);

	Point origin(void) const;

	Color color(void) const;
	Color &color(void);

	float operator[](int index) const;
	float &operator[](int index);

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualArrow * const actual_arrow(void) const;
	void make_actual(void);
};

inline
Arrow::Arrow(const Point &origin)
	: GeomObj(new ActualArrow(origin))
{
}

inline
Arrow::Arrow(const Space &space_, std::istream &is)
	: GeomObj(new ActualArrow(space_, is))
{
}

inline
Arrow::Arrow(const Arrow &arrow)
	: GeomObj(arrow)
{
}

inline
Arrow::Arrow(const Map &map, const Arrow &arrow)
	: GeomObj(map, arrow)
{
}

inline
Arrow::~Arrow(void)
{
}

inline ActualArrow * const
Arrow::actual_arrow(void) const
{
	return (ActualArrow *) actual;
}

inline void
Arrow::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualArrow(*actual_arrow());
	}
}

inline Point
Arrow::origin(void) const
{
	return actual_arrow()->origin;
}

inline Color
Arrow::color(void) const
{
	return actual_arrow()->color;
}

inline Color &
Arrow::color(void)
{
	make_actual();
	return actual_arrow()->color;
}

inline float
Arrow::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_arrow()->coords[index];
}

inline float &
Arrow::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_arrow()->coords[index];
}

#endif
