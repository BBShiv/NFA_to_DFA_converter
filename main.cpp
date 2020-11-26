#include <iostream>
#include <vector>
using namespace std;
int searchArr (int n, string arr[], string key);
int searchArr2 (int n, int arr[], int key);
int searchArr3 (int n, char arr[], char key);
int searchVector (vector <int> v , int key);
vector<int > e_closure(vector<int > t, vector<vector <int> > rules, vector<vector <int> > numOfRules ,int numOfAlphabets , char alphabets[]);
int main()
{
    cout<<"Enter the number of alphabets : ";
    int numOfAlphabets;
    cin>>numOfAlphabets;
    char alphabets[numOfAlphabets];
    for(int i=0; i<numOfAlphabets ; i++)
    {
        cout<<"Enter the elements of alphabets ( l if NFA contains Landa ): ";
        cin>>alphabets[i];
    }

    cout<<"\nEnter the number of states : ";
    int numOfStates;
    cin>>numOfStates;
    string states[numOfStates];
    for(int i=0 ; i<numOfStates ; i++)
    {
        cout<<"Enter the names of states : ";
        cin>>states[i];
    }
    vector <vector<int> >rules;
    int numOfRules2[numOfStates][numOfAlphabets];
    string rule;
    vector <int> row;
    row.clear();
    cout<<"Rules : \n";
    for(int i=0 ; i<numOfStates ; i++)
    {
        for(int j=0 ; j<numOfAlphabets ; j++)
        {
             cout<<"Enter the number of rules for "<<states[i]<<" with "<<alphabets[j]<<" : ";
             int num;
             cin>>num;
             while (alphabets[j] != 'l' && num <= 0 )
             {
                 cout<<"It must be positive.\nEnter the number of rules for "<<states[i]<<" with "<<alphabets[j]<<" : ";
                 cin>>num;
             }
             numOfRules2[i][j] = num;
             for(int k=0 ; k<num ; k++)
             {
                 cout<<states[i]<<" with "<<alphabets[j]<<" is : ";
                cin>>rule;
                while (searchArr(numOfStates, states, rule) == -1 )
                {
                    cout<<"The input state is not in state list.\n"<<states[i]<<" with "<<alphabets[j]<<" is : ";
                    cin>>rule;
                }
                row.push_back(searchArr(numOfStates, states, rule));
            }
        }
        rules.push_back(row);
        row.clear();
    }
    cout<<"Enter the start state : ";
    string start;
    cin>>start;
    while (searchArr(numOfStates, states, start) == -1 )
    {
        cout<<"The input alphabet is not in alphabet list.\n"<<"Enter the start state : ";
        cin>>start;
    }
    cout<<"Enter the number of final states : ";
    int numOfFinal;
    cin>>numOfFinal;
    int finalStates[numOfFinal];
    string finalState;
    for(int i=0 ; i<numOfFinal ; i++)
    {
        cout<<"Enter the elements of final states : ";
        cin>>finalState;
        while (searchArr(numOfStates, states, finalState) == -1 )
        {
            cout<<"The input state is not in state list.\n"<<cout<<"Enter the elements of final states : ";
            cin>>finalState;
        }
        finalStates[i] = searchArr(numOfStates, states, finalState);
    }
    vector<vector<int> > numOfRules;
    for(int i=0 ; i<numOfStates ; i++)
    {
        vector <int> num;
        num.clear();
        for(int j=0 ; j< numOfAlphabets ; j++)
        {
            num.push_back(numOfRules2[i][j]);
        }
        numOfRules.push_back(num);
    }
    //////////////////////////////////////////////////////////////
    vector<vector<int> > Dtrans;
    vector <int> start2;
    start2.clear();
    start2.push_back(searchArr(numOfStates, states, start));
    vector <int> kk = e_closure(start2,rules,numOfRules,numOfAlphabets,alphabets);
    Dtrans.push_back(kk);
    vector <bool> DtransStatus;
    DtransStatus.push_back(false);
    bool endd = true;
    while (endd)
    {
        for(int i=0 ; i<Dtrans.size(); i++)
        {
            if(!DtransStatus.at(i))
            {
                DtransStatus.at(i) = true;
                cout<<"Dtrans : ";
                for(int n=0 ; n<Dtrans[i].size() ; n++)
                    cout<<Dtrans[i][n]<<"\t";
                cout<<endl<<endl;
                vector <int> temp;
                temp.clear();
                for(int k=0 ; k<numOfAlphabets ; k++)
                {
                    if(alphabets[k] == 'l')
                        continue;
                    cout<<"with "<<alphabets[k]<<" : ";
                    temp.clear();
                    for(int j=0 ; j<Dtrans[i].size() ; j++)
                    {
                        int p=0;
                        for(int m=0 ; m<numOfAlphabets ; m++)
                        {
                            if(m==k)
                                break;
                            p += numOfRules2[Dtrans[i][j]][m];
                        }
                        for(int m=0 ; m<numOfRules2[Dtrans[i][j]][k] ; m++)
                        {
                            if(searchVector(temp, rules[Dtrans[i][j]][p+m]) == -1)
                                temp.push_back(rules[Dtrans[i][j]][p+m]);
                        }
                    }
                    bool equall;
                    vector <int> temp2;
                    temp2.clear();
                    temp2 = e_closure(temp, rules, numOfRules, numOfAlphabets, alphabets);
                    for(int q=0; q<temp2.size(); q++)
                        cout<<temp2.at(q)<<"\t";
                    cout<<endl<<endl;
                    for(int m=0 ; m<Dtrans.size() ; m++)
                    {
                        equall = false;
                        if(Dtrans[m].size() != temp2.size() )
                            continue;
                        for(int o=0 ; o<Dtrans[m].size() ; o++)
                        {
                            if(temp2[o] == Dtrans[m][o])
                            {
                                equall = true;
                            }
                            else
                                equall = false;
                        }
                        if(equall)
                        {
                            break;
                        }
                    }
                    if(!equall)
                    {
                        Dtrans.push_back(temp2);
                        DtransStatus.push_back(false);
                    }
                }
            }
        }
        for(int i=0 ; i<DtransStatus.size() ; i++)
        {
            if( !DtransStatus.at(i))
            {
                break;
            }
            if(i == DtransStatus.size()-1)
                endd = false;
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////
    int DFA_Rules [Dtrans.size()][numOfAlphabets];
    for(int i=0 ; i<Dtrans.size() ; i++)
    {
        vector <int> temp;
        temp.clear();
        for(int k=0 ; k<numOfAlphabets ; k++)
        {
            if(alphabets[k] == 'l')
            {
                DFA_Rules[i][k] = -1;
                continue;
            }
            temp.clear();
            for(int j=0 ; j<Dtrans[i].size() ; j++)
            {
                int p=0;
                for(int m=0 ; m<numOfAlphabets ; m++)
                {
                    if(m==k)
                        break;
                    p += numOfRules2[Dtrans[i][j]][m];
                }
                for(int m=0 ; m<numOfRules2[Dtrans[i][j]][k] ; m++)
                {
                    if(searchVector(temp, rules[Dtrans[i][j]][p+m]) == -1)
                        temp.push_back(rules[Dtrans[i][j]][p+m]);
                }
            }
            bool equall;
            vector <int> temp2;
            temp2.clear();
            temp2 = e_closure(temp, rules, numOfRules, numOfAlphabets, alphabets);
            for(int m=0 ; m<Dtrans.size() ; m++)
            {
                equall = false;
                if(Dtrans[m].size() != temp2.size() )
                    continue;
                for(int o=0 ; o<Dtrans[m].size() ; o++)
                {
                    if(temp2[o] == Dtrans[m][o])
                    {
                        equall = true;
                    }
                    else
                        equall = false;
                }
                if(equall)
                {
                    DFA_Rules[i][k] = m;
                    break;
                }
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////
    vector <int> DFA_Finals;
    bool ee;
    for(int i=0 ; i<Dtrans.size() ; i++)
    {
        for(int j=0 ; j<Dtrans[i].size() ; j++)
        {
            for(int k=0 ; k<numOfFinal ; k++)
            {
                if(Dtrans[i][j] == finalStates[k])
                {
                    ee = false;
                    for(int m=0 ; m<DFA_Finals.size() ; m++)
                    {
                        if(Dtrans[i][j] == DFA_Finals[m])
                        {
                            ee = true;
                        }
                    }
                    if(!ee)
                    {
                        DFA_Finals.push_back(i);
                    }
                }
            }
        }
    }
    cout<<"\nFinal states : ";
    for(int i=0 ; i<DFA_Finals.size() ; i++)
    {
        cout<<DFA_Finals[i]<<"   ";
    }
    cout<<endl;
    ///////////////////////////////////////////////////////////////////////////////////////
    cout<<"Now NFA converted to DFA, please enter the input string : ";
    string inputString;
    cin>>inputString;
    int nextState = 0;
    for(int i=0 ; i<inputString.size() ; i++)
    {
        char in = inputString.at(i);
        if(searchArr3(numOfAlphabets,alphabets,in) == -1)
        {
            cout<<"The input string is not made from alphabets.\n";
            break;
        }
        nextState = DFA_Rules[nextState][searchArr3(numOfAlphabets,alphabets,in)];
    }
    if(searchVector(DFA_Finals, nextState) != -1)
    {
        cout<<"DFA accepts the input string.\n";
    }
    else
    {
        cout<<"DFA rejects the input string;.\n";
    }
    return 0;
}
int searchArr(int n , string arr[] , string key)
{
    for(int i=0 ; i<n ; i++)
        if( key == arr[i])
            return i;
    return -1;
}
int searchArr2(int n , int arr[] , int key)
{
    for(int i=0 ; i<n ; i++)
        if( key == arr[i])
            return i;
    return -1;
}
int searchArr3(int n , char arr[] , char key)
{
    for(int i=0 ; i<n ; i++)
        if( key == arr[i])
            return i;
    return -1;
}
vector<int > e_closure(vector<int > t, vector<vector <int> > rules, vector<vector <int> > numOfRules, int numOfAlphabets , char alphabets[])
{
    int placeOfLanda;
    char landa = 'l';
    if(searchArr3(numOfAlphabets, alphabets , landa) == -1)
    {
        return t;
    }
    else
        placeOfLanda = searchArr3(numOfAlphabets, alphabets , landa);
    for(int i=0 ; i<t.size() ; i++)
    {
        for(int j=0 ; j<numOfRules[t[i]][placeOfLanda] ; j++)
        {
            int p = 0;
            for(int k=0 ; k<numOfAlphabets ; k++)
            {
                if(alphabets[k] == landa)
                {
                    break;
                }
                p += numOfRules[t[i]][k];
            }
            if(searchVector(t, rules[t[i]][p+j]) == -1)
                t.push_back(rules[t[i]][p+j]);
        }
    }
    return t;
}
int searchVector(vector <int> v , int key)
{
    for(int i=0 ; i< v.size() ; i++)
    {
        if (key == v[i])
            return i;
    }
    return -1;
}
