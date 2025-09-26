# 🚌 DSA - Route Finder

This is my **semester final project** for the **Data Structures & Algorithms** course.
It’s a C++ program that models a transport system as a graph of cities, routes, and buses.
You can enter two cities, and the program will find **all possible paths** between them, then display details of available buses and costs.

---

## ✨ Features

* Reads cities and routes from external files (`cities.txt`, `paths.txt`)
* Represents the transport network as a **graph**:

  * **City** → node
  * **Route** → edge (with distance + buses)
  * **Bus** → transport option on a route
* Uses **Depth-First Search (DFS)** to find all possible paths between two cities
* Lets the user pick a preferred route from the discovered paths
* Displays detailed info about buses and their costs on that route

---

## 📂 Files

* **cities.txt** → contains names of all cities in the network
* **paths.txt** → contains route definitions with distance and bus info

---

## ⚙️ How to Compile & Run

1. Clone this repo:

   ```bash
   git clone https://github.com/waseeq14/DSA-Final.git
   cd DSA-Final
   ```

2. Compile with g++:

   ```bash
   g++ pathFinder.cpp -o pathFinder
   ```

3. Make sure you have `cities.txt` and `paths.txt` in the project folder (or update file paths in `readFiles()`).

4. Run the program:

   ```bash
   ./pathFinder
   ```

5. Enter the **start city** and **end city** when prompted.

6. Pick a route from the displayed options to view bus details.

---
