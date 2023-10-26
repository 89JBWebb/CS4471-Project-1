make:
	gcc Source/RBFGen.c -o RBFGen
	gcc Source/IPCheck.c -o IPCheck
clean:
	rm RBFGen IPCheck