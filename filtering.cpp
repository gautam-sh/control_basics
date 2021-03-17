#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
//#include "matplotlibcpp.h" just for git

#define phi 0.7 //tuning parameter

using namespace std;

double filter(double x_curr, double x_prev)
{
    x_curr = phi*x_prev + (1-phi)*x_curr;
    return x_curr;
}

int main()
{
    ifstream fin;
    fin.open("q3_input.csv");
    vector<string> row;//dist,time;
    vector<double> time,dist;
    int i=0; double t,d;
    string line, word, temp;
    while(!fin.eof())
    {
        row.clear();
        getline(fin,line);
        stringstream s(line);
        while(getline(s,word,',')) row.push_back(word);
        //cout<<"copying..."<<endl;
        if(!row.empty())
        {
           if(row[0][0]=='T') continue;
           istringstream(row[0]) >> t;
           istringstream(row[1]) >> d;
           //cout<<t<<" "<<d<<endl;
            //double d = stod(row[1]);
            time.push_back(t);
            dist.push_back(d);
        }
    }

    double x_prev, x_curr;
    vector<double> filtered_dist,filtered_dist2;
    cout<<"After filtering"<<endl<<endl;
    for(int j=0;j<dist.size();j++)
    {
        x_prev = x_curr;
        if(j==0) x_prev = dist[0];
        x_curr = dist[j]; //sensor measurement
        x_curr = filter(x_curr,x_prev);
        filtered_dist.push_back(x_curr);
    }
    for(int j=0;j<dist.size();j++)
    {
        x_prev = x_curr;
        if(j==0) x_prev = filtered_dist[0];
        x_curr = filtered_dist[j]; //sensor measurement
        x_curr = filter(x_curr,x_prev);
        filtered_dist2.push_back(x_curr);
    }

    cout<<"size of time: "<<time.size()<<endl;
    cout<<"size of dist: "<<dist.size()<<endl;
    cout<<"size of filtered_dist: "<<filtered_dist.size()<<endl;

    ofstream filter_obj("q3_filtered_output.csv");
    int size = filtered_dist.size();
    i = 0;
    while(i < size)
    {
        filter_obj << time[i] << ',' << dist[i]<< ',' << filtered_dist[i]<< ',' << filtered_dist2[i]<<endl;
        i++;
    }
    cout<<"q3_filtered_output.csv generated!";
 
}
