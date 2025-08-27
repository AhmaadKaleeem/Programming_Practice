class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0 ;
    for (int i = 0 ; i < nums.size();i++){
        if (nums[i] != val){
         nums[k] = nums[i];
         k++;
        }
    }
    
    return k; 
    }
};
// This Works on Leet Code
// Runtime Analysis (This Works)
// 0 ms \\ Beats 100.00%
// Analyze Complexity
// Memory 11.69 MB \\ Beats 79.05%
