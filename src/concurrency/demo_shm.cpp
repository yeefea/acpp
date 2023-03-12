#include <iostream>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  const char *SHM_NAME = "/my_shm"; // name of shared memory
  const int SHM_SIZE = 4096;        // size of shared memory

  int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);                           // create shared memory object
  ftruncate(fd, SHM_SIZE);                                                                // truncate to size
  char *memPtr = (char *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // map shared memory to process

  pid_t child_pid = fork();
  if (child_pid == 0)
  {
    // child process writes data to shared memory
    std::string message = "Hello from child process!";
    strcpy(memPtr, message.c_str());
    exit(0);
  }
  else if (child_pid > 0)
  {
    // parent process reads data from shared memory after child writes it
    wait(NULL);
    std::cout << "Received message from child process: " << memPtr << std::endl;
  }
  else
  {
    std::cerr << "Error forking process." << std::endl;
    return 1;
  }

  munmap(memPtr, SHM_SIZE); // unmap shared memory
  shm_unlink(SHM_NAME);     // destroy shared memory object
  return 0;
}
