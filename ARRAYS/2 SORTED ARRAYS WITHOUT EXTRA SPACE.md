

Merge two Sorted Arrays Without Extra Space


https://www.naukri.com/code360/problems/merge-two-sorted-arrays-without-extra-space_6898839?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

125

10
Problem statement: Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order. Merge them in sorted order. Modify arr1 so that it contains the first N elements and modify arr2 so that it contains the last M elements.

Examples
Example 1:
Input:
 
n = 4, arr1[] = [1 4 8 10] 
m = 5, arr2[] = [2 3 9]

Output:
 
arr1[] = [1 2 3 4]
arr2[] = [8 9 10]

Explanation:

After merging the two non-decreasing arrays, we get, 1,2,3,4,8,9,10.

Example2:
Input:
 
n = 4, arr1[] = [1 3 5 7] 
m = 5, arr2[] = [0 2 6 8 9]

Output:
 
arr1[] = [0 1 2 3]
arr2[] = [5 6 7 8 9]

Explanation:

After merging the two non-decreasing arrays, we get, 0 1 2 3 5 6 7 8 9.

```cpp
  
#include <bits/stdc++.h>
using namespace std;

void merge(long long arr1[], long long arr2[], int n, int m) {

    //Declare a 3rd array and 2 pointers:
    long long arr3[n + m];
    int left = 0;
    int right = 0;

    int index = 0;

    //Insert the elements from the 2 arrays
    // into the 3rd array using left and right
    // pointers:

    while (left < n && right < m) {
        if (arr1[left] <= arr2[right]) {
            arr3[index] = arr1[left];
            left++, index++;
        }
        else {
            arr3[index] = arr2[right];
            right++, index++;
        }
    }

    // If right pointer reaches the end:
    while (left < n) {
        arr3[index++] = arr1[left++];
    }

    // If left pointer reaches the end:
    while (right < m) {
        arr3[index++] = arr2[right++];
    }

    // Fill back the elements from arr3[]
    // to arr1[] and arr2[]:
    for (int i = 0; i < n + m; i++) {
        if (i < n) arr1[i] = arr3[i];
        else arr2[i - n] = arr3[i];
    }
}

int main()
{
    long long arr1[] = {1, 4, 8, 10};
    long long arr2[] = {2, 3, 9};
    int n = 4, m = 3;
    merge(arr1, arr2, n, m);
    cout << "The merged arrays are: " << "\n";
    cout << "arr1[] = ";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\narr2[] = ";
    for (int i = 0; i < m; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}
```

Output: The merged arrays are: arr1[] = 1 2 3 4 arr2[] = 8 9 10 

Complexity Analysis
Time Complexity: O(n+m) + O(n+m), where n and m are the sizes of the given arrays.
Reason: O(n+m) is for copying the elements from arr1[] and arr2[] to arr3[]. And another O(n+m) is for filling back the two given arrays from arr3[].

Space Complexity: O(n+m) as we use an extra array of size n+m.


  Optimal Approach 1 (without using any extra space): 
In this optimal approach, we need to get rid of the extra space we were using.

Approach:
The sizes of the given arrays are n(size of arr1[]) and m(size of arr2[]).

The steps are as follows:

We will declare two pointers i.e. left and right. The left pointer will point to the last index of the arr1[](i.e. Basically the maximum element of the array). The right pointer will point to the first index of the arr2[](i.e. Basically the minimum element of the array).
Now, the left pointer will move toward index 0 and the right pointer will move towards the index m-1. While moving the two pointers we will face 2 different cases like the following:
If arr1[left] > arr2[right]: In this case, we will swap the elements and move the pointers to the next positions.
If arr1[left] <= arr2[right]: In this case, we will stop moving the pointers as arr1[] and arr2[] are containing correct elements.
Thus, after step 2, arr1[] will contain all smaller elements and arr2[] will contain all bigger elements. Finally, we will sort the two arrays.
Intuition:
If we merge the given array, one thing we can assure is that arr1[] will contain all the smaller elements and arr2[] will contain all the bigger elements. This is the logic we will use. Using the 2 pointers, we will swap the bigger elements of arr1[] with the smaller elements of arr2[] until the minimum of arr2[] becomes greater or equal to the maximum of arr1[].

Dry run: 
The dry run will further clarify the concepts:


Note: For a better understanding of intuition, please watch the video at the bottom of the page.

```cpp



#include <bits/stdc++.h>
using namespace std;

void merge(long long arr1[], long long arr2[], int n, int m) {

    //Declare 2 pointers:
    int left = n - 1;
    int right = 0;

    //Swap the elements until arr1[left] is
    // smaller than arr2[right]:
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--, right++;
        }
        else {
            break;
        }
    }

    // Sort arr1[] and arr2[] individually:
    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);
}

int main()
{
    long long arr1[] = {1, 4, 8, 10};
    long long arr2[] = {2, 3, 9};
    int n = 4, m = 3;
    merge(arr1, arr2, n, m);
    cout << "The merged arrays are: " << "\n";
    cout << "arr1[] = ";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\narr2[] = ";
    for (int i = 0; i < m; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}

```

Output: The merged arrays are: arr1[] = 1 2 3 4 arr2[] = 8 9 10 

Complexity Analysis
Time Complexity: O(min(n, m)) + O(n*logn) + O(m*logm), where n and m are the sizes of the given arrays.
Reason: O(min(n, m)) is for swapping the array elements. And O(n*logn) and O(m*logm) are for sorting the two arrays.

Space Complexity: O(1) as we are not using any extra space.


---

**in ninjas platform**

There are a few issues in your code snippet:

1. **Use of `sort(a, a+n)`**: This line is incorrect because `a` is a `std::vector`, not a raw array. The `sort` function from `<algorithm>` requires iterators, which for a `std::vector` would be `a.begin()` and `a.end()`.

2. **Use of `sort(b, b+m)`**: Similarly, `b` is a `std::vector`, and you should use iterators `b.begin()` and `b.end()` for sorting.

3. **Missing Header Files**: If you're using `swap`, `sort`, and `vector`, ensure the required headers like `<algorithm>` and `<vector>` are included.

4. **Logic for Sorted Arrays**: The merging logic is correct but could use some explanation for clarity. The while loop swaps elements from the end of `a` and the start of `b` until `a` and `b` are correctly ordered. Afterward, you sort both arrays, ensuring the final result is fully sorted.

### Fixed Code:
Here’s the corrected version:

```cpp
#include <vector>
#include <algorithm> // For sort and swap

void mergeTwoSortedArraysWithoutExtraSpace(std::vector<long long>& a, std::vector<long long>& b) {
    int m = b.size();
    int n = a.size();
    int left = n - 1;
    int right = 0;

    // Swap elements to ensure overall sorted order
    while (left >= 0 && right < m) {
        if (a[left] > b[right]) {
            std::swap(a[left], b[right]);
            left--;
            right++;
        } else {
            break;
        }
    }

    // Sort the vectors
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
}
```

### Explanation of Changes:
1. Used `a.begin()`, `a.end()`, `b.begin()`, and `b.end()` for `std::sort`.
2. Ensured proper headers are included for all used functions.
3. No changes to the logic as it seems correct, but comments are added for better understanding.

Now the function should work as intended for merging two sorted arrays without using extra space.

