musdl:
	@echo "Compiling program..."
	@g++ mtdata.cpp -o mp3mtdata 
	@echo "Moving to /bin"
	@sudo mv mp3mtdata /bin/
