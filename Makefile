make:
	gcc Source/RBFGen.c Source/sha256.c -o RBFGen -g
	gcc Source/IPCheck.c Source/sha256.c -o IPCheck -g
clean:
	rm RBFGen IPCheck sha256_test sha256_test2 output.txt
sha256_test:
	gcc Source/sha256_test.c Source/sha256.c -o sha256_test
sha256_test2:
	gcc Source/sha256_test2.c Source/sha256.c -o sha256_test2
test:
	gcc Source/Test.c -o test