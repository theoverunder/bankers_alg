
#ifndef BANK_H
#define BANK_H
#include "defines.h"
#include <iostream>
using namespace std;

class bank
{
private:
    int available[NUMBER_OF_RESOURCES];
    int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    
    int Work[NUMBER_OF_RESOURCES];
    int Need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    
    bool finished[NUMBER_OF_CUSTOMERS];
//    need = maximum - allocation
//    need_i is checked for safety
    
    // safety algorithm - needs to determine if resources can be 
    // given and safe sequence of processes to complete
    // request_resources(int customer_num, int res_request[])
    // (2, {1, 3, 0})
public:
    bool request_resources2(int customer_num, int res_request[])
    {
        if(request_check(customer_num, res_request))
        {
            
        }
        else
        {
            
        }
    }
    bool request_check(int customer_num, int res_request[])
    {
         bool looking = true;
            int i = 0;
            int z = 0;
            int processOrder[NUMBER_OF_CUSTOMERS];
            bool Finish[NUMBER_OF_CUSTOMERS];
            for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
            {
                Finish[i] = false;
                for(int j = 0; j < NUMBER_OF_RESOURCES; j++)
                {
                    Need[i][j] = maximum[i][j] - allocation[i][j];
                }
            }
            for(int i = 0; i < NUMBER_OF_RESOURCES; i ++)
            {
                //Available[i] = 10;
                Work[i] = available[i];
                
            }
            
            while(looking)
            {
                int count = 0;
                int count2 = 0;
                if(Finish[i] == false)
                {
                    for(int j = 0; j < NUMBER_OF_RESOURCES; j ++)
                    { 
                        
                        if(Work[j] >= Need[i][j])
                        {
                            count++;
                        }
                    }
                    if(count == NUMBER_OF_RESOURCES)
                    {
                        for(int j = 0; j < NUMBER_OF_RESOURCES; j ++)
                        {
                            
                            Work[j] +=  allocation[i][j];
                            Finish[i] = true;
                            processOrder[z] = i;
                            z++;
                        }
                        
                    }
                    
                }
                else 
                {
                    i++;
                    if(i == NUMBER_OF_CUSTOMERS)
                    {
                        i = 0;
                    }
                }
                for(int p = 0; p < NUMBER_OF_CUSTOMERS; p++)
                {
                    if(Finish[p] == true)
                    {
                        count2++;
                    }
                }
                if(count2 == NUMBER_OF_CUSTOMERS)
                {
                    looking = false;
                    return true;
                }
                i++;
            }
            return false;
       
    }
    bool is_safe(int cust_id, int res_req[]) 
    {
       // int work[NUMBER_OF_RESOURCES] = available;
        bool can_finish[NUMBER_OF_CUSTOMERS] = {0, 0, 0};
        
        if(finished[cust_id] == 0)
        {
            //check to see if resources are available && 
            //customer at cust_id has not used all resources
            for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
                if(res_req[i] > available[i]) // quit if not enough available
                     return false;
            
            // there are enough available - continue
            for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
            {
                // give out resources from request
                available[i] -= res_req[i]; //give the resources to request
                need[cust_id][i] -= res_req[i]; //reduce needed requests for later
                allocation[cust_id][i] += res_req[i]; //adjust allocated resources   
            }
            
            
            
            //find seq of processes  
            for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
            {
                for(int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
                {
                    if(!can_finish[j])
                    {
                        bool n = true;
                        
                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++)
                        {
                            if(need[j][k] > available[k])
                            {
                                n = 0;
                            }
                        }
                        
                        if(n)
                        {
                            can_finish[j] = 1;
                        }
                    }
                }
            }
                //rollback transaction - requested resources if cannot complete
                if(can_finish[cust_id] == false)
                {
                    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
                    {
                        available[i] += res_req[i]; //give the resources to request
                        need[cust_id][i] += res_req[i]; //reduce needed requests for later
                        allocation[cust_id][i] -= res_req[i]; //adjust allocated resources  
                    }
                }
        }
        
        // check if finished
        finished[cust_id] = 1;
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            if(need[cust_id][i] > 0)
            {
                finished[cust_id] = 0;
                break;
            }
        }
        int tempCount = 0;
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            if(can_finish[i] == 1)
            {
                tempCount++;
            }
        }
        if(tempCount == NUMBER_OF_CUSTOMERS)
        {
            return 1;
        }
        return 0;
    }
    
public:
    //bank();
    bank(int a,int b,int c)
    {
        available[0] = a;
        available[1] = b;
        available[2] = c;
        
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            for(int j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                allocation[i][j] = 0;
                //maximum[i][j] = need[i][j] = cust_needs[i][j];
            }
        } 
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            finished[i] = 0;
        }
    }
    
    bool request_resources(int customer_num, int res_request[])
    {
        if(is_safe(customer_num, res_request))
        {
            for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
            {
                available[i] -= res_request[i]; //give the resources to request
                need[customer_num][i] -= res_request[i]; //reduce needed requests for later
                allocation[customer_num][i] += res_request[i]; //adjust allocated resources   
            }
            return 1;
        }
        return 0;
    }
    int returnAllocated(int i, int j)
    {
        return allocation[i][j];
    }
    void enterMaximum(int id, int maxarray[])
    {
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            maximum[id][i] = maxarray[i];
        }
    }
    
    void release_resources(int customer_num, int res_release[])
    {
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            available[i] += res_release[i]; //give the resources to request
            allocation[customer_num][i] -= res_release[i]; //adjust allocated resources 
        }
        
    }
    
    void get_state()
    {
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            for(int j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                cout << allocation[i][j];
                cout << need[i][j];
                
            }
        } 
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            finished[i] = 0;
        }
    }
};


#endif /* BANK_H */

