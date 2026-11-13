#include <Stonefish/core/SimulationManager.h>

class avoe_sf_simulation_manager : public sf::SimulationManager {


public:
    	avoe_sf_simulation_manager(sf::Scalar stepsPerSecond);
    	void BuildScenario();
	void SimulationStepCompleted(sf::Scalar timeStep) override;

	avoe_sf_tardigrade_t avoe_shared_objects;
	char scenario_filename[64];
};
