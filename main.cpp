#include <iostream>
#include "environment.h"

using namespace std;

int main() {

    Environment env(8);

    Agent agent;

    env.AddAgents(agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent, agent);
    
    cout << "There are " << env.agents.size() << " agents active!" << endl;

    //Day
    env.Step();
    
    //Night
    env.Step();

    cout << "There are " << env.agents.size() << " agents active!" << endl;

    return 0;
}