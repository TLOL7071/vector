#include "test.h"
int main(){
    int option;
    cout<<"0 int-test.\n1 string-test\n2 struct-test\n3 2 dimensions vector\n5 quit\n";
    
    while(1){
        cin>>option;
        switch (option%5){
            case 0:test_int();break;
            case 1:test_string();break;
            case 2:test_struct();break;
            case 3:test_2D();break;
            default:return 0;;
        }
    }
    return 0;
}
