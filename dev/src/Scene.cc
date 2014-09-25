#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <Scene.h>
#include <Bond.h>
#include <BoundingBox.h>
#include <MultiPoint.h>
#include <MultiPolygon.h>
#include <MultiPolyline.h>
#include <Point.h>
#include <Polygon.h>
#include <Polyline.h>
#include <Arrow.h>

ActualScene::~ActualScene(void)
{
}

ActualScene::ActualScene(const Space &space_, std::istream &is)
	: ActualGeomObj(space_)
{
	const int MAX = 80;
	char buf[MAX];

	for ( ; ; ) {
		is >> buf;
		if (!is) return;
		if (strncmp(buf, Bond::name, MAX) == 0) {
			Bond obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, BoundingBox::name, MAX) == 0) {
			BoundingBox obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, MultiPoint::name, MAX) == 0) {
			MultiPoint obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, MultiPolygon::name, MAX) == 0) {
			MultiPolygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, MultiPolyline::name, MAX) == 0) {
			MultiPolyline obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, Point::name, MAX) == 0) {
			Point obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, Polygon::name, MAX) == 0) {
			Polygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, Polyline::name, MAX) == 0) {
			Polyline obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, Scene::name, MAX) == 0) {
			Scene obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (strncmp(buf, Arrow::name, MAX) == 0) {
			Arrow obj(space(), is);
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

void
ActualScene::draw(Prims &prims) const
{
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).draw(prims);
}

void
ActualScene::print(std::ostream &os) const
{
	os << Scene::name << "\n";
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).print(os);
	os << "#end of Scene\n";
}

Scene::~Scene(void)
{
}

void
Scene::empty(void)
{
	make_actual();
	actual_scene()->list.empty();
}

void
Scene::join(const Scene &scene)
{
#ifdef ERROR_CHECKING
	if (&space() != &scene.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.append(scene.actual_scene()->list);
}

void
Scene::add(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.append(geom_obj);
}

void
Scene::del(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.del(geom_obj);
}

void
Scene::del_last(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.del_last(geom_obj);
}

const char * const Scene::name = "#Scene";
