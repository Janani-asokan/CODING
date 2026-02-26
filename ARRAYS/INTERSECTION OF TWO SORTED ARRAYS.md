```cpp

class Solution {
public:
    vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {
        vector<int>ans;
        int j =0;
        int i =0;
        int n = nums1.size();
        int m = nums2.size();
        while(i<n && j<m)
        {
            if(nums1[i] == nums2[j])
            {
                ans.push_back(nums1[i]);
                j++;
                i++;
            }
            else if(nums1[i] > nums2[j])
            {
               j++; 
            }
            else{
                i++;
            }
        }return ans;
        
    }
};



```
Time Complexity: O(M+N), where M and N are the lengths of the given arrays.
This is because both the arrays are traversed once.

Space Complexity: O(min(m, n)), extra space to store answer is not considered.


---

brute force

```cpp

class Solution {
public:
    vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();  
    vector<int>visited(m,0);
    vector<int>ans;
    for(int i=0;i<n;i++)
    {
        for(int j =0;j<m;j++)
        {
            if(nums1[i]==nums2[j] && visited[j]==0)
            {
                ans.push_back(nums2[j]);
                visited[j] =1;
                break;
            }
            else if(nums1[i]<nums2[j]) break;
        }
    }return ans;
    }
};

```

---

Complexity Analysis 
Time Complexity: O(MxN), where M is the length of nums1 and N is the length of nums2.

Space Complexity: O(N), where N is size of nums2, extra space to store answer is not considered.


---

```cpp

class Solution {
public:
    vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {

        unordered_set<int> s(nums2.begin(), nums2.end());
        vector<int> ans;

        for(int x : nums1)
        {
            if(s.count(x))
            {
                ans.push_back(x);
                s.erase(x);
            }
        }
        return ans;
    }
};

```

---



```cpp
if(s.count(x))
```

---

# 🔹 First understand what `x` is

This loop:

```cpp
for(int x : nums1)
```

means:

👉 Take each element from `nums1` one by one.

Example:

```cpp
nums1 = {1,2,3}
```

Loop runs like this:

```
x = 1
x = 2
x = 3
```

---

# 🔹 What is `s`?

Earlier we created:

```cpp
unordered_set<int> s(nums2.begin(), nums2.end());
```

Example:

```cpp
nums2 = {2,3,4}
```

So set becomes:

```
s = {2,3,4}
```

---

# 🔹 What does `s.count(x)` mean?

It means:

👉 "Check if x exists in the set"

It returns:

```
1 → if exists
0 → if does not exist
```

---

# 🔹 Example dry run

nums1:

```
{1,2,3}
```

nums2:

```
{2,3,4}
```

Set:

```
s = {2,3,4}
```

---

## Iteration 1:

```
x = 1
```

Check:

```cpp
s.count(1)
```

Result:

```
0 (not present)
```

So skip.

---

## Iteration 2:

```
x = 2
```

Check:

```cpp
s.count(2)
```

Result:

```
1 (present)
```

So enter if block:

```cpp
ans.push_back(x);
```

Now:

```
ans = {2}
```

---

## Iteration 3:

```
x = 3
```

Check:

```cpp
s.count(3)
```

Result:

```
1
```

Add to answer:

```
ans = {2,3}
```

---

# 🔹 Simple meaning of Step 4

```cpp
if(s.count(x))
```

means:

👉 "If current element of nums1 exists in nums2"

---

# 🔹 Even simpler real-life example

nums1 = your bag 🎒
nums2 = your friend's bag 🎒

HashSet = friend's bag items list

You check each item in your bag:

```
Do you also have this item?
```

If YES → add to common list

---

# 🔹 Visual diagram

```
nums1:   1   2   3
nums2:   2   3   4

Set:    {2,3,4}

Check:

1 → no
2 → yes → add
3 → yes → add
```

Result:

```
{2,3}
```

---

# 🔹 What happens inside computer (fast lookup ⚡)

HashSet uses special hashing so checking:

```cpp
s.count(x)
```

takes:

```
O(1) time → instant
```

instead of slow search.

---

# 🔹 Summary in one line

```cpp
if(s.count(x))
```

means:

👉 "If x is present in nums2"

---


