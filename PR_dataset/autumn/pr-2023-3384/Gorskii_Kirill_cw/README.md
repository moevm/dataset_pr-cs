# About

Course work for option 4.21, created by Kirill Gorsky. Tested on Debian 12 «Bookworm» and Ubuntu 22.04 LTS. Receives input from stdin:

stdin:
```
COMMAND
TEXT...
...
```

List of commands:
* 0 - print preprocessed text.
* 1 - sort descending all sentences by time-sum and print resulted text.
* 2 - print sentences longer than 2 and less than 7 words.
* 3 - replace lowercase consonant letters with uppercase ones.
* 4 - remove all sentences with more then average letter count.
* 5 - print help message.

Text is a sequence of sentences separated by `'.'` character. Sentence is a sequence of words separated by `' '`, `','` or `'\n'` characters. Word is a sequence of latin letters and numbers OR `'-'` character. Double `'\n'` is interpreted as an end of text. Any violation from these simple rules will be considered an invalid input.

The 'test'  directory contains various tests.

# Build

Requirements:
* make
* gcc


First install the requirements and clone the repository, then:

```
git switch Gorskii_Kirill_cw
cd Gorskii_Kirill_cw/src
make all
./cw                                # Done!
```