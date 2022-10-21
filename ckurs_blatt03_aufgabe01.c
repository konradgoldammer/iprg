#include <unistd.h>

int main() {
  int hoehe = 10;
  int breite = 7;

  for (int i = 0; i < hoehe; i++) {
    for (int j = 0; j < breite; j++) {
      if (i == 0 || i == hoehe - 1 || j == 0 || j == breite - 1) {
        write(1, "A", 1);
        continue;
      }
      write(1, "B", 1);
    }
    write(1, "\n", 1);
  }
}