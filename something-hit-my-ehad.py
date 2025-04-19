n = int(input())
t = input().strip()
k = input().strip()

s = []
for i in range(n):
    if k[i] == '0':
        s.append(t[i])
    else:
        s.append('0' if t[i] == '1' else '1')

print("".join(s))
