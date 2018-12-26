k = [1,5,10,25]

def change_making(n):
    sum = 0
    for last in range(len(k)-1, -1, -1):
        if k[last] < n:
            sum += n//k[last]
            n = n%k[last]
    print("Fewest coins needed is ", sum)

change_making(49)



