from enums import RotorType, ReflectorType


ROTOR_PERMUTATIONS = {
    RotorType.I: ['AELTPHQXRU', 'BKNW', 'CMOY', 'DFG', 'IV', 'JZ', 'S'],
    RotorType.II: ['FIXVYOMW', 'CDKLHUP', 'ESZ', 'BJ', 'GR', 'NT', 'A', 'Q'],
    RotorType.III: ['ABDHPEJT', 'CFLVMZOYQIRWUKXSG', 'N'],
    RotorType.IV: ['AEPLIYWCOXMRFZBSTGJQNH', 'DV', 'KU'],
    RotorType.V: ['AVOLDRWFIUQ', 'BZKSMNHYC', 'EGTJPX'],
    RotorType.VI: ['AJQDVLEOZWIYTS', 'CGMNHFUX', 'BPRK'],
    RotorType.VII: ['ANOUPFRIMBZTLWKSVEGCJYDHXQ'],
    RotorType.VIII: ['AFLSETWUNDHOZVICQ', 'BKJ', 'GXY', 'MPR']
}

REFLECTOR_PERMUTATIONS = {
    ReflectorType.I: ['AE', 'BJ', 'CM', 'DZ', 'FL', 'GY', 'HX', 'IV', 'KW', 'NR', 'OQ', 'PU', 'ST'],
    ReflectorType.II: ['AY', 'BR', 'CU', 'DH', 'EQ', 'FS', 'GL', 'IP', 'JX', 'KN', 'MO', 'TZ', 'VW'],
    ReflectorType.III: ['AF', 'BV', 'CP', 'DJ', 'EI', 'GO', 'HY', 'KR', 'LZ', 'MX', 'NW', 'TQ', 'SU']
}

NOTCHES = {
    RotorType.I: [16],
    RotorType.II: [4],
    RotorType.III: [21],
    RotorType.IV: [9],
    RotorType.V: [25],
    RotorType.VI: [25, 12],
    RotorType.VII: [25, 12],
    RotorType.VIII: [25, 12]
}

right_rotor_type = RotorType.II
right_initial_setting = 12
right_ring_setting = 15

middle_rotor_type = RotorType.VII
middle_initial_setting = 3
middle_ring_setting = 20

left_rotor_type = RotorType.IV
left_initial_setting = 8
left_ring_setting = 5

reflector_type = ReflectorType.II

plugboard_pairs = ['AB', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
