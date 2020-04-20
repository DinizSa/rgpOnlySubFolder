#pragma once

namespace constants{ // Medidas em pix�is
	// ASSET cont�m as dimens�es de um bloco do Background
	const int ASSET_SIZE = 34;
	// MAP cont�m as dimens�es do mapa.txt, em pix�is
	const int MAP_WIDTH = ASSET_SIZE * 20; // currently maps have 20 x 20 blocks
	const int MAP_HEIGHT = ASSET_SIZE * 20;
	// VIEW � a sec��o da WINDOW que vemos de cada frame
	const int VIEW_WIDTH = 400;
	const int VIEW_HEIGHT = 400;
	// WINDOW
	const int FACTOR_WINDOW_X_VIEW = 2;
	const int WINDOW_WIDTH = VIEW_WIDTH * FACTOR_WINDOW_X_VIEW;
	const int WINDOW_HEIGHT = VIEW_HEIGHT * FACTOR_WINDOW_X_VIEW;
}