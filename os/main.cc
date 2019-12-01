/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 * Author: Louis Heery
 ******************************************************************/

#include "helper.h"

// Producer Function which produces a certain number of Sleep Jobs depending
// on the number specified by the user per producer thread.
void *producer (void *id);

// Consumer Function which consumes 1 Sleep Job per consumer thread.
void *consumer (void *id);

// Variable Declaration
int bufferItemsCounter; // Counts number of items in Buffer
int inItem; // Stores Location of current Item being added to Buffer by Producer
int outItem; // Stores Location of current Item being removed from Buffer by Consumer

key_t key; // Semaphore Key
int semid; // Semaphore Set ID Number

int sizeOfQueue; // Number of Sleep Jobs which can be stored in the Queue
int jobsPerProducer; // Number of Jobs each Producer can produce
int numProducers; // Number of Producers
int numConsumers; // Number of Consumers

const int MAX_SIZE_OF_QUEUE = 100;
int buffer_array[MAX_SIZE_OF_QUEUE]; // Buffer Array stores Sleep Jobs

int mutex, empty, full; // Stores position of each semaphore in Semaphore Array


int main (int argc, char **argv)
{
  // Checks correct number of arguments have been inputted
  if (argc != 5) {
    cerr << "Incorrect Number of Command Line arguments inputted." << endl;
    exit(-1);
  }


  // Set-up and initialise required data structures and variables
  sizeOfQueue = check_arg(argv[1]);
  jobsPerProducer = check_arg(argv[2]);
  numProducers = check_arg(argv[3]);
  numConsumers = check_arg(argv[4]);


  // Checks Arguments inputted are Numerical Values, and Queue size fits in Maximum Array Size
  if (sizeOfQueue == -1) {
    cerr << "Non-numerical Command Line arguments inputted for size of queue" << endl;
    exit(-1);
  }
  if (sizeOfQueue > MAX_SIZE_OF_QUEUE) {
    cerr << "Command Line arguments inputted for size of queue too large, input a value < " << MAX_SIZE_OF_QUEUE << endl;
    exit(-1);
  }
  if (jobsPerProducer == -1) {
    cerr << "Non-numerical Command Line arguments inputted for jobs per producer" << endl;
    exit(-1);
  }
  if (numProducers == -1) {
    cerr << "Non-numerical Command Line arguments inputted for number of producers" << endl;
    exit(-1);
  }
  if (numConsumers == -1) {
    cerr << "Non-numerical Command Line arguments inputted for number of consumers" << endl;
    exit(-1);
  }

  // Creates Producer and Consumer pthread Arrays
  pthread_t producerid[numProducers]; // stores producer threads
  pthread_t consumerid[numConsumers]; // stores  consumer threads

  // Initialises Items in Buffer and Position of Input and Output locations
  bufferItemsCounter = 0;
  inItem = 0;
  outItem = 0;

  // Set-up and initialise semaphores
  // Assign index values to each semaphore which will be assigned within semid
  mutex = 0;
  empty = 1;
  full = 2;
  
  // Create number of semaphores required in the 'semid' semaphore array
  key = SEM_KEY;
  semid = sem_create(key, 3);

  // Initialise Semaphores
  sem_init(semid, mutex, 1);            // mutual exclusion semaphore -- initial max. number of concurrent processes = 1
  sem_init(semid, empty, sizeOfQueue); // empty semaphore (to ensure buffer is not full) -- initial max. size of queue = sizeOfQueue
  sem_init(semid, full, 0);           // full semaphore (to ensure buffer is not empty) -- initial # of items = 0


  // Create POTIX threads for Producers
  int rc; // stores return code for error detection
  for (int t = 0; t < numProducers; t++) {
    cerr << "In Main: Creating Producer Thread Number " << (t + 1) << endl;
    rc = pthread_create (&producerid[t], NULL, producer, (void *)(intptr_t) t); // Returns 0 if pthread created successfully
    if (rc) { // If rc != 0
      cerr << "ERROR: Return code for pthread_create() is: " << rc << endl;
      exit(-1);
    }
  }

  // Create POTIX threads for Consumers
  for (int t = 0; t < numConsumers; t++) {
    cerr << "In Main: Creating Consumer Thread Number " << (t + 1) << endl;
    rc = pthread_create (&consumerid[t], NULL, consumer, (void *)(intptr_t) t); // Returns 0 if pthread created successfully
    if (rc) { // If rc != 0
      cerr << "ERROR: Return code for pthread_create() is: " << rc << endl;
      exit(-1);
    }
  }

  // Join POTIX threads for all Producers
  for (int t = 0; t < numProducers; t++) { // loops through all producers
    rc = pthread_join (producerid[t], NULL); // Returns 0 if pthread joined successfully

    if (rc) { // If rc != 0
      cerr << "ERROR: Return code for pthread_join() is: " << rc << endl;
      exit(-1);
    }
  }

  // Join POTIX threads for all Consumers
  for (int t = 0; t < numConsumers; t++) { // loops through all consumers
    rc = pthread_join (consumerid[t], NULL); // Returns 0 if pthread joined successfully

    if (rc) { // If rc != 0
      cerr << "ERROR: Return code for pthread_join() is: " << rc << endl;
      exit(-1);
    }
  }


  // Destroys Semaphores in the Semaphore Array
  sem_close(mutex);
  sem_close(empty);
  sem_close(full);

  return 0;
}

void *producer (void *parameter)
{

  // Initialise producer parameter
  int param = (intptr_t) parameter;

  int i = 0; // counts number of jobs produced by producer

  // repeats for each job the producer is required to produce
  while (i < jobsPerProducer) {
    // Producer Sleep for random 1-5 seconds
    int producerSleepDuration = rand() % 5 + 1;
    sleep (producerSleepDuration);

    // Generates Random Sleep Duration (between 1 and 10 seconds)
    // of the Job the Producer is producing
    int buffer_item = rand() % 10 + 1;

    // Waits for the 'empty' Semaphore to checks that there is Space in the Buffer Array
    sem_wait(semid, 1); // empty = at index 1 in semaphore set

    // Waits for the 'mutex' Semaphore to checks that there is Mutual Exclusion of Job Queue
    sem_wait(semid, 0); // mutex = at index 0 in semaphore set

    // Adds Sleep Job to the Queue IF Buffer is not full
    if (bufferItemsCounter < sizeOfQueue) {
      buffer_array[inItem] = buffer_item; // Adds Item to Buffer
      cerr << "Producer(" << (param + 1) << "): Job id " << (inItem + 1) << " duration " << buffer_item << endl; 
      inItem = (inItem + 1) % sizeOfQueue; // Increments current Input Item position by 1
      bufferItemsCounter++; // Increments number of items in Queue counter by 1
    } else {
      sleep(20); // Sleep for 20 seconds
      if (bufferItemsCounter < sizeOfQueue) {
        buffer_array[inItem] = buffer_item; // Add Item to Buffer
        cerr << "Producer(" << (param + 1) << "): Job id " << (inItem + 1) << " duration " << buffer_item << endl;
        inItem = (inItem + 1) % sizeOfQueue; // Increments current Input Item position by 1
        bufferItemsCounter++; // Increments number of items in Queue counter by 1
      } else {
        exit(1); // Otherwise Exit Thread
      }
    }

    // Signals the 'empty' Semaphore
    sem_signal(semid, 1); // empty = at index 1 in semaphore set

    // Signals the 'full' Semaphore
    sem_signal(semid, 2); // full = at index 2 in semaphore set

    i++;

  }

  cerr << "Producer(" << (param + 1) << "): No more jobs to generate." << endl;
  pthread_exit(0); // Exits pthread after Producer Job completed
}

void *consumer (void *id)
{
    // Initialise consumer id
    int myid = (intptr_t) id;

    // Loops indefinitely, will only exit if all Queue Items have been Executed
    while (1) {

      // Waits for the 'full' Semaphore to checks that there is an Item in the Job Queue Array
      sem_wait(semid, 2); // full = at index 2 in semaphore set

      // Waits for the 'mutex' Semaphore to checks that there is Mutual Exclusion of Job Queue
    sem_wait(semid, 0); // mutex = at index 0 in semaphore set

      // Take a job from circular queue & sleep for the duration specified
      int sleepItem; // Stores Length of Sleep Job

      if (bufferItemsCounter > 0) { // Checks There is at least 1 item in Job Queue
        sleepItem = buffer_array[outItem]; // Gets Item from Buffer
        cerr << "Consumer(" << (myid + 1) << "): Job id " << (outItem + 1) << " executing sleep duration " << sleepItem << endl;
        outItem = (outItem + 1) % sizeOfQueue; // Increments current Output Item position by 1
        bufferItemsCounter--; // Decrements number of items in Queue counter by 1
      } else {
        sleep(20); // Sleeps for 20 seconds
        if (bufferItemsCounter > 0) { // Checks There is at least 1 item in Job Queue
          sleepItem = buffer_array[outItem]; // Gets Item from Buffer
          cerr << "Consumer(" << (myid + 1) << "): Job id " << (outItem + 1) << " executing sleep duration " << sleepItem << endl;
          outItem = (outItem + 1) % sizeOfQueue; // Increments current Output Item position by 1
          bufferItemsCounter--; // Decrements number of items in Queue counter by 1
        } else {
          cerr << "Consumer(" << (myid + 1) << "): No more jobs left." << endl;
          pthread_exit(0); // Exits pthread after Producer Job completed
          exit(1); // Otherwise Exit Thread
        }
      }

      // Signals the 'mutex' Semaphore
      sem_signal(semid, 0); // mutex = at index 0 in semaphore set

      // Signals the 'empty' Semaphore
      sem_signal(semid, 1); // empty = at index 1 in semaphore set

    }
}
