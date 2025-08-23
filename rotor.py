from swapper import Swapper


class Rotor(Swapper):

    def __init__(self, permutation_cycles: list[str], notches: list[int], initial_setting: int, ring_setting: int):
        super().__init__(permutation_cycles)

        self.notches = notches

        self.initial_setting = initial_setting
        self.setting = initial_setting
        self.ring_setting = ring_setting

    def step(self):
        self.setting = (self.setting + 1) % 26

    def reset(self):
        self.setting = self.initial_setting

    def is_at_notch(self) -> bool:
        return self.setting in self.notches

    def swap_forward(self, c: str) -> str:
        shifted_index = (ord(c) - ord('A') + self.ring_setting) % 26

        shifted_char = chr(shifted_index + ord('A'))

        swapped_char = super().swap_forward(shifted_char)

        index = (ord(swapped_char) - ord('A') - self.ring_setting) % 26

        return chr(index + ord('A'))

    def swap_backward(self, c: str) -> str:
        index = (ord(c) - ord('A') + self.ring_setting) % 26

        shifted_char = chr(index + ord('A'))

        swapped_char = super().swap_backward(shifted_char)

        index = (ord(swapped_char) - ord('A') - self.ring_setting) % 26

        return chr(index + ord('A'))

    def swap_to_static(self, c: str) -> str:
        return Rotor.swap_between(c, self.setting, 0)

    def swap_from_static(self, c: str) -> str:
        return Rotor.swap_between(c, 0, self.setting)

    def swap_to_reflector(self, c: str) -> str:
        return Rotor.swap_between(c, self.setting, 0)

    def swap_from_reflector(self, c: str) -> str:
        return Rotor.swap_between(c, 0, self.setting)

    @staticmethod
    def swap_between(c: str, rotor_from_setting: int, rotor_to_setting: int) -> str:
        return chr((ord(c) - ord('A') + rotor_from_setting - rotor_to_setting) % 26 + ord('A'))
