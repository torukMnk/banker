/*
 * IPICYT - CNS LAB
 * Operating System Concepts
 * Professor: D. en C. Jorge C. Navarro Muñoz
 *
 * Developer: Guillermo Quezada
 * */

#include "processes.h"
#include <stdio.h>
#include <cstring>

processes process[PROCESSES];
resources resource[PROCESSES];
bool free_processes = false;

void initialize(){

  memset( &process, 0, sizeof(process));
  memset( &resource, 0, sizeof(resource));

  process[0].id = 0;
  process[0].allocation[0][0] = 0;
  process[0].allocation[0][1] = 1;
  process[0].allocation[0][2] = 0;
  process[0].needed[0][0] = 7;
  process[0].needed[0][1] = 4;
  process[0].needed[0][2] = 3;
  process[0].terminated = false;

  resource[0].process_id = 0;
  resource[0].max[0][0] = 7;
  resource[0].max[0][1] = 5;
  resource[0].max[0][2] = 3;
  resource[0].available[0][0] = 2;
  resource[0].available[0][1] = 3;
  resource[0].available[0][2] = 0;

  process[1].id = 1;
  process[1].allocation[0][0] = 3;
  process[1].allocation[0][1] = 0;
  process[1].allocation[0][2] = 2;
  process[1].needed[0][0] = 0;
  process[1].needed[0][1] = 2;
  process[1].needed[0][2] = 0;
  process[1].terminated = false;

  resource[1].process_id = 1;
  resource[1].max[0][0] = 3;
  resource[1].max[0][1] = 2;
  resource[1].max[0][2] = 2;

  process[2].id = 2;
  process[2].allocation[0][0] = 3;
  process[2].allocation[0][1] = 0;
  process[2].allocation[0][2] = 2;
  process[2].needed[0][0] = 6;
  process[2].needed[0][1] = 0;
  process[2].needed[0][2] = 0;
  process[2].terminated = false;

  resource[2].process_id = 2;
  resource[2].max[0][0] = 9;
  resource[2].max[0][1] = 0;
  resource[2].max[0][2] = 2;

  process[3].id = 3;
  process[3].allocation[0][0] = 2;
  process[3].allocation[0][1] = 1;
  process[3].allocation[0][2] = 1;
  process[3].needed[0][0] = 0;
  process[3].needed[0][1] = 1;
  process[3].needed[0][2] = 1;
  process[3].terminated = false;

  resource[3].process_id = 3;
  resource[3].max[0][0] = 2;
  resource[3].max[0][1] = 2;
  resource[3].max[0][2] = 2;

  process[4].id = 4;
  process[4].allocation[0][0] = 0;
  process[4].allocation[0][1] = 0;
  process[4].allocation[0][2] = 2;
  process[4].needed[0][0] = 4;
  process[4].needed[0][1] = 3;
  process[4].needed[0][2] = 1;
  process[4].terminated = false;

  resource[4].process_id = 4;
  resource[4].max[0][0] = 4;
  resource[4].max[0][1] = 3;
  resource[4].max[0][2] = 3;

}

void show_processes(){

  int p;
  printf("Process  Alloc \tMax Available \tNeeded Terminated\n");
  for(p = 0; p < PROCESSES; p++){
    printf("P%d \t  %d%d%d  \t%d%d%d \t%d%d%d \t%d%d%d \t%d\n",
            process[p].id,
            process[p].allocation[0][0],
            process[p].allocation[0][1],
            process[p].allocation[0][2],
            resource[p].max[0][0],
            resource[p].max[0][1],
            resource[p].max[0][2],
            resource[p].available[0][0],
            resource[p].available[0][1],
            resource[p].available[0][2],
            process[p].needed[0][0],
            process[p].needed[0][1],
            process[p].needed[0][2],
            process[p].terminated);
  }
  printf("====================================\n");
}


void assign_resources(){

  /*
   * @int unlock
   * Unlock when resources conditions == RESOURCES
   * */
  int unlock;

  /*
   * @int temp_resources[RESOURCES]
   * Holds available - needed
   * */
  int temp_resources[RESOURCES];

  /*
   * @int index
   * Process index
   * */
  int index = 0;

  /*
   * @int processes_free
   * Holds the number of processes done
   * Max = PROCESSES
   * */
  int processes_free = 0;

  /*
   * @int time
   * Get loop times
   * */
  int time = 0;

  /*
   * @int waiting
   * Holds unterminated processes index
   * */
  int waiting;

  memset(&temp_resources, 0, sizeof(temp_resources));

  do{

  printf("====================================\n");
    printf("PRESS ENTER...\n");
  printf("====================================\n");
    printf("::Time(%d) -->P[%d]::\n",time,index);
    show_processes();

    time +=1;
    unlock = 0;

    /*Review resources conditions */
    if(process[index].terminated == false){

      for(int subindex = 0; subindex < RESOURCES; subindex++){
        if(process[index].needed[0][subindex] <= resource[index].available[0][subindex])
            unlock +=1;
        else break;
      }

      /*Unlock IF has resources*/
      if(unlock == RESOURCES){

        printf("-Unlocked P[%d]\n",process[index].id);
        processes_free++;

        /*Moves resources*/
        for(int subindex = 0; subindex < RESOURCES; subindex++){
          /*IF index == last process list*/
          if(index == PROCESSES-1){
            /*Allocation*/
            process[index].allocation[0][subindex] += process[index].needed[0][subindex];
            /*Available*/
            temp_resources[subindex] = resource[index].available[0][subindex] - process[index].needed[0][subindex];
            /*New Available*/
            resource[0].available[0][subindex] = process[index].allocation[0][subindex] + temp_resources[subindex];
            /*Clean Needed*/
            process[index].needed[0][subindex] = resource[index].max[0][subindex] - process[index].allocation[0][subindex];
            /*Mark terminated true*/
            process[index].terminated = true;
          }else{
            /*Allocation*/
            process[index].allocation[0][subindex] += process[index].needed[0][subindex];
            /*New Available*/
            temp_resources[subindex] = resource[index].available[0][subindex] - process[index].needed[0][subindex];
            /*Clean Needed*/
            process[index].needed[0][subindex] = resource[index].max[0][subindex] - process[index].allocation[0][subindex];
            /*Mark terminated true*/
            process[index].terminated = true;

            /* Asign new resources to unterminated processes*/
            for(waiting = index +1; waiting < PROCESSES; waiting++){
              if(process[waiting].terminated == false){
                resource[waiting].available[0][subindex] = process[index].allocation[0][subindex] + temp_resources[subindex];
                break;
              }
            }

          }
        }

      }
      /*Moves resources*/
      else{

          printf("-Locked P[%d]\n",process[index].id);
          /*IF index == last process list*/
          if(index == PROCESSES-1){
            for(int subindex = 0; subindex < RESOURCES; subindex++){
              resource[0].available[0][subindex] = resource[index].available[0][subindex];
              resource[index].available[0][subindex] = 0;
            }
          }else{
            for(int subindex = 0; subindex < RESOURCES; subindex++){
              resource[index+1].available[0][subindex] = resource[index].available[0][subindex];
              resource[index].available[0][subindex] = 0;
            }
          }

      }
    }

    printf("-Free(%d)\n", processes_free);
    printf("------------------------------\n");
    getchar();
    index +=1;

    /*IF index == last process list*/
    if(index == PROCESSES) index = 0;

    /*IF all PROCESSES are free*/
    if(processes_free == PROCESSES){ free_processes = true; }

  }while(free_processes == false);
  show_processes();
}
