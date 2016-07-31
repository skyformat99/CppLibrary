#ifndef SIMULATION_H
#define SIMULATION_H

#include <QtCore>
#include <ralph/simulation/data/simulationdescription.h>

namespace ralph {
    namespace simulation {
        class Simulation
        {
        public:
            Simulation(SimulationDescription description);
        };
    }
}

#endif // SIMULATION_H
