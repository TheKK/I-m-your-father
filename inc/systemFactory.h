#ifndef SYSTEM_FACTOR_H
#define SYSTEM_FACTOR_H
#pragma once

#include <string>
#include <memory>

#include "system.h"

namespace SystemFactory
{
	System* build(const std::string& configFile);
}

#endif /* SYSTEM_FACTOR_H */
