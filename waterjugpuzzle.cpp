/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Dominick Battinelli & Zachary Rimshnick
 * Date        : October 22nd, 2022
 * Description : Solves Water Jug Puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack> 
#include <sstream>
using namespace std;

// Struct to represent state of water in the jugs.
struct State {
  int a, b, c;
  string directions;
  State *parent;

  State(int _a, int _b, int _c, string _directions)
      : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

  // String representation of state in tuple form.
  string to_string() {
    ostringstream oss;
    oss << "(" << a << ", " << b << ", " << c << ")";
    return oss.str();
  }
};

// Checks if current State is equal to the goal state
bool reach_goal(State curr, State goal) {
  if (curr.a == goal.a) {
    if (curr.b == goal.b) {
      if (curr.c == goal.c) {
        return true;
      }
    }
  }
  return false;
}

//Prints the directions to solve the waterjug puzzle
void print_solution(State curr){
  State *next_ptr = curr.parent;
  stack <string> direction_list;   //Stack of directions

  //Gathers all directions in a stack
  string end = curr.to_string();
  string dir = curr.directions + " " + end;
  direction_list.push(dir);

  while(next_ptr != nullptr ){
    State *state = next_ptr;
    end = state->to_string();
    dir = state->directions + " " + end;
    next_ptr = state->parent;
    direction_list.push(dir);
  }

  //Prints directions from stack
  while(!direction_list.empty()){
    cout << direction_list.top() << endl;
    direction_list.pop();
  }

  return;
}

//Runs the Breadth First Search
void bfs(State initial_state, int capA, int capB, int capC, State goal_state) {
  int new_a, new_b, new_c, pour;
  string str;
  State *parent;
  stack<State*> all;  //Stack of all pointers made (for cleanup purposes)

  //Initalizes found array
  bool **found = new bool *[capA + 1];
  for (int i = 0; i < capA + 1; i++) {
    found[i] = new bool[capB + 1];
    fill(found[i], found[i] + (capB + 1), false);
  }
  found[initial_state.a][initial_state.b] = true;

  //Initalizes Queue
  queue<State> queue;
  queue.push(initial_state);

  // BFS SEARCH
  while (!queue.empty()) {
    
    State curr = queue.front();
    State* next = new State(curr.a,curr.b,curr.c,curr.directions);
    next->parent = curr.parent;
    all.push(next);
    parent = next;
    // Check if solution is found
    if (reach_goal(curr, goal_state)) {
      print_solution(curr);

      //Deletes found array
      for(int i = 0; i < capA + 1; i++) {
        delete [] found[i];
      }
      delete [] found;

      //Deletes all pointers
      while(!all.empty()){
        delete all.top();
        all.pop();
      }
      
      return;
    }

    // POUR C TO A
    if (curr.c != 0) {
      if (curr.a != capA) {
        new_a = curr.a;
        new_c = curr.c;
        pour = 0;
        //Pours water
        while (new_a != capA && new_c != 0) {
          new_a++;
          new_c--;
          pour++;
        }
        if(pour == 1){
          str = "Pour " + to_string(pour) + " gallon from C to A.";
          }else
        {
           str = "Pour " + to_string(pour) + " gallons from C to A.";
        }
        //Checks if state already exists
        if (found[new_a][curr.b] == false) {
          found[new_a][curr.b] = true;
          State next = State(new_a, curr.b, new_c, str);
          next.parent = parent;
          queue.push(next);
        }
      }
    }

    // POUR B TO A
    if (curr.b != 0) {
      if (curr.a != capA) {
        new_a = curr.a;
        new_b = curr.b;
        pour = 0;
        while (new_a != capA && new_b != 0) {
          new_a++;
          new_b--;
          pour++;
        }
        if(pour == 1){
          str = "Pour " + to_string(pour) + " gallon from B to A.";
        }
        else{
          str = "Pour " + to_string(pour) + " gallons from B to A.";
        }
        if(found[new_a][new_b] == false){
          found[new_a][new_b] = true;
          State next = State(new_a, new_b, curr.c, str);
          next.parent = parent;
          queue.push(next);
      }
    }
  }

    // POUR C TO B
    if (curr.c != 0) {
      if (curr.b != capB) {
        new_b = curr.b;
        new_c = curr.c;
        pour = 0;
        while (new_b != capB && new_c != 0) {
          new_b++;
          new_c--;
          pour++;
        }
        if(pour == 1){
           str = "Pour " + to_string(pour) + " gallon from C to B.";
        }
        else{
           str = "Pour " + to_string(pour) + " gallons from C to B.";
        }
        if (found[curr.a][new_b] == false) {
          found[curr.a][new_b] = true;
          State next = State(curr.a, new_b, new_c, str);
          next.parent = parent;
          queue.push(next);
        }
      }
    }

    // POUR A TO B
    if (curr.a != 0) {
      if (curr.b != capB) {
        new_a = curr.a;
        new_b = curr.b;
        pour = 0;
        while (new_b != capB && new_a != 0) {
          new_b++;
          new_a--;
          pour++;
        }
        if(pour == 1){
          str = "Pour " + to_string(pour) + " gallon from A to B.";
        }
        else{
          str = "Pour " + to_string(pour) + " gallons from A to B.";
        }
        if (found[new_a][new_b] == false) {
          found[new_a][new_b] = true;
          State next = State(new_a, new_b, curr.c, str);
          next.parent = parent;
          queue.push(next);
        }
      }
    }

    // POUR B TO C
    if (curr.b != 0) {
      if (curr.c != capC) {
        new_b = curr.b;
        new_c = curr.c;
        pour = 0;
        while (new_c != capC && new_b != 0) {
          new_c++;
          new_b--;
          pour++;
        }
        if(pour == 1){
          str = "Pour " + to_string(pour) + " gallon from B to C.";
        }
        else{
          str = "Pour " + to_string(pour) + " gallons from B to C.";
        }
        if (found[curr.a][new_b] == false) {
          found[curr.a][new_b] = true;
          State next = State(curr.a, new_b, new_c, str);
          next.parent = parent;
          queue.push(next);
        }
      }
    }
    
    // POUR A TO C
    if (curr.a != 0) {
      if (curr.c != capC) {
        new_a = curr.a;
        new_c = curr.c;
        pour = 0;
        while (new_c != capC && new_a != 0) {
          new_c++;
          new_a--;
          pour++;
        }
        if(pour == 1){
          str = "Pour " + to_string(pour) + " gallon from A to C.";
        }else{
          str = "Pour " + to_string(pour) + " gallons from A to C.";
        }
        if (found[new_a][curr.b] == false) {
          found[new_a][curr.b] = true;
          State next = State(new_a, curr.b, new_c, str);
          next.parent = parent;
          queue.push(next);
        }
      }
    }

    queue.pop();
  }
  //BFS END
  
  //No Solution Found
  cout << "No solution." << endl;

  //Deletes found array
  for(int i = 0; i < capA + 1; i++) {
    delete [] found[i];
  }
  delete [] found;

  //Deletes all pointers 
  while(!all.empty()){
    delete all.top();
    all.pop();
  }
  return;
}

int main(int argc, char *argv[]) {
  istringstream iss;
  int capA, capB, capC, goalA, goalB, goalC;

  // ERROR CHECKING

  //Check for correct number of args
  if (argc != 7) {
    cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    return -1;
  }
  
  // Checks for correct inputs

  iss.str(argv[1]);
  if (!(iss >> capA) || (capA < 1)) {
    cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
    return -1;
  }
  iss.clear();

  iss.str(argv[2]);
  if (!(iss >> capB) || (capB < 1)) {
    cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
    return -1;
  }
  iss.clear();

  iss.str(argv[3]);
  if (!(iss >> capC) || (capC < 1)) {
    cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
    return -1;
  }
  iss.clear();

  iss.str(argv[4]);
  if (!(iss >> goalA) || (goalA < 0)) {
    cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
    return -1;
  }
  iss.clear();

  iss.str(argv[5]);
  if (!(iss >> goalB) || (goalB < 0)) {
    cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
    return -1;
  }
  iss.clear();

  iss.str(argv[6]);
  if (!(iss >> goalC) || (goalC < 0)) {
    cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
    return -1;
  }
  iss.clear();

  // Checks if goal <= capacity

  if (goalA > capA) {
    cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
    return -1;
  }
  if (goalB > capB) {
    cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
    return -1;
  }
  if (goalC > capC) {
    cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
    return -1;
  }
  // Checks if capC == goal state
  if (!(capC == (goalA + goalB + goalC))) {
    cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
    return -1;
  }

  
  State initial = State(0, 0, capC, "Initial state.");  //Creates Start State
  State goal = State(goalA, goalB, goalC, "");          //Creates Goal State
  bfs(initial, capA, capB, capC, goal);                 //Runs BFS

  return 0;
}

