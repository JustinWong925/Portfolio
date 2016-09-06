CMPS 111: Introduction to Operating Systems

This course was about operating systems. How they work, design choices and so on.
Our assignments included taking a FreeBSD virtual machine and modifying different aspects of the
default kernel. While I didn't include the actual files, I did inlcude the design documents which were
completed before the actual coding. When looking through an existing code base so massive it was important
to understand where it is that everything is connected to before starting to change code.

The design documents included here will illustrate my group's way of thinking and our design choices are 
explained, as well as which files we looked through and which ones we actually modified.
1. asg2_design.pdf: The original scheduler for FreeBSD uses round-robin scheduling, we changed that to
   a less efficient lottery scheduler.

2. asg3_design.pdf: Page replacement, the default paging algorithm for FreeBSD is similar to the CLOCK algorithm
   we needed to modify the paging algorithm in a couple of ways then find a way to track and analyze the
   consequences of the change.

3. asg4_design.pdf: Security, the goal of this modification was to create an encrpytion and decryption layer. Adding
   a key associated with users and their files they would be able to encrypt/decrypt the file by going through another
   layer.