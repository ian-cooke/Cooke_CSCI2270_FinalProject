#include "System.h"
#include <iostream>
#include <vector>

using namespace std;
using std::vector;

System::System()
{
    Vissarion.currentLocation = "Io";
    Vissarion.fuelLeft = 100;
}

System::~System()
{
    //dtor
}

void System::addBody(string type, string name, string parentName)
{
    bool found = false;
    for (int i = 0; i < planets.size(); i++)
    {
        if (planets[i].name == name)
        {
            found = true;
            cout<<planets[i].name<<" already exists."<<endl;
        }
        for (int j = 0; j < planets[i].moons.size(); j++)
        {
            if (planets[i].moons[j].name == name)
            {
                found = true;
                cout<<planets[i].moons[j].name<<" already exists."<<endl;
            }
        }
    }
    if (!found)
    {
        Body b = Body(type, name);
        if (type == "planet")
        {
            planets.push_back(b);
        }
        else
        {
            for (int i = 0; i < planets.size(); i++)
            {
                if (planets[i].name == parentName)
                {
                    b.parent = findBody(parentName);
                    planets[i].moons.push_back(b);
                }
            }
        }
    }
}

void System::addEdge(string body1, string body2, float weight)
{
    Body *parent = findBody(body1);
    Body *other = findBody(body2);
    for (int i = 0; i < planets.size(); i++)
    {
        if (planets[i].name == body1)
        {
            if (other->type == "planet")
            {
                for (int j = 0; j < planets.size(); j++)
                {
                    if (planets[j].name == body2 && i != j)
                    {
                        adjBody ab;
                        ab.b = &planets[j];
                        ab.deltaV = weight;
                        ab.b->parent = parent;
                        planets[i].adjPlanets.push_back(ab);
                    }
                }
            }
            else
            {
                for (int j = 0; j < planets[i].moons.size(); j++)
                {
                    if (planets[i].moons[j].name == body2 && i != j)
                    {
                        adjBody ab;
                        ab.b = &planets[i].moons[j];
                        ab.deltaV = weight;
                        ab.b->parent = parent;
                        planets[i].adjPlanets.push_back(ab);
                        //cout<<planets[i].name<<"..."<<planets[i].adjPlanets.back().b->name<<endl;
                    }
                }
            }
        }
    }
}

void System::displaySystem()
{
    for (int i = 0; i < planets.size(); i++)
    {
        cout<<planets[i].name;
        for (int j = 0; j < planets[i].moons.size(); j++)
        {
            cout<<"*"<<planets[i].moons[j].name;
        }
        cout<<endl;
    }
}

void System::displayShipState()
{
    cout<<"Currently orbiting "<<Vissarion.currentLocation<<endl;
    cout<<"Delta-V remaining: "<<Vissarion.fuelLeft<<" km/s"<<endl;
}

void System::makeTrip(string destination)
{
    Body *dest = findBody(destination);
    Body *current = findBody(Vissarion.currentLocation);
    if (dest == NULL)
    {
        cout<<destination<<" not found."<<endl;
    }
    else
    {
        float fuelRequired;
        if (dest->type == "planet")
        {
            if (current -> type == "planet") // current and dest are planets
            {
                for (int i = 0; i < current->adjPlanets.size(); i++)
                {
                    if (current->adjPlanets[i].b->name == destination)
                    {
                        fuelRequired= current->adjPlanets[i].deltaV;
                    }
                }
            }
            else // current is moon, dest is planet
            {
                Body *Parent = findBody(current->parent->name);
                if (Parent -> name == dest->name) // moon and planet are in the same system
                {
                    for (int i = 0; i < dest->adjPlanets.size(); i++)
                    {
                        if (dest->adjPlanets[i].b->name == current->name)
                        {
                            fuelRequired = dest->adjPlanets[i].deltaV*-1;
                        }
                    }
                }
                for (int i = 0; i < Parent->adjPlanets.size(); i++)
                {
                    if (Parent->adjPlanets[i].b->name == current -> name)
                    {
                        for (int j = 0; j < Parent->adjPlanets.size(); j++)
                        {
                            if (Parent->adjPlanets[j].b->name == destination)
                            {
                                fuelRequired = Parent->adjPlanets[i].deltaV + Parent->adjPlanets[j].deltaV;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (current -> type == "planet") // current is planet, dest is moon
            {
                Body * Parent = findBody(destination)->parent;
                if (Parent == current) // destination is current's own moon
                {
                    for (int i = 0; i < current->adjPlanets.size(); i++)
                    {
                        if (current->adjPlanets[i].b->name == destination)
                        {
                            fuelRequired = current->adjPlanets[i].deltaV*-1;
                        }
                    }
                }
                for (int i = 0; i < Parent->adjPlanets.size(); i++)
                {
                    if (current->name == Parent->adjPlanets[i].b->name)
                    {
                        for (int j = 0; j < Parent->adjPlanets.size(); j++)
                        {
                            if (Parent->adjPlanets[j].b->name == destination)
                            {
                                fuelRequired = Parent->adjPlanets[i].deltaV + Parent->adjPlanets[j].deltaV;
                            }
                        }
                    }
                }
            }
            else // current and dest are both moons
            {
                Body *Parent1 = current->parent;
                Body *Parent2 = findBody(destination)->parent;
                if (Parent1 == Parent2) // moons orbit same planet
                {
                    for (int i = 0; i < Parent1->adjPlanets.size(); i++)
                    {
                        if (Parent1->adjPlanets[i].b->name == current->name)
                        {
                            for (int j = 0; j < Parent1->adjPlanets.size(); j++)
                            {
                                if (Parent1->adjPlanets[j].b->name==destination)
                                {
                                    fuelRequired = Parent1->adjPlanets[i].deltaV*-1 + Parent1->adjPlanets[j].deltaV*-1;
                                }
                            }
                        }
                    }
                }
                for(int i = 0; i < Parent1->adjPlanets.size(); i++)
                {
                    if (Parent1->adjPlanets[i].b->name == Parent2->name)
                    {
                        for (int j = 0; j < Parent1->adjPlanets.size(); j++)
                        {
                            if (Parent1->adjPlanets[j].b->name == current->name)
                            {
                                for (int k = 0; k < Parent2->adjPlanets.size(); k++)
                                {
                                    if (Parent2->adjPlanets[k].b->name == destination)
                                    {
                                        fuelRequired = Parent1->adjPlanets[i].deltaV + Parent1->adjPlanets[j].deltaV + Parent2->adjPlanets[k].deltaV;
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
        if (fuelRequired > Vissarion.fuelLeft)
        {
            cout<<"Not enough fuel remaining."<<endl;
        }
        else
        {
            Vissarion.currentLocation = dest->name;
            cout<<"You have arrived at "<<Vissarion.currentLocation<<"."<<endl;
            Vissarion.fuelLeft -= fuelRequired;
            displayShipState();
        }
    }
}

void System::refuel()
{
    Vissarion.fuelLeft += 50;
    displayShipState();
}

void System::showOrder()
{
    string chars[5] = {"a","b","c","d","e"};
    for (int i = 0; i < planets.size(); i++)
    {
        cout<<i+1<<":"<<planets[i].name;
        for (int j = 0; j < planets[i].moons.size(); j++)
        {
            cout<<":"<<chars[j]<<":"<<planets[i].moons[j].name;
        }
        cout<<endl;
    }
}

// Private Functions
Body * System::findBody(string name)
{
    for (int i = 0; i < planets.size(); i++)
    {
        if (planets[i].name == name)
        {
            return &planets[i];
        }
        for (int j = 0; j < planets[i].moons.size(); j++)
        {
            if (planets[i].moons[j].name == name)
            {
                return &planets[i].moons[j];
            }
        }
    }
    return NULL;
}
