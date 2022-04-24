#include <bits/stdc++.h>

using namespace std;

void mergeKSorted(vector<vector<int> *> runs, vector<int> *rec, int k, int start)
{
    if (k <= 0)
        return;

    int *index = new int[k];
    for (int i = 0; i < k; i++)
    {
        index[i] = 0;
    }

    int count = 1;
    while (count > 0)
    {
        count = 0;

        int min = INT_MAX, minIndex = -1;
        for (int i = start; i < start + k; i++)
        {
            if (index[i - start] != -1 && min > runs[i]->at(index[i - start]))
            {
                min = runs[i]->at(index[i - start]);
                minIndex = i - start;
                count++;
            }
        }

        if (count > 0)
        {
            rec->push_back(min);
            index[minIndex]++;

            int s = runs[start + minIndex]->size();
            if (s == index[minIndex])
                index[minIndex] = -1;
        }
    }

    delete[] index;
    return;
}

void MergeRuns(vector<vector<int> *> &runs, int B)
{
    if (runs.size() <= 1)
        return;

    vector<vector<int> *> run2;
    vector<int> *rec = new vector<int>();

    int h = runs.size() / (B - 1);
    for (int i = 0; i < h; i++)
    {
        int offset = i * (B - 1);
        mergeKSorted(runs, rec, B - 1, offset);

        run2.push_back(rec);
        rec = new vector<int>();
    }

    int h1 = runs.size() % (B - 1);
    if (h1 > 0)
    {
        int offset = h * (B - 1);
        mergeKSorted(runs, rec, h1, offset);

        run2.push_back(rec);
    }

    runs = run2;
    MergeRuns(runs, B);

    return;
}

void ExternalSort(vector<int> records, vector<vector<int> *> &runs, int B, int pageSize)
{
    // Pass 0: creating runs of size B pages
    vector<int> *rec = new vector<int>();
    for (int i = 0; i < records.size(); i++)
    {
        rec->push_back(records[i]);

        if (rec->size() % (B * pageSize) == 0)
        {
            sort(rec->begin(), rec->end());
            runs.push_back(rec);

            rec = new vector<int>();
        }
    }

    if (rec->size() > 0)
    {
        sort(rec->begin(), rec->end());
        runs.push_back(rec);

        rec = new vector<int>();
    }

    // B-1 way Merge
    MergeRuns(runs, B);

    return;
}

int main()
{
    int B, pageSize, numRecords;
    cin >> B >> pageSize >> numRecords;

    int numPages = ceil((float)numRecords / (float)pageSize);

    vector<int> records;
    for (int i = 0; i < numRecords; i++)
    {
        int x;
        cin >> x;

        records.push_back(x);
    }

    if (B < 3)
    {
        sort(records.begin(), records.end());
        for (int i = 0; i < records.size(); i++)
        {
            cout << records[i] << endl;
        }
    }
    else
    {
        vector<vector<int> *> runs;
        ExternalSort(records, runs, B, pageSize);

        // Print
        // cout << runs.size() << endl;
        // cout << runs[0]->size() << endl;
        for (int i = 0; i < runs[0]->size(); i++)
        {
            cout << runs[0]->at(i) << endl;
        }
    }
    return 0;
}