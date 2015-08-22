#ifndef I_COLLIDAGLE_H
#define I_COLLIDAGLE_H

#include <vector>

#include "rect.h"

class ICollidable
{
public:
	virtual std::vector<Rect> getCollideRects(Rect& target) = 0;
};

#endif /* I_COLLIDAGLE_H */
