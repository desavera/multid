#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetView2d.h>

TargetView2d::TargetView2d(SourceScene &source_scene, const Map &map,
		View2d &view_2d__)
	: TargetView(source_scene, map, view_2d__),
	  view_2d_(view_2d__)
{
}

TargetView2d::~TargetView2d(void)
{
}
