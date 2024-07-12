#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#include <set>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class City;
class Route;
class Bus;
class Graph;

void readFiles();
void displayRoute(stack<Route*>);

class City {
	public:
		string name;
		list<Route*> r;
		City(string name){
			this->name = name;
		}
};

class Bus {
	public:
		string name;
		int cost;
		Bus(string name, int cost){
			this->name = name;
			this->cost = cost;
		}
};


class Route {
	public:
		City* from;
		City* to;
		int distance;
		list<Bus*> bus;
		Route(City* from, City* to, int distance, list<Bus*>bus){
			this->from = from;
			this->to = to;
			this->distance = distance;
			this->bus = bus;
		}
};

list<stack<Route*>> routes;

class Graph {
	private:
		list<City*> graph;
	public:
		Graph() {}
		
		void addCity(City* city) {
			int z = 0;
			for (City* c: graph) {
				if(c->name == city->name)
					z=1;
			}
			if (z == 0) {
				graph.push_back(city);
			}
		}
		void addRoute(City* from, City* to, int distance, list<Bus*> bus) {
			Route* r1 = new Route(from, to, distance, bus);
			Route* r2 = new Route(to, from, distance, bus);
			from->r.push_back(r1);
			to->r.push_back(r2);
		}
		City* find(string name) {
			for(City* c: graph){
				if(c->name == name)
					return c;
			}
            return NULL;
		}
		void findPathsDFS(int& count, City* start, City* end, stack<City*> path, set<City*> visited, stack<Route*> route) {
    		visited.insert(start);
    		path.push(start);
    		if (start == end) {
                if (count == 1) {
                    cout << "\nAll Possible Routes:\n";
                }
        		printPath(count, path, route);
                count++;
    		} else {
        		for (Route* r: start->r) {
            		if (visited.find(r->to) == visited.end()) {
                        route.push(r);
                        findPathsDFS(count, r->to, end, path, visited, route);
                        route.pop();
                    }
                }
            }
            path.pop();
            visited.erase(start);
		}
		void findPaths(City* start, City* end) {
            int count = 1;
    		set<City*> visited;
    		stack<City*> path;
            stack<Route*> route;
    		findPathsDFS(count, start, end, path, visited, route);
		}
		
		void printPath(int& count, stack<City*> path, stack<Route*> route) {
			cout << count << ": ";

            ::routes.push_back(stack<Route*> (route));

            stack<Route*> revRoute;

            while (!route.empty()) {
                revRoute.push(route.top());
                route.pop();
            }

            int i = 0;
            while (!revRoute.empty()) {
                if (i == 0) {
                    cout << revRoute.top()->from->name;
                    i++;
                }
                cout << " -> " << revRoute.top()->to->name;
                revRoute.pop();
            }

            cout << endl;
		}
};

Graph graph;

int main() {
    readFiles();
    
    string startCity, endCity;

    cout << "Enter the start city: ";
    cin >> startCity;
    cout << "Enter the end city: ";
    cin >> endCity;

    City *start = graph.find(startCity);
    City *end = graph.find(endCity);

    graph.findPaths(start, end);

    if (routes.size() > 0) {
        int choice;
        if (routes.size() == 1)
            cout << "\nEnter the route you want to take (1): ";
        else
            cout << "\nEnter the route you want to take (1 - " << routes.size() << "): ";
        cin >> choice;

        if ((choice - 1) >= routes.size() || (choice - 1) < 0) {
            return 0;
        }

        list<stack<Route*>>::iterator it = routes.begin();
        for (int i = 0; i < (choice - 1); i++) ++it;

        displayRoute(*it);
    }

    return 0;
}

void displayRoute(stack<Route*> route) {
    cout << "\nDetail of the route: " << endl;

    stack<Route*> revRoute;

    while (!route.empty()) {
        revRoute.push(route.top());
        route.pop();
    }

    while (!revRoute.empty()) {
        cout << revRoute.top()->from->name << " -> " << revRoute.top()->to->name << ": " << endl;
        cout << "Buses:" << endl;
        for (Bus* bus: revRoute.top()->bus) {
            cout << bus->name << " | " << bus->cost << endl;
        }
        revRoute.pop();
    }
}

void readFiles() {
    ifstream pathsFile("C:\\Users\\HP\\OneDrive\\Desktop\\Codes\\c++\\paths.txt"), citiesFile("C:\\Users\\HP\\OneDrive\\Desktop\\Codes\\c++\\cities.txt");
    string line;

    while (getline(citiesFile, line)) {
        stringstream ss(line);
        string city;
        while (ss >> city) {
            graph.addCity(new City(city));
        }
    }

    while (getline(pathsFile, line)) {
        stringstream ss(line);
        string city1, city2, bus;
        int distance, cost;
        list<Bus*> buses;

        ss >> city1 >> city2 >> distance;
        while (ss >> bus >> cost) {
        	buses.push_back(new Bus(bus, cost));
        }
        
        City* c1 = graph.find(city1);
        City* c2 = graph.find(city2);

        graph.addRoute(c1, c2, distance, buses);
        
    }

    pathsFile.close();
    citiesFile.close();
}
