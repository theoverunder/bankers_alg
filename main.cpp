

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <unistd.h>

#include "bank.h"
#include "customer.h"
// NUMBER_OF_CUSTOMERS 5
// NUMBER_OF_RESOURCES 3
using namespace std;
int maxResources[NUMBER_OF_RESOURCES];
int count = 0;
//bank b1(0);
pthread_mutex_t mutex, mutex1;


bank * b1;
 void *createCustomer(void* params)
{
    
     pthread_mutex_lock(&mutex);
     cout << "Maximum Resources Needed for Process:\n";
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        maxResources[i] = rand() % MAX_RESOURCE_TOTAL;
        cout << maxResources[i] << endl;
    }
    while(true) {
    
    customer customerThread(maxResources, count, b1);
    count++;
    pthread_mutex_unlock(&mutex);
    int c = 0;
    int requestedResources[NUMBER_OF_RESOURCES];
    c = rand() % 2;
    if(c == 0)
    {   // request
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            requestedResources[i] = customerThread.rand_request(i);
        }
         pthread_mutex_lock(&mutex1);
         sleep(rand() % 10 );
         
                 for(int i = 0; i < NUMBER_OF_RESOURCES; i ++)
                 {
                     cout << "Process requesting: " << requestedResources[i] << " of resource " << i << endl;
                 }
        if(b1->request_resources(customerThread.returnId(), requestedResources) == 1)
        {
            cout << "Resource Request Allocated Successfully \n";
            customerThread.decrementNeed(requestedResources);
        }
        else
        {
            cout << "Resource Request Denied\n";
        }
          pthread_mutex_unlock(&mutex1);
    }
    else
    { // release
        int releaseResources[NUMBER_OF_RESOURCES];
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            releaseResources[i] = customerThread.rand_request2(i, *b1);
        }
        
        b1->release_resources(customerThread.returnId(), releaseResources);
        for(int i = 0; i < NUMBER_OF_RESOURCES; i ++)
        {
            cout << "Process released: " << releaseResources[i] << " of resource " << i << endl;
        }
        sleep(25);
    }
    
    }
    
}


int main(int argc, char** argv) {
//    int customer_needs[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {{1, 2, 3}, 
//        {2, 4, 3}, 
//        {3, 4, 2},
//        {3, 2, 1},
//        {2, 2, 2}};
    //customer * customers[NUMBER_OF_CUSTOMERS];
    int a,b,c;
    cout << "How many instances of resource A?: " << endl;
    cin >> a;
    cout << "How many instances of resource B?: " << endl;
    cin >> b;
    cout << "How many instances of resource C?: " << endl;
    cin >> c;
    b1 = new bank(a, b, c);
    pthread_attr_t thread_attributes;
    pthread_t threads[NUMBER_OF_CUSTOMERS];
    
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex1, NULL);
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        pthread_create(&threads[i], NULL, &createCustomer, NULL);
       // cout << "something" << endl;
        
    }
     for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
       
        pthread_join(threads[i], NULL);
   }
    
    
    
    
    return 0;
}

