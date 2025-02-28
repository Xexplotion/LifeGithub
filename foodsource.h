#include "agent.h"
#include <iostream>
#include <vector>

class FoodSource {
    public:
        bool isOccupied;
        int availableFruit;
        std::vector<Agent> occupants;

        FoodSource() : availableFruit(1) {};

        void AddOccupants(Agent occupant1, Agent occupant2) {
            if(occupants.size() >= 2) {
                std::cout << "There are already 2 occupants! Try again on another source." << std::endl;
                return;
            }
            occupants.push_back(occupant1);
            occupants.push_back(occupant2);
            isOccupied = true;
        }
        
        void Step() {
            if(!isOccupied) return;
            int randomNumber = (std::rand() % 2);
            //std::cout << "Agent: " << randomNumber << std::endl;
            if(randomNumber == 0) { occupants.front().Feed(availableFruit); }
            if(randomNumber == 1) { occupants.back().Feed(availableFruit); }
            return;
        }
};