#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// void addCulprits(vector<int> culprits, int culprit)
// {
//     int len = culprits.size();

//     if(len < 1)
//     {
//         culprits.push_back
//     }
// }

int findCulprits(vector<int> culprits, int suspect) {

    int cnt = 0;

    for(int i = 0; i < culprits.size(); i++)
    {
        if(culprits[i] > suspect)
        {
            cnt++;
        }
    }

    return cnt;
}

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {

    int bribes = 0;
    int delta = 0;
    int toCh = 0; 
    vector<int> culprits;
    int Culcnt = 0;

    for(int i = 0; i < q.size(); i++)
    {
        delta = q[i] - (i + 1);
        // positive shift cases
        if(delta > 0)
        {
            if(delta > 2)
            {
                toCh = 1; // true
            }
            bribes += delta;

            culprits.push_back(q[i]);
            //printf("Found culprit: %d\n", q[i]);
        }
        else 
        {
            Culcnt = findCulprits(culprits, q[i]);
            if((Culcnt + delta) > 0)
            {
                // q[i] is also a culprit
                culprits.push_back(q[i]);
                //printf("Found culprit: %d\n", q[i]);
                bribes += (Culcnt + delta);

                if((Culcnt + delta) > 2)
                {
                    toCh = 1; // true
                }
            }
        }

       // printf("[%d] delta: %d \t bribes: %d \t CH: %d\n", i, delta, bribes, toCh);
    }

    if(toCh)
    {
        printf("Too chaotic\n");
    }
    else
    {
        printf("%d\n", bribes);
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

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
