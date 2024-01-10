#!/bin/bash  
filename=$1
filename_without_extension="${filename%.*}"



echo "
.data					#symbol data table

vara:	.quad 0
varb:   .quad 0
varc:   .quad 0
a:	.quad 0
b:	.quad 0
c:	.quad 0
d:	.quad 0
e:	.quad 0
f:	.quad 0
g:	.quad 0
h:	.quad 0
i:	.quad 0
j:	.quad 0
k:	.quad 0
l:	.quad 0
m:	.quad 0
n:	.quad 0
o:	.quad 0
p:	.quad 0
q:	.quad 0
r:	.quad 0
s:	.quad 0
t:	.quad 0
u:	.quad 0
v:	.quad 0
w:	.quad 0
x:	.quad 0
y:	.quad 0
z:	.quad 0
print123:
	.string \"%ld\n\" 
	
.text
.global main
main:
	pushq	%rbp			
	movq	%rsp, %rbp
" > $filename_without_extension.s
assembly= ./bin/calc3i.exe < "$1" >> $filename_without_extension.s
echo "
    movq \$60,%rax
 	xorq %rdi, %rdi
 	syscall
    " >> $filename_without_extension.s
gcc -no-pie -o $filename_without_extension $filename_without_extension.s
./$filename_without_extension