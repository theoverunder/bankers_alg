
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "bank.h"

class customer
{
private:
    int max[NUMBER_OF_RESOURCES]; //maximum demand of each resource
    int cust_id; //unique id
    int request_resource_count[NUMBER_OF_RESOURCES]; //number of resources to request
    int need[NUMBER_OF_RESOURCES]; //still needed by customer thread
    int randomNeeded;
    
public:
    customer(int maxneeded[], int id, bank * b1)
    {
        for(int i =0; i < NUMBER_OF_RESOURCES; i++)
        {
            max[i] = maxneeded[i];
            need[i] = max[i];
        }
        cust_id = id;
        randomNeeded=0;
        
        b1->enterMaximum(cust_id, max);
    }
    int rand_request(int i)
    {
        int randomNeeded = 0;
        randomNeeded = (rand() % MAX_RESOURCE_TOTAL) + 1;
        if (randomNeeded > need[i])
        {
            randomNeeded = need[i];
        }
        return randomNeeded;
        
    }
    int rand_request2(int i, bank b1)
    {
        int randomNeeded = 0;
        randomNeeded = (rand() % MAX_RESOURCE_TOTAL) + 1;
        if (randomNeeded > b1.returnAllocated(cust_id, i) || randomNeeded < 0)
        {
            randomNeeded = b1.returnAllocated(cust_id, i);
        }
        if (randomNeeded > 0)
        return randomNeeded;
        else
            return 0;
        
    }
    int returnId()
    {
        return cust_id;
    }
    void decrementNeed(int resourcesIssued[])
    {
        for(int i =0; i < NUMBER_OF_RESOURCES; i++)
        {
            need[i] -= resourcesIssued[i];
        }
    }
};

/*
if(bank.request_resources(this->cust_id, request_resource_count)
{
    need[i] -= rand_req();
};*/
#endif /* CUSTOMER_H */

