import sys


class MinimumDamage:
    def solve(self):
        from bisect import bisect_left
        from collections import defaultdict

        n, m = [int(_) for _ in input().split()]
        meds = []
        for i in range(m):
            l, r, d = [int(_) for _ in input().split()]
            meds.append([l - 0.5, r + 0.5, d])

        ans = defaultdict(lambda: float('inf'))
        ans[0] = 0
        st = [[0, 0]]
        meds.sort(key=lambda v: v[1])
        for k in range(m):
            l, r, d = meds[k]
            rightmost_left_pos = int(l)
            j = bisect_left(st, [rightmost_left_pos, 0])
            if j < len(st):
                ans[r] = st[j][1] + int(d * (r - l))
            if int(r) > 0 and ans[r] < ans[int(r)]:
                ans[int(r)] = ans[r]
                while st and st[-1][1] > ans[int(r)]:
                    st.pop()
                st.append([int(r), ans[int(r)]])

        print(ans[n] if ans[n] != float('inf') else -1)


solver = MinimumDamage()
input = sys.stdin.readline

solver.solve()
