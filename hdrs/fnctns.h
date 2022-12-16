//
// Created by sam on 15.12.22.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "mssn_rlztn.h"
#include <string>
#include <vector>

#  define RESET "\e[0m"
#  define GREEN "\e[92m"

bool validation(vector<Mission *> tasks);
void print_tasks(vector<Mission *> mission);
void write_to_file(vector<Mission *> &mission);
void edit_task(vector<Mission *> &Missions, int id);
void delete_task(vector<Mission *> &Missions, int id);
void insert_task(vector<Mission *> &Missions, int id);
void exchange_tasks(vector<Mission *> &Missions, int id1, int id2);
void read_from_file(vector<Mission *> &Missions, const string& path);
void print_help();

#endif // FUNCTIONS_H
