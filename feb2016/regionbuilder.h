#ifndef __REGION_BUILDER_H
#define __REGION_BUILDER_H

#include "region.h"

class RegionBuilder
{
public:
	static Region *buildRegion(int regionSize);
private:
	static Region *buildTiny();
	static Region *buildSmall();
	static Region *buildMedium();
	static Region *buildLarge();
};

#endif
