#include <iostream>
#include <vector>
#include<ctime>
using namespace std;
vector<int> res;

void print(vector<int>* dq){
    for(int i = dq->size() - 1; i >= 0; i--){
        cout << (*dq)[i];
    }
    cout <<"\ndigit count: "<<dq->size()<< endl;
}


vector<int>* fact(int num){
    register int i,j,rem = 0,l = 0,pdt,size;
    res.push_back(1);
    for(i = 2; i <= num; i++){
        size = res.size();
        for(j = 0; j < size; j++){
            pdt = res[j] * i + rem;
            //cout<<"res["<<j<<"]= "<<res[j]<<"\ti = "<<i<<"\tpdt = "<<pdt<<"\tsize = "<<res.size()<<endl;
            rem = pdt / 10;
            res[j] = pdt % 10;
            //cout<<"rem = "<<rem<<"\tres["<<j<<"]= "<<res[j]<<endl;
            if(j == (res.size() - 1)){
                while(rem > 0){
                    res.push_back(rem % 10);
                    rem /= 10;
                }
                rem = 0;
            }
        }//cout<<endl;
    }
    return &res;    
}

int main(){
    int num;
    vector<int> *res;
    cout <<"factorial finder"<<endl;
    cout <<"enter a number: ";
    cin >> num;
    clock_t start_time = clock();
    res = fact(num);
    print(res);
    cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
    return 0;
}
