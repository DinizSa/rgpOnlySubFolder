#pragma once

namespace constants{ // Medidas em pix�is
	// ASSET cont�m as dimens�es de um bloco do Background
	const int FPS = 60;
	const int ASSET_SIZE = 34;
	// MAP cont�m as dimens�es do mapa.txt, em pix�is
	// VIEW � a sec��o da WINDOW que vemos de cada frame
	const int VIEW_WIDTH = 300;
	const int VIEW_HEIGHT = 300;
	// WINDOW
	const int FACTOR_WINDOW_X_VIEW = 3;
	const int WINDOW_WIDTH = VIEW_WIDTH * FACTOR_WINDOW_X_VIEW;
	const int WINDOW_HEIGHT = VIEW_HEIGHT * FACTOR_WINDOW_X_VIEW;
}
