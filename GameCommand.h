using namespace std;
#include "Model.h"
#include "Point2D.h"
#include "View.h"

#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

  //Functions to be used in main
  void DoMoveCommand(Model& model, int pokemon_id, Point2D p1);
  void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id);
  void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id);
  void DoStopCommand(Model& model, int pokemon_id);
  void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units);
  void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int training_units);
  void DoGoCommand(Model& model, View& view);
  void DoRunCommand(Model& model, View& view);
  void DoBattleCommand(Model& model, int pokemon_id, int rival_id);
  void DoMoveToArenaCommand(Model& model, int pokemon_id, int arena_id);
  void DoSaveCommand (Model& model, string& file);
  void DoReadCommand (Model& model, string& file);
#endif // GAMECOMMAND_H