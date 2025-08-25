#include <time.h>

class log_t{
	private:
		int entries = 0;
		std::string working_file = "";
		std::string time_str;
		//fstream file; //declare a file
		FILE *filePtr;
		time_t rawtime;
		struct tm * timeinfo;

	public:
		std::string makeFileName(std::string input){
		/* replace spaces with '_' */
		std::string temp = "";
		for (int i = 0; i < (input.length() - 1); i++){
			if ((input[i] != ' ') && (input[i] != ':')){
				temp += input[i];
			}else {
				temp += '_';
			}

		}

		//temp[temp.length() - 1] = '_';
		return temp;
	}


	void init(){
		/* generate filename */
		std::string file_str = makeFileName(time_str);
		working_file += LOG_DIR;
		working_file += '/';
		working_file += file_str;
		working_file += ".txt";	

		/* make a file */
		filePtr = fopen(working_file.c_str(), "w");
		/* write header */
		fputs("AUV LOG FILE: ", filePtr);
		fputs(time_str.c_str(), filePtr);
		fputs("\n", filePtr);
		std::cout << "header written\n";
		fclose(filePtr);
	}

	void setTimeStr(std::string input){
		time_str = input;
	}

	void log(std::string input){
		/* write timestamp and log input */
		filePtr = fopen(working_file.c_str(), "a");

		entries++;
		//get time
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		char *new_time_str = asctime(timeinfo);

		char *entry_str;
		sprintf(entry_str, "%d", entries);

		fputs(entry_str, filePtr); //write entry number
		fputs(" ", filePtr); //space
		fputs(new_time_str, filePtr); // write time
		fputs(input.c_str(), filePtr); //write log
		fputs("\n", filePtr); // new line char
		
		fclose(filePtr);



	}

	std::string getName(){
		return working_file;
	}

	void endLog(){

		fclose(filePtr);
	}

};
