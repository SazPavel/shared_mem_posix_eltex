#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main()
{
    int md;
    char tmp[] = "Hi!\n";
    caddr_t addr;
    sem_t *sem;
    md = shm_open("shm", O_CREAT|O_RDWR, 0600);
    sem = sem_open("sem", O_CREAT, 0600, 0);
    if(md < 0)
    {
        perror("shm_open");
        exit(-1);
    }
    if(sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(-1);
    }
    if(ftruncate(md, 10) < 0)
    {
        perror("ftruncate");
        exit(-1);
    }
    addr = mmap(0, 10, PROT_WRITE, MAP_SHARED, md, 0);
    if(addr < 0)
    {
        perror("mmap");
        exit(-1);
    }
    sem_post(sem);
    memcpy(addr, tmp, 5);
    sem_wait(sem);
    sleep(3);
    sem_unlink("sem");
    exit(0);
}
