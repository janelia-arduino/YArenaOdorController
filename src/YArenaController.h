// ----------------------------------------------------------------------------
// YArenaController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_CONTROLLER_H
#define Y_ARENA_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "YArenaController/Constants.h"


class YArenaController : public ModularDeviceBase
{
public:
  YArenaController();
  virtual void setup();

  void setValve(size_t arm,
    size_t valve);

private:
  modular_server::Property properties_[y_arena_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[y_arena_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[y_arena_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[y_arena_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
