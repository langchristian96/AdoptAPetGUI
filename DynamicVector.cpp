#include "DynamicVector.h"


void testBonus()
{
	DynamicVector<Dog> dgs;
	Dog d{ "metis","testname",12,"blabla" };

	Dog d2{ "metis","testname2",12,"blabla" };
	dgs = dgs + d;
	assert(dgs.getSize() == 1);
	dgs = d2 + dgs;
	assert(dgs.getSize() == 2);

	dgs = dgs - d;
	assert(dgs.getSize() == 1);

	dgs = dgs - d2;
	assert(dgs.getSize() == 0);
}