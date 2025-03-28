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
    void Preorder(node* p)
        {
            if(p != NULL)
            {
                cout << p->iteam << " ";
                Preorder(p->left);
                Preorder(p->right);
            }
        }
        void Inorder(node* p)
        {
            if(p != NULL)
            {
                Inorder(p->left);
                cout << p->iteam << " ";
                Inorder(p->right);
            }
        }
        void Postorder(node* p)
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
            return a >= b? a : b;
        }
        int height(node* p)
        {
            if(p == NULL) return 0;
            else return 1 + max(height(p->left),height(p->right));
        }
        int BalancedFactor(node* p)
        {
            return p == NULL? 0 :height(p->left) - height(p->right);
        }
        node* LLRotation(node* p)
        {
            node* curr = p->left;
            node* temp = curr->right;
            curr->right = p;
            p->left = temp;
            return curr;
        }
        node* RRRotation(node* p)
        {
            node* curr = p->right;
            node* temp = curr->left;
            curr->left = p;
            p->right = temp;
            return curr;
        }
        node* InsertAVL(node* p,t element)
        {
            if(p == NULL)
            {
                node* newnode = new node;
                newnode->iteam = element;
                newnode->left = newnode->right = NULL;
                length++;
                return newnode;
            }
            if(element > p->iteam)
            p->right = InsertAVL(p->right , element);
            else if(element < p->iteam)
            p->left = InsertAVL(p->left , element);
            else return p;

            int balance = BalancedFactor(p);

            if(balance > 1 && p->right && element > p->right->iteam)
                return RRRotation(p);
    
            else if(balance < -1 && p->left && element < p->left->iteam)
                return LLRotation(p);
        
            else if(balance < -1  && p->left && element > p->left->iteam)
            {
                p->left = RRRotation(p->left);
                return LLRotation(p);
            }

            else if(balance > 1 && p->right && element < p->right->iteam)
            {
                 p->right = LLRotation(p->right);
                 return RRRotation(p);
            }
            return p;
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
    node* Delete_Avl(node* p , t element)
    {
        if(p == NULL) return p;
        else if(p->iteam > element)
            p->left = Delete_Avl(p->left , element);
        else if(p->iteam < element)
            p->right = Delete_Avl(p->right , element);
        else
        {
            node* curr = p; node* prev = NULL;
            if(p->left == NULL && p->right == NULL)
            {
                delete p;
                p = NULL;
            }
            else if(p->left == NULL)
            {
                p = p->right;
                delete curr;
                // return p;
            }
            else if (p->right == NULL)
            {
                p = p->left;
                delete curr;
                // return p;
            }
            else
            {
                prev = curr;
                curr = p->left;
                while (curr->right != NULL)
                {
                    prev = curr;
                    curr = curr->right;
                }

                p->iteam = curr->iteam;
                if(prev == NULL) p->left = curr->left;
                else prev->right = curr->right;
                delete curr;
            }
            
        }
        
        if(!p) return p;

        int balance = BalancedFactor(p);

        if(balance > 1 && BalancedFactor(p->left) >= 0)
            return LLRotation(p);
    
        else if(balance > 1 && BalancedFactor(p->left) < 0)
        {
            p->left = RRRotation(p->left);
            return LLRotation(p);
        }
    
        else if(balance < -1 && BalancedFactor(p->right) <= 0)
            return RRRotation(p);
    
        else if(balance < -1 && BalancedFactor(p->right) > 0)
        {
            p->right = LLRotation(p->right);
            return RRRotation(p);
        }                                                   
        return p;
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
        void insertAVL(t element)
        {
            root = InsertAVL(root , element);
        }
        void RemoveAVL(t element)
        {
            root = Delete_Avl(root , element);
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
            if(curr == NULL) cout<<"The delete item is not in the tree."<<endl;	
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
    binary_tree<int> avl;
    avl.insertAVL(30);
    avl.insertAVL(20);
    avl.insertAVL(40);
    avl.insertAVL(10);
    avl.insertAVL(25);
    avl.insertAVL(35);
    avl.insertAVL(50);
    avl.insertAVL(5);
    avl.insertAVL(15);
    // avl.RemoveAVL(30);
    // avl.InorderTraversal();
    cout << "Postorder Traversal: ";
    avl.PostorderTraversal();
    cout << endl;
    cout << "Preorder Traversal: ";
    avl.PreorderTraversal();
    cout << endl;
    cout << "Inorder Traversal: ";
    avl.InorderTraversal();
    cout << endl;
    cout << "Tree Height: " << avl.TreeHeight() << endl;
    cout << "Tree Node: " << avl.TreeNode() << endl;
    cout << "Tree Leaves: " << avl.TreeLeaves() << endl;
    cout << "Tree Size: " << avl.size() << endl;
    cout << "Is Tree Empty: " << avl.isempty() << endl;
    cout << "Search 25: " << avl.search(25) << endl;
    cout << "Search 100: " << avl.search(100) << endl;
    return 0;
}