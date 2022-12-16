//
// Created by sam on 15.12.22.
//

#include "../hdrs/fnctns.h"
#include "../hdrs/object.h"
#include <fstream>
#include <iomanip>
#include <iostream>

bool validation(vector<Mission *> tasks) {
  string error;
  object rov(0, 0, 0, 0);
  MoveTo *moveto = nullptr;
  Dive *dive = nullptr;
  Lift *lift = nullptr;
  Return *ret = nullptr;

  for (int i = 0; i < tasks.size(); i++) {
    if (dynamic_cast<MoveTo *>(tasks[i])) {
      moveto = dynamic_cast<MoveTo *>(tasks[i]);
      if (!rov.update_coords('M', moveto->x, moveto->y)) {
        cout << "Invalid task: " << i + 1 << " " << endl;
        return false;
      }
    } else if (dynamic_cast<Dive *>(tasks[i])) {
      dive = dynamic_cast<Dive *>(tasks[i]);
      if (!rov.update_coords('D', dive->z, -1)) {
        cout << "> Invalid task: " << i + 1 << " " << endl;
        cout << "> Current z = " << rov.z << ", can't dive to " << dive->z
             << endl;
        return false;
      }
    } else if (dynamic_cast<Lift *>(tasks[i])) {
      lift = dynamic_cast<Lift *>(tasks[i]);
      if (!rov.update_coords('L', lift->z, -1)) {
        cout << "> Invalid task: " << i + 1 << " " << endl;
        cout << "> Current z = " << rov.z << ", can't lift to " << lift->z
             << endl;
        return false;
      }
    } else if (dynamic_cast<Return *>(tasks[i])) {
      ret = dynamic_cast<Return *>(tasks[i]);
      rov.update_coords('R', -1, -1);
    }
  }
  return true;
}

void print_tasks(vector<Mission *> mission) {
  cout << endl << "Task list:" << endl;
  for (int i = 0; i < mission.size(); i++) {
    string s_ = mission[i]->toFile();
    cout << i + 1 << ". " << s_ << endl;
  }
}

void write_to_file(vector<Mission *> &mission) {
  if (mission.empty()) {
    cout << "Task list is empty, nothing to write" << endl;
    return;
  }

  if (!validation(mission)) {
    cout << endl << "Mission validation didn't pass, try again" << endl;
    return;
  }

  auto *last = dynamic_cast<Return *>(mission[mission.size() - 1]);
  if (last == nullptr) {
    cout << "Each mission should be ended with Return" << endl;
    auto *r = new Return();
    mission.push_back(r);
  }

  ofstream file;
  file.open("../Mission.txt", ofstream::out | ofstream::trunc);

  for (int i = 0; i < mission.size(); i++) {
    string str_tmp = to_string(i + 1) + " " + mission[i]->toFile();
    cout << str_tmp << endl;
    file << str_tmp << endl;
  }
  
  file << flush;
  file.close();
  cout << "Tasks were written to file \"../Mission.txt\"" << endl;
}

void edit_task(vector<Mission *> &Missions, int id) {
  cout << "> ";
  string input_string;
  getline(cin, input_string);
  istringstream iss(input_string);

  char command = input_string[0];
  int op1 = -1;
  int op2 = -1;

  MoveTo *moveto = nullptr;
  Dive *dive = nullptr;
  Lift *lift = nullptr;
  Return *ret = nullptr;
  Mission *deleting = Missions[id - 1];
  delete deleting;

  switch (command) {
  case 'M':
    iss >> command >> op1 >> op2;
    moveto = new MoveTo(op1, op2);
    Missions[id - 1] = moveto;
    break;
  
  case 'R':
    ret = new Return();
    Missions[id - 1] = ret;
    break;
  
  case 'D':
    iss >> command >> op1;
    dive = new Dive(op1);
    Missions[id - 1] = dive;
    break;
  
  case 'L':
    iss >> command >> op1;
    lift = new Lift(op1);
    Missions[id - 1] = lift;
    break;
  
  default:
    break;
  }
  }

void delete_task(vector<Mission *> &Missions, int id) {

  // NB: id = [1..size()]
  if (Missions.empty()) {
    cout << "No tasks to delete";
    return;
  } else if (id > Missions.size() || id < 1) {
    cout << "Index is out of range";
    return;
  } else if (Missions.size() == 1) {
    delete Missions[id - 1];
    return;
  }

  Mission *deleting = Missions[id - 1];
  delete deleting;

  for (int i = id - 1; i < Missions.size() - 1; i++) {
    Missions[i] = Missions[i + 1];
  }
  Missions.resize(Missions.size() - 1);
}

void insert_task(vector<Mission *> &Missions, int id) {
  if (id < 1 || id > Missions.size() + 1) {
    cout << "Index out of range" << endl;
    return;
  }

  cout << "> ";

  string input_string;
  char command;

  double op1 = -1;
  char op1_k = '.';
  double op2 = -1;
  char op2_k = '.';

  const char key = '/';

  getline(cin, input_string);

  command = input_string[0];

  istringstream iss(input_string);
  iss >> command >> op1_k >> op1 >> op2_k >> op2;

  MoveTo *moveto = nullptr;
  Dive *dive = nullptr;
  Lift *lift = nullptr;
  Return *ret = nullptr;
  Mission *m = nullptr;

  object r(0, 0, 0, 0);

  switch (command) {
  case 'M':
    if (op1_k != key || op2_k != key) {
      cout << "Incorrect number of args" << endl;
      break;
    } else if (op1 < 0 || op2 < 0 || op1 > r.MAX_X || op2 > r.MAX_Y) {
      cout << "\t Insertion failed: "
           << "op1 < 0 or op2 < 0 or op1 > MAX_X or op2 > MAX_Y" << endl;
      break;
    }
    moveto = new MoveTo(op1, op2);
    m = moveto;
    break;

  case 'R':
    ret = new Return();
    m = ret;
    break;

  case 'D':
    if (op1_k != key) {
      cout << "Incorrect number of args" << endl;
      break;
    } else if (op1 > r.MAX_Z || op1 < 0 || r.z > op1) {
      cout << "\t Insertion failed: "
           << "op1 > MAX_Z || op1 < 0 || z > op1" << endl;
      break;
    }
    dive = new Dive(op1);
    m = dive;
    break;

  case 'L':
    if (op1_k != key) {
      cout << "Incorrect number of args" << endl;
      break;
    } else if (op1 > r.MAX_Z || op1 < 0 || r.z < op1) {
      cout << "\t Insertion failed: "
           << "op1 > MAX_Z or op1 < 0 or z < op1" << endl;
      break;
    }
    lift = new Lift(op1);
    m = lift;
    break;
  default:
    break;
  }

  if (Missions.empty() || id > Missions.size()) {
    Missions.push_back(m);
    return;
  }

  int counter = 0;
  for (auto it = Missions.begin(); it != Missions.end(); ++it) {
    counter++;
    if (counter == id) {
      Missions.insert(++it, m);
      break;
    }
  }

  }

void exchange_tasks(vector<Mission *> &Missions, int id1, int id2) {
  Mission *temp = nullptr;
  if (id1 > 0 && id1 <= Missions.size() && id2 > 0 && id2 <= Missions.size()) {
    temp = Missions[id1 - 1];
    Missions[id1 - 1] = Missions[id2 - 1];
    Missions[id2 - 1] = temp;
  } else {
    cout << "Arguments out of range" << endl;
  }
  }

void read_from_file(vector<Mission *> &Missions, const string& path = "../Mission.txt") {

  string line;
  int id = 0;
  string command;
  double op1 = -1;
  double op2 = -1;

  ifstream in(path);

  if (in.is_open()) {
    while (getline(in, line)) {
      cout << line << endl;

      istringstream iss(line);
      iss >> id >> command;

      MoveTo *moveto = nullptr;
      Dive *dive = nullptr;
      Lift *lift = nullptr;
      Return *ret = nullptr;

      switch (command[0]) {
      case 'M':
        iss >> op1 >> op2;
        moveto = new MoveTo(op1, op2);
        Missions.push_back(moveto);
        break;
      case 'R':
        iss >> op1;
        ret = new Return();
        Missions.push_back(ret);
        break;
      case 'D':
        iss >> op1;
        dive = new Dive(op1);
        Missions.push_back(dive);
        break;
      case 'L':
        iss >> op1;
        lift = new Lift(op1);
        Missions.push_back(lift);
        break;
      }
    }
    in.close();
    cout << "End of reading of file" << endl;
  } else {
    cout << "Can't read from file";
  }
  }

void print_help() {
  cout << GREEN << "~~~~~~~~~~~~~~Supporting options list~~~~~~~~~~~~~~" << endl << RESET << endl;

  cout << setw(15) << " \"M >X >Y\""
       << " - move to (X,Y) with constant depth"
       << endl;
  cout << setw(15) << " \"D >d\""
       << " - instantly dive to depth = d"
       << endl;
  cout << setw(15) << " \"L >h\""
       << " - instantly pop up"
       << endl;
  cout << setw(15) << " \"R\""
       << " - return to start coordinates (0,0)"
       << endl;

  cout << endl;
  cout << setw(15) << "\"w\""
       << " - write to file"
       << endl;
  cout << setw(15) << "\"r\""
       << " - read from file"
       << endl;
  cout << setw(15) << "\"p\""
       << " - print tasks"
       << endl;
  cout << endl;
  cout << setw(15) << "\"e >id\""
       << " - edit"
       << endl;
  cout << setw(15) << "\"d >id\""
       << " - delete task"
       << endl;
  cout << setw(15) << "\"i >id\""
       << " - insert task"
       << endl;
  cout << setw(15) << "\"x >id1 >id2\""
       << " - exchange tasks"
       << endl;
  cout << endl;
  cout << setw(15) << "\"q\""
       << " - quit"
       << endl;
}
