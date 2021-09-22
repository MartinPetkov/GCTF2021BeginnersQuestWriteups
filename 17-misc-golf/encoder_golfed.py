r=range;P=[k&0xff for k in r(2,9000) if all(k%i for i in r(2,k))]
def encode(t):l=b'\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz';return bytes(b^p for b,p in zip(b'BEGN'+l+b'DATA'+len(t).to_bytes(4,'big')+t+b'END.'+l.upper(),P))
#END
