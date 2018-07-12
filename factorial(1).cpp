#include <iostream>
#include <deque>
#include<ctime>
using namespace std;
deque<int> res;

void print(deque<int>* dq){
    for(int i = 0; i < dq->size(); i++){
        cout << dq->at(i);
    }
    cout <<"\ndigits = "<<dq->size()<< endl;
}


deque<int>* fact(int num){
    register int i,j,rem = 0,l = 0,pdt;
    res.push_front(1);
    for(i = 2; i <= num; i++){
        for(j = l; j >= 0; j--){
            pdt = res[j] * i + rem;
            rem = pdt / 10;
            res[j] = pdt % 10;
            if(j == 0){
                while(rem > 0){
                    res.push_front(rem % 10);
                    rem /= 10;
                    l++;
                }
                rem = 0;
            }
        }
    }
    return &res;    
}

int main(){
    int num;
    deque<int> *res;
    cout <<"factorial finder"<<endl;
    cout <<"enter a number: ";
    cin >> num;
    clock_t start_time = clock();
    res = fact(num);
    print(res);
    cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
    return 0;
}
