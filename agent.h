#include <iostream>

class Agent {
    public:
        int ID;
        bool isAlive;
        int foodAmount;
        void Feed(int amount) {
            foodAmount += amount;
        };
        void Starve(int amount) {
            foodAmount -= amount;
            if (foodAmount < 0) isAlive = false;
            //std::cout << ID << " has " << isAlive << " food." << std::endl;
        };
        Agent() {
            foodAmount = 0;
            ID = -1;
            isAlive = true;
        }
        void setID(int newID) { ID = newID;}
    private:
        bool active;
};