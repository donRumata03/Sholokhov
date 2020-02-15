import os

all_files = ["D:\\Projects\\Sholokhov\\data\\" + i for i in os.listdir("D:\\Projects\\Sholokhov\\data\\") if i[-len(".txt"):] == ".txt"] + \
["D:\\Projects\\Sholokhov\\data\\other\\" + i for i in os.listdir("D:\\Projects\\Sholokhov\\data\\other\\") if i[-len(".txt"):] == ".txt"]

print("\n".join(all_files))

for filename in all_files:
	file = open(filename, encoding="utf-8", errors = 'ignore').read()
	new_filename = "D:\\Projects\\Sholokhov\\data\\decoded\\" + filename.split("\\")[-1]
	new_str : bytes = file.encode("cp1251")
	open(new_filename, "wb").write(new_str)
