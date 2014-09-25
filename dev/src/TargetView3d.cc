#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetView3d.h>

TargetView3d::TargetView3d(SourceScene &source_scene, const Map &map,
		View3d &view_3d__)
	: TargetView(source_scene, map, view_3d__),
	  view_3d_(view_3d__)
{
}

TargetView3d::~TargetView3d(void)
{
}
