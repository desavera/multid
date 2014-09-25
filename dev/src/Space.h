#ifndef _Space_h
#define _Space_h
#ifdef __GNUC__
#pragma interface
#endif

#include <cstring>
#include <iostream>

class Space
{
public:
	Space(const char *name_, int dim_);
	Space(std::istream &is);
	~Space(void);

	int dim(void) const;
	const char *name(void) const;

private:
	void init(const char *name_);

	int dimension;
	char *space_name;

	Space(const Space &space);		// Do not define.
	Space &operator=(const Space &space);	// Do not define.
};

std::ostream &
operator<<(std::ostream &os, const Space &space);

inline void
Space::init(const char *name_)
{
	int n = strlen(name_) + 1;
	space_name = new char[n];
	(void) strncpy(space_name, name_, n);
}

inline
Space::Space(const char *name_, int dim_)
	: dimension(dim_)
{
	init(name_);
}

inline
Space::~Space(void)
{
	delete [] space_name;
}

inline int
Space::dim(void) const
{
	return dimension;
}

inline const char *
Space::name(void) const
{
	return space_name;
}

#endif
