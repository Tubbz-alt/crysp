[ALPHA] dynamically typed extension for C++
===

Stores tagged values in the "payload" bits of floating point NaN (not a number).

Idea taken from several javascript VM implementations - most notably from Mozilla Firefox.

In a IEEE double, NaN is not a single sequence of bits: any double whose bit representation
is one of the following is a NaN:
```
0x7FFxxxxxxxxxxxxx with x != 0: +NaN
0xFFFxxxxxxxxxxxxx with x != 0: -NaN
```
The `x` bits are the NaN payload. And yes, NaN has sign too.

If the top bit of xxxxxxxxxxxxx is set, the NaN is quiet, otherwise it is signaling.
In the following list, `y` is a hexadecimal digit between '0' and '7' while
`z` is a a hexadecimal digit between '8' and 'F':
```
0x7FFyxxxxxxxxxxxx = +signaling NaN. has 51-bit payload, except x = 0 that means +infinity
0xFFFyxxxxxxxxxxxx = -signaling NaN. has 51-bit payload, except x = 0 that means -infinity
0x7FFzxxxxxxxxxxxx = +quiet NaN.     has 51-bit payload.
0xFFFzxxxxxxxxxxxx = -quiet NaN.     has 51-bit payload.
```
in total, almost 53 bits are available as NaN payload, divided in four blocks.

They can be used to store integers, single-precision floats, Unicode characters, and even pointers:
on x86-64, the hardware currently supports 48 bits virtual memory addressing even though pointers
are 64 bits wide.

TODO: complete the implementation and document it.
