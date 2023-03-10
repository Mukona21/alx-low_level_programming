#  C - Static libraries

# Learning Objectives
- At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

* What is a static library, how does it work, how to create one, and how to use it
* Basic usage of ar, ranlib, nm

# Tasks

* 0. A library is not a luxury but one of the necessities of life

- Create the static library libmy.a containing all the functions listed below:

If you haven’t coded all of the above functions create empty ones with the right prototype.
Don’t forget to push your main.h file to your repository. It should at least contain all the prototypes of the above functions.

* 1. Without libraries what have we? We have no past and no future

- Create a script called create_static_lib.sh that creates a static library called liball.a from all the .c files that are in the current directory.

# Technologies

All files are compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89 
Code is using the Betty style. and will be checked using betty-style.pl and betty-doc.pl

