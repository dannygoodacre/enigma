class Swapper:

    def __init__(self, permutation_cycles: list[str]):
        self.forward_map = {}

        for cycle in permutation_cycles:
            n = len(cycle)

            for i in range(n):
                self.forward_map[cycle[i]] = cycle[(i + 1) % n]

        self.backward_map = {v: k for k, v in self.forward_map.items()}

    def swap_forward(self, c: str) -> str:
        return self.forward_map[c]

    def swap_backward(self, c: str) -> str:
        return self.backward_map[c]
