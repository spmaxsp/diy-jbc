#include "display.h"

Menue::Menue(){
  submenue functions_menue = {
    "Functions",
    0,
    false,
    {
      {"Sleep D. (s)", 0, "i", 1, 3600},
      {"Sleep T. (C)", 0, "f", 0, 500},
      {"Hib. D. (s)", 0, "i", 1, 3600},
      {"Hib T. (C)", 0, "f", 0, 500}
    }
  };

  submenue pid_menue = {
    "PID",
    0,
    false,
    {
      {"KP", 0, "f", 0, 100},
      {"KI", 0, "f", 0, 100},
      {"KD", 0, "f", 0, 100}
    }
  };

  submenue temp_calib_menue = {
    "Temp. Calibration",
    0,
    false,
    {
      {"A", 0, "f", -100, 100},
      {"B", 0, "f", -100, 100},
      {"C", 0, "f", -100, 100},
    }
  };

  menue menue_structure = {
    "Main Menue",
    0,
    false,
    {functions_menue,pid_menue,temp_calib_menue}
  };
}

