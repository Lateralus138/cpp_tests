#include "stdafx.h"
int main(const int argc, const char *argv[]) {
	ArgsParser args_parser(argc, const_cast<char**>(argv));
	args_parser.add_argument("help", "Display this help message.");
	args_parser.add_argument("h", "Display this help message.");
	args_parser.parse();
	//try {
	//	std::string arg = args_parser.get_value<std::string>("h");
	//	std::cout << "Argument 'h': " << arg << std::endl;
	//}
	//catch (const std::runtime_error & err) {
	//	std::cerr << "Error: " << err.what() << std::endl;
	//	return 1;
	//}
	const int mode_result = _setmode(_fileno(stdout), _O_U16TEXT);
	if (mode_result == -1) {
		std::wcerr << L"Failed to set stdout mode to UTF-16." << std::endl;
		return 1;
	}
	auto &dashed = box_drawing::boxes["Light Dashed"];
	std::wcout << dashed["upperLeft"] << L"\n";
}
