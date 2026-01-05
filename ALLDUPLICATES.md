https://leetcode.com/problems/find-all-duplicates-in-an-array/solutions/



```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
     
    int n = nums.size();
    vector<int> result;
    vector<int> freq(n + 1, 0); // Create frequency array initialized to 0
    
    // Count frequencies of elements
    for (int i = 0; i < n; i++) {
        freq[nums[i]]++;
    }
    
    // Find elements with frequency greater than 1
    for (int i = 0; i <= n; i++) {
        if (freq[i] > 1) {
            result.push_back(i);
        }
    }
    
    return result;
}


    
};

```
Time Complexity: 

O(n), where 

n is the size of the array. This is because we are making two passes over the array: one for counting the frequency of elements, and another for collecting duplicates.
Space Complexity: 

O(n), because we are using an extra freq[] array of size 

n+1 to store frequencies. Additionally, the space for storing the result (vector<int> result) contributes to the space complexity, but it will be at most 

O(n).
JUST MODIFICATION OF THIS CODE IN DUPLICATES IN ARRAY:

```cpp

#include<bits/stdc++.h>

using namespace std;
int findDuplicate(vector < int > & arr) {
  int n = arr.size();
  int freq[n + 1] = {
    0
  };
  for (int i = 0; i < n; i++) {
    if (freq[arr[i]] == 0) {
      freq[arr[i]] += 1;
    } else {
      return arr[i];
    }
  }
  return 0;
}
int main() {
  vector < int > arr;
  arr = {1,3,4,2,3};
  cout << "The duplicate element is " << findDuplicate(arr) << endl;
}
```

optimized soln:
The code you provided is based on Floyd's Cycle Detection Algorithm (Tortoise and Hare), 
which is specifically designed to detect one duplicate number in a list, assuming the list contains numbers in a
cycle-like structure.
However, it does not work for finding multiple duplicates.

Problem with Current Code:
Returning a Single Duplicate: The current code only returns one value (slow), and it's trying to find a cycle.
But you're supposed to return all duplicates.
Input List with Multiple Duplicates: The given problem asks to find all duplicates, so we need a different 
approach that handles multiple duplicates.
Modifying the Code:
Since you are tasked with finding all duplicates, l
et's modify your current approach to a more appropriate solution that works with finding multiple duplicates.

Optimized Code:
Here's a solution that finds all duplicates in the list:

```cpp
    
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        
        // Iterate through the array
        for (int i = 0; i < nums.size(); i++) {
            // Get the absolute value of the current element
            int index = abs(nums[i]) - 1; 
            
            // If the value at the corresponding index is negative, it's a duplicate
            if (nums[index] < 0) {
                result.push_back(abs(nums[i]));
            } else {
                // Mark the value at the index as visited by negating it
                nums[index] = -nums[index];
            }
        }
        
        return result;
    }
};

```
Explanation:
We loop through each element in the array.
For each number, we calculate its absolute value and treat it as an index (adjusted by -1
because arrays are 0-indexed).
If the value at that index is already negative, it means the number is a duplicate.
Otherwise, we negate the value at the corresponding index to mark it as visited.
Finally, we collect all the duplicates and return them.
Example:
Input:

plaintext
Copy code
nums = [4,3,2,7,8,2,3,1]
Output:

plaintext
Copy code
[2, 3]
Time and Space Complexity:
Time Complexity: 

O(n), where 

n is the number of elements in the array. We only loop through the array once.
Space Complexity: 

O(1) (excluding the space for the result vector), since we are modifying the array in place.
Why This Works:
By using the array itself to track visited elements by negating them,
we avoid the need for extra memory, making the solution both time and space efficient 
for this particular problem. This approach also avoids the need for cycle detection
(as in the original Tortoise and Hare algorithm),
which is not suitable when multiple duplicates are present.

nums = [4, 3, 2, 7, 8, 2, 3, 1]
Step 1:
Current element: nums[0] = 4
Calculate the index: abs(4) - 1 = 3
Check nums[3] = 7, which is positive.
So, negate it: nums[3] = -7
Array after Step 1:

css
Copy code
nums = [4, 3, 2, -7, 8, 2, 3, 1]
Step 2:
Current element: nums[1] = 3
Calculate the index: abs(3) - 1 = 2
Check nums[2] = 2, which is positive.
So, negate it: nums[2] = -2
Array after Step 2:

css
Copy code
nums = [4, 3, -2, -7, 8, 2, 3, 1]
Step 3:
Current element: nums[2] = -2 (we use absolute value).
Calculate the index: abs(-2) - 1 = 1
Check nums[1] = 3, which is positive.
So, negate it: nums[1] = -3
Array after Step 3:

css
Copy code
nums = [4, -3, -2, -7, 8, 2, 3, 1]
Step 4:
Current element: nums[3] = -7 (use absolute value).
Calculate the index: abs(-7) - 1 = 6
Check nums[6] = 3, which is positive.
So, negate it: nums[6] = -3
Array after Step 4:

css
Copy code
nums = [4, -3, -2, -7, 8, 2, -3, 1]
Step 5:
Current element: nums[4] = 8
Calculate the index: abs(8) - 1 = 7
Check nums[7] = 1, which is positive.
So, negate it: nums[7] = -1
Array after Step 5:

css
Copy code
nums = [4, -3, -2, -7, 8, 2, -3, -1]
Step 6:
Current element: nums[5] = 2
Calculate the index: abs(2) - 1 = 1
Check nums[1] = -3, which is already negative. This means we've encountered the number 2 before, so it's a duplicate!
Add 2 to the result list.
Array after Step 6:

css
Copy code
nums = [4, -3, -2, -7, 8, 2, -3, -1]
Result so far: [2]

Step 7:
Current element: nums[6] = -3 (use absolute value).
Calculate the index: abs(-3) - 1 = 2
Check nums[2] = -2, which is already negative. This means we've encountered the number 3 before, so it's a duplicate!
Add 3 to the result list.
Array after Step 7:

css
Copy code
nums = [4, -3, -2, -7, 8, 2, -3, -1]
Result so far: [2, 3]

Step 8:
Current element: nums[7] = -1 (use absolute value).
Calculate the index: abs(-1) - 1 = 0
Check nums[0] = 4, which is positive.
So, negate it: nums[0] = -4
Array after Step 8:

css
Copy code
nums = [-4, -3, -2, -7, 8, 2, -3, -1]
Final Result:
After iterating through all the elements, the duplicates are stored in the result list:

csharp
Copy code
[2, 3]
Time and Space Complexity:
Time Complexity: 

O(n), because we iterate through the array once, performing constant-time operations on each element.
Space Complexity: 

O(1), because we are not using any extra space except for the result vector 
(which doesn't count as extra space since the problem asks us to return the result).
