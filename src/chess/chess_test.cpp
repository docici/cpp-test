/*!
 * This file is PART of chess/gobang project
 * gobang, FIR, you can call it
 * @author hongjun.liao <docici@126.com>
 * @date 2017/03/31

 * test for chess project
 */

#include "plcdn_cpp_test.h"	/* chess_test_main */
#include "chess.h"			/* chess_board_find, ... */
#include <stdio.h>
#include <stdlib.h>	        /* malloc */
#include <assert.h>			/* assert */

#define CHESS_W 10	/* chessboard width */
#define CHESS_H 10  /* chessboard height */
#define CHESS_N 5   /* n for win */

int verbose = 0; /* verbose output? */

static void chess_board_debug_print(chess_board const& board);

static void chess_board_debug_print(chess_board const& board)
{
	for(int i = 0; i != board.H; ++i){
		for(int j = i * board.W; j != (i + 1) * board.W; ++j){
			int c = (board.pts[j].hit == 0? 0 : (board.pts[j].hit == 1? 31 : 32));
			fprintf(stdout, "\e[%dm[%d,%d,%d\e[0m] ", c, board.pts[j].x, board.pts[j].y, board.pts[j].hit);
		}
		fprintf(stdout, "\n");
	}
}

int chess_test_main(int argc, char ** argv)
{
	if(argc > 1)
		verbose = atoi(argv[1]);
	auto pt = (chess_pt *)malloc(sizeof(chess_pt) * CHESS_W * CHESS_H);
	if(!pt){
		return -1;
	}
	chess_board board = { pt, CHESS_W, CHESS_H };

#if 1	/* TEST */
	chess_pt * pts[CHESS_N];

	/*********************************************************/
	fprintf(stdout, "%s: test search left-right: \n", __FUNCTION__);
	/* left-right */
	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 0;
	board.pts[3 * CHESS_W + 3].hit = 1;
	board.pts[3 * CHESS_W + 4].hit = 1;
	board.pts[3 * CHESS_W + 5].hit = 1;
	board.pts[3 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 1;
	board.pts[3 * CHESS_W + 3].hit = 0;
	board.pts[3 * CHESS_W + 4].hit = 1;
	board.pts[3 * CHESS_W + 5].hit = 1;
	board.pts[3 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 1;
	board.pts[3 * CHESS_W + 3].hit = 1;
	board.pts[3 * CHESS_W + 4].hit = 0;
	board.pts[3 * CHESS_W + 5].hit = 1;
	board.pts[3 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 1;
	board.pts[3 * CHESS_W + 3].hit = 1;
	board.pts[3 * CHESS_W + 4].hit = 1;
	board.pts[3 * CHESS_W + 5].hit = 0;
	board.pts[3 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 1;
	board.pts[3 * CHESS_W + 3].hit = 1;
	board.pts[3 * CHESS_W + 4].hit = 1;
	board.pts[3 * CHESS_W + 5].hit = 1;
	board.pts[3 * CHESS_W + 6].hit = 0;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 2].hit = 1;
	board.pts[3 * CHESS_W + 3].hit = 1;
	board.pts[3 * CHESS_W + 4].hit = 1;
	board.pts[3 * CHESS_W + 5].hit = 1;
	board.pts[3 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) == 0);

	/*********************************************************/
//	/* top-bottom */
	fprintf(stdout, "%s: test search top-bottom : \n", __FUNCTION__);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 0;
	board.pts[4 * CHESS_W + 6].hit = 1;
	board.pts[5 * CHESS_W + 6].hit = 1;
	board.pts[6 * CHESS_W + 6].hit = 1;
	board.pts[7 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 1;
	board.pts[4 * CHESS_W + 6].hit = 0;
	board.pts[5 * CHESS_W + 6].hit = 1;
	board.pts[6 * CHESS_W + 6].hit = 1;
	board.pts[7 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 1;
	board.pts[4 * CHESS_W + 6].hit = 1;
	board.pts[5 * CHESS_W + 6].hit = 0;
	board.pts[6 * CHESS_W + 6].hit = 1;
	board.pts[7 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 1;
	board.pts[4 * CHESS_W + 6].hit = 1;
	board.pts[5 * CHESS_W + 6].hit = 1;
	board.pts[6 * CHESS_W + 6].hit = 0;
	board.pts[7 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 1;
	board.pts[4 * CHESS_W + 6].hit = 1;
	board.pts[5 * CHESS_W + 6].hit = 1;
	board.pts[6 * CHESS_W + 6].hit = 1;
	board.pts[7 * CHESS_W + 6].hit = 0;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) != 0);

	chess_board_reset(board);
	board.pts[3 * CHESS_W + 6].hit = 1;
	board.pts[4 * CHESS_W + 6].hit = 1;
	board.pts[5 * CHESS_W + 6].hit = 1;
	board.pts[6 * CHESS_W + 6].hit = 1;
	board.pts[7 * CHESS_W + 6].hit = 1;

	chess_board_debug_print(board);

	fprintf(stdout, "%s: search result: %s\n", __FUNCTION__, (chess_board_find(board, pts, CHESS_N) == 0? "found!" : "none"));
	assert(chess_board_find(board, pts, CHESS_N) == 0);

#endif
	free(pt);
	return -1;
}




