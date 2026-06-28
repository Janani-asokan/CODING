COMPLETE SLIDING WINDOW MASTERY - Pattern-Based Problem Classification
You've given me your complete problem list. Now I'll organize EVERY problem that uses Sliding Window patterns, categorize them by sub-type, and explain exactly which optimal approach to use.

📊 SLIDING WINDOW PROBLEM CLASSIFICATION
Problem	Sliding Window Type	Optimal Approach	Key Insight
Maximum Consecutive Ones	Fixed Window	Single Pass	Track current count, reset on 0
Longest Subarray with Sum K (Positives)	Variable (Max)	Two Pointers	Shrink when sum > K
Longest Subarray with Sum K	Variable (Max)	Prefix Sum + HashMap	Handles negatives
Count Subarrays with Sum K	Counting	Prefix Sum + HashMap	Count frequencies
Count Subarrays with XOR K	Counting	Prefix XOR + HashMap	XOR property
Largest Subarray with Sum 0	Variable (Max)	Prefix Sum + HashMap	First occurrence tracking
Two Sum	Not Sliding	HashMap	Opposite direction
3 Sum	Not Sliding	Sorting + Two Pointers	Opposite direction
4 Sum	Not Sliding	Sorting + Two Pointers	Opposite direction
Sort Colors	Not Sliding	Dutch Flag	Three pointers
Majority Element I	Not Sliding	Boyer-Moore	Voting algorithm
Kadane's Algorithm	Not Sliding	Single Pass	Track max ending here
Stock Buy and Sell	Not Sliding	Single Pass	Track min price
Rearrange by Sign	Not Sliding	Two Pointers	Separate arrays
Next Permutation	Not Sliding	Single Pass	Find dip, reverse
Leaders in Array	Not Sliding	Single Pass	Traverse from right
Longest Consecutive Sequence	Not Sliding	HashSet	Find sequence starts
Set Matrix Zeroes	Not Sliding	Matrix	Use first row/col as markers
Rotate Matrix 90°	Not Sliding	Matrix	Transpose + Reverse
Spiral Matrix	Not Sliding	Matrix	Four boundaries
Pascal's Triangle	Not Sliding	DP	Generate rows
Merge Overlapping Intervals	Not Sliding	Sorting	Sort by start
Merge Two Sorted Arrays	Not Sliding	Two Pointers	Merge from end
Find Repeating & Missing	Not Sliding	XOR / Math	Use XOR properties
Count Inversions	Not Sliding	Merge Sort	Divide and conquer
Reverse Pairs	Not Sliding	Merge Sort	Modified merge
Maximum Product Subarray	Not Sliding	Single Pass	Track max AND min
🔥 SLIDING WINDOW PROBLEMS - DEEP DIVE
TYPE 1: FIXED WINDOW (Simple Sliding)
Problem: Maximum Consecutive Ones
Pattern Recognition: "Maximum consecutive" → Fixed window scanning

Brute Force (O(n²)):

cpp
int findMaxConsecutiveOnesBrute(vector<int>& nums) {
    int maxCount = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            int count = 0;
            for (int j = i; j < nums.size() && nums[j] == 1; j++) {
                count++;
            }
            maxCount = max(maxCount, count);
        }
    }
    return maxCount;
}
Optimal (O(n), O(1)):

cpp
int findMaxConsecutiveOnes(vector<int>& nums) {
    int maxCount = 0, currentCount = 0;
    for (int num : nums) {
        if (num == 1) {
            currentCount++;
            maxCount = max(maxCount, currentCount);
        } else {
            currentCount = 0;  // Reset on zero
        }
    }
    return maxCount;
}
🚨 MISTAKE ALERT: Forgetting to reset currentCount to 0 when encountering 0.

TYPE 2: VARIABLE WINDOW - MAXIMUM LENGTH
Problem: Longest Subarray with Sum K (Positives Only)
Pattern Recognition: "Longest subarray with sum K" + "positive numbers" → Variable sliding window

Brute Force (O(n²)):

cpp
int longestSubarraySumKBrute(vector<int>& nums, int K) {
    int maxLen = 0;
    for (int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            if (sum == K) {
                maxLen = max(maxLen, j - i + 1);
            }
            if (sum > K) break;  // Early break for positives
        }
    }
    return maxLen;
}
Optimal (O(n), O(1) - Sliding Window):

cpp
int longestSubarraySumK(vector<int>& nums, int K) {
    int left = 0, sum = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        // Shrink while sum > K (since all positives)
        while (sum > K && left <= right) {
            sum -= nums[left];
            left++;
        }
        
        // Check if we have a valid window
        if (sum == K) {
            maxLen = max(maxLen, right - left + 1);
        }
    }
    return maxLen;
}
🎯 TRICK: Update maxLen AFTER the while loop (since we want maximum length).

🚨 MISTAKE ALERT: This ONLY works for positive numbers. For negatives, use Prefix Sum + HashMap.

Problem: Longest Subarray with Sum K (Including Negatives)
Optimal (O(n), O(n) - Prefix Sum + HashMap):

cpp
int longestSubarraySumK(vector<int>& nums, int K) {
    unordered_map<int, int> prefixSum;  // Store first occurrence
    int sum = 0, maxLen = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        
        // If sum == K, subarray from 0 to i
        if (sum == K) {
            maxLen = max(maxLen, i + 1);
        }
        
        // Check if (sum - K) exists
        if (prefixSum.find(sum - K) != prefixSum.end()) {
            maxLen = max(maxLen, i - prefixSum[sum - K]);
        }
        
        // Store first occurrence only (to maximize length)
        if (prefixSum.find(sum) == prefixSum.end()) {
            prefixSum[sum] = i;
        }
    }
    return maxLen;
}
🎯 TRICK: Store first occurrence of each prefix sum to maximize length.

TYPE 3: VARIABLE WINDOW - COUNTING
Problem: Count Subarrays with Sum K
Pattern Recognition: "Count subarrays with sum K" → Prefix Sum + HashMap

Optimal (O(n), O(n)):

cpp
int subarraySum(vector<int>& nums, int K) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // CRITICAL: Empty subarray
    int sum = 0, count = 0;
    
    for (int num : nums) {
        sum += num;
        count += prefixCount[sum - K];
        prefixCount[sum]++;
    }
    return count;
}
🚨 MISTAKE ALERT: Forgetting prefixCount[0] = 1 misses subarrays starting at index 0.

Problem: Count Subarrays with XOR K
Optimal (O(n), O(n) - Prefix XOR + HashMap):

cpp
int subarrayXOR(vector<int>& nums, int K) {
    unordered_map<int, int> prefixXorCount;
    prefixXorCount[0] = 1;
    int xorSum = 0, count = 0;
    
    for (int num : nums) {
        xorSum ^= num;
        count += prefixXorCount[xorSum ^ K];
        prefixXorCount[xorSum]++;
    }
    return count;
}
🎯 TRICK: XOR has inverse property: (a ^ b) = K → a = b ^ K.

TYPE 4: VARIABLE WINDOW - LARGEST SUBARRAY WITH SUM 0
Problem: Largest Subarray with Sum 0
Optimal (O(n), O(n) - Prefix Sum + HashMap):

cpp
int maxLenZeroSum(vector<int>& nums) {
    unordered_map<int, int> prefixSum;
    int sum = 0, maxLen = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        
        if (sum == 0) {
            maxLen = max(maxLen, i + 1);
        }
        
        if (prefixSum.find(sum) != prefixSum.end()) {
            maxLen = max(maxLen, i - prefixSum[sum]);
        } else {
            prefixSum[sum] = i;  // Store first occurrence
        }
    }
    return maxLen;
}
🎯 TRICK: For sum 0, we're looking for prefix sums that are equal.

🔥 MASTER CHEAT SHEET: WHICH OPTIMAL APPROACH TO USE
Problem Type	Optimal Approach	Time	Space
Maximum Consecutive Ones	Single Pass	O(n)	O(1)
Longest Subarray Sum K (Positives)	Sliding Window	O(n)	O(1)
Longest Subarray Sum K (Any)	Prefix Sum + HashMap	O(n)	O(n)
Count Subarrays Sum K	Prefix Sum + HashMap	O(n)	O(n)
Count Subarrays XOR K	Prefix XOR + HashMap	O(n)	O(n)
Largest Subarray Sum 0	Prefix Sum + HashMap	O(n)	O(n)
Two Sum	HashMap	O(n)	O(n)
3 Sum	Sort + Two Pointers	O(n²)	O(1)
4 Sum	Sort + Two Pointers	O(n³)	O(1)
Sort Colors	Dutch Flag (3 pointers)	O(n)	O(1)
Majority Element	Boyer-Moore	O(n)	O(1)
Kadane's Algorithm	Single Pass	O(n)	O(1)
Stock Buy and Sell	Single Pass	O(n)	O(1)
Next Permutation	Single Pass	O(n)	O(1)
Longest Consecutive Sequence	HashSet	O(n)	O(n)
Merge Overlapping Intervals	Sort + Merge	O(n log n)	O(n)
Count Inversions	Merge Sort	O(n log n)	O(n)
💡 RECOGNITION TRIGGERS: SLIDING WINDOW VS OTHER PATTERNS
Trigger Phrase	Pattern	Why
"Longest subarray with sum K"	Sliding Window (if positives)	Window expands/shrinks
"Count subarrays with sum K"	Prefix Sum + HashMap	Need frequency counting
"Maximum consecutive"	Sliding Window	Simple scan
"Find pairs that sum to target"	Two Pointers (if sorted)	Opposite direction
"Find all unique triplets"	Sort + Two Pointers	Need 3 elements
"Find majority element"	Boyer-Moore	Cancellation property
"Maximum subarray sum"	Kadane's Algorithm	Track max ending here
"Sort 0,1,2"	Dutch Flag	Three pointers
"Next permutation"	Single Pass	Find dip pattern
"Merge intervals"	Sort + Merge	Overlap logic
🚨 THE 10 MOST COMMON SLIDING WINDOW MISTAKES
#	Mistake	Fix
1	Forgetting left <= right in while loop	Always check bounds
2	Using if instead of while for shrinking	Use while to shrink multiple times
3	Updating answer inside shrink for MAX	Update AFTER shrink
4	Updating answer outside shrink for MIN	Update INSIDE shrink
5	Forgetting prefixCount[0] = 1	Always initialize
6	Using Sliding Window with negatives	Use Prefix Sum instead
7	Not handling empty array	Add early return
8	Forgetting k % n in rotations	Mod before rotating
9	Not handling duplicates in 3Sum	Skip duplicates
10	Forgetting long long for large sums	Prevent overflow
📅 YOUR 30-DAY SLIDING WINDOW MASTERY PLAN
Week 1: Basics (Fixed Window)
Day	Problem	Focus
1	Maximum Consecutive Ones	Simple sliding
2	Largest Element	Basic tracking
3	Second Largest	Two variables
4	Check if Sorted	Single pass
5	Remove Duplicates	Slow/fast pointers
6	Move Zeros	Partition
7	Left Rotate by 1	Array manipulation
Week 2: Variable Window (Positive Numbers)
Day	Problem	Focus
8	Longest Subarray Sum K (Positives)	Variable window
9	Minimum Size Subarray Sum	Shrink to min
10	Longest Substring Without Repeating	Sliding with set
11	Fruit Into Baskets	K=2 sliding
12	Longest Repeating Character Replacement	With replacements
13	Subarray Product Less Than K	Product sliding
14	Review Week	All problems again
Week 3: Counting & Prefix Sum
Day	Problem	Focus
15	Count Subarrays Sum K	Prefix + HashMap
16	Count Subarrays XOR K	XOR + HashMap
17	Largest Subarray Sum 0	First occurrence
18	Two Sum	HashMap
19	Find Missing Number	XOR
20	Find Number Appears Once	XOR
21	Find Duplicate Number	Floyd's cycle
Week 4: Advanced Patterns
Day	Problem	Focus
22	3 Sum	Sort + Two Pointers
23	4 Sum	Sort + Two Pointers
24	Sort Colors	Dutch Flag
25	Kadane's Algorithm	Max subarray
26	Stock Buy and Sell	Track min
27	Merge Overlapping Intervals	Sort + Merge
28	Longest Consecutive Sequence	HashSet
29	Maximum Product Subarray	Track max & min
30	Final Mock Interview	All patterns
🎯 YOUR MOCK INTERVIEW SCRIPT
When you see a Sliding Window problem:

"I recognize this as a Sliding Window problem because it asks for a subarray/substring with a specific condition. I'll use two pointers moving in the same direction.

The right pointer expands the window, and the left pointer shrinks when the condition is violated.

Since we're looking for the [maximum/minimum/count], I'll update my answer [after/before/inside] the shrink loop.

Time complexity is O(n) because each element is processed at most twice. Space complexity is O(1) for variable window or O(n) for prefix sum approach."

🔥 THE "70k" QUALITY REVISION CHECKLIST
Identify the pattern before coding

Explain the approach before writing code

Handle edge cases (empty, single element, all same)

Use the right data structure (set, map, vector)

Update answer at the right time (before/after shrink)

Check bounds (left <= right)

Use long long for large sums

Skip duplicates when needed

Explain time & space complexity

Walk through example with your code

You now have a complete, battle-tested guide to all Sliding Window and Array patterns. Go crush your interviews! 🚀

okay now list oonly the single pass allthe probelms related to it and what approach and what mistakes can make hwo to aproach in interview try to give brute, better , optimal and give me the depth understanding of it
🎯 SINGLE PASS PATTERN - Complete Mastery Guide
📚 TABLE OF CONTENTS
What is Single Pass Pattern?

Problem Classification

Deep Dive: Each Problem

Common Mistakes

Interview Strategy

Practice Plan

<a name="what"></a>🔷 WHAT IS SINGLE PASS PATTERN?
The Core Concept
Definition: Processing an array in ONE linear traversal (O(n)) with O(1) extra space.

Visual Representation:

text
Array: [1, 3, 5, 7, 9]
        →
        We traverse from left to right (or right to left)
        Tracking variables as we go
🧠 Why Single Pass is Powerful
Time Complexity: O(n) - Optimal for array problems

Space Complexity: O(1) - No extra data structures

Cache Friendly: Sequential memory access

Streaming Friendly: Can process data as it arrives

📝 The Master Template
cpp
class SinglePassTemplate {
public:
    // Generic single pass pattern
    int solve(vector<int>& nums) {
        // Initialize tracking variables
        int answer = INITIAL_VALUE;
        int tracker = INITIAL_VALUE;
        
        // Single pass through array
        for (int i = 0; i < nums.size(); i++) {
            // Process current element
            // Update tracker
            // Update answer
        }
        
        return answer;
    }
};
<a name="classification"></a>📋 COMPLETE PROBLEM CLASSIFICATION (Single Pass)
Problem	Direction	Tracking Variables	Key Insight
Largest Element	Left → Right	maxVal	Track maximum
Second Largest	Left → Right	first, second	Two variables
Check if Sorted	Left → Right	prev	Compare adjacent
Linear Search	Left → Right	None	Compare each element
Maximum Consecutive Ones	Left → Right	currentCount, maxCount	Track streaks
Remove Duplicates	Left → Right	slow (writer)	Fast & Slow pointers
Move Zeros	Left → Right	slow (boundary)	Partition
Left Rotate by 1	Left → Right	first	Store first, shift
Left Rotate by K	Left → Right	Multiple reverses	Reverse trick
Find Missing Number	Left → Right	xorSum	XOR property
Number Appears Once	Left → Right	xorSum	XOR cancels duplicates
Kadane's Algorithm	Left → Right	currentMax, globalMax	Max subarray sum
Stock Buy and Sell	Left → Right	minPrice, maxProfit	Track min price
Leaders in Array	Right → Left	maxFromRight	Track max from right
Next Permutation	Right → Left then Left → Right	i (dip)	Find dip, reverse
Majority Element	Left → Right	candidate, count	Boyer-Moore
Maximum Product Subarray	Left → Right	maxProd, minProd	Track both
Pascal's Triangle	Left → Right	row	Generate rows
Rearrange by Sign	Left → Right	posIdx, negIdx	Two write pointers
<a name="deepdive"></a>🔷 DEEP DIVE: Each Problem - Brute → Better → Optimal
PROBLEM 1: LARGEST ELEMENT
Problem: Find the maximum element in an array.

❌ Brute Force (O(n) but with extra logic)
cpp
int largestBrute(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    // You can't do better than O(n) for this!
    // This IS the optimal, but let's write it cleanly
    int maxVal = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    return maxVal;
}
🎯 Wait, this IS optimal! You can't find max without scanning all elements.

🚀 Optimal (O(n), O(1))
cpp
int largestElement(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    int maxVal = nums[0];  // Initialize with first element
    for (int num : nums) {
        maxVal = max(maxVal, num);  // Or use if condition
    }
    return maxVal;
}
🚨 MISTAKE ALERT: Never initialize maxVal = 0 if array can have negative numbers!

Interviewer Follow-up: "What if the array is empty?"
Your Answer: "I handle it with if (nums.empty()) return INT_MIN; or throw an exception."

PROBLEM 2: SECOND LARGEST ELEMENT
Problem: Find the second largest element in an array.

❌ Brute Force (O(n log n) - Sorting)
cpp
int secondLargestBrute(vector<int>& nums) {
    sort(nums.begin(), nums.end(), greater<int>());
    // Skip duplicates
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[0]) return nums[i];
    }
    return -1;
}
❌ Problems: O(n log n) time, modifies array.

⚡ Better (O(n) - Two Pass)
cpp
int secondLargestBetter(vector<int>& nums) {
    // First pass: find largest
    int largest = nums[0];
    for (int num : nums) {
        largest = max(largest, num);
    }
    
    // Second pass: find largest != largest
    int secondLargest = INT_MIN;
    for (int num : nums) {
        if (num != largest) {
            secondLargest = max(secondLargest, num);
        }
    }
    return secondLargest;
}
✅ Good but: Requires two passes.

🚀 Optimal (O(n), O(1) - Single Pass)
cpp
int secondLargest(vector<int>& nums) {
    if (nums.size() < 2) return -1;
    
    int first = nums[0];
    int second = INT_MIN;
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > first) {
            second = first;    // Old largest becomes second
            first = nums[i];   // New largest
        } else if (nums[i] > second && nums[i] != first) {
            second = nums[i];  // New second largest
        }
    }
    return second;
}
🎯 Visual Walkthrough:

text
nums = [3, 5, 1, 7, 4]
first=3, second=INT_MIN

i=1: num=5 > first=3 → second=3, first=5
i=2: num=1 → not > first, not > second → skip
i=3: num=7 > first=5 → second=5, first=7
i=4: num=4 → not > first=7, but > second=5? No → skip
Answer = 5
🚨 MISTAKE ALERT: Forgetting to handle duplicates! Use nums[i] != first check.

PROBLEM 3: CHECK IF ARRAY IS SORTED
Problem: Check if array is sorted in non-decreasing order.

❌ Brute Force (O(n²) - All pairs)
cpp
bool isSortedBrute(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] > nums[j]) return false;
        }
    }
    return true;
}
❌ Problems: O(n²) time - terrible for large arrays.

🚀 Optimal (O(n), O(1) - Single Pass)
cpp
bool isSorted(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < nums[i-1]) return false;
    }
    return true;
}
🎯 TRICK: For "Check if Array is Sorted II" (rotated sorted), count how many times nums[i] > nums[i+1].

cpp
bool isRotatedSorted(vector<int>& nums) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > nums[(i + 1) % nums.size()]) {
            count++;
        }
        if (count > 1) return false;
    }
    return true;
}
🚨 MISTAKE ALERT: Forgetting to use modulo for circular comparison.

PROBLEM 4: LINEAR SEARCH
Problem: Find if target exists in array.

❌ Brute (O(n) - Already optimal)
cpp
int linearSearch(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == target) return i;
    }
    return -1;
}
🎯 This IS optimal for unsorted arrays! Only Binary Search can do better, but requires sorted array.

Interviewer Follow-up: "Can we do better than O(n)?"
Your Answer: "Only if the array is sorted. Then we'd use Binary Search for O(log n). For unsorted arrays, O(n) is optimal because we must check every element."

PROBLEM 5: MAXIMUM CONSECUTIVE ONES
Problem: Find maximum number of consecutive 1s.

❌ Brute (O(n²) - All substrings)
cpp
int maxConsecutiveOnesBrute(vector<int>& nums) {
    int maxCount = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            int count = 0;
            for (int j = i; j < nums.size() && nums[j] == 1; j++) {
                count++;
            }
            maxCount = max(maxCount, count);
        }
    }
    return maxCount;
}
🚀 Optimal (O(n), O(1) - Single Pass)
cpp
int findMaxConsecutiveOnes(vector<int>& nums) {
    int maxCount = 0;
    int currentCount = 0;
    
    for (int num : nums) {
        if (num == 1) {
            currentCount++;
            maxCount = max(maxCount, currentCount);
        } else {
            currentCount = 0;  // Reset on zero
        }
    }
    return maxCount;
}
🎯 Visual Walkthrough:

text
nums = [1, 1, 0, 1, 1, 1]
i=0: num=1 → current=1, max=1
i=1: num=1 → current=2, max=2
i=2: num=0 → current=0
i=3: num=1 → current=1, max=2
i=4: num=1 → current=2, max=2
i=5: num=1 → current=3, max=3
Answer = 3
🚨 MISTAKE ALERT: Forgetting to update maxCount when currentCount is reset!

PROBLEM 6: REMOVE DUPLICATES FROM SORTED ARRAY
Problem: Remove duplicates in-place and return new length.

❌ Brute (O(n²) - Shift elements)
cpp
int removeDuplicatesBrute(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] == nums[i+1]) {
            // Shift all elements left
            for (int j = i + 1; j < n - 1; j++) {
                nums[j] = nums[j+1];
            }
            n--;
            i--;
        }
    }
    return n;
}
❌ Problems: O(n²) time - terrible for large arrays.

⚡ Better (O(n) time, O(n) space)
cpp
int removeDuplicatesBetter(vector<int>& nums) {
    vector<int> unique;
    for (int num : nums) {
        if (unique.empty() || unique.back() != num) {
            unique.push_back(num);
        }
    }
    for (int i = 0; i < unique.size(); i++) {
        nums[i] = unique[i];
    }
    return unique.size();
}
🚀 Optimal (O(n), O(1) - Single Pass with Two Pointers)
cpp
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0;  // Last unique element position
    
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    return slow + 1;
}
🎯 Visual Walkthrough:

text
nums = [1, 1, 2, 2, 3, 4, 4]
slow=0, fast=1

fast=1: nums[1]=1 == nums[0]=1 → duplicate, fast++
fast=2: nums[2]=2 != nums[0]=1 → new! slow=1, nums[1]=2
        [1, 2, 2, 2, 3, 4, 4]
fast=3: nums[3]=2 == nums[1]=2 → duplicate, fast++
fast=4: nums[4]=3 != nums[1]=2 → new! slow=2, nums[2]=3
        [1, 2, 3, 2, 3, 4, 4]
fast=5: nums[5]=4 != nums[2]=3 → new! slow=3, nums[3]=4
        [1, 2, 3, 4, 3, 4, 4]
fast=6: nums[6]=4 == nums[3]=4 → duplicate, fast++

Return slow+1 = 4 → [1, 2, 3, 4]
🚨 MISTAKE ALERT: Forgetting to handle empty array! Always check if (nums.empty()).

Interviewer Follow-up: "What if we want to allow at most 2 duplicates?"
Your Answer: "I modify the condition to compare with nums[slow-1]:

cpp
int removeDuplicatesII(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    int slow = 2;
    for (int fast = 2; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow-2]) {
            nums[slow++] = nums[fast];
        }
    }
    return slow;
}
This works because sorted array means we check 2 positions behind slow."

PROBLEM 7: MOVE ZEROS TO END
Problem: Move all zeros to the end while maintaining relative order.

❌ Brute (O(n²) - Bubble zeros)
cpp
void moveZeroesBrute(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] != 0) {
                    swap(nums[i], nums[j]);
                    break;
                }
            }
        }
    }
}
⚡ Better (O(n) time, O(n) space)
cpp
void moveZeroesBetter(vector<int>& nums) {
    vector<int> nonZeros;
    for (int num : nums) {
        if (num != 0) nonZeros.push_back(num);
    }
    for (int i = 0; i < nonZeros.size(); i++) {
        nums[i] = nonZeros[i];
    }
    for (int i = nonZeros.size(); i < nums.size(); i++) {
        nums[i] = 0;
    }
}
🚀 Optimal (O(n), O(1) - Single Pass with Swap)
cpp
void moveZeroes(vector<int>& nums) {
    int slow = 0;  // Position to place next non-zero
    
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            swap(nums[slow], nums[fast]);  // Swap with slow position
            slow++;
        }
    }
}
🎯 Visual Walkthrough:

text
nums = [0, 1, 0, 3, 12]
slow=0, fast=0

fast=0: nums[0]=0 → skip
fast=1: nums[1]=1 → swap(nums[0], nums[1]) → [1, 0, 0, 3, 12], slow=1
fast=2: nums[2]=0 → skip
fast=3: nums[3]=3 → swap(nums[1], nums[3]) → [1, 3, 0, 0, 12], slow=2
fast=4: nums[4]=12 → swap(nums[2], nums[4]) → [1, 3, 12, 0, 0], slow=3

Result: [1, 3, 12, 0, 0]
🚨 MISTAKE ALERT: Using assignment instead of swap loses the zeros at the front.

PROBLEM 8: LEFT ROTATE BY ONE
Problem: Rotate array left by 1 position.

❌ Brute (O(n²) - Shift one by one)
cpp
void rotateByOneBrute(vector<int>& nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        swap(nums[i], nums[i+1]);  // Bubble left
    }
}
❌ Problems: O(n²) if done K times.

🚀 Optimal (O(n), O(1) - Single Pass)
cpp
void rotateLeftByOne(vector<int>& nums) {
    if (nums.empty()) return;
    int first = nums[0];
    for (int i = 0; i < nums.size() - 1; i++) {
        nums[i] = nums[i + 1];
    }
    nums[nums.size() - 1] = first;
}
🎯 Visual Walkthrough:

text
nums = [1, 2, 3, 4, 5]
first = 1
i=0: nums[0] = nums[1] = 2 → [2, 2, 3, 4, 5]
i=1: nums[1] = nums[2] = 3 → [2, 3, 3, 4, 5]
i=2: nums[2] = nums[3] = 4 → [2, 3, 4, 4, 5]
i=3: nums[3] = nums[4] = 5 → [2, 3, 4, 5, 5]
nums[4] = first = 1 → [2, 3, 4, 5, 1]
🚨 MISTAKE ALERT: Forgetting to store the first element before overwriting!

PROBLEM 9: LEFT ROTATE BY K
Problem: Rotate array left by K positions.

❌ Brute (O(n*k) - Rotate one by one)
cpp
void rotateByKBrute(vector<int>& nums, int k) {
    k = k % nums.size();
    for (int i = 0; i < k; i++) {
        int first = nums[0];
        for (int j = 0; j < nums.size() - 1; j++) {
            nums[j] = nums[j + 1];
        }
        nums[nums.size() - 1] = first;
    }
}
❌ Problems: O(n*k) time - terrible for large k.

🚀 Optimal (O(n), O(1) - Reverse Trick)
cpp
void rotateLeftByK(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;  // CRITICAL: Handle k > n
    
    // Reverse first k elements
    reverse(nums.begin(), nums.begin() + k);
    // Reverse remaining elements
    reverse(nums.begin() + k, nums.end());
    // Reverse entire array
    reverse(nums.begin(), nums.end());
}
🎯 Visual Walkthrough:

text
nums = [1, 2, 3, 4, 5], k = 2

Step 1: Reverse first k elements
[1, 2, 3, 4, 5] → reverse first 2 → [2, 1, 3, 4, 5]

Step 2: Reverse remaining elements
[2, 1, 3, 4, 5] → reverse from index 2 → [2, 1, 5, 4, 3]

Step 3: Reverse entire array
[2, 1, 5, 4, 3] → reverse all → [3, 4, 5, 1, 2]

Result: [3, 4, 5, 1, 2]
🚨 MISTAKE ALERT: Forgetting k = k % n causes unnecessary rotations!

Interviewer Follow-up: "What if we need to rotate right?"
Your Answer: "For right rotation by K, we can either:

Reverse entire, then reverse first K, then reverse rest

Or call rotateLeftByK(nums, n - k)

PROBLEM 10: FIND MISSING NUMBER
Problem: Find the missing number from 0 to n.

❌ Brute (O(n) with boolean array)
cpp
int missingNumberBrute(vector<int>& nums) {
    int n = nums.size();
    vector<bool> present(n + 1, false);
    for (int num : nums) present[num] = true;
    for (int i = 0; i <= n; i++) {
        if (!present[i]) return i;
    }
    return -1;
}
❌ Problems: O(n) extra space.

⚡ Better (O(n) - Math)
cpp
int missingNumberMath(vector<int>& nums) {
    int n = nums.size();
    int total = n * (n + 1) / 2;  // RISK: Overflow!
    int sum = 0;
    for (int num : nums) sum += num;
    return total - sum;
}
✅ Good but: Risk of integer overflow for large n.

🚀 Optimal (O(n), O(1) - XOR)
cpp
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int xorSum = 0;
    
    // XOR all numbers from 0 to n
    for (int i = 0; i <= n; i++) {
        xorSum ^= i;
    }
    
    // XOR with all elements in array
    for (int num : nums) {
        xorSum ^= num;
    }
    
    return xorSum;
}
🎯 Visual Walkthrough:

text
nums = [3, 0, 1], n = 3

Step 1: XOR 0 to 3
xorSum = 0 ^ 1 ^ 2 ^ 3 = 0

Step 2: XOR with array
xorSum = 0 ^ 3 ^ 0 ^ 1 = 2

Answer = 2
🧠 WHY XOR WORKS:

a ^ a = 0

a ^ 0 = a

When we XOR all numbers 0..n with the array, all numbers that appear cancel out

Only the missing number remains

🚨 MISTAKE ALERT: Forgetting to XOR with the full range 0..n!

PROBLEM 11: NUMBER APPEARS ONCE (Others Twice)
Problem: Find the number that appears exactly once.

❌ Brute (O(n²) - Check each)
cpp
int singleNumberBrute(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        bool found = false;
        for (int j = 0; j < nums.size(); j++) {
            if (i != j && nums[i] == nums[j]) {
                found = true;
                break;
            }
        }
        if (!found) return nums[i];
    }
    return -1;
}
⚡ Better (O(n) time, O(n) space)
cpp
int singleNumberBetter(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int num : nums) freq[num]++;
    for (auto& [num, count] : freq) {
        if (count == 1) return num;
    }
    return -1;
}
🚀 Optimal (O(n), O(1) - XOR)
cpp
int singleNumber(vector<int>& nums) {
    int xorSum = 0;
    for (int num : nums) {
        xorSum ^= num;
    }
    return xorSum;
}
🎯 Visual Walkthrough:

text
nums = [4, 1, 2, 1, 2]
xorSum = 0
4 ^ 1 = 5
5 ^ 2 = 7
7 ^ 1 = 6
6 ^ 2 = 4
Answer = 4
🧠 WHY XOR WORKS:

a ^ a = 0 (pairs cancel out)

a ^ 0 = a (single number remains)

🚨 MISTAKE ALERT: This only works when all other numbers appear exactly twice.

PROBLEM 12: KADANE'S ALGORITHM
Problem: Find maximum subarray sum.

❌ Brute (O(n²) - All subarrays)
cpp
int maxSubArrayBrute(vector<int>& nums) {
    int maxSum = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            maxSum = max(maxSum, sum);
        }
    }
    return maxSum;
}
🚀 Optimal (O(n), O(1) - Kadane's)
cpp
int maxSubArray(vector<int>& nums) {
    int currentSum = nums[0];
    int maxSum = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        // Either extend previous subarray or start new
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
🎯 Visual Walkthrough:

text
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

i=0: current=-2, max=-2
i=1: current=max(1, -2+1=-1)=1, max=max(-2,1)=1
i=2: current=max(-3, 1-3=-2)=-2, max=max(1,-2)=1
i=3: current=max(4, -2+4=2)=4, max=max(1,4)=4
i=4: current=max(-1, 4-1=3)=3, max=max(4,3)=4
i=5: current=max(2, 3+2=5)=5, max=max(4,5)=5
i=6: current=max(1, 5+1=6)=6, max=max(5,6)=6
i=7: current=max(-5, 6-5=1)=1, max=max(6,1)=6
i=8: current=max(4, 1+4=5)=5, max=max(6,5)=6

Answer = 6 (subarray [4, -1, 2, 1])
🚨 MISTAKE ALERT: Initializing maxSum = 0 fails when all numbers are negative!

Interviewer Follow-up: "Print the subarray with maximum sum."
Your Answer: "I track start and end indices:

cpp
int maxSubArrayWithIndices(vector<int>& nums) {
    int currentSum = nums[0], maxSum = nums[0];
    int start = 0, end = 0, tempStart = 0;
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > currentSum + nums[i]) {
            currentSum = nums[i];
            tempStart = i;
        } else {
            currentSum = currentSum + nums[i];
        }
        
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
    }
    // Now print subarray from start to end
    return maxSum;
}
PROBLEM 13: STOCK BUY AND SELL
Problem: Maximize profit from buying and selling stock.

❌ Brute (O(n²) - All pairs)
cpp
int maxProfitBrute(vector<int>& prices) {
    int maxProfit = 0;
    for (int i = 0; i < prices.size(); i++) {
        for (int j = i + 1; j < prices.size(); j++) {
            maxProfit = max(maxProfit, prices[j] - prices[i]);
        }
    }
    return maxProfit;
}
🚀 Optimal (O(n), O(1) - Single Pass)
cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);  // Track minimum so far
        maxProfit = max(maxProfit, price - minPrice);  // Calculate profit
    }
    return maxProfit;
}
🎯 Visual Walkthrough:

text
prices = [7, 1, 5, 3, 6, 4]

i=0: price=7 → minPrice=7, maxProfit=max(0,0)=0
i=1: price=1 → minPrice=1, maxProfit=max(0,0)=0
i=2: price=5 → minPrice=1, maxProfit=max(0,4)=4
i=3: price=3 → minPrice=1, maxProfit=max(4,2)=4
i=4: price=6 → minPrice=1, maxProfit=max(4,5)=5
i=5: price=4 → minPrice=1, maxProfit=max(5,3)=5

Answer = 5 (buy at 1, sell at 6)
🚨 MISTAKE ALERT: Forgetting to initialize minPrice = INT_MAX.

Interviewer Follow-up: "What if you can buy and sell multiple times?"
Your Answer: "Then I sum all positive differences:

cpp
int maxProfitMultiple(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i-1]) {
            profit += prices[i] - prices[i-1];
        }
    }
    return profit;
}
This works because we can buy and sell on consecutive days."

PROBLEM 14: LEADERS IN AN ARRAY
Problem: Find all leaders (elements greater than all elements to their right).

❌ Brute (O(n²) - Check each)
cpp
vector<int> leadersBrute(vector<int>& nums) {
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        bool isLeader = true;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] > nums[i]) {
                isLeader = false;
                break;
            }
        }
        if (isLeader) result.push_back(nums[i]);
    }
    return result;
}
🚀 Optimal (O(n), O(1) - Traverse from Right)
cpp
vector<int> leaders(vector<int>& nums) {
    vector<int> result;
    int maxFromRight = INT_MIN;
    
    // Traverse from right to left
    for (int i = nums.size() - 1; i >= 0; i--) {
        if (nums[i] > maxFromRight) {
            result.push_back(nums[i]);
            maxFromRight = nums[i];
        }
    }
    
    reverse(result.begin(), result.end());
    return result;
}
🎯 Visual Walkthrough:

text
nums = [16, 17, 4, 3, 5, 2]
maxFromRight = INT_MIN

i=5: num=2 > INT_MIN → leader! result=[2], maxFromRight=2
i=4: num=5 > 2 → leader! result=[2,5], maxFromRight=5
i=3: num=3 > 5? No
i=2: num=4 > 5? No
i=1: num=17 > 5 → leader! result=[2,5,17], maxFromRight=17
i=0: num=16 > 17? No

Reverse result → [17, 5, 2]
🚨 MISTAKE ALERT: Forgetting to reverse the result (since we traversed from right).

PROBLEM 15: NEXT PERMUTATION
Problem: Find the next lexicographically larger permutation.

❌ Brute (O(n!) - Generate all permutations)
cpp
void nextPermutationBrute(vector<int>& nums) {
    // Generate all permutations, find next
    // O(n!) - NOT FEASIBLE
}
🚀 Optimal (O(n), O(1) - Single Pass with Reverse)
cpp
void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;
    
    // Step 1: Find first decreasing element from right
    while (i >= 0 && nums[i] >= nums[i+1]) {
        i--;
    }
    
    // Step 2: If found, swap with next larger element
    if (i >= 0) {
        int j = n - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    
    // Step 3: Reverse the suffix
    reverse(nums.begin() + i + 1, nums.end());
}
🎯 Visual Walkthrough:

text
nums = [1, 2, 3]

Step 1: Find dip
i = 1 (nums[1]=2 < nums[2]=3)

Step 2: Find next larger
j = 2 (nums[2]=3 > nums[1]=2)
swap → [1, 3, 2]

Step 3: Reverse suffix from i+1
reverse from index 2 → [1, 3, 2]

Answer = [1, 3, 2]
text
nums = [3, 2, 1]

Step 1: Find dip
i = -1 (No dip found)

Step 2: Skip swap

Step 3: Reverse entire array
reverse from 0 → [1, 2, 3]

Answer = [1, 2, 3] (wraps around to smallest)
🚨 MISTAKE ALERT: Forgetting to reverse the suffix after swapping!

PROBLEM 16: MAJORITY ELEMENT (Boyer-Moore)
Problem: Find element that appears more than n/2 times.

❌ Brute (O(n²) - Count each)
cpp
int majorityElementBrute(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        int count = 0;
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] == nums[i]) count++;
        }
        if (count > nums.size() / 2) return nums[i];
    }
    return -1;
}
🚀 Optimal (O(n), O(1) - Boyer-Moore)
cpp
int majorityElement(vector<int>& nums) {
    int candidate = nums[0];
    int count = 0;
    
    for (int num : nums) {
        if (count == 0) {
            candidate = num;
            count = 1;
        } else if (num == candidate) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}
🎯 Visual Walkthrough:

text
nums = [3, 3, 4, 2, 3, 3, 3]

i=0: num=3 → count=0 → candidate=3, count=1
i=1: num=3 → count=1 → count=2
i=2: num=4 → count=2 → count=1
i=3: num=2 → count=1 → count=0
i=4: num=3 → count=0 → candidate=3, count=1
i=5: num=3 → count=1 → count=2
i=6: num=3 → count=2 → count=3

Answer = 3
🧠 WHY IT WORKS:

We maintain a candidate

If we see the same number, we increase count

If we see a different number, we decrease count

When count hits 0, we pick a new candidate

The majority element survives this cancellation process

🚨 MISTAKE ALERT: Forgetting that majority element is guaranteed to exist.

PROBLEM 17: MAXIMUM PRODUCT SUBARRAY
Problem: Find maximum product of any subarray.

❌ Brute (O(n²) - All subarrays)
cpp
int maxProductBrute(vector<int>& nums) {
    int maxProd = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        int prod = 1;
        for (int j = i; j < nums.size(); j++) {
            prod *= nums[j];
            maxProd = max(maxProd, prod);
        }
    }
    return maxProd;
}
🚀 Optimal (O(n), O(1) - Track Max & Min)
cpp
int maxProduct(vector<int>& nums) {
    int maxProd = nums[0];
    int minProd = nums[0];
    int result = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < 0) {
            swap(maxProd, minProd);  // Negative flips max and min
        }
        
        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        
        result = max(result, maxProd);
    }
    return result;
}
🎯 Visual Walkthrough:

text
nums = [2, 3, -2, 4]

i=0: maxProd=2, minProd=2, result=2
i=1: num=3 → maxProd=max(3,6)=6, minProd=min(3,6)=3, result=6
i=2: num=-2 → swap(maxProd=6, minProd=3) → maxProd=3, minProd=6
         maxProd=max(-2, -6)=-2, minProd=min(-2, -12)=-12, result=6
i=3: num=4 → maxProd=max(4, -8)=4, minProd=min(4, -48)=-48, result=6

Answer = 6 (subarray [2, 3])
🧠 WHY TRACK MIN:

Negative × Negative = Positive

We need minProd to handle cases where multiplying two negatives gives a large positive

🚨 MISTAKE ALERT: Forgetting to swap maxProd and minProd when encountering a negative number!

<a name="mistakes"></a>🚨 THE 20 MOST COMMON SINGLE PASS MISTAKES
#	Mistake	Why It Happens	How to Avoid
1	Initializing max with 0	Assumes positive numbers	Use nums[0] or INT_MIN
2	Forgetting empty array check	Assumes input always has elements	Always add guard clause
3	Forgetting k % n in rotation	Rotates more than needed	Always mod before rotating
4	Not handling duplicates in Second Largest	Returns duplicate as second	Use num != first check
5	Forgetting to store first element in rotation	Overwrites before saving	Always store first
6	Using assignment instead of swap in Move Zeros	Loses zeros at front	Use swap
7	Forgetting to update maxCount when resetting	Answer remains stale	Update before reset
8	Not handling negative numbers in Kadane	maxSum=0 fails	Use nums[0]
9	Forgetting to reverse suffix in Next Permutation	Wrong next permutation	Always reverse after swap
10	Forgetting XOR with full range in Missing Number	Wrong result	XOR 0..n AND array
11	Not tracking minProd in Product Subarray	Misses negative × negative	Always track both
12	Forgetting to swap in Product Subarray on negative	Wrong max/min	Swap when nums[i] < 0
13	Not handling empty in Leaders	Accessing invalid index	Add early return
14	Forgetting to reverse result in Leaders	Wrong order	Reverse before returning
15	Not handling array of size 1	Logic fails	Add early return
16	Forgetting to update minPrice in Stock	Stale min price	Update every iteration
17	Using <= instead of < in while	Infinite loop	Check carefully
18	Not handling negative numbers in Kadane	Wrong result	Use max(nums[i], current + nums[i])
19	Forgetting to reset currentCount on zero	Counts across zeros	Reset to 0
20	Not handling when all elements are same	Logic fails	Test with duplicate arrays
<a name="strategy"></a>🎯 INTERVIEW STRATEGY FOR SINGLE PASS
The 5-Step Approach
Listen & Identify: "Is this a single pass problem?"

Keywords: "Find maximum", "Check if", "Remove duplicates", "Find missing"

Usually O(n) with O(1) space

State the Approach: "I'll use a single pass O(n) approach with O(1) space."

Mention tracking variables

Write the Code: Use the template structure

Walk Through Example: Use a small example

Discuss Edge Cases: Empty array, single element, all same, negative numbers

The Interview Script
Interviewer: "Find the maximum element in an array."

You (The Expert):

"I'll use a single pass approach. I initialize a variable with the first element, then traverse the array, updating the maximum whenever I find a larger element.

Time complexity is O(n) because we traverse the array once. Space complexity is O(1) because we only use a single variable.

Let me write the code. I'll also handle the edge case where the array is empty."

cpp
int largestElement(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    int maxVal = nums[0];
    for (int num : nums) {
        maxVal = max(maxVal, num);
    }
    return maxVal;
}
Interviewer: "What if the array is empty?"

You: "I handled that with the guard clause returning INT_MIN. Alternatively, I could throw an exception. In production code, we'd want to handle this gracefully."

<a name="practice"></a>📅 30-DAY SINGLE PASS MASTERY PLAN
Week 1: Basic Tracking (Day 1-7)
Day	Problem	Focus
1	Largest Element	Single variable tracking
2	Second Largest	Two variable tracking
3	Check if Sorted	Compare adjacent
4	Linear Search	Basic traversal
5	Maximum Consecutive Ones	Streak counting
6	Left Rotate by 1	Array manipulation
7	Left Rotate by K	Reverse trick
Week 2: Partition & Duplicates (Day 8-14)
Day	Problem	Focus
8	Remove Duplicates	Fast & Slow pointers
9	Move Zeros	Partition with swap
10	Find Missing Number	XOR
11	Number Appears Once	XOR
12	Majority Element	Boyer-Moore
13	Leaders in Array	Traverse from right
14	Review Week	All problems again
Week 3: Advanced Single Pass (Day 15-21)
Day	Problem	Focus
15	Kadane's Algorithm	Max subarray sum
16	Print Subarray with Max Sum	Track indices
17	Stock Buy and Sell	Track min price
18	Next Permutation	Find dip and reverse
19	Maximum Product Subarray	Track max & min
20	Rearrange by Sign	Two write pointers
21	Review Week	Mixed problems
Week 4: Integration & Mock (Day 22-30)
Day	Activity	Focus
22	Solve 5 random single pass problems	Pattern recognition
23	Solve 5 random single pass problems	Edge cases
24	Solve 5 random single pass problems	Time complexity
25	Solve 5 random single pass problems	Space complexity
26	Mock Interview 1	With timer
27	Mock Interview 2	With timer
28	Mock Interview 3	With timer
29	Review all solutions	Write from memory
30	Final Assessment	All patterns
🔥 QUICK REFERENCE: SINGLE PASS CHEAT SHEET
Problem	Tracking Variables	Key Operation
Largest Element	maxVal	max(maxVal, num)
Second Largest	first, second	Chain updates
Check Sorted	prev	prev <= num
Max Consecutive Ones	current, max	Reset on 0
Remove Duplicates	slow	nums[slow++] = nums[fast]
Move Zeros	slow	swap(nums[slow], nums[fast])
Left Rotate K	first	Store, shift, replace
Missing Number	xorSum	XOR all
Number Appears Once	xorSum	XOR all
Kadane's	current, max	max(num, current+num)
Stock	minPrice, maxProfit	price - minPrice
Leaders	maxFromRight	Traverse right
Next Permutation	i, j	Find dip, swap, reverse
Majority Element	candidate, count	Cancel pairs
Max Product	maxProd, minProd	Track both, swap on negative
You now have complete mastery of Single Pass patterns. Go ace that interview! 🚀
