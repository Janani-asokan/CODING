https://leetcode.com/problems/n-repeated-element-in-size-2n-array/?envType=daily-question&envId=2026-01-02


Your code is *almost* correct, but there are a few **logical bugs** and **assumptions** that can make it fail.

Let’s go through what’s wrong and how to fix it.

---

## Problems in your code

### 1. **Wrong assumption about value range**

```cpp
vector<int> freq(n+1, 0);
```

You assume that values in `nums` are in the range `[0, n]`.

⚠️ **But in LeetCode 961 (Repeated N Times)**:

* `nums.size() = 2N`
* Values are in the range `[0, 10^4]`

So `freq[nums[i]]` can go **out of bounds**.

✅ **Fix**: Use `unordered_map` or a larger array.

---

### 2. **Incorrect loop range**

```cpp
for(int i = 0; i < n-1; i++)
```

You are iterating only up to `n-2`, but:

* The repeated number might be `n` or larger.

✅ **Fix**: Loop over the entire frequency container.

---

### 3. **You overwrite `result` instead of returning immediately**

```cpp
if(freq[i] > 1) {
    result = i;
}
```

If multiple values had `freq > 1`, you’d return the **last one**, not the correct one.

✅ **Fix**: Return immediately when found.

---

## Corrected Version (Minimal Change)

```cpp
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_map<int, int> freq;
        
        for (int x : nums) {
            freq[x]++;
            if (freq[x] > 1)
                return x;
        }
        return -1; // safety
    }
};
```

---

## Even Better Solution (O(1) space)

Because only **one number repeats N times**, you can do this:

```cpp
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j])
                    return nums[i];
            }
        }
        return -1;
    }
};
```

Or the **standard optimal solution**:

```cpp
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> seen;
        for (int x : nums) {
            if (seen.count(x)) return x;
            seen.insert(x);
        }
        return -1;
    }
};
```

---

## Summary of What Was Wrong

❌ Assumed wrong value range
❌ Incorrect loop bounds
❌ Didn’t return immediately

If you want, I can also explain **why this problem guarantees only one repeated number** or help optimize further 🚀
