HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Loki Rasmussen>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None really, the interwebs, lots of the interwebs >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 35 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?
My map data structure is a string of a map which is a string of a map of string and int pair. This memory is then a tree style so m for the first layer of unique words, then m for every layer of unique words to each m, but in the end it ends up being a tree structure, so I believe the memory would be logm. 



What is the order notation for performance (running time) of each of
the commands?
load order notation would be the same as the memory storage when it runs through, so log m 
print for a single window runs through the single layer looking for a word that matches and then runs through each of those words in that single word so m to run through the words and m^m
print for a double window would be m^m^m so m raised to the power of the window size
generate most common and random should have about the same order notation since it just requires one extra for look to create the vector to use for random percentage
they go through and look for the given word then go through the options to find the next word then go through that one so it would be m * the length of the sentence which is just m 



EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


