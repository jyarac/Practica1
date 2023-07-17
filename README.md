# Hashing and proccess forking
this project is an example of proccess comunication using pipes.
uses a uber dataset with travel times between many destinations, at various hours of the day
Hash the dataset in order to make faster petitions.


hash.h is the library, has all the code related to the creation and consulting to the hashmap.

a fork is created, the son procces will receive data from the user and will send this data to father proccess, which will use search function in hash.h to search the meantime.
