//
// Created by sam on 12.12.22.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../hdrs/mssn_rlztn.h"
#include "../hdrs/object.h"
#include "../hdrs/fnctns.h"

int main() {
  object Rov(0, 0, 0, 0);
  vector<Mission *> Tasks;
  vector<char> TasksSequence;
  string Input;
  string New_missin;

  char command;
  double op1 = -1;
  char op1_k = '.';
  double op2 = -1;
  char op2_k = '.';
  const char key = '>';

  print_help();

  while (true) {
    getline(cin, Input);
    if (Input == "q")
      break;
    else if (Input.empty() || Input == "\n")
      continue;
    op1_k = op2_k = '.';
    command = Input[0];
    istringstream iss(Input);
    iss >> command >> op1_k >> op1 >> op2_k >> op2;

    MoveTo *moveto = nullptr;
    Dive *dive = nullptr;
    Lift *lift = nullptr;
    Return *ret = nullptr;

    switch (command) {
    case 'M':
      if (op1_k != key || op2_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      } else if (!Rov.update_coords(command, op1, op2))
        break;
      moveto = new MoveTo(op1, op2);
      Tasks.push_back(moveto);
      TasksSequence.push_back(command);
      break;
      
    case 'R':
      ret = new Return();
      Tasks.push_back(ret);
      TasksSequence.push_back(command);
      break;
      
    case 'D':
      if (op1_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      } else if (!Rov.update_coords(command, op1, op2))
        break;
      dive = new Dive(op1);
      Tasks.push_back(dive);
      TasksSequence.push_back(command);
      break;
      
    case 'L':
      if (op1_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      } else if (!Rov.update_coords(command, op1, op2))
        break;
      lift = new Lift(op1);
      Tasks.push_back(lift);
      TasksSequence.push_back(command);
      break;

    case 'e':
      if (op1_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      }
      edit_task(Tasks, int(op1));
      break;

    case 'h':
      print_help();
      break;

    case 'p':
      print_tasks(Tasks);
      break;

    case 'w':
      write_to_file(Tasks);
      break;

    case 'd':
      if (op1_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      }
      delete_task(Tasks, int(op1));
      break;

    case 'i':
      if (op1_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      } else
        insert_task(Tasks, int(op1));
      break;

    case 'x':
      if (op1_k != key || op2_k != key) {
        cout << "Incorrect number of arguments" << endl;
        break;
      }
      exchange_tasks(Tasks, int(op1), int(op2));
      break;

    case 'r':
      read_from_file(Tasks, "../Mission.txt");
      break;

    default:
      break;
    }
  }
}
