//判断平衡二叉树

//自定向下递归,o(nlogn)-o(n^2)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root)
        return true;

        if(abs(get_depth(root->left) - get_depth(root->right)) > 1)
        return false;

        return isBalanced(root->left) && isBalanced(root->right);



    }

    int get_depth(TreeNode *node)
    {
        if(!node)
        return 0;

        return max(1+get_depth(node->right),1+get_depth(node->left));
    }
};

//自底向上递归,类似于后序遍历
class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);//得到左子树高度
        int rightHeight = height(root->right);//得到右子树高度

        //判断是否满足条件
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
            return -1;
        } else {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }
};


/*
给你二叉树的根结点 root ，此外树的每个结点的值要么是 0 ，要么是 1 。

返回移除了所有不包含 1 的子树的原二叉树。

节点 node 的子树为 node 本身加上所有 node 的后代。


*/
//二叉树剪枝,利用后序遍历的思想
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = pruneTree(root->left); //剪枝左子树
        TreeNode* right = pruneTree(root->right);//剪枝右子树

        //判断根节点是都需要剪枝
        if (root->val == 0 && left == nullptr && right == nullptr) {
            return nullptr;
        }

        //得到剪枝后的树
        root->left = left;
        root->right = right;
        return root;
    }
};


//二叉树镜像,太经典了!
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};


//判断二叉树镜像
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {

        return check(root,root);
    }

    bool check(TreeNode*lnode,TreeNode* rnode)
    {
        if(!lnode && !rnode)
        return true;

        if(!lnode || !rnode)
        return false;
        

        return lnode->val == rnode->val && check(lnode->right,rnode->left) && check(lnode->left,rnode->right);
    }
};


//上下翻转二叉树.这种递归思想真的太巧妙了
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left) return root;           // root->left为null，说明是转换后的根节点
        TreeNode* tmp = upsideDownBinaryTree(root->left);// 先转换左子树
        TreeNode* q = tmp;
        while (q->right) q = q->right;                   // 找到转换后树的最右
        q->left = root->right;                           // root->right设置为左子
        q->right = root;                                 // root设置为右子
        root->left = root->right = 0;                    // 次数不设置会陷入死循环
        return tmp;                                      // 返回转换后的根节点
    }
};
