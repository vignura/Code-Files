#include <cstdio>
#include <vector>

using namespace std;

bool isPresent(vector<int> &arr, int num){
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == num){
            return true;
        }
    }
    return false;
}

int minimumSwaps(vector<int> arr) {
    int iCycleLen = 0;
    int j = 0;
    int iMinSwaps = 0;
    vector<int> isVisited(arr.size(), 0);

    printf("isVisited len: %d\n", isVisited.size());

    for(int i = 0; i < arr.size(); i++){
        iCycleLen = 0;
        j = i;
        if(!isVisited[j]){
            do{
                isVisited[j] = 1;
                printf("%d -> ", arr[j]);
                j = (arr[j] -1);
                iCycleLen++;

            }while((arr[i] != arr[j]) && (iCycleLen < arr.size()));
            
            printf("%d len: %d\n", arr[j], iCycleLen);
            iMinSwaps += (iCycleLen - 1);  
        }
    }
    return iMinSwaps;
}

int main()
{
    vector<int> arr;
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(1);
    printf("minimum Swaps: %d\n", minimumSwaps(arr));
    return 0;
}