from enigma import Enigma


enigma = Enigma()

result = enigma.swap('HELLOWORLD')

print(result) # Gibberish

enigma.reset()

result = enigma.swap(result)

print(result) # 'HELLOWORLD'
