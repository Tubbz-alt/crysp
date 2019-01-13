[ALPHA] dynamically typed extension for C++
===

Stores tagged values in the "payload" bits of floating point NaN (not a number).

Idea taken from several javascript VM implementations - most notably from Mozilla Firefox.

+NaN = 0x7FFxxxxxxxxxxxxx with x != 0
-NaN = 0xFFFxxxxxxxxxxxxx with x != 0

If the top bit of xxxxxxxxxxxxx is set, the NaN is quiet, otherwise it is signaling.

+signaling NaN = 0x7FFxxxxxxxxxxxxx has 51-bit payload, except x = 0 that means +infinity
-signaling NaN = 0xFFFxxxxxxxxxxxxx has 51-bit payload, except x = 0 that means -infinity
+quiet NaN     = 0x7FFyxxxxxxxxxxxx has 51-bit payload
-quiet NaN     = 0xFFFyxxxxxxxxxxxx has 51-bit payload
 
in total, almost 53 bits are available as payload, divided in four blocks.

TODO: complete the implementation and document it.
