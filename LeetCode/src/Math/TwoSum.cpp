#include <cstdio>
#include <cstdlib>


/**
 * https://leetcode.com/problems/two-sum/
 * nums: 无序数组
 * numsSize: nums数组元素个数
 * target: 目标和
 * returnSize: 返回数组的个数
 * return: 返回指定值在nums的下标
 */
int* forceTwoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int *result = (int *)malloc(sizeof(int) * (*returnSize));
    int i, j, temp;

    // 双重遍历
    for (i = 0; i < numsSize; i++) {
        temp = target;
        result[0] = i;
        temp -= nums[i];
        for (j = i + 1; j < numsSize; j++) {
            if (temp == nums[j]) {
                result[1] = j;
                return result;
            }
        }
    }
    // 无解
    *returnSize = 0;
    return NULL;
}

struct node {
    int index;
    int value;
};

void quickSort(struct node *array, int left, int right) {
    if (left >= right) return;
    struct node *pivot = array + left;
    int l = left + 1;
    int r = right;
    while (1) {
        while (l < right && (array + l)->value < pivot->value) l++;
        while (r > left && (array + r)->value >= pivot->value) r--;
        if (l >= r) break;
        struct node temp = *(array + l);
        *(array + l) = *(array + r);
        *(array + r) = temp;
    }
    struct node temp = *(array + left);
    *(array + left) = *(array + r);
    *(array + r) = temp;
    quickSort(array, left, r - 1);
    quickSort(array, r + 1, right);
    }

int* twoSum(int *nums, int numsSize, int target, int *returnSize) {
    struct node array[numsSize];
    int i = 0;
    for (i = 0; i < numsSize; i++) {
        array[i].index = i;
        array[i].value = nums[i];
    }
    quickSort(array, 0, numsSize - 1);
    
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int sum = (array + left)->value + (array + right)->value;
        if (sum > target) {
            right--;
        } else if (sum < target) {
            left++;
        } else {
            *returnSize = 2;
            int *result = (int*)malloc(sizeof(int)*(*returnSize));
            *(result + 0) = (array + left)->index;
            *(result + 1) = (array + right)->index;
            return result;
        }

    }
    *returnSize = 0;
    return NULL;
}

int main() {
    int nums[] = {572,815,387,418,434,530,376,190,196,74,830,561,973,771,640,37,539,369,327,51,623,575,988,44,659,48,22,776,487,873,486,169,499,82,128,31,386,691,553,848,968,874,692,404,463,285,745,631,304,271,40,921,733,56,883,517,99,580,55,81,232,971,561,683,806,994,823,219,315,564,997,976,158,208,851,206,101,989,542,985,940,116,153,47,806,944,337,903,712,138,236,777,630,912,22,140,525,270,997,763,812,597,806,423,869,926,344,494,858,519,389,627,517,964,74,432,730,843,673,985,819,397,607,34,948,648,43,212,950,235,995,76,439,614,203,313,180,760,210,813,920,229,615,730,359,863,678,43,293,978,305,106,797,769,3,700,945,135,430,965,762,479,152,121,935,809,101,271,428,608,8,983,758,662,755,190,632,792,789,174,869,622,885,626,310,128,233,82,223,339,771,741,227,131,85,51,361,343,641,568,922,145,256,177,329,959,991,293,850,858,76,291,134,254,956,971,718,391,336,899,206,642,254,851,274,239,538,418,21,232,706,275,615,568,714,234,567,994,368,54,744,498,380,594,415,286,260,582,522,795,261,437,292,887,405,293,946,678,686,682,501,238,245,380,218,591,722,519,770,359,340,215,151,368,356,795,91,250,413,970,37,941,356,648,594,513,484,364,484,909,292,501,59,982,686,827,461,60,557,178,952,218,634,785,251,290,156,300,711,322,570,820,191,755,429,950,18,917,905,905,126,790,638,94,857,235,889,611,605,203,859,749,874,530,727,764,197,537,951,919,24,341,334,505,796,619,492,295,380,128,533,600,160,51,249,5,837,905,747,505,82,158,687,507,339,575,206,28,29,91,459,118,284,995,544,3,154,89,840,364,682,700,143,173,216,290,733,525,399,574,693,500,189,590,529,972,378,299,461,866,326,43,711,460,426,947,391,536,26,579,304,852,158,621,683,901,237,22,225,59,52,798,262,754,649,504,861,472,480,570,347,891,956,347,31,784,581,668,127,628,962,698,191,313,714,893};
    // struct node t[] = {{0, 3}, {1, 2}, {2, 4}};
    // quickSort(t, 0, 2);
    // int a = 3, b = 4;
    // printf("%d \n %d\n", a, b);
    // quickSort(nums, 0, 2);
    int numsSize = 446;
    int target = 6;
    int returnSize = 0;
    int *result = twoSum(nums, numsSize, target, &returnSize);
    if (returnSize != 0) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
    }
    free(result);
    return 0;
}
