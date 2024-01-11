#include <bits/stdc++.h>
using namespace std;

void maxArea(vector<int> height){
    int vol = 0;
    vector<pair<int,int>> h_sorted;
    for(int i=0;i<height.size();i++){
        h_sorted[i].first = i;
        h_sorted[i].second = height[i];
    }
    int len = height.size();
    
    sort(h_sorted.begin(), h_sorted.end(), [](auto &left, auto &right) {
    return left.second < right.second;
    });

    for(auto it: h_sorted){
        cout<<it.first<<" "<<it.second<<endl;
    }

    // for(int i=1;i<height.size();i++){
    //     int temp_vol = h_sorted[i-1].second * abs(h_sorted[i].first - h_sorted[i-1].first);
    //     if(vol <temp_vol) vol = temp_vol; 
    // }

    // return vol;

}


int main(){
    vector<int> h;
    int n;

    cin>>n;
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        h.push_back(temp);
    }
    // cout<<"Ans "<<maxArea(h);
    maxArea(h);
    
}