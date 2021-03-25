import datetime
import hashlib
import math

def the_difficulty_formula(size_bytes):
    return 10 * math.sqrt(math.log(size_bytes)) + 1

def test(size_bytes):
     nonce = 0
     difficulty = the_difficulty_formula(size_bytes)
     h = hashlib.sha512()
     h.update(str(nonce).encode('utf-8'))
     start = datetime.datetime.now()
     while int(h.hexdigest(), 16) > 2**(512-difficulty):
             nonce += 1
             h.update(str(nonce).encode('utf-8'))
     end = datetime.datetime.now()
     print("\n\n====================\n")
     print("hash: ", h.hexdigest())
     print("size: ", size_bytes)
     print("difficulty: ", difficulty)
     print("nonce: ", nonce)
     print("time: ", end - start)
     print()
     
     log = open("results.csv", "a")
     log.write("{},{},{},{}\n".format(size_bytes, difficulty, nonce, end - start))
     log.close()


for i in [2**n for n in range(36)]:
    test(i)

log = open("results.csv", "a")
log.write("done.")
log.close()
