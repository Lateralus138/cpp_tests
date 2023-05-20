#include "BoxUniCharsLib.h"
void BoxUniCharsLib::Initiate(std::string mode)
{
  const bool ALTMODE = (mode != "hexadecimal");
	const std::string CAPTION = ((mode != "hexadecimal") ? "Alt Codes" : "Hex Codes");
  std::string single_top_left_corner = ((ALTMODE) ? " 218" : "250C");
  std::string single_top_middle = ((ALTMODE) ? " 194" : "252C");
  std::string single_top_right_corner = ((ALTMODE) ? " 191" : "2510");
  std::string single_horizontal = ((ALTMODE) ? " 196" : "2500");
  std::string single_left_middle = ((ALTMODE) ? " 195" : "251C");
  std::string single_middle = ((ALTMODE) ? " 197" : "253C");
  std::string single_vertical = ((ALTMODE) ? " 179" : "2502");
  std::string single_right_middle = ((ALTMODE) ? " 180" : "2524");
  std::string single_bottom_left_corner = ((ALTMODE) ? " 192" : "2514");
  std::string single_bottom_middle = ((ALTMODE) ? " 193" : "2534");
  std::string single_bottom_right_corner = ((ALTMODE) ? " 217" : "2518");
  std::string double_top_left_corner = ((ALTMODE) ? " 201" : "2554");
  std::string double_top_middle = ((ALTMODE) ? " 203" : "2566");
  std::string double_top_right_corner = ((ALTMODE) ? " 187" : "2557");
  std::string double_horizontal = ((ALTMODE) ? " 205" : "2550");
  std::string double_left_middle = ((ALTMODE) ? " 204" : "2560");
  std::string double_middle = ((ALTMODE) ? " 206" : "256C");
  std::string double_vertical = ((ALTMODE) ? " 186" : "2551");
  std::string double_right_middle = ((ALTMODE) ? " 185" : "2563");
  std::string double_bottom_left_corner = ((ALTMODE) ? " 200" : "255A");
  std::string double_bottom_middle = ((ALTMODE) ? " 202" : "2569");
  std::string double_bottom_right_corner = ((ALTMODE) ? " 188" : "255D");
  std::string single_vert_double_horz_top_left_corner = ((ALTMODE) ? " 213" : "2552");
  std::string single_vert_double_horz_top_middle = ((ALTMODE) ? " 209" : "2564");
  std::string single_vert_double_horz_top_right_corner = ((ALTMODE) ? " 184" : "2555");
  std::string single_vert_double_horz_left_middle = ((ALTMODE) ? " 198" : "255E");
  std::string single_vert_double_horz_middle = ((ALTMODE) ? " 216" : "256A");
  std::string single_vert_double_horz_right_middle = ((ALTMODE) ? " 181" : "2561");
  std::string single_vert_double_horz_bottom_left_corner = ((ALTMODE) ? " 212" : "2558");
  std::string single_vert_double_horz_bottom_middle = ((ALTMODE) ? " 207" : "2567");
  std::string single_vert_double_horz_bottom_right_corner = ((ALTMODE) ? " 190" : "255B");
  std::string double_vert_single_horz_top_left_corner = ((ALTMODE) ? " 214" : "2553");
  std::string double_vert_single_horz_top_middle = ((ALTMODE) ? " 210" : "2565");
  std::string double_vert_single_horz_top_right_corner = ((ALTMODE) ? " 183" : "2556");
  std::string double_vert_single_horz_left_middle = ((ALTMODE) ? " 199" : "255F");
  std::string double_vert_single_horz_middle = ((ALTMODE) ? " 215" : "256B");
  std::string double_vert_double_horz_right_middle = ((ALTMODE) ? " 182" : "2562");
  std::string double_vert_single_horz_bottom_left_corner = ((ALTMODE) ? " 211" : "2559");
  std::string double_vert_single_horz_bottom_middle = ((ALTMODE) ? " 208" : "2568");
  std::string double_vert_single_horz_bottom_right_corner = ((ALTMODE) ? " 189" : "255C");
  BOXUNICHARS_ALL_DEFAULT =
    u8"┌───────────────────────────────────────────────────────────────────────┐"
    u8"\n│                         Box Unicode Characters                        │"
    u8"\n├───────────────────────────────────┬───────────────────────────────────┤"
    u8"\n│ ╔═╦═╗                             │ ╒═╤═╕                             │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╠═╬═╣          " + CAPTION + u8"          │ ╞═╪═╡          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╚═╩═╝                             │ ╘═╧═╛                             │"
    u8"\n│ "
		+ double_top_left_corner
		+ u8" ╔ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_middle
		+ u8" ╦ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_right_corner
		+ u8" ╗│ "
		+ single_vert_double_horz_top_left_corner
		+ u8" ╒ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_middle
		+ u8" ╤ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_right_corner
		+ u8" ╕│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_left_middle
		+ u8" ╠ "
		+ double_horizontal
		+ u8" ═ "
		+ double_middle
		+ u8" ╬ "
		+ double_horizontal
		+ u8" ═ "
		+ double_right_middle
		+ u8" ╣│ "
		+ single_vert_double_horz_left_middle
		+ u8" ╞ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_middle
		+ u8" ╪ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_right_middle
		+ u8" ╡│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_bottom_left_corner
		+ u8" ╚ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_middle
		+ u8" ╩ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_right_corner
		+ u8" ╝│ "
		+ single_vert_double_horz_bottom_left_corner
		+ u8" ╘ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_middle
		+ u8" ╧ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_right_corner
		+ u8" ╛│"
    u8"\n├───────────────────────────────────┼───────────────────────────────────┤"
    u8"\n│ ╓─╥─╖                             │ ┌─┬─┐                             │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╟─╫─╢          " + CAPTION + u8"          │ ├─┼─┤          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╙─╨─╜                             │ └─┴─┘                             │"
    u8"\n│ "
		+ double_vert_single_horz_top_left_corner
		+ u8" ╓ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_middle
		+ u8" ╥ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_right_corner
		+ u8" ╖│ "
		+ single_top_left_corner
		+ u8" ┌ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_middle
		+ u8" ┬ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_right_corner
		+ u8" ┐│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_vert_single_horz_left_middle
		+ u8" ╟ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_middle
		+ u8" ╫ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_double_horz_right_middle
		+ u8" ╢│ "
		+ single_left_middle
		+ u8" ├ "
		+ single_horizontal
		+ u8" ─ "
		+ single_middle
		+ u8" ┼ "
		+ single_horizontal
		+ u8" ─ "
		+ single_right_middle
		+ u8" ┤│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_vert_single_horz_bottom_left_corner
		+ u8" ╙ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_middle
		+ u8" ╨ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_right_corner
		+ u8" ╜│ "
		+ single_bottom_left_corner
		+ u8" └ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_middle
		+ u8" ┴ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_right_corner
		+ u8" ┘│"
    u8"\n└───────────────────────────────────┴───────────────────────────────────┘\n";
  BOXUNICHARS_ALL_HORZ =
    u8"┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐"
    u8"\n│                                                 Box Unicode Characters and their alt codes.                                                   │"
    u8"\n├───────────────────────────────────┬───────────────────────────────────┬───────────────────────────────────┬───────────────────────────────────┤"
    u8"\n│ ╔═╦═╗                             │ ╒═╤═╕                             │ ╓─╥─╖                             │ ┌─┬─┐                             │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╠═╬═╣          " + CAPTION + u8"          │ ╞═╪═╡          " + CAPTION + u8"          │ ╟─╫─╢          " + CAPTION + u8"          │ ├─┼─┤          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │ │ │ │                             │ ║ ║ ║                             │ │ │ │                             │"
    u8"\n│ ╚═╩═╝                             │ ╘═╧═╛                             │ ╙─╨─╜                             │ └─┴─┘                             │"
    u8"\n│ "
		+ double_top_left_corner
		+ u8" ╔ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_middle
		+ u8" ╦ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_right_corner
		+ u8" ╗│ "
		+ single_vert_double_horz_top_left_corner
		+ u8" ╒ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_middle
		+ u8" ╤ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_right_corner
		+ u8" ╕│ "
		+ double_vert_single_horz_top_left_corner
		+ u8" ╓ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_middle
		+ u8" ╥ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_right_corner
		+ u8" ╖│ "
		+ single_top_left_corner
		+ u8" ┌ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_middle
		+ u8" ┬ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_right_corner
		+ u8" ┐│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_left_middle
		+ u8" ╠ "
		+ double_horizontal
		+ u8" ═ "
		+ double_middle
		+ u8" ╬ "
		+ double_horizontal
		+ u8" ═ "
		+ double_right_middle
		+ u8" ╣│ "
		+ single_vert_double_horz_left_middle
		+ u8" ╞ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_middle
		+ u8" ╪ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_right_middle
		+ u8" ╡│ "
		+ double_vert_single_horz_left_middle
		+ u8" ╟ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_middle
		+ u8" ╫ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_double_horz_right_middle
		+ u8" ╢│ "
		+ single_left_middle
		+ u8" ├ "
		+ single_horizontal
		+ u8" ─ "
		+ single_middle
		+ u8" ┼ "
		+ single_horizontal
		+ u8" ─ "
		+ single_right_middle
		+ u8" ┤│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ double_bottom_left_corner
		+ u8" ╚ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_middle
		+ u8" ╩ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_right_corner
		+ u8" ╝│ "
		+ single_vert_double_horz_bottom_left_corner
		+ u8" ╘ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_middle
		+ u8" ╧ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_right_corner
		+ u8" ╛│ "
		+ double_vert_single_horz_bottom_left_corner
		+ u8" ╙ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_middle
		+ u8" ╨ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_right_corner
		+ u8" ╜│ "
		+ single_bottom_left_corner
		+ u8" └ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_middle
		+ u8" ┴ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_right_corner
		+ u8" ┘│"
    u8"\n└───────────────────────────────────┴───────────────────────────────────┴───────────────────────────────────┴───────────────────────────────────┘\n";
  BOXUNICHARS_ALL_VERT =
    u8"┌───────────────────────────────────┐"
    u8"\n│    Box Unicode Characters and     │"
    u8"\n│         their alt codes.          │"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ╔═╦═╗                             │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╠═╬═╣          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╚═╩═╝                             │"
    u8"\n│ "
		+ double_top_left_corner
		+ u8" ╔ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_middle
		+ u8" ╦ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_right_corner
		+ u8" ╗│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_left_middle
		+ u8" ╠ "
		+ double_horizontal
		+ u8" ═ "
		+ double_middle
		+ u8" ╬ "
		+ double_horizontal
		+ u8" ═ "
		+ double_right_middle
		+ u8" ╣│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_bottom_left_corner
		+ u8" ╚ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_middle
		+ u8" ╩ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_right_corner
		+ u8" ╝│"
    u8"\n├───────────────────────────────────┼"
    u8"\n│ ╒═╤═╕                             │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ╞═╪═╡          " + CAPTION + u8"          │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ╘═╧═╛                             │"
    u8"\n│ "
		+ single_vert_double_horz_top_left_corner
		+ u8" ╒ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_middle
		+ u8" ╤ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_right_corner
		+ u8" ╕│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_vert_double_horz_left_middle
		+ u8" ╞ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_middle
		+ u8" ╪ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_right_middle
		+ u8" ╡│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_vert_double_horz_bottom_left_corner
		+ u8" ╘ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_middle
		+ u8" ╧ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_right_corner
		+ u8" ╛│"
    u8"\n├───────────────────────────────────┼"
    u8"\n│ ╓─╥─╖                             │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╟─╫─╢          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╙─╨─╜                             │"
    u8"\n│ "
		+ double_vert_single_horz_top_left_corner
		+ u8" ╓ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_middle
		+ u8" ╥ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_right_corner
		+ u8" ╖│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_vert_single_horz_left_middle
		+ u8" ╟ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_middle
		+ u8" ╫ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_double_horz_right_middle
		+ u8" ╢│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_vert_single_horz_bottom_left_corner
		+ u8" ╙ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_middle
		+ u8" ╨ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_right_corner
		+ u8" ╜│"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ┌─┬─┐                             │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ├─┼─┤          " + CAPTION + u8"          │"
    u8"\n│ │ │ │                             │"
    u8"\n│ └─┴─┘                             │"
    u8"\n│ "
		+ single_top_left_corner
		+ u8" ┌ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_middle
		+ u8" ┬ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_right_corner
		+ u8" ┐│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_left_middle
		+ u8" ├ "
		+ single_horizontal
		+ u8" ─ "
		+ single_middle
		+ u8" ┼ "
		+ single_horizontal
		+ u8" ─ "
		+ single_right_middle
		+ u8" ┤│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_bottom_left_corner
		+ u8" └ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_middle
		+ u8" ┴ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_right_corner
		+ u8" ┘│"
    u8"\n└───────────────────────────────────┘\n";
  BOXUNICHARS_SINGLE_SINGLE =
    u8"┌───────────────────────────────────┐"
    u8"\n│    Box Unicode Characters and     │"
    u8"\n│         their alt codes.          │"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ┌─┬─┐                             │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ├─┼─┤          " + CAPTION + u8"          │"
    u8"\n│ │ │ │                             │"
    u8"\n│ └─┴─┘                             │"
    u8"\n│ "
		+ single_top_left_corner
		+ u8" ┌ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_middle
		+ u8" ┬ "
		+ single_horizontal
		+ u8" ─ "
		+ single_top_right_corner
		+ u8" ┐│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_left_middle
		+ u8" ├ "
		+ single_horizontal
		+ u8" ─ "
		+ single_middle
		+ u8" ┼ "
		+ single_horizontal
		+ u8" ─ "
		+ single_right_middle
		+ u8" ┤│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_bottom_left_corner
		+ u8" └ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_middle
		+ u8" ┴ "
		+ single_horizontal
		+ u8" ─ "
		+ single_bottom_right_corner
		+ u8" ┘│"
    u8"\n└───────────────────────────────────┘\n";
  BOXUNICHARS_SINGLE_DOUBLE =
    u8"┌───────────────────────────────────┐"
    u8"\n│    Box Unicode Characters and     │"
    u8"\n│         their alt codes.          │"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ╔═╦═╗                             │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╠═╬═╣          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╚═╩═╝                             │"
    u8"\n│ "
		+ double_top_left_corner
		+ u8" ╔ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_middle
		+ u8" ╦ "
		+ double_horizontal
		+ u8" ═ "
		+ double_top_right_corner
		+ u8" ╗│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_left_middle
		+ u8" ╠ "
		+ double_horizontal
		+ u8" ═ "
		+ double_middle
		+ u8" ╬ "
		+ double_horizontal
		+ u8" ═ "
		+ double_right_middle
		+ u8" ╣│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_bottom_left_corner
		+ u8" ╚ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_middle
		+ u8" ╩ "
		+ double_horizontal
		+ u8" ═ "
		+ double_bottom_right_corner
		+ u8" ╝│"
    u8"\n└───────────────────────────────────┘\n";
  BOXUNICHARS_SINGLE_SINGLE_VERT_DOUBLE_HORZ =
    u8"┌───────────────────────────────────┐"
    u8"\n│    Box Unicode Characters and     │"
    u8"\n│         their alt codes.          │"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ╒═╤═╕                             │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ╞═╪═╡          " + CAPTION + u8"          │"
    u8"\n│ │ │ │                             │"
    u8"\n│ ╘═╧═╛                             │"
    u8"\n│ "
		+ single_vert_double_horz_top_left_corner
		+ u8" ╒ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_middle
		+ u8" ╤ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_top_right_corner
		+ u8" ╕│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_vert_double_horz_left_middle
		+ u8" ╞ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_middle
		+ u8" ╪ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_right_middle
		+ u8" ╡│"
    u8"\n│ "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" │        "
		+ single_vertical
		+ u8" ││"
    u8"\n│ "
		+ single_vert_double_horz_bottom_left_corner
		+ u8" ╘ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_middle
		+ u8" ╧ "
		+ double_horizontal
		+ u8" ═ "
		+ single_vert_double_horz_bottom_right_corner
		+ u8" ╛│"
    u8"\n└───────────────────────────────────┘\n";
  BOXUNICHARS_SINGLE_DOUBLE_VERT_SINGLE_HORZ =
    u8"┌───────────────────────────────────┐"
    u8"\n│    Box Unicode Characters and     │"
    u8"\n│         their alt codes.          │"
    u8"\n├───────────────────────────────────┤"
    u8"\n│ ╓─╥─╖                             │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╟─╫─╢          " + CAPTION + u8"          │"
    u8"\n│ ║ ║ ║                             │"
    u8"\n│ ╙─╨─╜                             │"
    u8"\n│ "
		+ double_vert_single_horz_top_left_corner
		+ u8" ╓ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_middle
		+ u8" ╥ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_top_right_corner
		+ u8" ╖│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_vert_single_horz_left_middle
		+ u8" ╟ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_middle
		+ u8" ╫ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_double_horz_right_middle
		+ u8" ╢│"
    u8"\n│ "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║        "
		+ double_vertical
		+ u8" ║│"
    u8"\n│ "
		+ double_vert_single_horz_bottom_left_corner
		+ u8" ╙ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_middle
		+ u8" ╨ "
		+ single_horizontal
		+ u8" ─ "
		+ double_vert_single_horz_bottom_right_corner
		+ u8" ╜│"
    u8"\n└───────────────────────────────────┘\n";
}
std::string BoxUniCharsLib::Default()
{
  return BOXUNICHARS_ALL_DEFAULT;
}
std::string BoxUniCharsLib::Horizontal()
{
  return BOXUNICHARS_ALL_HORZ;
}
std::string BoxUniCharsLib::Vertical()
{
  return BOXUNICHARS_ALL_VERT;
}
std::string BoxUniCharsLib::SingleVerticalDoubleHorizontal()
{
  return BOXUNICHARS_SINGLE_SINGLE_VERT_DOUBLE_HORZ;
}
std::string BoxUniCharsLib::DoubleVerticalSingleHorizontal()
{
  return BOXUNICHARS_SINGLE_DOUBLE_VERT_SINGLE_HORZ;
}
std::string BoxUniCharsLib::Single()
{
  return BOXUNICHARS_SINGLE_SINGLE;
}
std::string BoxUniCharsLib::Double()
{
  return BOXUNICHARS_SINGLE_DOUBLE;
}