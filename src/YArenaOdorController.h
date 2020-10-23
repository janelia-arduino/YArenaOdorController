// ----------------------------------------------------------------------------
// YArenaOdorController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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

  typedef Array<long,y_arena_odor_controller::constants::ARM_COUNT> Odors;

  Odors getOdorsOpen();
  void setOdorsOpen(Odors odors);
  void setAllOdorsClosed();

private:
  modular_server::Pin pins_[y_arena_odor_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[y_arena_odor_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[y_arena_odor_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[y_arena_odor_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[y_arena_odor_controller::constants::CALLBACK_COUNT_MAX];

  Odors odors_open_;

  Odors jsonArrayToOdors(ArduinoJson::JsonArray json_array);

  void setArmOdorOpen(size_t arm,
    size_t odor);
  void setArmOdorOutputClosed(size_t arm,
    size_t odor);
  void setArmOdorOutputOpen(size_t arm,
    size_t odor);
  void setAllArmOdorOutputsClosed(size_t arm);
  void initializeOdors();

  // Handlers
  void getOdorsOpenHandler();
  void setOdorsOpenHandler();
  void setAllOdorsClosedHandler(modular_server::Pin * pin_ptr);

};

#endif
