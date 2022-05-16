/*
滑动窗口的题目一般是需要在这个窗口维持某种状态,然后求窗口的最大值,一般是线性复杂度

然后我们需要考虑的就是怎么来记录这种状态的变迁来使窗口移动
*/



//至多包含 K 个不同字符的最长子串:窗口内的字符数需要小于k
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char,int> mp;
        int res=0;
        int cnt=0;
        int l=0,r=0;
        while(r<s.length())
        {
            if(mp[s[r]]==0)
                cnt++;
            mp[s[r]]++;
            while(cnt>k)
            {
                mp[s[l]]--;
                if(mp[s[l]]==0)
                cnt--;

                l++;
            }
            r++;
            res=max(res,r-l);

        }
        return res;
    }
};