#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <vector>

using namespace std;

struct adjBody;

struct Body
{
    string type;
    string name;
    Body *parent;
    vector<adjBody> adjPlanets;
    vector<Body> moons;
    Body() {};
    Body(string in_type, string in_name)
    {
        type = in_type;
        name = in_name;
    }
};

struct adjBody
{
    Body *b;
    float deltaV;
};

struct Ship
{
    string currentLocation;
    float fuelLeft;
};

class System
{
    public:
        System();
        ~System();
        void addBody(string type, string name, string parentName);
        void addEdge(string body1, string body2, float weight);
        void displaySystem();
        void displayShipState();
        void makeTrip(string destination);
        void refuel();
        void showOrder();
        void showStar();
    protected:
    private:
        vector<Body> planets;
        Body *findBody(string name);
        Ship Vissarion;
};

#endif // SYSTEM_H
