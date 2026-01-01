
**Before going into the solution lets focus on the mistakes**

**This is the incorrect code**

---

```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size()-1;
        vector<int>a;
        for(int i =0;i<n;i++)
        {
            if(nums[i] == nums[i+1]) #Duplicates are not guaranteed to be adjacent important thing i learnt
            {
                a.push_back(nums[i]);
            }
            
        }return a;
        
    }
};

```
 **here is the explanation of incorrect logic**

 Your code has several **syntax errors** and **logic issues**. Let’s go through them briefly, then I’ll give you a **correct working solution**.

---

## What’s wrong in your code

1. **Out-of-bounds access**

```cpp
nums[i+1]
```

When `i == n-1`, `i+1` is invalid.

2. **Wrong duplicate logic**
   Duplicates are **not guaranteed to be adjacent**, so `nums[i] == nums[i+1]` won’t work.

3. **Invalid assignment**

```cpp
a = nums[i];
```

`a` is a `vector<int>`, not an `int`. You should use `a.push_back(nums[i]);`

4. **Extra `i++` inside loop**
   You already increment `i` in the `for` loop.

5. **Missing return statement**
   Your function must return `a`.

---

## Correct & Efficient Solution (O(n) time, O(1) extra space)

This is the **standard LeetCode approach** using index marking.

### Idea

* Numbers are in range `[1, n]`
* Use the index corresponding to a number
* Mark visited numbers by negating values
* If already negative → duplicate found

---



 


442. Find All Duplicates in an Array
Solved
Medium
Topics
Companies
Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output

 https://leetcode.com/problems/find-all-duplicates-in-an-array/description/

 https://www.geeksforgeeks.org/problems/two-repeated-elements-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]
Example 2:

Input: nums = [1,1,2]
Output: [1]
Example 3:

Input: nums = [1]
Output: []

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

OPITMAL 

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
Let’s go through a dry run of the code with an example input step-by-step.

Suppose the input array is:
```cpp
nums = [4, 3, 2, 7, 8, 2, 3, 1]
```

### Initial Setup
1. We initialize an empty `result` vector to store the duplicates.
2. We will iterate through each element in `nums`, and for each element, we calculate an index based on its absolute value (adjusted by subtracting 1 since array indices are 0-based).

### Step-by-Step Dry Run
Let’s go through each iteration and understand what happens.

#### Iteration 1:
- **`i = 0`**: `nums[0] = 4`
  - `index = abs(nums[0]) - 1 = 4 - 1 = 3`
  - `nums[3] = 7` (value at index 3 is positive)
  - Mark `nums[3]` as visited by negating it: `nums[3] = -7`
  - **Updated `nums`**: `[4, 3, 2, -7, 8, 2, 3, 1]`

#### Iteration 2:
- **`i = 1`**: `nums[1] = 3`
  - `index = abs(nums[1]) - 1 = 3 - 1 = 2`
  - `nums[2] = 2` (value at index 2 is positive)
  - Mark `nums[2]` as visited by negating it: `nums[2] = -2`
  - **Updated `nums`**: `[4, 3, -2, -7, 8, 2, 3, 1]`

#### Iteration 3:
- **`i = 2`**: `nums[2] = -2` (already negative due to previous step)
  - `index = abs(nums[2]) - 1 = 2 - 1 = 1`
  - `nums[1] = 3` (value at index 1 is positive)
  - Mark `nums[1]` as visited by negating it: `nums[1] = -3`
  - **Updated `nums`**: `[4, -3, -2, -7, 8, 2, 3, 1]`

#### Iteration 4:
- **`i = 3`**: `nums[3] = -7` (already negative due to previous step)
  - `index = abs(nums[3]) - 1 = 7 - 1 = 6`
  - `nums[6] = 3` (value at index 6 is positive)
  - Mark `nums[6]` as visited by negating it: `nums[6] = -3`
  - **Updated `nums`**: `[4, -3, -2, -7, 8, 2, -3, 1]`

#### Iteration 5:
- **`i = 4`**: `nums[4] = 8`
  - `index = abs(nums[4]) - 1 = 8 - 1 = 7`
  - `nums[7] = 1` (value at index 7 is positive)
  - Mark `nums[7]` as visited by negating it: `nums[7] = -1`
  - **Updated `nums`**: `[4, -3, -2, -7, 8, 2, -3, -1]`

#### Iteration 6:
- **`i = 5`**: `nums[5] = 2`
  - `index = abs(nums[5]) - 1 = 2 - 1 = 1`
  - `nums[1] = -3` (value at index 1 is negative, indicating a duplicate)
  - Add `abs(nums[5]) = 2` to `result`
  - **Updated `result`**: `[2]`

#### Iteration 7:
- **`i = 6`**: `nums[6] = -3` (already negative)
  - `index = abs(nums[6]) - 1 = 3 - 1 = 2`
  - `nums[2] = -2` (value at index 2 is negative, indicating a duplicate)
  - Add `abs(nums[6]) = 3` to `result`
  - **Updated `result`**: `[2, 3]`

#### Iteration 8:
- **`i = 7`**: `nums[7] = -1` (already negative)
  - `index = abs(nums[7]) - 1 = 1 - 1 = 0`
  - `nums[0] = 4` (value at index 0 is positive)
  - Mark `nums[0]` as visited by negating it: `nums[0] = -4`
  - **Updated `nums`**: `[-4, -3, -2, -7, 8, 2, -3, -1]`

### Final Result
After all iterations, `result` contains the duplicates found in the array:
```cpp
result = [2, 3]
```

### Summary
This algorithm effectively identifies duplicates by using the input array itself to mark visited indices. By making elements at certain indices negative, it tracks if an index has been visited more than once, which signals a duplicate.

---

 There are two issues in the code:

1. **Out-of-Bounds Error in the Loop**:  
   The loop currently iterates with `i < nums.size() + 2`. This will cause an out-of-bounds access error because you’re trying to access elements beyond the end of the `nums` array. The loop should only iterate up to `nums.size()` to avoid going beyond the bounds of the array.

2. **Index Calculation**:  
   In this line:
   ```cpp
   int index = abs(nums[i]);
   ```
   `index` is intended to be a 0-based index. However, `nums[i]` can be any integer in the range `[1, n]`, so `index` should be calculated as `abs(nums[i]) - 1`. Without subtracting 1, you’re accessing an out-of-bounds index if `index == nums.size()`.

### Corrected Code:
Here’s the corrected code with these changes:

```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        
        // Iterate through the array
        for (int i = 0; i < nums.size(); i++) {
            // Get the correct index by subtracting 1
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

### Explanation of Changes
1. **Loop Bound**: Changed `nums.size() + 2` to `nums.size()` to prevent accessing elements outside of the array.
2. **Index Calculation**: Changed `int index = abs(nums[i]);` to `int index = abs(nums[i]) - 1;` to ensure we’re using a 0-based index correctly.
   

This corrected version should now work as expected without errors.

 ---
 
** GFGs**


 

You are given an integer n and an integer array arr of size n+2. All elements of the array are in the range from 1 to n. Also, all elements occur once except two numbers which occur twice. Find the two repeating numbers.
Note: Return the numbers in their order of appearing twice. So, if x and y are repeating numbers, and x's second appearance comes before the second appearance of y, then the order should be (x, y).

Examples:

Input: n = 4, arr[] = [1, 2, 1, 3, 4, 3]
Output: 1 3
Explanation: In the given array, 1 and 3 are repeated two times, and as 1's second appearance occurs before 2's second appearance, so the output should be 1 3.
Input: n = 2, arr[] = [1, 2, 2, 1]
Output: 2 1
Explanation: In the given array, 1 and 2 are repeated two times and second occurence of 2 comes before 1. So the output is 2 1.
Expected Time Complexity: O(n).
Expected Auxiliary Space: O(1). 

```cpp

class Solution {
  public:
    // Function to find two repeated elements.
    vector<int> twoRepeated(int n, int arr[]) {
        // Your code here
        vector<int>ans;
        for(int i=0;i<n+2;i++)
        {
            int index = abs(arr[i]);
        if(arr[index]<0) ans.push_back(index);
        else arr[index] = -arr[index];
        if(ans.size()==2) break;
        }return ans;
    }
};


```

n = 4
arr = {1, 2, 1, 3, 4, 3}
We are looking for two repeating numbers in the array, which are in the range 1 to n.

Step-by-Step Dry Run
Initial Array State: {1, 2, 1, 3, 4, 3}

First Iteration (i = 0):

Current element: arr[0] = 1
index = abs(arr[0]) = 1
arr[1] is positive, so negate arr[1] to mark 1 as seen.
Array after change: {1, -2, 1, 3, 4, 3}
Second Iteration (i = 1):

Current element: arr[1] = -2
index = abs(arr[1]) = 2
arr[2] is positive, so negate arr[2] to mark 2 as seen.
Array after change: {1, -2, -1, 3, 4, 3}
Third Iteration (i = 2):

Current element: arr[2] = -1
index = abs(arr[2]) = 1
arr[1] is negative, indicating 1 is a duplicate.
Add 1 to ans.
Array remains: {1, -2, -1, 3, 4, 3}
ans = {1}
Fourth Iteration (i = 3):

Current element: arr[3] = 3
index = abs(arr[3]) = 3
arr[3] is positive, so negate arr[3] to mark 3 as seen.
Array after change: {1, -2, -1, -3, 4, 3}
Fifth Iteration (i = 4):

Current element: arr[4] = 4
index = abs(arr[4]) = 4
arr[4] is positive, so negate arr[4] to mark 4 as seen.
Array after change: {1, -2, -1, -3, -4, 3}
Sixth Iteration (i = 5):

Current element: arr[5] = 3
index = abs(arr[5]) = 3
arr[3] is negative, indicating 3 is a duplicate.
Add 3 to ans.
Array remains: {1, -2, -1, -3, -4, 3}
ans = {1, 3}
Exit the loop since ans now contains two elements.
Final Output
ans = {1, 3}
Explanation of the Result
The duplicates 1 and 3 were detected in the order they appear for the second time, resulting in the output 1 3.

---


Given a list of array elements with all unique elements, except one element which comes two times, find that duplicate number. It was similar to this Repeating element except the array elements were not from 1 to n. I gave him the hashing solution but he wanted it in O(1) space complexity and O(n) time complexity.

If the array elements are unique except for one duplicate, and the elements are not constrained to be from 1 to n, you can solve this problem in \( O(n) \) time and \( O(1) \) space by using the **XOR method**.

### Explanation of the XOR Method:
1. XOR has a unique property where:
   - \( a \oplus a = 0 \) (any number XORed with itself is 0)
   - \( a \oplus 0 = a \) (any number XORed with 0 is the number itself)
2. When you XOR all numbers in the array, the duplicate number will remain, as every other unique number cancels out itself due to the XOR property.

### Solution:
To implement this, simply XOR all elements in the array. The result will be the duplicate element.

Here's how it works in code:

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int xorResult = 0;

        // XOR all elements in the array
        for (int num : nums) {
            xorResult ^= num;
        }

        return xorResult;
    }
};
```

### Example:
Consider the input array:
```cpp
nums = [5, 2, 3, 4, 5]
```


- XOR all elements:
  - \( 5 \oplus 2 \oplus 3 \oplus 4 \oplus 5 \)
  - Result: `5` (since the unique elements cancel out, leaving only the duplicate)

### Explanation of Complexity:

![10 11 2024_13 32 43_REC](https://github.com/user-attachments/assets/ee858f07-7cf7-47f4-8649-72c31faa994c)


- **Time Complexity**: \( O(n) \), as we are iterating through the array once.
- **Space Complexity**: \( O(1) \), as we use only a single variable `xorResult` to store the XOR result.

This approach meets the requirements of \( O(n) \) time and \( O(1) \) space complexity.


---

The second question he asked was this – In an array, all elements are repeated twice except one element which comes thrice, find that element. I gave him the simple XOR solution, where we XOR all the elements and the final result is the answer.


The XOR solution won't work here because XOR is effective only when elements appear exactly twice (or an odd number of times). In this case, where all elements appear **twice** except for **one element that appears three times**, we need a different approach to find the element appearing three times in \(O(n)\) time and \(O(1)\) space.

### Solution: Bit Manipulation (Sum of Bits)

Here's an efficient approach using bit manipulation based on summing the bits of each position across all numbers:

1. **Count the occurrence of each bit across all numbers**: 
   For each bit position (from 0 to 31 for a 32-bit integer), count the number of `1`s across all numbers in the array.

2. **Modulo 3 for Each Bit**:
   If a bit appears three times in total across all numbers, it means this bit contributes fully to elements that appear twice. The bit of the unique element that appears only once will have a remainder of `1` in that bit position when counted modulo 3. 

3. **Reconstruct the Unique Number**:
   By taking the modulo of the bit count with 3 for each bit position, we can reconstruct the unique element.

### Code:

Here's the code to implement this solution:

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int findUniqueElement(vector<int>& nums) {
        int result = 0;

        // Iterate through each bit position
        for (int i = 0; i < 32; ++i) {
            int bitCount = 0;

            // Count how many numbers have a 1 at the i-th bit position
            for (int num : nums) {
                if (num & (1 << i)) {
                    bitCount++;
                }
            }

            // If bitCount % 3 is 1, this bit belongs to the unique element
            if (bitCount % 3 != 0) {
                result |= (1 << i);
            }
        }

        return result;
    }
};
```

### Explanation:

- **Counting Bits**: For each bit position `i` (from 0 to 31), we count the number of numbers that have a `1` at that bit position.
- **Modulo Operation**: If `bitCount % 3 != 0`, it means this bit position contributes to the unique number (the one that appears three times).
- **Setting the Result**: Set the corresponding bit in the `result` using bitwise OR.

### Complexity Analysis:

- **Time Complexity**: \( O(n) \), since we loop through each element and then each bit position (a constant 32-bit loop).
- **Space Complexity**: \( O(1) \), as we only use a fixed amount of extra space for counting bits.

This approach effectively finds the element that appears three times without needing extra space beyond the counters and operates in linear time.


Sure! I'll walk you through each line of the code with a detailed explanation and a step-by-step dry run to make sure each part of the logic is clear. I'll also include the mathematical reasoning behind the bitwise operations to illustrate how the algorithm works.

### Problem Overview
The code is designed to find a unique element in an array where:
- All elements appear exactly three times except for one element, which appears only once.
- The goal is to identify this unique element using **O(1) space complexity** and **O(n) time complexity**.

### Code Explanation with Dry Run

Given array example: `nums = [2, 2, 3, 2]`  
Binary representations:
- `2` = `0010`
- `3` = `0011`

Expected output: `3`

Here's the code and a detailed dry run through each line.

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int findUniqueElement(vector<int>& nums) {
        int result = 0;
```

1. **Line**: `int result = 0;`
   - **Explanation**: Initialize `result` to `0`. This variable will store the final answer — the unique number in the array that appears only once.
   - **Dry Run**: `result = 0`

```cpp
        for (int i = 0; i < 32; ++i) {
            int bitCount = 0;
```

2. **Line**: `for (int i = 0; i < 32; ++i)`
   - **Explanation**: This loop iterates through each bit position from `0` to `31`. We are analyzing each bit position (for all numbers in `nums`) to determine how many of them have a `1` in that bit position.
   - **Dry Run**: Begin with `i = 0`, representing the least significant bit.

3. **Line**: `int bitCount = 0;`
   - **Explanation**: Initializes `bitCount` to `0` for each bit position `i`. This variable will keep track of the number of `1`s at the `i-th` bit across all elements in `nums`.
   - **Dry Run**: `bitCount = 0`

```cpp
            for (int num : nums) {
```

4. **Line**: `for (int num : nums)`
   - **Explanation**: This nested loop iterates over each element in `nums` to analyze the `i-th` bit of each number.
   - **Dry Run**: Begin iterating over `nums = [2, 2, 3, 2]`.

```cpp
                if (num & (1 << i)) {
                    bitCount++;
                }
```

5. **Line**: `if (num & (1 << i))`
   - **Explanation**: This line checks if the `i-th` bit of `num` is `1`.
     - `(1 << i)` is a bitmask with a `1` only at the `i-th` position. For example, if `i = 1`, then `1 << 1 = 0010`.
     - `num & (1 << i)` performs a bitwise AND operation between `num` and `(1 << i)`. This is non-zero if the `i-th` bit of `num` is `1`.
6. **Line**: `bitCount++`
   - **Explanation**: If the `i-th` bit of `num` is `1`, increment `bitCount` by `1`.
   - **Dry Run (by bit position)**:

      **For `i = 0`** (checking the 0th bit of each number in `nums`):
      - `num = 2` (binary: `0010`): `2 & 1 = 0`, so `bitCount` remains `0`.
      - `num = 2` (binary: `0010`): `2 & 1 = 0`, so `bitCount` remains `0`.
      - `num = 3` (binary: `0011`): `3 & 1 = 1`, so `bitCount` becomes `1`.
      - `num = 2` (binary: `0010`): `2 & 1 = 0`, so `bitCount` remains `1`.

      **For `i = 1`** (checking the 1st bit of each number in `nums`):
      - `num = 2` (binary: `0010`): `2 & 2 = 2`, so `bitCount` becomes `1`.
      - `num = 2` (binary: `0010`): `2 & 2 = 2`, so `bitCount` becomes `2`.
      - `num = 3` (binary: `0011`): `3 & 2 = 2`, so `bitCount` becomes `3`.
      - `num = 2` (binary: `0010`): `2 & 2 = 2`, so `bitCount` becomes `4`.

      **For `i = 2` and above**:
      - For all bits from the 2nd position onwards, `bitCount` remains `0` because the numbers in `nums` have `0`s in these bit positions.

```cpp
            if (bitCount % 3 != 0) {
                result |= (1 << i);
            }
```

7. **Line**: `if (bitCount % 3 != 0)`
   - **Explanation**: After counting the `1`s at the `i-th` position across all numbers, check if `bitCount % 3 != 0`. If `bitCount % 3 == 0`, it means that all numbers contributing `1` to this bit are part of sets of three, hence no unique element in that bit. If `bitCount % 3 != 0`, it indicates that this bit is part of the unique element that doesn’t appear three times.
8. **Line**: `result |= (1 << i);`
   - **Explanation**: If `bitCount % 3 != 0`, set the `i-th` bit in `result` to `1` by using the bitwise OR operation.
   - **Dry Run**:
      - For `i = 0`: `bitCount = 1`, `bitCount % 3 != 0`, so set the 0th bit of `result`. Now, `result = result | (1 << 0) = 1`.
      - For `i = 1`: `bitCount = 4`, `bitCount % 3 != 0`, so set the 1st bit of `result`. Now, `result = result | (1 << 1) = 3`.

After finishing the loop, `result` holds the value `3`.

```cpp
        return result;
    }
};
```

9. **Line**: `return result;`
   - **Explanation**: The function returns the value of `result`, which is the unique element that appears only once in `nums`.

### Final Dry Run Summary
Given `nums = [2, 2, 3, 2]`, the algorithm determines that the element `3` is unique because:
- At bit positions where `3` has `1`s, the counts of `1`s modulo `3` are not zero, indicating these bits belong to the unique number.
  
### Mathematical Formula and Concept
The core formula here is:
1. **Bitwise Counting**: `bitCount % 3 != 0` signifies that the bits at positions where this is true belong to the unique number.
2. **Result Construction**: `result |= (1 << i)` is used to set each bit in the result where the unique number has `1`s, effectively reconstructing the number in `O(1)` space.

This line checks whether the \(i\)-th bit of the current number (`num`) is `1`. Here’s a breakdown of how it works:

```cpp
if (num & (1 << i)) {
    bitCount++;
}
```

### Explanation

1. **Bit Shifting**: 
   - The expression `(1 << i)` takes the number `1` (which in binary is `000...001`) and shifts it left by `i` positions. 
   - This creates a binary number where only the \(i\)-th bit is set to `1`, and all other bits are `0`.
   - For example:
     - If `i = 0`, then `(1 << i)` is `000...001`.
     - If `i = 1`, then `(1 << i)` is `000...010`.
     - If `i = 2`, then `(1 << i)` is `000...100`.
   
2. **Bitwise AND (`&`)**:
   - The expression `num & (1 << i)` checks if the \(i\)-th bit in `num` is `1`.
   - When you perform a bitwise `AND` with `(1 << i)`, the result will be `0` if the \(i\)-th bit in `num` is `0`, and it will be non-zero if the \(i\)-th bit in `num` is `1`.

3. **Condition Check**:
   - If `num & (1 << i)` is non-zero, it means that the \(i\)-th bit in `num` is `1`, so `bitCount` is incremented.

### Example

Suppose `num = 5` (binary `0101`) and we want to check if the 0th, 1st, and 2nd bits are set:

- For `i = 0`:
  - `(1 << 0)` is `0001` (in binary).
  - `0101 & 0001` results in `0001` (non-zero), so the 0th bit in `num` is `1`.
  - `bitCount` would be incremented.

- For `i = 1`:
  - `(1 << 1)` is `0010` (in binary).
  - `0101 & 0010` results in `0000` (zero), so the 1st bit in `num` is `0`.
  - `bitCount` would not be incremented.

- For `i = 2`:
  - `(1 << 2)` is `0100` (in binary).
  - `0101 & 0100` results in `0100` (non-zero), so the 2nd bit in `num` is `1`.
  - `bitCount` would be incremented.

This approach lets the code efficiently check each bit position in `num`.


Let’s break down this line of code:

```cpp
if (bitCount % 3 != 0) {
    result |= (1 << i);
}
```

### Explanation

This line is part of the logic to reconstruct the unique element that appears only once in the array, while every other element appears exactly three times. Here's what each part of the code does:

#### 1. **`bitCount % 3 != 0`**:
- **`bitCount`** is the number of `1` bits at the \(i\)-th position across all the numbers in the array.
- **`bitCount % 3`** computes the remainder when `bitCount` is divided by 3.
  - If all numbers except the unique one appear **three times**, then the total number of `1`s at the \(i\)-th position will be a multiple of 3. 
  - The only exception to this rule will be the unique element, which contributes `1` at the \(i\)-th position just **once**. This causes `bitCount % 3` to be non-zero.
  
So, this condition is checking whether the \(i\)-th bit position has a non-multiple-of-3 count of `1`s, which means this bit belongs to the unique element.

#### 2. **`result |= (1 << i)`**:
- **`1 << i`**: This creates a number where only the \(i\)-th bit is set to `1`, and all other bits are set to `0`. For example:
  - For \(i = 2\), `1 << 2` produces `0100` (binary).
  - For \(i = 3\), `1 << 3` produces `1000` (binary).
  
- **`result |= (1 << i)`**: This uses the **bitwise OR assignment** (`|=`) to set the \(i\)-th bit in the `result` to `1`.
  - If `bitCount % 3 != 0`, this means that the unique number has a `1` at the \(i\)-th bit position. So, this line ensures that the \(i\)-th bit in the `result` will be `1`.

### Why Bitwise OR (`|=`)?
The bitwise OR operator (`|`) is used to modify the `result` while preserving the existing bits. When you perform `result |= (1 << i)`, it ensures that the \(i\)-th bit in `result` is set to `1` without affecting other bits.

### Example
Suppose `bitCount` is `7` (i.e., the total number of `1`s at the \(i\)-th position across all elements). Here’s what happens:

1. `bitCount % 3 = 7 % 3 = 1`, so `bitCount % 3 != 0` (the condition is true).
2. Then, the line `result |= (1 << i)` will set the \(i\)-th bit of `result` to `1`.

If `result` was previously `0110` (binary) and `i = 1`:
- `1 << i` will be `0010` (binary).
- `result |= 0010` will set the second bit of `result`, resulting in `0110 | 0010 = 0110`.

This process continues for all bit positions (from `0` to `31`), ensuring that the `result` is correctly constructed to represent the unique element.

### Summary
- The `bitCount % 3 != 0` checks if the current bit position has been affected by the unique element.
- The `result |= (1 << i)` sets that bit position in the result, which eventually helps in constructing the unique element.
