// ----------------------------------------------------------------------------
// YArenaOdorController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_ODOR_CONTROLLER_H
#define Y_ARENA_ODOR_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "YArenaOdorController/Constants.h"


class YArenaOdorController : public ModularDeviceBase
{
public:
  YArenaOdorController();
  virtual void setup();

  typedef Array<long,y_arena_odor_controller::constants::ARM_COUNT> ArenaOdors;

  ArenaOdors getArenaOdors();
  void setArenaOdors(ArenaOdors arena_odors);

private:
  modular_server::Pin pins_[y_arena_odor_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[y_arena_odor_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[y_arena_odor_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[y_arena_odor_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[y_arena_odor_controller::constants::CALLBACK_COUNT_MAX];

  ArenaOdors arena_odors_;

  ArenaOdors jsonArrayToArenaOdors(ArduinoJson::JsonArray json_array);

  void setArmOdor(size_t arm,
    size_t odor);
  void setArmOdorValveClosed(size_t arm,
    size_t odor);
  void setArmOdorValveOpen(size_t arm,
    size_t odor);
  void setAllArmOdorValvesClosed(size_t arm);
  void initializeArenaOdors();

  // Handlers
  void getArenaOdorsHandler();
  void setArenaOdorsHandler();

};

#endif
