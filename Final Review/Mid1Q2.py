# code not complete work on line 19...

def single_element(lst):
    #print(lst)
    if len(lst)==1:
        return lst[0]
    # We can confirm either index 0&1 are the same OR 1&2
    elif len(lst)==3:
        if lst[0] == lst[1]:
            return lst[2]
        else:
            return lst[0]
    else:
        middle = len(lst)//2
        left = lst[middle-1]
        mid = lst[middle]
        right = lst[middle+1]

        if left == mid:
            left = lst[:middle-1]
            right = lst[middle+1:]
            return single_element(check_odd(left,right))
        elif right == mid:
            left = lst[:middle]
            right = lst[middle+2:]
            return single_element(check_odd(left,right))
        else:
            return mid

def check_odd(left, right):
    if len(left)%2==1:
        return left
    else:
        return right

print(single_element([2,2,7,7,8,10,10,12,12,14,14]))
print(single_element([2,2,7,7,10,10,12,12,14,14,15]))