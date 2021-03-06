#ifndef _MobiusControl_h
#define _MobiusControl_h

#include <PanelButton.h>

class Mobius;

class Euclid2Button
	: private PanelButton
{
public:
	Euclid2Button(const Panel &parent_, Mobius &mobius_);

private:
	Mobius &mobius;

	void proc(void);
};

class Euclid3Button
	: private PanelButton
{
public:
	Euclid3Button(const Panel &parent_, Mobius &mobius_);

private:
	Mobius &mobius;

	void proc(void);
};

class MobiusButton
	: private PanelButton
{
public:
	MobiusButton(const Panel &panel);
	~MobiusButton(void);

private:
	Mobius *mobius;

	void proc(void);
};

#endif
