#include<iostream>
#include<cassert>

using namespace std;

template<class t>
class binary_tree
{
private:
    struct node
    {
        t iteam;
        node* right;
        node* left;
    };
    node* root;
    int length;
    void Preorder(node* p) // root left right
        {
            if(p != NULL)
            {
                cout << p->iteam << " ";
                Preorder(p->left);
                Preorder(p->right);
            }
        }
        void Inorder(node* p) // left right root
        {
            if(p != NULL)
            {
                Inorder(p->left);
                cout << p->iteam << " ";
                Inorder(p->right);
            }
        }
        void Postorder(node* p) // left right root
        {
            if(p != NULL)
            {
                Postorder(p->left);
                Postorder(p->right);
                cout << p->iteam << " ";
            }
        }
        int max(int a , int b)
        {
            return a >= b ? a : b;
        }
        int height(node* p)
        {
            if(p == NULL) return 0;
            else return 1 + max(height(p->left),height(p->right));
        }
        void clear(node* &p)
        {
            if(p != NULL)
            {
                clear(p->left);
                clear(p->right);
                delete p;
                p = NULL;
            }
        }
        int NodeCount(node* p)
        {
             return p == NULL? 0 : 1 + NodeCount(p->left) + NodeCount(p->right);
        }
        int LeavesCount(node* p)
        {
            if(p == NULL) return 0;
            else if(p->left == NULL && p->right == NULL) return 1;
            else return LeavesCount(p->left) + LeavesCount(p->right);
        }
        bool RecSearch(node* p , t element)
        {
            if(p == NULL) return false;
            else if (p->iteam == element) return true;
            else if (p->iteam > element) return RecSearch(p->left , element);
            else return RecSearch(p->right , element);
        }
        void Delete(node* &p)
        {
            node *curr;
            node *prev;
            node *temp;
            if(p->left == NULL && p->right == NULL)
            {
                delete p;
                p = NULL;
            }
           else if(p->left == NULL)
            {
                temp = p;
                p = p->right;
                delete temp;
            }
            else if(p->right == NULL)
            {
                temp = p;
                p = p->left;
                delete temp;
            }
            else
            {
                curr = p->left;
                prev = NULL;
                while(curr->right != NULL)
                {
                    prev = curr;
                    curr = curr->right;
                }
                p->iteam = curr->iteam;
                if(prev == NULL)
                p->left = curr->left;
                else
                prev->right = curr->left;

                delete curr;
            }
        }
public:
        binary_tree()
        {
            root = NULL;
            length = 0;
        }
        bool isempty()
        {
            return root == NULL;
        }
        int size()
        {
            return length;
        }
        int TreeHeight()
        {
            return height(root);
        }
        int TreeNode()
        {
            return NodeCount(root);
        }
        int TreeLeaves()
        {
            return LeavesCount(root);
        }
        void insert(t element)
        {
            node* newnode = new node;
            node* curr;
            node* prev;
            newnode->iteam = element;
            newnode->left = newnode->right = NULL; 
            if(isempty())
            {
                root = newnode;
            }
            else
            {
                curr = root;
                while(curr != NULL)
                {
                    prev = curr;
                    if(curr->iteam == element)
                    {
                        cout << "This element is already exist\n";
                        return;
                    }
                    else
                    {
                        if(curr->iteam < element)
                        curr = curr->right;
                        else 
                        curr = curr->left;
                    }
                }
                if(prev->iteam > element)
                prev->left = newnode;
                else prev->right = newnode;
            }
            length++;
        }
        void Remove(t element)
        {
            node *curr;
            node *prev;
            if(isempty())
            {
                cout << "Tree is empty\n";
                return;
            }
            if (root->iteam == element)
            {
                Delete(root);
                return;
            }
            prev = root;
            if(root->iteam > element)
            curr = root->left;
            else
            curr = root->right;

            while (curr != NULL)
            {
                if(curr->iteam == element) break;
                else
                {
                    prev = curr;
                    if(curr->iteam > element)
                    curr = curr->left;
                    else
                    curr = curr->right;
                }
            }
            if(curr == NULL) cout << "The delete item is not in the tree." << endl;	
            else if(prev->iteam > element)
                Delete(prev->left);
            else
                Delete(prev->right);
        }
        void PreorderTraversal()
        {
            Preorder(root);
        }
        void InorderTraversal()
        {
            Inorder(root);
        }
        void PostorderTraversal()
        {
            Postorder(root);
        }
        
        bool search(t element)
        {
            node* curr = root;
            while (curr != NULL)
            {
                if(curr->iteam == element) return true;
                else if (curr->iteam > element) curr = curr->left;
                else curr = curr->right;
            }
            return false;
        }
        t Research(t element)
        {
            node* curr = root;
            bool found = false;
            while (curr != NULL)
            {
                if(curr->iteam == element)  
                {
                    found = true;    
                    return curr->iteam;
                }
                else if (curr->iteam > element) curr = curr->left;
                else curr = curr->right;
            }
           // throw runtime_error("Element not found");
           return -1;
        }
        bool TreeRecSearch(t element)
        {
            return RecSearch(root , element);
        }
        void ClearTree()
        {
            clear(root);
            length = 0;
        }
        ~binary_tree()
        {
            clear(root);
        }
};

int main()
{
    binary_tree<int> bt;
    bt.insert(50);
    bt.insert(20);
    bt.insert(24);
    bt.insert(23);
    bt.insert(13);
    bt.insert(10);
    bt.insert(15);
    bt.insert(60);
    bt.insert(55);
    bt.insert(65);
    bt.insert(56);
    // bt.Remove(23);
    // bt.Remove(50);
    // bt.InorderTraversal();
    // cout << bt.TreeLeaves() << endl;
    // cout << bt.TreeHeight() << endl;
    // cout << bt.TreeNode() << endl;
    // if(bt.search(40)) cout << "Element found\n";
    // else cout << "Element not found\n";
    return 0;
}