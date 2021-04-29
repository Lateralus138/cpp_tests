#include <iostream>
int main(int argc, char *argv[]) { 
  if (argc > 1) {
    int index;
    std::cout << "\033]0;";
    for (index=1;index<argc;++index) {
      std::cout << argv[index];
      if (index < argc - 1)
        std::cout << " ";
    }
    std::cout << "\007";
    return 0;
  } else {
    return 1;
  }
}
