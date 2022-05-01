/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> vec1;
    vector<int> vec2;
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        dfs(root1,1);
        dfs(root2,0);
        vector<int> ans;

        int i=0;
        int j=0;
        while(i<vec1.size() && j<vec2.size())
        {
            if(vec1[i]<vec2[j])
            {
                ans.push_back(vec1[i]);
                i++;
            }
            else
            {
                ans.push_back(vec2[j]);
                j++;
            }       
        }

        while(i<vec1.size())
        ans.push_back(vec1[i]),i++;

        while(j<vec2.size())
        ans.push_back(vec2[j]),j++;

        return ans;

    }

    void dfs(TreeNode* node,int flag)
    {
        if(!node)
        return;

        dfs(node->left,flag);
        if(flag)
          vec1.push_back(node->val);
        else
          vec2.push_back(node->val);
        dfs(node->right,flag);
    }



};