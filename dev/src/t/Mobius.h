#ifndef _Mobius_h
#define _Mobius_h

#include <View2d.h>
#include <Maps.h>
#include <MobiusControl.h>

class Euclid2;
class Euclid3;

class Mobius
	: public View2d
{
public:
	Mobius(const Frame &parent);
	~Mobius(void);

	static Space mobius_space;

	void button_proc(Button button, float x, float y);
	void drag_proc(Button button, float x, float y);
	void leftkey_proc(int key, float x, float y);

private:
	Euclid2 *euclid2;
	BlowUpCollapsingMap collapsing;
	Euclid3 *euclid3;
	BlowUpImbeddingMap imbedding;

	Euclid2Button euclid2_button;
	Euclid3Button euclid3_button;

	void update(GeomObj &geom_obj);

	friend class Euclid2Button;
	friend class Euclid3Button;
};

#endif
