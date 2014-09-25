#ifndef _Euclid3_h
#define _Euclid3_h

#include <View3d.h>

class Euclid3
	: public View3d
{
public:
	Euclid3(const Frame &parent);

	static Space euclid3_space;

	void button_proc(Button button, float x, float y, float z);
	void drag_proc(Button button, float x, float y, float z);
};

#endif
