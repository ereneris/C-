#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>

class file_error{};
class open_error : public file_error{};
class closeerror : public file_error {};
class write_error : public file_error {};

class file {
public:
	file(const char* filename) :
		m_file_handle(std::fopen(filename, "w+")) {
		if (m_file_handle == NULL) {
			throw open_error();
		}
	}
	//constructor
	~file(){
		std::fclose(m_file_handle);
	}

	void write(const char* str) {
		if (std::fputs(str, m_file_handle) == EOF) {
			throw write_error();
		}
	}

	void write(const char* buffer, std::size_t num_chars) {
		if (num_chars != 0 && std::fwrite(buffer,num_chars,1,m_file_handle)==0 ){
			throw write_error();
		}
	}
private:
	std::FILE* m_file_handle;
	file(const file&);
	file& operator=(const file&);
};


void main() {

	file logfile("sample.txt");
	logfile.write("Hello World");
}