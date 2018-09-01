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
    typedef TreeNode Node;
    std::stack<Node *> m_lhs;
    std::stack<Node *> m_rhs;
    Node *m_root;
    Node *m_left;
    Node *m_right;
    
    void init(Node *root) {
        
        m_left = nullptr;
        m_right = nullptr;
        
        if (root == nullptr)
            return;
        
        Node *curr = root;
        while (curr) {
            m_left = curr;
            m_lhs.push(curr);
            curr = curr->left;
        }
        
        curr = root;
        while (curr) {
            m_right = curr;
            m_rhs.push(curr);
            curr = curr->right;
        }
    }
    
    void getLhs() {
        
        if (m_lhs.empty())
            return;
        
        Node *top = m_lhs.top();
        m_lhs.pop();
        
        Node *curr = top->right;
        while (curr) {
            m_lhs.push(curr);
            curr = curr->left;
        }       
        
        if (m_lhs.empty() == false)
            m_left = m_lhs.top();
        else
            m_left = nullptr;
    }
    
    void getRhs() {
        if (m_rhs.empty())
            return;
        
        Node *top = m_rhs.top();
        m_rhs.pop();
        
        Node *curr = top->left;
        while (curr) {
            m_rhs.push(curr);
            curr = curr->right;
        }                
        
        if (m_rhs.empty() == false)
            m_right = m_rhs.top();
        else
            m_right = nullptr;
    }
    
    bool findTarget(TreeNode* root, int k) {
        if (root == nullptr)
            return false;
        
        init(root);
        
        while (m_left != m_right) {
            int lo = m_left->val;
            int hi = m_right->val;
            
            if (lo + hi > k)
            {
                getRhs();
            }
            else if (lo + hi < k)
            {
                getLhs();
            }
            else
            {
                return true;
            }            
        }
        
        return false;
    }
    
};

