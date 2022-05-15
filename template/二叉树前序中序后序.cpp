
//根据前序和后序构建二叉树,用的是递归迭代思路.
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

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {

        return build(preorder,0,preorder.size()-1,postorder,0,postorder.size()-1);

    }

    TreeNode* build(vector<int> &preorder,int pl,int pr,vector<int> &postorder,int pol,int por)
    {
        if(pl>pr || pol>por)
        return nullptr;

        TreeNode* root = new TreeNode(preorder[pl]);

        if(pr==pl)
        return root;


        //这里找出左子树和右子树的分界点,用set属实zz了一点= =
        int len=0;

       for(int i=pol;i<por;i++)
       {
           if(postorder[i] == preorder[pl+1])
           {
               len=i-pol+1;
               break;
           }
       }
         root->left = build(preorder,pl+1,pl+len,postorder,pol,pol+len-1);
         root->right = build(preorder,pl+len+1,pr,postorder,pol+len,por-1);

        return root;
    }
};


//根据前序和中序构建,根据二叉搜索树的前序或后续构建,思路大概一致.






