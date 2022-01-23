# Parity-Game

https://acm.timus.ru/problem.aspx?space=1&num=1003
https://www.fi.muni.cz/ceoi1999/parity.txt


Parity game

Now and then you play the following game with your friend. Your friend
writes down a sequence consisting of zeroes and ones. You choose a
continuous subsequence (for example the subsequence from the third to
the fifth digit inclusively) and ask him, whether this subsequence
contains even or odd number of ones. Your friend answers your question
and you can ask him about another subsequence and so on. Your task is
to guess the entire sequence of numbers.

You suspect some of your friend's answers may not be correct and you
want to convict him of falsehood. Thus you have decided to write a
program to help you in this matter. The program will receive a series
of your questions together with the answers you have received from
your friend. The aim of this program is to find the first answer which
is provably wrong, i.e. that there exists a sequence satisfying
answers to all the previous questions, but no such sequence satisfies
this answer.

Input:

The first line of input file PARITY.IN contains one number, which is
the length of the sequence of zeroes and ones. This length is less or
equal to 1000000000. In the second line, there is one positive integer
which is the number of questions asked and answers to them. The number
of questions and answers is less or equal to 5000. The remaining lines
specify questions and answers. Each line contains one question and the
answer to this question: two integers (the position of the first and
last digit in the chosen subsequence) and one word which is either
`even' or `odd' (the answer, i.e. the parity of the number of ones in
the chosen subsequence, where `even' means an even number of ones and
`odd' means an odd number).

Output:

There is only one line in output file PARITY.OUT containing one
integer X. Number X says that there exists a sequence of zeroes and
ones satisfying first X parity conditions, but there exists none
satisfying X+1 conditions. If there exists a sequence of zeroes and
ones satisfying all the given conditions, then number X should be the
number of all the questions asked.

Example 1:

PARITY.IN
		10
		5
		1 2 even
		3 4 odd
		5 6 even
		1 6 even
		7 10 odd

PARITY.OUT
		3

Example 2:

PARITY.IN
		10
		5
		1 2 even
		1 4 even
		2 4 odd
		1 10 even
		3 10 even

PARITY.OUT
		5
		
		
SOLUTION:
If an interval <A,B> has even parity, that means intervals <0, A-1> and <0, B> have the SAME parity.
If an interval <A,B> has odd parity, that means intervals <0, A-1> and <0, B> have the OPPOSITE parity.
We need to group intervals based on parity info. Grupping the intervals with the SAME parity can simply be done by gathering them in UnionFind structure. But this method must be extended to accomodate for situation when we gate info about OPPOSITE parity. 
For this reason we need to keep two groups for each interval, eg. a and !a. They can be stored in two tables eg. P[idx] = a and NP [idx] = !a
If we have two intervals eg. x and y with the SAME parity then P[x] is in the same group as P[y], and NP[x] is in the same group as NP[y]
If we have two intervals eg. x and y with the OPPOSITE parity then P[x] is in the same group as NP[y], and NP[x] is in the same group as P[y]
So consider the example:
3 10 even -> P[2] = P[10] & NP[2] = NP[10]
2 4 odd -> P[1] = NP[4] & P[4] = NP[1]
UnionFind can be used to keep track of those groups, but there must be separate indexes for them. In my case I used indexes > length for storing NP

The same element cannot be in both groups in the same time. If such thing happens, that means that this guess was incorrect.
