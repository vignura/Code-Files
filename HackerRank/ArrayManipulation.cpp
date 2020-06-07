#include <bits/stdc++.h>
#include <cstring>
#include <string.h>
using namespace std;

vector<string> split_string(string);

void print(vector<long>& a)
{
    printf("[ ");
    for (int i = 0; i < a.size(); ++i)
    {
        printf("%d ", a[i]);
    }
    printf(" ]\n");
}

#if 0
// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int> > queries) {

    vector<long> arr(n, 0);
    long max = 0;
    int a, b, k;

    for(int i = 0; i < queries.size(); i++)
    {
        a = queries[i][0];
        b = queries[i][1];
        k = queries[i][2];

        // printf("%d %d %d\n", a, b, k);
        for (int j = a -1; j < b; ++j)
        {
            arr[j] += k;
            if(max < arr[j])
            {
                max = arr[j];
            }
        }

        print(arr);
    }

    // for(int i = 0; i < n; i++)
    // {
    //     if(max < arr[i])
    //     {
    //         max = arr[i];
    //     }
    // }

    printf("max =  %d\n", max);

    return max;
}
long arrayManipulation(int n, vector<vector<int> > queries) {

    // vector<long> arr(n, 0);
    long sum = 0;
    long max = 0;
    int a, b, k;

    for(int i = 0; i < n; i++)
    {
        sum = 0;
        for(int j = 0; j < queries.size(); j++)
        {
            if(((i + 1) >= queries[j][0]) && ((i + 1) <= queries[j][1]))
            {
                sum += queries[j][2];
            }
        }

        if(max < sum)
        {
            max = sum;
        }
    }

    // for(int i = 0; i < n; i++)
    // {
    //     if(max < arr[i])
    //     {
    //         max = arr[i];
    //     }
    // }

    printf("max =  %d\n", max);

    return max;
}
#else

long arrayManipulation(int n, vector<vector<int> > queries) {

    vector<long> arr(n +1, 0);
    long max = 0, x = 0;
    int a, b, k;

    for(int i = 0; i < queries.size(); i++)
    {
        a = queries[i][0];
        b = queries[i][1];
        k = queries[i][2];

        arr[a] += k;
        if((b + 1) <= n)
        {   
            arr[b + 1] -= k;
        }

        // if(max < arr[a -1])
        // {
        //     max = arr[a -1];
        // }
        
        // printf("%d %d %d\n", a, b, k);
        // for (int j = a -1; j < b; ++j)
        // {
        //     arr[j] += k;
        //     if(max < arr[j])
        //     {
        //         max = arr[j];
        //     }
        // }

        print(arr);
    }

    for(int i = 0; i < n+1; i++)
    {
        x += arr[i];
        if(max < x)
        {
            max = x;
        }
    }

    printf("max =  %d\n", max);

    return max;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int> > queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
