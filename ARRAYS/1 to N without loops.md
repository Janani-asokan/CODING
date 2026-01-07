
 "Recursion" involves two key elements:


1.the base case (or termination case).
2. the recursive case.


Understanding these elements is crucial for solving recursive problems. I used to encounter challenges with recursion, but I've recently started learning and solving problems to improve my understanding.


here is some of the problem which is solved till now are.


Print 1 to N || vice verca

Height of a Binary Tree.

Sort an array using recursion

Sort a stack using recursion.

Delete middle Element Using stack.

Reverse stack Using recursion.

here is the code of
---
You are given an integer N. Print numbers from 1 to N without the help of loops.

Examples:


Input: N = 5
Output: 1 2 3 4 5
Explanation: We have to print numbers from 1 to 5.


Input: N = 10
Output: 1 2 3 4 5 6 7 8 9 10
Explanation: We have to print numbers from 1 to 10.


Approach: If we take a look at this problem carefully, we can see that the idea of “loop” is to track some counter value, e.g., “i = 0” till “i <= 100”. So, if we aren’t allowed to use loops, how can we track something?

Well, one possibility is the use of ‘recursion‘, provided we use the terminating condition carefully. Here is a solution that prints numbers using recursion. 
 

// C++ program to How will you print
//  numbers from 1 to n without using a loop?
#include <iostream>
using namespace std;
```cpp
class gfg {

    // It prints numbers from 1 to n.
public:
    void printNos(unsigned int n)
    {
        if (n > 0) {
            printNos(n - 1);
            cout << n << " ";
        }
        return;
    }
};

// Driver code
int main()
{
    int n = 10;
    gfg g;
    g.printNos(n);
    return 0;
}

```
Output
1 2 3 4 5 6 7 8 9 10 
Time Complexity: O(n)
Auxiliary Space: O(n)

Below is the Python equivalent of the given C++ program to print numbers from 1 to \( N \) without using loops. It uses recursion to achieve this.

### Python Implementation

```python
def print_numbers(n):
    if n > 0:
        # Recursive call to print numbers up to n-1
        print_numbers(n - 1)
        # Print the current number
        print(n, end=" ")

# Example usage
N = 10  # Change this to any positive integer
print_numbers(N)
```

### How it Works
1. **Base Case**:
   - The function stops calling itself once \( n \) becomes 0, preventing infinite recursion.
   
2. **Recursive Step**:
   - The function first calls itself with \( n - 1 \), progressing towards the base case.
   - After returning from the recursive call, it prints the current value of \( n \).

### Example Walkthrough

**Input**:
```python
N = 5
```

**Execution**:
1. `print_numbers(5)` calls `print_numbers(4)`.
2. `print_numbers(4)` calls `print_numbers(3)`.
3. `print_numbers(3)` calls `print_numbers(2)`.
4. `print_numbers(2)` calls `print_numbers(1)`.
5. `print_numbers(1)` calls `print_numbers(0)` (base case reached, returns without doing anything).
6. After `print_numbers(0)` returns:
   - `print(1)` is executed.
   - `print(2)` is executed.
   - `print(3)` is executed.
   - `print(4)` is executed.
   - `print(5)` is executed.

**Output**:
```plaintext
1 2 3 4 5
```

### Complexity
- **Time Complexity**: \( O(n) \)
   - Each number from 1 to \( n \) is processed exactly once.
- **Auxiliary Space**: \( O(n) \)
   - Due to the recursive function calls, the call stack grows to a depth of \( n \).

This approach is simple and effectively replaces loops with recursion.
**Print 1 To N**
```cpp
void oneton(int n){
    if(n == 1){
        cout << n<<" ";
        return;
    }
    oneton(n-1);
    cout << n;
    return;
}

```
---

**Height of a binary Tree.**

```cpp

int maxDepth(TreeNode* root) {
        if(root == NULL){
            return 0;
            
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return 1 + max(left,right);
        
    }

```
---

**Sort an array Using Recursion.**

approch for this code is , 

we first try to decrease the size of the array and then sort the array while we decrese it
```cpp

void insertin(vector<int> & nums,int temp){
       if(nums.size() == 0 || nums[nums.size()-1] <= temp){
           nums.push_back(temp);
           return;
       }
       int val = nums[nums.size() -1];
       nums.pop_back();
       insertin(nums,temp);
       nums.push_back(val);
       return;
   }
   void arraysort(vector<int>& nums){
       if(nums.size() == 1){
           return;
       }
       int temp = nums[nums.size()-1];
       nums.pop_back();
       arraysort(nums);
       insertin(nums,temp);
       return;
       
   }
```
   ---
   
**Sort Stack Using Recursion.**

```cpp

void insertin(stack<int> &st,int temp){
    if(st.empty() || st.top() <= temp){
        st.push(temp);
        return;
    }
    int val = st.top();
    st.pop();
    insertin(st,temp);
    st.push(val);
    return;
}

void sortstack(stack<int> &st){
    if(st.size() == 1){
        return;
    }
    int temp = st.top();
    st.pop();
    sortstack(st);
    insertin(st,temp);
    return;

}

```
---

**Delete Middle Element in stack Using Recursion.**

```cpp

Here d is the middle elemnt d = ( st.size()/2 ) +1 

void delstack(stack<int> &st,int d){
    if(st.size() == d){
        st.pop();
        return;
    }
    int temp = st.top();
    st.pop();
    delstack(st,d);
    st.push(temp);
    return;
    
}

```
---

**Reverse Stack Using recursion**

```cpp

void insertin(stack<int> &st,int ele){
    if(st.empty()){
        st.push(ele);
        return;
    }
    int temp = st.top();
    st.pop();
    insertin(st,ele);
    st.push(temp);
    return;
}
void revstack(stack<int> &st){
    if(st.empty()){
        return;
    }
    int ele = st.top();
    st.pop();
    revstack(st);
    
    insertin(st,ele);
    return;
}

```
---
7 . [Subsets]

```cpp
	void subset(vector<int> & nums, vector<int>temp, int i,vector<vector<int>> &ans){
        if(i >=  nums.size()){
            ans.push_back(temp);
            
            return;
        }
        subset(nums,temp,i+1,ans);
        temp.push_back(nums[i]);
        subset(nums,temp,i+1,ans);
        
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;
        subset(nums,temp,0,ans);
        return ans;
    }

```

---

Subset ||

```cpp
	void print(vector<int>&nums, int i, vector<int>ss,set<vector<int>>&st){
        
        if(i >= nums.size()){
            st.insert(ss);
            return;
        }
        print(nums,i+1, ss,st);
        int ele = nums[i];
        ss.push_back(ele);
        print(nums,i+1, ss,st);
        
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        set<vector<int>>st;
        vector<int>ss;
        sort(nums.begin(), nums.end());
        print(nums,0, ss,st);
        for(auto it = st.begin(); it != st.end(); it++){
            res.push_back(*it);
            
        }
        return res;
        
            
    }


    ```
