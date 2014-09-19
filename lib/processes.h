/*
 * IPICYT - CNS LAB
 * Operating System Concepts
 * Professor: D. en C. Jorge C. Navarro Muñoz
 *
 * Developer: Guillermo Quezada
 * */

#ifndef PROCESSES_H
#define PROCESSES_H

#define PROCESSES 5
#define RESOURCES 3
#define V_ROW 1

struct processes{
  int id;
  int allocation[V_ROW][RESOURCES];
  int needed[V_ROW][RESOURCES];
  bool terminated;
};

struct resources{
  int process_id;
  int available[V_ROW][RESOURCES];
  int max[V_ROW][RESOURCES];
};

void initialize();
void show_processes();
void assign_resources();

#endif
