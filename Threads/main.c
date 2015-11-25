//
//Matthew Szczeblewski
//
//Program Description
//Generate a Fibonacci Sequence based on user input.
//Pass the sequence generation along to threads which will return the values to the parent thread and output them.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



struct thread_data{
    
    int num;
    char *info;
    int fibSequence[50];
};

void getFib(void *ptr);
void print(struct thread_data *thread_array);


int main(){
    //Create 4 structures to store inputs, name/info, and the Fibonacci sequence
    struct thread_data thread_array[4];
    thread_array[0].info="Matthew";
    thread_array[1].info="Szczeblewski";
    thread_array[2].info="CPSC";
    thread_array[3].info="ESU";
    
    //Thread IDs
    pthread_t thread[4];

    //Take input from user
    printf("Please enter 4 Integers\n" );
    scanf("%d %d %d %d", &thread_array[0].num, &thread_array[1].num, &thread_array[2].num, &thread_array[3].num);

    //Create the 4 threads, Pass the fib function to them and pass my structures as an argument
    pthread_create(&thread[0], NULL, (void *) &getFib, (void *) &thread_array[0]);
    pthread_create(&thread[1], NULL, (void *) &getFib, (void *) &thread_array[1]);
    pthread_create(&thread[2], NULL, (void *) &getFib, (void *) &thread_array[2]);
    pthread_create(&thread[3], NULL, (void *) &getFib, (void *) &thread_array[3]);
    
    //Use the join command to make the main wait untill all threads complete their tasks
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    
    //Print out my Name,CPSC,ESU and the Fibonacci sequences
    print(&thread_array[0]);
    print(&thread_array[1]);
    print(&thread_array[2]);
    print(&thread_array[3]);
    
    return 0;
}

//Pass my storage structure into the function to clean up the printing sequence of the info and Fibonacci sequences
void print(struct thread_data *thread_array){
    int i;
    
    printf("\n");
    printf("%s ", thread_array->info);

    for (i=0; i<thread_array->num; i++) {
        printf("%i ", thread_array->fibSequence[i]);
    }
}

//
void getFib(void *ptr){
    //Typcasting my arguments passed into the thread since they must go in as a void
    struct thread_data *t_info;
    t_info = (struct thread_data *) ptr;
    
    int i;
    double prev= -1;
    double result= 1;
    double sum;
    
    //Generating the fibonacci sequence non recursively so I can store each value into my array for printing later
    for(i=0;i <= t_info->num; i++){
        sum= result + prev;
        prev= result;
        result= sum;
        t_info->fibSequence[i]= sum;
    }
    pthread_exit(0);
}
