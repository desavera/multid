#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <View3d.h>

inline void
View3d::set_bbox(const Bounds3d &bounds3d)
{
	bbox.corner1(0) = bounds3d.xmin;
	bbox.corner1(1) = bounds3d.ymin;
	bbox.corner1(2) = bounds3d.zmin;
	bbox.corner2(0) = bounds3d.xmax;
	bbox.corner2(1) = bounds3d.ymax;
	bbox.corner2(2) = bounds3d.zmax;
}

inline void
View3d::init(void)
{
#ifdef ERROR_CHECKING
	if (space().dim() != 3)
		throw WrongDimension();
#endif
	display_label(space().name());

	Bounds3d bounds3d = GWin3d::bounds();
	set_bbox(bounds3d);
}

View3d::View3d(const Space &space, const Frame &parent,
		int panel_height, int x, int y, int height, int width)
	: GWin3d(parent, panel_height, x, y, height, width),
	  Scene(space),
	  bbox(space)
{
	init();
}

View3d::View3d(const Scene &scene_, const Frame &parent,
		int panel_height, int x, int y, int height, int width)
	: GWin3d(parent, panel_height, x, y, height, width),
	  Scene(scene_),
	  bbox(scene_.space())
{
	init();
}

View3d::View3d(const Map &map, const Scene &scene_, const Frame &parent,
		int panel_height, int x, int y, int height, int width)
	: GWin3d(parent, panel_height, x, y, height, width),
	  Scene(map, scene_),
	  bbox(map.codomain())
{
	init();
}

View3d::~View3d(void)
{
}

void
View3d::bounds(const Bounds3d &bounds3d)
{
	GWin3d::bounds(bounds3d);
	set_bbox(bounds3d);
}

const Bounds3d &
View3d::bounds(void) const
{
	return GWin3d::bounds();
}

void
View3d::empty(void)
{
	prims().clear();
	bbox.draw(prims());
	Scene::empty();
}

void
View3d::join(const Scene &scene_)
{
	scene_.draw(prims());
	bbox.draw(prims());
	Scene::join(scene_);
}

void
View3d::add(const GeomObj &geom_obj)
{
	geom_obj.draw(prims());
	bbox.draw(prims());
	Scene::add(geom_obj);
}

void
View3d::del(const GeomObj &geom_obj)
{
	Scene::del(geom_obj);
	prims().clear();
	repaint_proc();
}

void
View3d::del_last(const GeomObj &geom_obj)
{
	Scene::del_last(geom_obj);
	prims().clear();
	repaint_proc();
}

void
View3d::repaint_proc(void)
{
	Scene::draw(prims());
	bbox.draw(prims());
}

std::ostream &
operator<<(std::ostream &os, const View3d &view3d)
{
	view3d.print(os);
	return os;
}
