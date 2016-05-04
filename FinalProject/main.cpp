#include <iostream>
#include <fstream>
#include <sstream>
#include "System.h"

using namespace std;

int main()
{
    System SolarSystem;
    /* ***UNCOMMENT HERE***
    // File I/O
    // Planets file is an adjacency list that will be placed into a graph
    string planetFile = "Planets.txt";
    string planets[10];
    ifstream inFilePlanet;
    inFilePlanet.open(planetFile);
    string trash, token, line;
    getline(inFilePlanet,line);
    stringstream ss(line);
    getline(ss,trash,',');
    int i = 0;
    int j = 0;
    while(!ss.eof())
    {
        getline(ss,token,',');
        planets[i] = token;
        SolarSystem.addBody("planet",token,"0");
        i++;
    }
    i = 0;
    // add bodies by reading in first line of file (basically same file I/O as assignment 10)
    while(getline(inFilePlanet,line))
    {
        stringstream iss(line);
        getline(iss,trash,','); // get rid of first token in line
        while(!iss.eof())
        {
            getline(iss,token,',');
            float deltaV = stof(token);
            if (deltaV != 0)
            {
                SolarSystem.addEdge(planets[i],planets[j],deltaV); // add edges
            }
            j++;
        }
        i++;
        j = 0;
    }

    // Moons
    // Now read in the moons file
    // THe moons will be added to the adjacency lists of their parent planets
    string moonFile = "Moons.txt";
    fstream inFileMoon;
    inFileMoon.open(moonFile);
    i = 0;
    while (getline(inFileMoon,line))
    {
        string parentPlanet, exist;
        stringstream iiss(line);
        getline(iiss,parentPlanet,',');
        getline(iiss,exist,',');
        if (stoi(exist) != 0)
        {
            string moonName;
            string weightS;
            int j = 1;
            while (!iiss.eof())
            {
                getline(iiss,moonName,',');
                getline(iiss,weightS,',');
                float weight = stof(weightS);
                SolarSystem.addBody("moon",moonName,parentPlanet);
                j++;
            }
            j = 1;
        }
        i++;
    }
    inFileMoon.clear();
    inFileMoon.seekg(0, ios_base::beg); // go back to beginning of file

    i = 0;
    while (getline(inFileMoon,line))
    {
        string parentPlanet, exist;
        stringstream iiss(line);
        getline(iiss,parentPlanet,',');
        getline(iiss,exist,',');
        if (stoi(exist) != 0)
        {
            string moonName;
            string weightS;
            int j = 1;
            while (!iiss.eof())
            {
                getline(iiss,moonName,',');
                getline(iiss,weightS,',');
                float weight = stof(weightS);
                SolarSystem.addEdge(parentPlanet,moonName,weight); // add edges after reading in file again otherwise it causes problems.
                j++;
            }
            j = 1;
        }
        i++;
    }
    ***UNCOMMENT HERE*** */
    string input = "0";
    int x=0;
    while (input != "8")
    {
        cout << "======Main Menu======" << endl;
        cout<<"1. Display State of Ship"<<endl;
        cout<<"2. Display System"<<endl;
        cout<<"3. Travel Through System"<<endl;
        cout<<"4. Refuel ship"<<endl;
        cout<<"5. Add Celestial Body"<<endl;
        cout<<"6. Add Edge"<<endl;
        cout<<"7. Show Order of Planets and Moons"<<endl;
        cout<<"8. Leave System"<<endl;
        if(x==1){
            cout<<"The previous input was not a number between 1 and 8"<<endl;
        }
        x=1;
        cin>>input;
        string destination, type, name, parent, body1, body2, deltav;
        if(input=="1"){
            x=0;
            SolarSystem.displayShipState();
        }else if(input== "2" ){
            x=0;
            SolarSystem.displaySystem();
        }else if(input== "3" ){
            x=0;
            cin.ignore();
            cout<<"Enter a destination: "<<endl;
            getline(cin,destination);
            SolarSystem.makeTrip(destination);
        }else if(input== "4" ){
            x=0;
            SolarSystem.refuel();
        }else if(input== "5" ){
            x=0;    
            cin.ignore();
            cout<<"Enter the new body's type: "<<endl;
            getline(cin,type);
            cout<<"Enter the new body's name: "<<endl;
            getline(cin,name);
            cout<<"Enter the new body's parent's name (enter '0' if not a moon):"<<endl;
            getline(cin,parent);
            SolarSystem.addBody(type,name,parent);
        }else if(input== "6" ){
            x=0;    
            cin.ignore();
            cout<<"Enter the first body"<<endl;
            getline(cin,body1);
            cout<<"Enter the second body"<<endl;
            getline(cin,body2);
            cout<<"Enter the delta-v required"<<endl;
            getline(cin,deltav);
            SolarSystem.addEdge(bod1,body2,stof(deltav));
        }else if(input== "7" ){
            x=0;
            SolarSystem.showOrder();
        }else if(input== "8"){
            x=0;
            cout<<"Goodbye!"<<endl;
        }
        
    }

    return 0;
}
