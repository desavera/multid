#ifndef _BoundingBox_h
#define _BoundingBox_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Space.h>
#include <Map.h>
#include <GeomObj.h>

class ActualBoundingBox
	: public ActualGeomObj
{
protected:
	ActualBoundingBox(const Space &space_);
	ActualBoundingBox(const Space &space_, std::istream &is);
	ActualBoundingBox(const ActualBoundingBox &actual_bounding_box);
	ActualBoundingBox(const Map &map,
		const ActualBoundingBox &actual_bounding_box);
	~ActualBoundingBox(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain : public std::exception { };
	class InappropriateDimension : public std::exception { };

private:
	Color color;
	float *corner1_coords, *corner2_coords;

	friend class BoundingBox;
};

inline
ActualBoundingBox::ActualBoundingBox(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND)
{
	corner1_coords = new float[space().dim()];
	corner2_coords = new float[space().dim()];
}

inline
ActualBoundingBox::ActualBoundingBox(const Map &map,
	const ActualBoundingBox &actual_bounding_box)
	: ActualGeomObj(map.codomain()),
	  color(actual_bounding_box.color)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_bounding_box.space())
		throw IncompatibleMapDomain();
#endif
	corner1_coords = new float[space().dim()];
	corner2_coords = new float[space().dim()];
	map.apply(actual_bounding_box.corner1_coords, corner1_coords);
	map.apply(actual_bounding_box.corner2_coords, corner2_coords);
}

inline
ActualBoundingBox::~ActualBoundingBox(void)
{
	delete [] corner1_coords;
	delete [] corner2_coords;
}

inline ActualGeomObj *
ActualBoundingBox::image(const Map &map) const
{
	ActualBoundingBox *mapped = new ActualBoundingBox(map, *this);
	return (ActualGeomObj *) mapped;
}

class BoundingBox
	: public GeomObj
{
public:
	BoundingBox(const Space &space_);
	BoundingBox(const Space &space_, std::istream &is);
	BoundingBox(const BoundingBox &bounding_box);
	BoundingBox(const Map &map, const BoundingBox &bounding_box);
	~BoundingBox(void);

	Color color(void) const;
	Color &color(void);

	float corner1(int index) const;
	float &corner1(int index);
	float corner2(int index) const;
	float &corner2(int index);

	static const char * const name;

	class RangeViolation : public std::exception { };

protected:
	ActualBoundingBox * const actual_bounding_box(void) const;
	void make_actual(void);
};

inline
BoundingBox::BoundingBox(const Space &space_)
	: GeomObj(new ActualBoundingBox(space_))
{
}

inline
BoundingBox::BoundingBox(const Space &space_, std::istream &is)
	: GeomObj(new ActualBoundingBox(space_, is))
{
}

inline
BoundingBox::BoundingBox(const BoundingBox &bounding_box)
	: GeomObj(bounding_box)
{
}

inline
BoundingBox::BoundingBox(const Map &map, const BoundingBox &bounding_box)
	: GeomObj(map, bounding_box)
{
}

inline
BoundingBox::~BoundingBox(void)
{
}

inline ActualBoundingBox * const
BoundingBox::actual_bounding_box(void) const
{
	return (ActualBoundingBox *) actual;
}

inline void
BoundingBox::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualBoundingBox(*actual_bounding_box());
	}
}

inline Color
BoundingBox::color(void) const
{
	return actual_bounding_box()->color;
}

inline Color &
BoundingBox::color(void)
{
	make_actual();
	return actual_bounding_box()->color;
}

inline float
BoundingBox::corner1(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bounding_box()->corner1_coords[index];
}

inline float &
BoundingBox::corner1(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bounding_box()->corner1_coords[index];
}

inline float
BoundingBox::corner2(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bounding_box()->corner2_coords[index];
}

inline float &
BoundingBox::corner2(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bounding_box()->corner2_coords[index];
}

#endif
