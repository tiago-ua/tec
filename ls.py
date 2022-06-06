import os
import string

str = os.popen('ls AmberTarget_*.root').read()

root_files = list(string.split(str))

#testar
print(root_files[3])