from config import *
from rotor import Rotor
from swapper import Swapper


class Enigma:
    """An emulator of the Enigma encryption device."""

    def __init__(self):
        """Create an Enigma device with the configuration specified in `config.py`."""

        self.left_rotor = Rotor(ROTOR_PERMUTATIONS[left_rotor_type],
                                NOTCHES[left_rotor_type],
                                left_initial_setting,
                                left_ring_setting)

        self.middle_rotor = Rotor(ROTOR_PERMUTATIONS[middle_rotor_type],
                                  NOTCHES[middle_rotor_type],
                                  middle_initial_setting,
                                  middle_ring_setting)

        self.right_rotor = Rotor(ROTOR_PERMUTATIONS[right_rotor_type],
                                 NOTCHES[right_rotor_type],
                                 right_initial_setting,
                                 right_ring_setting)

        self.reflector = Swapper(REFLECTOR_PERMUTATIONS[reflector_type])

        self.plugboard = Swapper(plugboard_pairs)

    def swap(self, message: str) -> str:
        """Pass the message through the device.

        Parameters
        ----------
        message : str
            The message to be encrypted/decrypted.

        Returns
        -------
        str
            The resultant message.
        """

        result = ''

        for c in message:
            self.__step()

            c = self.plugboard.swap_forward(c)
            c = self.right_rotor.swap_from_static(c)
            c = self.right_rotor.swap_forward(c)
            c = Rotor.swap_between(c, self.right_rotor.setting, self.middle_rotor.setting)
            c = self.middle_rotor.swap_forward(c)
            c = Rotor.swap_between(c, self.middle_rotor.setting, self.left_rotor.setting)
            c = self.left_rotor.swap_forward(c)
            c = self.left_rotor.swap_to_reflector(c)
            c = self.reflector.swap_forward(c)
            c = self.left_rotor.swap_from_reflector(c)
            c = self.left_rotor.swap_backward(c)
            c = Rotor.swap_between(c, self.left_rotor.setting, self.middle_rotor.setting)
            c = self.middle_rotor.swap_backward(c)
            c = Rotor.swap_between(c, self.middle_rotor.setting, self.right_rotor.setting)
            c = self.right_rotor.swap_backward(c)
            c = self.right_rotor.swap_to_static(c)
            c = self.plugboard.swap_backward(c)

            result += c

        return result

    def reset(self):
        """Set the rotor settings to their initial values."""
        self.left_rotor.reset()
        self.middle_rotor.reset()
        self.right_rotor.reset()

    def __step(self):
        is_right_at_notch = self.right_rotor.is_at_notch()
        is_middle_at_notch = self.middle_rotor.is_at_notch()

        self.right_rotor.step()

        if is_right_at_notch or is_middle_at_notch:
            self.middle_rotor.step()

        if is_middle_at_notch:
            self.left_rotor.step()
