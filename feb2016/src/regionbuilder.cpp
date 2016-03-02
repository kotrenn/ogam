#include "regionbuilder.h"

Region *RegionBuilder::buildRegion(int regionSize)
{
	Region *region;

	if (regionSize <= 1) region = buildSmall();
	if (regionSize >= 3) region = buildLarge();
	if (regionSize == 2) region = buildMedium();

	region->computeRotations();

	return region;
}

Region *RegionBuilder::buildTiny()
{
	Region *region = new Region(1);
	region->addLink(0, NORTH, 0);
	region->addLink(0, SOUTH, 0);
	region->addLink(0, WEST, 0);
	region->addLink(0, EAST, 0);

	return region;
}

Region *RegionBuilder::buildSmall()
{
	Region *region = new Region(5);
	
	region->addLink(0, NORTH, 1);
	region->addLink(0, SOUTH, 3);
	region->addLink(0, WEST, 2);
	region->addLink(0, EAST, 4);

	region->addLink(1, NORTH, 3);
	region->addLink(1, SOUTH, 0);
	region->addLink(1, WEST, 2);
	region->addLink(1, EAST, 4);

	region->addLink(2, NORTH, 3);
	region->addLink(2, SOUTH, 0);
	region->addLink(2, WEST, 4);
	region->addLink(2, EAST, 1);

	region->addLink(3, NORTH, 0);
	region->addLink(3, SOUTH, 1);
	region->addLink(3, WEST, 2);
	region->addLink(3, EAST, 4);

	region->addLink(4, NORTH, 0);
	region->addLink(4, SOUTH, 1);
	region->addLink(4, WEST, 3);
	region->addLink(4, EAST, 2);

	return region;
}

Region *RegionBuilder::buildMedium()
{
	Region *region = new Region(10);

	region->addLink(0, NORTH, 5);
	region->addLink(0, SOUTH, 9);
	region->addLink(0, WEST, 3);
	region->addLink(0, EAST, 2);

	region->addLink(1, NORTH, 5);
	region->addLink(1, SOUTH, 3);
	region->addLink(1, WEST, 4);
	region->addLink(1, EAST, 6);

	region->addLink(2, NORTH, 0);
	region->addLink(2, SOUTH, 6);
	region->addLink(2, WEST, 4);
	region->addLink(2, EAST, 7);

	region->addLink(3, NORTH, 0);
	region->addLink(3, SOUTH, 7);
	region->addLink(3, WEST, 8);
	region->addLink(3, EAST, 1);

	region->addLink(4, NORTH, 8);
	region->addLink(4, SOUTH, 2);
	region->addLink(4, WEST, 9);
	region->addLink(4, EAST, 1);

	region->addLink(5, NORTH, 1);
	region->addLink(5, SOUTH, 0);
	region->addLink(5, WEST, 9);
	region->addLink(5, EAST, 6);

	region->addLink(6, NORTH, 5);
	region->addLink(6, SOUTH, 7);
	region->addLink(6, WEST, 1);
	region->addLink(6, EAST, 2);

	region->addLink(7, NORTH, 2);
	region->addLink(7, SOUTH, 3);
	region->addLink(7, WEST, 8);
	region->addLink(7, EAST, 6);

	region->addLink(8, NORTH, 3);
	region->addLink(8, SOUTH, 4);
	region->addLink(8, WEST, 9);
	region->addLink(8, EAST, 7);

	region->addLink(9, NORTH, 5);
	region->addLink(9, SOUTH, 8);
	region->addLink(9, WEST, 0);
	region->addLink(9, EAST, 4);
	
	return region;
}

Region *RegionBuilder::buildLarge()
{
	Region *region = new Region(20);

	region->addLink(0, NORTH, 17);
	region->addLink(0, SOUTH, 2);
	region->addLink(0, WEST, 5);
	region->addLink(0, EAST, 1);

	region->addLink(1, NORTH, 18);
	region->addLink(1, SOUTH, 3);
	region->addLink(1, WEST, 0);
	region->addLink(1, EAST, 6);

	region->addLink(2, NORTH, 0);
	region->addLink(2, SOUTH, 16);
	region->addLink(2, WEST, 9);
	region->addLink(2, EAST, 4);

	region->addLink(3, NORTH, 1);
	region->addLink(3, SOUTH, 19);
	region->addLink(3, WEST, 4);
	region->addLink(3, EAST, 7);

	region->addLink(4, NORTH, 15);
	region->addLink(4, SOUTH, 8);
	region->addLink(4, WEST, 2);
	region->addLink(4, EAST, 3);

	region->addLink(5, NORTH, 12);
	region->addLink(5, SOUTH, 0);
	region->addLink(5, WEST, 14);
	region->addLink(5, EAST, 10);

	region->addLink(6, NORTH, 13);
	region->addLink(6, SOUTH, 1);
	region->addLink(6, WEST, 10);
	region->addLink(6, EAST, 11);

	region->addLink(7, NORTH, 11);
	region->addLink(7, SOUTH, 14);
	region->addLink(7, WEST, 3);
	region->addLink(7, EAST, 12);

	region->addLink(8, NORTH, 4);
	region->addLink(8, SOUTH, 10);
	region->addLink(8, WEST, 13);
	region->addLink(8, EAST, 12);

	region->addLink(9, NORTH, 14);
	region->addLink(9, SOUTH, 13);
	region->addLink(9, WEST, 11);
	region->addLink(9, EAST, 2);

	region->addLink(10, NORTH, 15);
	region->addLink(10, SOUTH, 8);
	region->addLink(10, WEST, 5);
	region->addLink(10, EAST, 6);

	region->addLink(11, NORTH, 16);
	region->addLink(11, SOUTH, 7);
	region->addLink(11, WEST, 6);
	region->addLink(11, EAST, 9);

	region->addLink(12, NORTH, 7);
	region->addLink(12, SOUTH, 5);
	region->addLink(12, WEST, 8);
	region->addLink(12, EAST, 17);

	region->addLink(13, NORTH, 9);
	region->addLink(13, SOUTH, 6);
	region->addLink(13, WEST, 18);
	region->addLink(13, EAST, 8);

	region->addLink(14, NORTH, 19);
	region->addLink(14, SOUTH, 9);
	region->addLink(14, WEST, 7);
	region->addLink(14, EAST, 5);

	region->addLink(15, NORTH, 4);
	region->addLink(15, SOUTH, 10);
	region->addLink(15, WEST, 19);
	region->addLink(15, EAST, 16);

	region->addLink(16, NORTH, 15);
	region->addLink(16, SOUTH, 17);
	region->addLink(16, WEST, 11);
	region->addLink(16, EAST, 2);

	region->addLink(17, NORTH, 12);
	region->addLink(17, SOUTH, 0);
	region->addLink(17, WEST, 18);
	region->addLink(17, EAST, 16);

	region->addLink(18, NORTH, 13);
	region->addLink(18, SOUTH, 1);
	region->addLink(18, WEST, 19);
	region->addLink(18, EAST, 17);

	region->addLink(19, NORTH, 15);
	region->addLink(19, SOUTH, 18);
	region->addLink(19, WEST, 3);
	region->addLink(19, EAST, 14);

	return region;
}
