HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  <LOki Rasmussen name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< lots of website work, a little bit talking to bobby, mostly stack overflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 35 >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree


size()
  running time: 0(n)
  memory usage: n

insert()
  running time: 0(n)
  memory usage: 1

find()
  running time: 0(logn)
  memory usage: 1

height()
  running time: 0(logn)
  memory usage: 1

begin()
  running time: 0(n)
  memory usage: 1

end()
  running time: 0(n)
  memory usage: 1

bf_begin()
  running time: 0(n)
  memory usage: 0(n)

bf_end()
  running time: 0(n)
  memory usage: 0(n)

operator++()
  running time: 0(logn)
  memory usage: 0(n)

operator*()
  running time: 1
  memory usage: 0(n)

getLabel()
  running time: 1
  memory usage: 0(n)

getDepth()
  running time: 1
  memory usage: 0(n)

copy constructor
  running time: 0(n^2)
  memory usage: 0(n)

assignment operator
  running time: 0(n^2)
  memory usage: 0(n)

destructor
  running time: 0(n^2)
  memory usage: 0(n)



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


