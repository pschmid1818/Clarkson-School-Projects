Question 3: Collaberated with Andrew York, but did not share code.

1). Dup uses the same access modes

2). The access modes using O_RDWR and O_RDONLY | O_WRONLY are different 
                           32770      32796

3). They always have an offset of 0

---- Output -------------------------------------------------------

$ ./testdupattr
File FD: 3
Dup FD: 4
File Descriptors do not match...

File Status Flags: 32769
Dup Status Flags: 32769
Status Flags match!

File Offset: 0
Dup Offset: 0

$ ./testdupattr rdwr
With O_RDWR
File FD: 3
Dup FD: 4
File Descriptors do not match...

File Status Flags: 32770
Dup Status Flags: 32770
Status Flags match!

File Offset: 0
Dup Offset: 0

