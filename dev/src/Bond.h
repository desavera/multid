#ifndef _Bond_h
#define _Bond_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Point.h>

class ActualBond
	: public ActualGeomObj
{
protected:
	ActualBond(const Space &space_);
	ActualBond(const Space &space_, std::istream &is);
	ActualBond(const ActualBond &actual_bond);
	ActualBond(const Map &map, const ActualBond &actual_bond);
	~ActualBond(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain : public std::exception { };

private:
	Color color;
	float *coords;		// single subscript for efficiency

	friend class Bond;
};

inline
ActualBond::ActualBond(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND)
{
	coords = new float[2*space().dim()];
}

inline
ActualBond::ActualBond(const Map &map, const ActualBond &actual_bond)
	: ActualGeomObj(map.codomain()),
	  color(actual_bond.color)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_bond.space())
		throw IncompatibleMapDomain();
#endif
	int n = actual_bond.space().dim(), m = space().dim();
	coords = new float[2*m];
	map.apply(actual_bond.coords, coords);
	map.apply(actual_bond.coords + n, coords + m);
}

inline
ActualBond::~ActualBond(void)
{
	delete [] coords;
}

inline ActualGeomObj *
ActualBond::image(const Map &map) const
{
	ActualBond *mapped = new ActualBond(map, *this);
	return (ActualGeomObj *) mapped;
}

class Bond
	: public GeomObj
{
public:
	Bond(const Space &space_);
	Bond(const Space &space_, std::istream &is);
	Bond(const Bond &bond);
	Bond(const Map &map, const Bond &bond);
	~Bond(void);

	Color color(void) const;
	Color &color(void);

	float beginning(int index) const;
	float &beginning(int index);
	float end(int index) const;
	float &end(int index);
	float length(void) const;
	Point midpoint(void) const;
	Point interpolant(float fraction) const;

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualBond * const actual_bond(void) const;
	void make_actual(void);
};

inline
Bond::Bond(const Space &space_)
	: GeomObj(new ActualBond(space_))
{
}

inline
Bond::Bond(const Space &space_, std::istream &is)
	: GeomObj(new ActualBond(space_, is))
{
}

inline
Bond::Bond(const Bond &bond)
	: GeomObj(bond)
{
}

inline
Bond::Bond(const Map &map, const Bond &bond)
	: GeomObj(map, bond)
{
}

inline
Bond::~Bond(void)
{
}

inline ActualBond * const
Bond::actual_bond(void) const
{
	return (ActualBond *) actual;
}

inline void
Bond::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualBond(*actual_bond());
	}
}

inline Color
Bond::color(void) const
{
	return actual_bond()->color;
}

inline Color &
Bond::color(void)
{
	make_actual();
	return actual_bond()->color;
}

inline float
Bond::beginning(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bond()->coords[index];
}

inline float&
Bond::beginning(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bond()->coords[index];
}

inline float
Bond::end(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bond()->coords[space().dim() + index];
}

inline float&
Bond::end(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bond()->coords[space().dim() + index];
}

#endif
