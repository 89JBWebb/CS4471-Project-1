make:
	gcc Source/RBFGen.c -o RBFGen
	gcc Source/IPCheck.c -o IPCheck
clean:
	rm RBFGen IPCheck
sha256:
	gcc Source/sha256_test.c Source/sha256.c -o sha256