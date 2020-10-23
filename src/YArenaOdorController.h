// ----------------------------------------------------------------------------
// YArenaValveController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_VALVE_CONTROLLER_H
#define Y_ARENA_VALVE_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "YArenaValveController/Constants.h"


class YArenaValveController : public ModularDeviceBase
{
public:
  YArenaValveController();
  virtual void setup();

  typedef Array<long,y_arena_valve_controller::constants::ARM_COUNT> Valves;

  Valves getValvesOpen();
  void setValvesOpen(Valves valves);
  void setAllValvesClosed();

private:
  modular_server::Pin pins_[y_arena_valve_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[y_arena_valve_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[y_arena_valve_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[y_arena_valve_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[y_arena_valve_controller::constants::CALLBACK_COUNT_MAX];

  Valves valves_open_;

  Valves jsonArrayToValves(ArduinoJson::JsonArray json_array);

  void setArmValveOpen(size_t arm,
    size_t valve);
  void setArmValveOutputClosed(size_t arm,
    size_t valve);
  void setArmValveOutputOpen(size_t arm,
    size_t valve);
  void setAllArmValveOutputsClosed(size_t arm);
  void initializeValves();

  // Handlers
  void getValvesOpenHandler();
  void setValvesOpenHandler();
  void setAllValvesClosedHandler(modular_server::Pin * pin_ptr);

};

#endif
