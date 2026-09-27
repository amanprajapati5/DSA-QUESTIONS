class Solution:
    def crackSafe(self, n: int, k: int) -> str:
        visited = set()
        result = []

        def dfs(node):
            for digit in range(k):
                edge = node + str(digit)

                if edge not in visited:
                    visited.add(edge)

                    next_node = edge[1:]

                    dfs(next_node)

                    result.append(str(digit))

        start = "0" * (n - 1)
        dfs(start)

        return start + "".join(reversed(result))