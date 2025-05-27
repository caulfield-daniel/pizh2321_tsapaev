#include <Parser.h>

#include <iostream>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <mp3-file>" << std::endl;
		return 1;
	}
	Parser tag(argv[1]);
	if (tag.parse()) {
		tag.show();
	} else {
		return 1;
	}
	
	return 0;
}
