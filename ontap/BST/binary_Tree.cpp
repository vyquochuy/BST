#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE{
    int key;
    NODE* pLeft;
    NODE* pRight;

    NODE (int val){
        key = val;
        pLeft = nullptr;
        pRight = nullptr;
    }
};

void Insert(NODE*& root, int x){
    if(root == nullptr){
        root = new NODE(x);
        return;
    }

    if(root->key == x)
        return;
    if(root->key < x)
        Insert(root->pRight, x);
    else
        Insert(root->pLeft, x);
}
//pre orther: duyet truoc
void NLR(NODE *root){
    if(root == nullptr)
        return;
    
    cout << root->key << " ";
    NLR(root->pLeft);
    NLR(root->pRight);
}
//in orther
void LNR(NODE* root){
    if(root == nullptr)
        return;

    LNR(root->pLeft);
    cout << root->key << " ";
    LNR(root->pRight);
}
//post orther
void LRN(NODE* root){
    if(root == nullptr)
        return;

    LRN(root->pLeft);
    LRN(root->pRight);
    cout << root->key << " ";
}

void LevelOrder(NODE* root){
    queue<NODE*> q;
    q.push(root);

    while(!q.empty()){
        int n = q.size();
        for (int i = 0; i < n; i++){
            NODE* temp = q.front();
            q.pop();

            cout << temp->key << " ";

            if(temp->pLeft != nullptr)
                q.push(temp->pLeft);
            if(temp->pRight != nullptr)
                q.push(temp->pRight);
        }
        cout << endl;
    }
}

int Height(NODE* root){
    if(root == nullptr)
        return 0;
    int leftHeight = Height(root->pLeft);
    int rightHeight = Height(root->pRight);

    return 1 + max(leftHeight, rightHeight);
}

int countNODE(NODE *root){
    if(root == nullptr)
        return 0;
    int countLeft = countNODE(root->pLeft);
    int countRight = countNODE(root->pRight);

    return 1 + countLeft + countRight;
}

int sumNODE(NODE* root){
    if(root == nullptr)
        return 0;
    int sumLeft = sumNODE(root->pLeft);
    int sumRight = sumNODE(root->pRight);

    return root->key + sumLeft + sumRight;
}
NODE* Search(NODE* root, int x){
    if(root == nullptr || root->key == x)
        return root;

    if(root->key > x)
        return Search(root->pLeft, x);
    else
        return Search(root->pRight, x);
}

NODE* FindMinRight(NODE* node){
    while(node->pLeft != nullptr){
        node = node->pLeft;
    }
    return node;
}

void Remove(NODE* &root, int x){
    if(root == nullptr)
        return;

    if (x > root->key)
        Remove(root->pRight, x);
    else if (x < root->key)
        Remove(root->pLeft, x);

    else {
        // Trường hợp 1: NODE cần xóa có 1 con
        if (root->pLeft == nullptr) {
            NODE* temp = root;
            root = root->pRight;
            delete temp;
            return;
        }
        else if (root->pRight == nullptr) {
            NODE* temp = root;
            root = root->pLeft;
            delete temp;
            return;
        }
        // Trường hợp 2: NODE cần xóa có 2 con
        else {
            NODE* successor = FindMinRight(root->pRight);
            root->key = successor->key;
            Remove(root->pRight, successor->key);
        }
    }
}

NODE* createTree(int a[], int n){
    NODE* tree = nullptr;
    for(int i = 0; i < n; i++)
        Insert(tree, a[i]);
    
    return tree;
}

void RemoveTree(NODE* &root){
    while(root != nullptr){
        Remove(root, root->key);
    }
    //cout << "xoa het r" << endl;
}

int heightNODE(NODE* root, int value){
    NODE* find = Search(root, value);
    return (find == nullptr) ?  -1 :  Height(find);
}

int Level(NODE* root, NODE* p) {
    if (root == nullptr || p == nullptr)
        return -1;

    queue<NODE*> q;
    q.push(root);

    int level = 1;

    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            NODE* current = q.front();
            q.pop();

            if (current == p)
                return level;

            if (current->pLeft != nullptr)
                q.push(current->pLeft);

            if (current->pRight != nullptr)
                q.push(current->pRight);
        }
        ++level;
    }
    return 0;
}

int countLeaf(NODE* root){
    if(root == nullptr)
        return 0;
    if (root->pLeft == nullptr && root->pRight == nullptr)
        return 1;

    return countLeaf(root->pLeft) + countLeaf(root->pRight);
}

int countLess(NODE* root, int x){
    if(root == nullptr)
        return 0;
    if(root->key > x)
        return countLess(root->pLeft, x);
    else
       	return (root->key != x) + countLess(root->pLeft, x) + countLess(root->pRight, x);
}

int countGrater(NODE* root, int x){
    if(root == nullptr)
        return 0;
    if(root->key < x)
        return countGrater(root->pRight, x);
    else
        return (root->key != x) + countGrater(root->pLeft, x) + countGrater(root->pRight, x);
    
}

bool isBST(NODE* root, int minValue, int maxValue) {
    if (root == nullptr)
        return true;

    // Kiểm tra giá trị của NODE hiện tại
    if (root->key < minValue || root->key > maxValue)
        return false;

    // Kiểm tra cây con bên trái với giới hạn mới
    // Tất cả các giá trị trong cây con bên trái phải nhỏ hơn giá trị của NODE hiện tại
    bool leftValid = isBST(root->pLeft, minValue, root->key - 1);

    // Kiểm tra cây con bên phải với giới hạn mới
    // Tất cả các giá trị trong cây con bên phải phải lớn hơn giá trị của NODE hiện tại
    bool rightValid = isBST(root->pRight, root->key + 1, maxValue);

    return leftValid && rightValid;
}


// tim to tien chung thap nhat cua 2 NODE co gia tri n1 n2
NODE* LCA(NODE *root, int n1, int n2){
    // code here
    NODE* p = Search(root, n1);
    NODE* q = Search(root, n2);
    if (!root || root == q || root == p)
        return root;
    
    NODE  *leftLCA = LCA(root->pLeft, n1, n2);
    NODE *rightLCA = LCA(root->pRight, n1, n2);
    
    if (leftLCA && rightLCA)
        return root;
    
    return leftLCA ? leftLCA : rightLCA;
}

// tim so NODE tren duong di ngan nhat den la
int minDepth(NODE *root) {
    if(root == nullptr)
        return 0;
    // Your code here
    queue<NODE*> q;
    q.push(root);
    int mindepth = 1;
    while(!q.empty()) {
        int n = q.size();
        
        for(int i = 0; i < n; i++){
            NODE* p = q.front();
            q.pop();
            
            if (p->pLeft == nullptr && p->pRight == nullptr)
                return mindepth;
                
            if (p->pLeft != nullptr)
                q.push(p->pLeft);
            
            if (p->pRight != nullptr)
                q.push(p->pRight);
            
        }
        ++mindepth;
    }
    return mindepth;
}

// khi nhin cay tu ben phai
void rightView(NODE *root){
    // Your Code here
    if (root == nullptr)
        return ;
        
    queue<NODE*> q;
    q.push(root);
    while(!q.empty()){
        
        int n = q.size();
        for (int i = 0; i < n; i++){
            NODE* node = q.front();
            q.pop();
            
            if (i + 1 == n)
                cout << node->key << " - ";
            
            if (node->pLeft != nullptr)
                q.push(node->pLeft);
            
            if (node->pRight != nullptr)
                q.push(node->pRight);
            
        }
    }
}

void PreOrderTravelsal(NODE* root1, NODE* root2, vector<int>& c){
    if (root1 == nullptr)
        return;
        
    NODE *k = Search(root2, root1->key);
    if (k != nullptr)
        c.push_back(k->key);

    PreOrderTravelsal(root1->pLeft, root2, c);
    PreOrderTravelsal(root1->pRight, root2, c);
}

vector<int> findCommons(NODE *root1, NODE *root2)
{
    //Your code here
    vector<int> c;
    PreOrderTravelsal(root1, root2, c);
    sort(c.begin(), c.end());
    return c;
}

int main(){
    int a[] = {10, 20, 40, 50, 15, 5, 2, 1, 7, 45, 30};
    int b[] = {19, 30, 70, 22, 2};
    int n = sizeof(a)/sizeof(a[0]);
    int m = sizeof(b)/sizeof(b[0]);

    NODE* tree = createTree(a, n);
    NODE* tree2 = createTree(b, m);
    NLR(tree);  cout << endl;
    LNR(tree);  cout << endl;
    LRN(tree);  cout << endl;
    LevelOrder(tree);    
    
    //RemoveTree(tree);
    cout << "chieu cao cua NODE co gia tri 2 la " << heightNODE(tree, 2);
    cout << "\nlevel cua NODE co gia tri 2 la " << Level(tree, Search(tree, 2));
    cout << "\nso luong la co trong cay nay la " << countLeaf(tree);
    cout << "\nto tien gan nhat cua 2 NODE mang gia tri 15 va 7 la " << LCA(tree, 15, 7)->key;   
    cout << "\nso NODE tren duong di ngan nhat tu root toi 1 la la " << minDepth(tree);
    cout << "\ncay khi nhin tu ben phai \n"; rightView(tree);
    vector<int> Commons = findCommons(tree, tree2);


    return 0;
}