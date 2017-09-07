How to translate IUP strings to your language
=============================================

1. copy translate.me template file as <your_language>.utf-8

2. translate the file (use UTF-8 encoding)
   The strings to translate use the following format (on three lines):
     IUP_ERROR  # dialog title
     Error!
     Error!
   The first line contains a string variable and a comment that helps you understand
   the usage of the string.
   The second line is the string in English.
   The third line should be replaced with your translated string.
   Only translate the third lines! Do not change the previous two.

3. make the same translation in latin1 encoding and name it <your_language>.latin1
   Note:
     It can be done in Linux, for example, by
     iconv -f utf-8 -t latin1 lang/<lang>.utf8 > lang/<lang>.latin1
   If there are characters in your language that can't be represented in latin1,
   you would need to replace them manually with some substitutes.
   https://en.wikipedia.org/wiki/ISO/IEC_8859-1
