#include <iostream>
#include "queue.h"
#include <fstream>
#include <vector>
#include <string>

//structure of customer
//has money spend by customer, arrival time and processing time
struct customer{
    double amount=0;
    int arrival=0;
    int process=0;
};


//this function gets all the data in the file choosed by user and store it in vector of customers
//parameter: filename(user input), customerList(vector)
void readFile(const std::string &filename, std::vector<customer> &customerList){
    std::ifstream in;
    in.open(filename);
    std::string line;
    int count=0;
    customer newCustomer;
    if(in.is_open())
    {
        while(in>>line)
        {
            if(count==0){
                newCustomer.arrival=std::stoi(line);
                count++;
            }
            else if(count==1){
                newCustomer.process=std::stoi(line);
                count++;
            }
            else{
                newCustomer.amount=std::stod(line);
                count=0;
                customerList.push_back(newCustomer);
            }
        }
        in.close();
    }
}

//main function
//calls queue call and other functions
//find all the required data and display it
//return 0
int main(){
    std::string filename;
    std::cout<< "What file would you like to run ";
    std::cin>>filename;
    int cashiers;
    std::cout<<"Number of cashiers  ";
    std::cin>>cashiers;
    std::vector<queue<customer>> cashCounter;
    queue<customer> temp;
    std::vector<customer> customerList;
    readFile(filename,customerList);
    for(int i=0;i<cashiers;i++){
        cashCounter.push_back(temp);    
    }
    int numberOfCustomers=customerList.size();
    for(int i=0;i<numberOfCustomers;i++){
        for(int j=0;j<cashiers;j++){
            if(cashCounter[j].isFree(customerList[i].arrival)){
                cashCounter[j].enqueue(customerList[i]);
                break;
            }
            if(j==cashiers-1){
                int min=cashCounter[0].totalTime();
                int minIndex=0;
                for(int i=1;i<cashiers;i++){
                    if(min>cashCounter[i].totalTime()){
                        min=cashCounter[i].totalTime();
                        minIndex=i;
                    }
                }
                cashCounter[minIndex].enqueue(customerList[i]);
            }
        }
    }
    int max=cashCounter[0].totalTime();
    for(int i=1;i<cashiers;i++){
        if(max<cashCounter[i].totalTime()){
            max=cashCounter[i].totalTime();
        }
    }
    std::cout << "Total time " <<max<< std::endl;
    for(int i=0;i<cashiers;i++){
        std::cout << "Cashier "<<i<<" helped "<<cashCounter[i].getCount()<<" customers and took in $"<<cashCounter[i].getCash() << std::endl;
    }
    return 0;
}
