#include <assert.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>

#define N 10

int *xs = 0;

void print_xs(void)
{
    assert(N >= 1);
    printf("%d", xs[0]);
    for (int i = 1; i < N; ++i) {
        printf(" %d", xs[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{

    //do you want to shared to any one mapstahre other wise mapprivate
    // back to any file map anonymous
    
xs  =(int*) mmap(NULL,N*sizeof(int), 
            PROT_READ |PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,
            0,0
        );
        assert(xs != MAP_FAILED);
    for (int i = 0; i < N; ++i) {
        xs[i] = i+1;
     // std::cout<<xs[i]<<std::endl;
    }

    pid_t child_pid = fork();
    assert(child_pid != -1);

    if (child_pid == 0) {
        //child
        for (int i = 0; i < N / 2; ++i) {
            int t = xs[i];
            xs[i] = xs[N - i - 1];
            xs[N - i - 1] = t;
        }
        printf("Child:\t");
        while(true){
            print_xs();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        
    } else {
        // parent
        waitpid(child_pid, NULL, 0);
        printf("Parent:\t");
        while(true){
            print_xs();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    return 0;
}