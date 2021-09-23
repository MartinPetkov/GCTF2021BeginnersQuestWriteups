r=range;P=[n&0xff for n in r(2,8000) if all(n%i for i in r(2,n))]
def encode(t):l=b'\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz';return bytes(b^p for b,p in zip(b'BEGN'+l+b'DATA'+len(t).to_bytes(4,'big')+t+b'END.'+l.upper(),P))
#END
