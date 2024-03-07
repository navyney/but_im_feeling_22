#include <iostream>
#include <fstream>
#include <string>
using namespace std;

    int sum = 0;
    int x;
    double Average;
    
int main(int argc,char* argv[]){

    if(argc <= 1){ 
        cout << "Please input numbers to find average.";}
        
    else{
    for(int i=0;i < argc;i++){
        x = atoi(argv[i]);
        sum += x;
            if(i == argc-1){
                Average = sum/i;
                cout << "---------------------------------" << endl;
                cout << "Average of " << i << " numbers = " << Average << endl;
                cout << "---------------------------------" << endl;
            }
        }
    }

}
