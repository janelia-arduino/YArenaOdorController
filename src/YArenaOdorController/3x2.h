// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_ODOR_CONTROLLER_3X2_CONSTANTS_H
#define Y_ARENA_ODOR_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace y_arena_odor_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum{ARM_COUNT=3};
enum{ODOR_PER_ARM_COUNT=3};

extern const size_t odor_pin_numbers[ARM_COUNT][ODOR_PER_ARM_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long initial_odors_setting_default[ARM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
