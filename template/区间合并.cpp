#include <bits/stdc++.h>

using namespace std;


/*区间合并,可以用set来做(数据量较大时)
  整体思路:首先将区间从小到大排序,如果右端点大于下一个区间的左端点,说明有重叠区间,就更新右端点
*/


//常规区间合并:以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 
 vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        int left = intervals[0][0];
        int right = intervals[0][1];

        vector<vector<int>> ans;
        int i=0;
        while(i<intervals.size())
        {
            if(right>=intervals[i][0])
            {
                right=max(right,intervals[i][1]);
                i++;
            }
            else
            {
                ans.push_back({left,right});
                left=intervals[i][0];
                right=intervals[i][1];
                i++;
            }
        }

        ans.push_back({left,right});
        return ans;
}


//线性区间插入:给你一个无重叠的 ，按照区间起始端点排序的区间列表。
//在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
//复杂度为o(n)
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int left=newInterval[0];
    int right=newInterval[1];

    int pos=0;
    vector<vector<int>> ans;
    for(;pos<intervals.size();pos++)
    {
        if(intervals[pos][1]>=left)//说明开始出现重叠了
            break; 
        ans.push_back(intervals[pos]);
    }
    while(pos < intervals.size())//这里合并区间
    {
        if(right<intervals[pos][0]) break;

        left=min(left,intervals[pos][0]);
        right=max(right,intervals[pos][1]);
        pos++;
    }
    ans.push_back({left,right});
    for(;pos<intervals.size();pos++)
    ans.push_back(intervals[pos]);

    return ans;
}


//set保存区间合并,并计算区间总长度,st的erase函数里面是具体的值,还有对应的lower_bound函数
class CountIntervals {
    typedef pair<int, int> pii;

    int ans = 0;
    set<pii> st;

public:
    CountIntervals() {
    }
    
    void add(int left, int right) {
        int L = left, R = right;
        auto it = st.lower_bound(pii(left - 1, -2e9));
        while (it != st.end()) {
            if (it->second > right + 1) break;
            L = min(L, it->second);
            R = max(R, it->first);
            ans -= it->first - it->second + 1;
            st.erase(it++);
        }
        ans += R - L + 1;
        st.insert(pii(R, L));
    }
    
    int count() {
        return ans;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */