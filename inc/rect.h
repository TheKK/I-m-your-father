#ifndef RECT_H
#define RECT_H
#pragma once

#include <cstdint>

struct Rect {
	int x;
	int y;
	int w;
	int h;
};

bool hasIntersection(const Rect& A, const Rect& B);

#endif /* RECT_H */
