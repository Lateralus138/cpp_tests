#include "box_characters.h"
#include "stdafx.h"

namespace box_drawing {
	std::map<std::string, std::map<std::string, std::wstring>> boxes = {
		{
			"Light",
			{
				{ "horizontal", L"─" }, { "vertical", L"│" }, { "upperLeft", L"┌" }, { "upperRight", L"┐" },
				{ "lowerLeft", L"└" }, { "lowerRight", L"┘" }, { "middleLeft", L"├" }, { "middleRight", L"┤" },
				{ "middleTop", L"┬" }, { "middleBottom", L"┴" }, { "middle", L"┼" }
			}
		},
		{
			"Heavy",
			{
				{ "horizontal", L"━" }, { "vertical", L"┃" }, { "upperLeft", L"┏" }, { "upperRight", L"┓" },
				{ "lowerLeft", L"┗" }, { "lowerRight", L"┛" }, { "middleLeft", L"┣" }, { "middleRight", L"┫" },
				{ "middleTop", L"┳" }, { "middleBottom", L"┻" }, { "middle", L"╋" }
			}
		},
		{
			"Double",
			{
				{ "horizontal", L"═" }, { "vertical", L"║" }, { "upperLeft", L"╔" }, { "upperRight", L"╗" },
				{ "lowerLeft", L"╚" }, { "lowerRight", L"╝" }, { "middleLeft", L"╠" }, { "middleRight", L"╣" },
				{ "middleTop", L"╦" }, { "middleBottom", L"╩" }, { "middle", L"╬" }
			}
		},
		{
			"Light Dashed",
			{
				{ "horizontal", L"┄" }, { "vertical", L"┆" }, { "upperLeft", L"┌" }, { "upperRight", L"┐" },
				{ "lowerLeft", L"└" }, { "lowerRight", L"┘" }, { "middleLeft", L"├" }, { "middleRight", L"┤" },
				{ "middleTop", L"┬" }, { "middleBottom", L"┴" }, { "middle", L"┼" }
			}
		},
		{
			"Heavy Dashed",
			{
				{ "horizontal", L"┅" }, { "vertical", L"┇" }, { "upperLeft", L"┏" }, { "upperRight", L"┓" },
				{ "lowerLeft", L"┗" }, { "lowerRight", L"┛" }, { "middleLeft", L"┣" }, { "middleRight", L"┫" },
				{ "middleTop", L"┳" }, { "middleBottom", L"┻" }, { "middle", L"╋" }
			}
		},
		{
			"Light Quad Dashed",
			{
				{ "horizontal", L"┈" }, { "vertical", L"┊" }, { "upperLeft", L"┌" }, { "upperRight", L"┐" },
				{ "lowerLeft", L"└" }, { "lowerRight", L"┘" }, { "middleLeft", L"├" }, { "middleRight", L"┤" },
				{ "middleTop", L"┬" }, { "middleBottom", L"┴" }, { "middle", L"┼" }
			}
		},
		{
			"Heavy Quad Dashed",
			{
				{ "horizontal", L"┉" }, { "vertical", L"┋" }, { "upperLeft", L"┏" }, { "upperRight", L"┓" },
				{ "lowerLeft", L"┗" }, { "lowerRight", L"┛" }, { "middleLeft", L"┣" }, { "middleRight", L"┫" },
				{ "middleTop", L"┳" }, { "middleBottom", L"┻" }, { "middle", L"╋" }
			}
		},
		{
			"Light Arc",
			{
				{ "horizontal", L"─" }, { "vertical", L"│" }, { "upperLeft", L"╭" }, { "upperRight", L"╮" },
				{ "lowerLeft", L"╰" }, { "lowerRight", L"╯" }, { "middleLeft", L"├" }, { "middleRight", L"┤" },
				{ "middleTop", L"┬" }, { "middleBottom", L"┴" }, { "middle", L"┼" }
			}
		}
	};
}
//const std::vector<BoxStyle> styles = {
//    { L"Light", L'─', L'│', L'┌', L'┐', L'└', L'┘', L'├', L'┤', L'┬', L'┴', L'┼' },
//    { L"Heavy", L'━', L'┃', L'┏', L'┓', L'┗', L'┛', L'┣', L'┫', L'┳', L'┻', L'╋' },
//    { L"Double", L'═', L'║', L'╔', L'╗', L'╚', L'╝', L'╠', L'╣', L'╦', L'╩', L'╬' },
//    { L"Light Dashed", L'┄', L'┆', L'┌', L'┐', L'└', L'┘', L'├', L'┤', L'┬', L'┴', L'┼' },
//    { L"Heavy Dashed", L'┅', L'┇', L'┏', L'┓', L'┗', L'┛', L'┣', L'┫', L'┳', L'┻', L'╋' },
//    { L"Light Quad Dashed", L'┈', L'┊', L'┌', L'┐', L'└', L'┘', L'├', L'┤', L'┬', L'┴', L'┼' },
//    { L"Heavy Quad Dashed", L'┉', L'┋', L'┏', L'┓', L'┗', L'┛', L'┣', L'┫', L'┳', L'┻', L'╋' },
//    { L"Light Arc", L'─', L'│', L'╭', L'╮', L'╰', L'╯', L'├', L'┤', L'┬', L'┴', L'┼' }
//};