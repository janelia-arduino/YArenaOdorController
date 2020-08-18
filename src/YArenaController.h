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


class YArenaController : public ServoController
{
public:
  YArenaController();
  virtual void setup();

  void expose(size_t channel);
  void exposeForDuration(size_t channel,
    size_t duration);
  void exposeAll();
  void exposeAllForDuration(size_t duration);
  void hide(size_t channel);
  void hideAll();
  bool exposed(size_t channel);
  void toggle(size_t channel);
  void toggleAll();

private:
  modular_server::Property properties_[y_arena_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[y_arena_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[y_arena_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[y_arena_controller::constants::CALLBACK_COUNT_MAX];

  bool exposed_[y_arena_controller::constants::CHANNEL_COUNT];
  long expose_durations_[y_arena_controller::constants::CHANNEL_COUNT];

  // Handlers
  void updateExposeOrHideAngleHandler(size_t channel);
  void exposeHandler();
  void exposeForDurationHandler();
  void exposeAllForDurationHandler();
  void hideHandler();
  void hideHandler(int channel);
  void waitThenHideHandler(int channel);
  void exposeAllHandler(modular_server::Pin * pin_ptr);
  void hideAllHandler(modular_server::Pin * pin_ptr);
  void toggleAllHandler(modular_server::Pin * pin_ptr);

};

#endif
