import random

def generate_input(n):
    nums = list(range(1,n+1))
    missing = random.choice(nums)
    nums.pop(missing - 1)
    duplicate = random.choice(nums)
    nums.append(duplicate)
    random.shuffle(nums)
    return nums, missing, duplicate


def find_missing_and_duplicate(nums):
    r'''
    Given an array of the numbers from 1...N, except one number 
    is missing and replaced with a duplicate. Find the missing,
    and the duplicate.    
    
    5 4 3 3 1
    5 4 3 3 -1
    5 4 3 -3 -1
    5 4 3 -3 -1
    5 4 -3 -3 -1
    '''
    duplicate = 0;
    missing = 0;
    for i in range(0,len(nums)):
        idx = num[i] - 1
        if (nums[i] < 0):
            duplicate = num[i]
            print ("Duplicate number")
        else:
            num[idx] = -num[idx]
    for i in range(0,N):
        if (nums[i] < 0):

    pass

def assert_eq(exp, acc):
    assert acc == exp, "Expected {}. Actual {}".format(exp, acc)

n = 5
nums, missing, duplicate = generate_input(n)
assert_eq((missing, duplicate), find_missing_and_duplicate(nums))
