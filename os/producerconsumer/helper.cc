/******************************************************************
 * The helper file that contains the following helper functions:
 * check_arg - Checks if command line input is a number and returns it
 * sem_create - Create number of semaphores required in a semaphore array
 * sem_init - Initialise particular semaphore in semaphore array
 * sem_wait - Waits on a semaphore (akin to down ()) in the semaphore array
 * sem_signal - Signals a semaphore (akin to up ()) in the semaphore array
 * sem_close - Destroy the semaphore array
* Author: Provided by Course Coordinator
 ******************************************************************/

# include "helper.h"

int check_arg (char *buffer)
{
  int i, num = 0, temp = 0;
  if (strlen (buffer) == 0)
    return -1;
  for (i=0; i < (int) strlen (buffer); i++)
  {
    temp = 0 + buffer[i];
    if (temp > 57 || temp < 48)
      return -1;
    num += pow (10, strlen (buffer)-i-1) * (buffer[i] - 48);
  }
  return num;
}

int sem_create (key_t key, int num)
{
  int id;
  if ((id = semget (key, num,  0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    cerr << "ERROR: Error in sem_create(), due to semget() function returning negative semaphore id for SEM_KEY of: " << key << endl;
    return -1;
  }
  return id;
}

int sem_init (int id, int num, int value)
{
  union semun semctl_arg;

  semctl_arg.val = value;
  if (semctl (id, num, SETVAL, semctl_arg) < 0) {
    cerr << "ERROR: Error in sem_init(), due to semctl() function failure for semaphore with index number of: " << num << endl;
    return -1;
  }
  return 0;
}

void sem_wait (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };
  int i;
  i = semop (id, op, 1);
  if (i < 0) { // semop() will return value < 0 if it has failed
    cerr << "ERROR: Error in sem_init(), due to semop() function failure for semaphore with index number of: " << num << endl;
  }
}

void sem_signal (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, 1, SEM_UNDO}
  };
  int i;
  i = semop (id, op, 1);
  if (i < 0) { // semop() will return value < 0 if it has failed
    cerr << "ERROR: Error in sem_signal(), due to semop() function failure for semaphore with index number of: " << num << endl;
  }
}

int sem_close (int id)
{
  int i;
  i = semctl (id, 0, IPC_RMID, 0);
  if (i < 0) {
    cerr << "ERROR: Error in sem_close(), due to semctl() function failure for semaphore with id: " << id << endl;
    return -1;
  }
  return 0;
}
