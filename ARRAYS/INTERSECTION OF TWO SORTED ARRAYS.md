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

Good 👍 Step 6 is:

```cpp
s.erase(x);
```

This means:

👉 **Remove the element `x` from the HashSet `s`**

---

# 🔹 Why do we remove it?

To **prevent duplicates in the answer**.

Because HashSet originally contains elements from `nums2`. If we don't remove, same element could be added multiple times.

---

# 🔹 Example WITHOUT erase ❌

```cpp
nums1 = {2,2,2}
nums2 = {2}
```

Step 1: Create set

```cpp
s = {2}
```

Loop through nums1:

Iteration 1:

```
x = 2
s.count(2) → true
ans = {2}
```

Iteration 2:

```
x = 2
s.count(2) → true
ans = {2,2} ❌ duplicate
```

Iteration 3:

```
x = 2
s.count(2) → true
ans = {2,2,2} ❌ duplicate
```

Wrong result.

---

# 🔹 Example WITH erase ✅

```cpp
nums1 = {2,2,2}
nums2 = {2}
```

Step 1:

```cpp
s = {2}
```

Iteration 1:

```
x = 2
found in set
ans = {2}
```

Now erase:

```cpp
s.erase(2)
```

Set becomes:

```cpp
s = {}
```

Iteration 2:

```
x = 2
s.count(2) → false
```

Iteration 3:

```
x = 2
s.count(2) → false
```

Final answer:

```cpp
{2} ✅ correct
```

---

# 🔹 Visual diagram

Before erase:

```id="o2f42c"
Set s = {2,3,4}
```

After:

```cpp
s.erase(2);
```

Set becomes:

```id="vvyxt5"
Set s = {3,4}
```

2 is removed.

---

# 🔹 Real-life example 🎒

Set = basket with fruits

```
Basket = {apple, banana, mango}
```

You pick apple and put in answer.

Now remove apple from basket:

```
Basket = {banana, mango}
```

So you won't pick apple again.

---

# 🔹 What erase does internally

```cpp
s.erase(x);
```

means:

```
Find x in set
Delete it
```

---

# 🔹 Summary

```cpp
s.erase(x);
```

means:

👉 Remove element from set
👉 Prevent duplicate answers
👉 Ensure intersection contains unique elements

---

# 🔹 Full simple flow

```cpp
Set s = {2,3,4}

nums1 = {1,2,2,3}

Check 1 → no
Check 2 → yes → add → erase 2
Set = {3,4}

Check 2 → no
Check 3 → yes → add → erase 3
Set = {4}

Final answer = {2,3}
```

---

If you want, I can explain the **entire code in one picture-style dry run** so you fully master HashSet questions (very common in interviews).


