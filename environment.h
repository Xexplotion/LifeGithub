#include "foodsource.h"
#include <vector>
#include <algorithm>
#include <random>


class Environment {
    public:
        std::vector<Agent> agents;
        std::vector<FoodSource> foodSources;
        bool isDay;
        void Step() {
            if(!isDay) Day();
            else Night();
            for (Agent agent : agents) {
                 if(!agent.isAlive) RemoveAgentByID(agents, agent.ID);   
            }
        }
        void Day() {
            isDay = true;

            auto pairs = ShuffleAgents(agents);
            for (const auto& pair : pairs) {
                FoodSource* nextNonOccupied = findNextNonOccupied(foodSources);

                if (nextNonOccupied) {
                    std::cout << "Found a non-occupied food source!" << std::endl;
                    std::cout << "Adding agent with id of " << pair.first.ID << " to food source." << std::endl;
                    std::cout << "Adding agent with id of " << pair.second.ID << " to food source." << std::endl;
                    nextNonOccupied->AddOccupants(pair.first, pair.second);
                } else {
                    std::cout << "No available food sources." << std::endl;
                }
            }

            for(auto& source : foodSources) {
                source.Step();
            }
        }
        void Night() {
            isDay = false;
            for (Agent agent : agents) {
                if(!agent.isAlive) RemoveAgentByID(agents, agent.ID);   
                agent.Starve(1);
                if(agent.foodAmount >= 1) {
                    std::cout << "Makething children" << std::endl;
                    AddAgents(Agent());
                }
            }
        }
        template<typename... Agent>
        void AddAgents(Agent... toBeAdded) {
            (AssignIDAndAdd(std::forward<Agent>(toBeAdded)), ...);
        }
        int FindFreeID() {
            return 1;
        }
        void RemoveAgentByID(std::vector<Agent>& agents, int targetID) {
            agents.erase(std::remove_if(agents.begin(), agents.end(),
                                        [targetID](const Agent& agent) { return agent.ID == targetID; }),
                         agents.end());
        }
        Environment(int foodSourceAmount) {
            isDay = false;
            for (int i = 1; i <= foodSourceAmount; i++) {
                foodSources.push_back(FoodSource());
            }
        }
    private:
        int nextID = 0;  // Keeps track of the next available ID
        void AssignIDAndAdd(Agent&& agent) {
            agent.setID(nextID++); // Assign ID before adding
            agents.emplace_back(std::move(agent));
        }
        
        std::vector<std::pair<Agent, Agent>> ShuffleAgents(std::vector<Agent> agents) {
            std::vector<std::pair<Agent, Agent>> pairs;

            // Shuffle the elements randomly
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(agents.begin(), agents.end(), g);
        
            // Pair adjacent elements
            for (size_t i = 0; i + 1 < agents.size(); i += 2) {
                pairs.emplace_back(agents[i], agents[i + 1]);
            }
        
            return pairs; // Return the list of pairs
        }
        FoodSource* findNextNonOccupied(std::vector<FoodSource>& foodSources) {
            for (auto& food : foodSources) {
                if (!food.isOccupied) {
                    return &food; // Return the first non-occupied food source
                }
            }
            return nullptr; // If all are occupied, return nullptr
        }
        
};