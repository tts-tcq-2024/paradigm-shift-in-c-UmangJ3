#include "messages.h"

Messages messages[] = {
    {
        {"Temperature is out of range!", "Temperatur ist außerhalb des Bereichs!"},
        {"Warning: Temperature nearing lower limit", "Warnung: Temperatur nähert sich dem unteren Grenzwert"},
        {"Warning: Temperature nearing upper limit", "Warnung: Temperatur nähert sich dem oberen Grenzwert"}
    },
    {
        {"State of Charge is out of range!", "Ladezustand ist außerhalb des Bereichs!"},
        {"Warning: State of Charge nearing lower limit", "Warnung: Ladezustand nähert sich dem unteren Grenzwert"},
        {"Warning: State of Charge nearing upper limit", "Warnung: Ladezustand nähert sich dem oberen Grenzwert"}
    },
    {
        {"Charge Rate is too high!", "Laderate ist zu hoch!"},
        {"", ""},
        {"Warning: Charge Rate nearing upper limit", "Warnung: Laderate nähert sich dem oberen Grenzwert"}
    }
};

