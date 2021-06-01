% Question 1 ----------------------------------------------------------------------------
/*
insert has 3 arguments
1. an integer: N
2. a list of integers which we can assume is sorted: xs
3. The list xs with N inserted into its proper place

Example:  insert(4,[1,3,5,7],[1,3,4,5,7]).
*/
insert(N,[X|XS],[X|YS]) :- 
  X < N, 
  insert(N,XS,YS).
insert(N,[N|XS],[N|XS]).
insert(N,[X|XS],[N,X|XS]) :- 
  X > N.
insert(N,[],[N]).

% Question 2 ----------------------------------------------------------------------------
/*
insertionSort has 2 arguments
1. a list of integers: xs
2. The sorted version of xs, sorted using insertion sort

In insertion sort, we sort all but the first element, 
  then insert the first element in its proper place.
*/
sorting([X|XS],[Y|YS]) :- 
  sorting(XS, YS), insert([X, YS, Y]).
sorting([], []).

% Question 3 ----------------------------------------------------------------------------
/* 
part has 4 arguments
1. an integer: P
2. a list: xs
3. a list of all the elements of xs less than or equal to P.
4. a list of all the elements of xs greater than P.

Example:  part(5,[6,3,4,8,2,5],[3,4,2,5],[6,8]).
*/
part(P,[X|XS],[Y|YS],[Z|ZS]) :-
  part(P, XS, [X,YS]), ZS),
  X >= P.
part(P,[X|XS],YS,ZS) :-
  part(P, XS, YS, [X,ZS]),
  X < P.
part(P, [], [P], []).

% Question 4 ----------------------------------------------------------------------------
/*
quickSort has 2 arguments
1. a list of integers xs
2. The list xs sorted using quick sort

In quick sort, the list is partitioned around the first element,
  then each partition is then sorted and appended together.
*/
quicksort([X|XS],YS) :-
  partition(XS,X,Left,Right),
  quicksort(Left,LS),
  puicksort(Right,RS),
  append(LS,[X|RS],YS).
quicksort([],[]).

partition([X|XS],Y,[X|LS],RS) :-
 x =< Y, partition(XS,Y,LS,RS).
partition([X|XS],Y,LS,[X|RS]) :-
  X > Y, partition(XS,Y,LS,RS).
partion([],Y,[],[]).

append([],YS,YS).
append([X|XS],YS,[X|ZS]) :- append(XS,YS,ZS).

% Question 5 ----------------------------------------------------------------------------
/*
takeout has 3 arguments
1. an integer: N
2. a list xs
3. a list that is the same as xs but one occurence of N is removed

Example:  takeout(3,[1,2,3,4,5],[1,2,4,5]).
*/
takeout(N, [N|XS], YS) :-
  takeout(N, XS, XS]).
takeout(N, XS, YS) :-
  takeout(N, XS, YS]).
takeout(N, [], []).

% Question 6 ----------------------------------------------------------------------------
/*
perm has 2 arguments
1. a list xs
2. a permutation of xs

Example:  perm([2,7,3,8,5,1],[3,8,1,2,5,7]).
*/
perm(XS,[Y|YS]) :-
 append(A,[Y|C],XS),
 append(A,C,B), perm(B,YS).
perm([],[]).

% Question 7 ----------------------------------------------------------------------------
/*
sorted has 1 argument
1. a sorted list
*/
sorted[A,B,|XS] :-
  A =< B,
  sorted([B,XS]).
sorted[].
sorted[_].

% Question 8 ----------------------------------------------------------------------------
/*
dumbSort has 2 arguments
1. a list xs
2. The list xs sorted using dumb sort

In dumb sort, the permutations of a list are created,
  and checked to see if they are sorted.
*/
dumbSort([X|XS],YS) :-
  perm([X|XS],L),
  sorted(L),
  dumbSort([X|XS],YS).
dumb([],[]).
  
