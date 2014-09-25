#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <Space.h>

Space::Space(std::istream &is)
{
	is >> dimension;
	if (!is) {
		dimension = 1;
		init("");
		return;
	}
	is.ignore();
	const int MAX = 80;
	char buf[MAX];
	is.get(buf, MAX);
	if (!is) {
		init("");
		return;
	}
	init(buf);
}

std::ostream &
operator<<(std::ostream &os, const Space &space)
{
	os << "#Space " << space.dim() << " " << space.name() << "\n";
	return os;
}
