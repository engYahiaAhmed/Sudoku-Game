#ifndef SUDOKU_GAME_H_
#define SUDOKU_GAME_H_
void color(int color_val);
void moveToX_Y(int x,int y);
void sudoku_print(int val,int x,int y);
void arr_2DPrint(void);
void sudoku_SetValue(int x,int y,int val);
void sudoku_deleteValue(int x,int y);
int sudoku_IsFull();
int sudoku_CheckBox(int x,int y,int val,int FuncCheckFlag);
int sudoku_rowCheckTraverse(int x,int y,int val,int FuncCheckFlag);
int sudoku_colCheckTraverse(int x,int y,int val,int FuncCheckFlag);
int sudoku_isValidCoordinate(int x,int y);
int sudoku_checkVal(int val);
void sudoku_intiStatic(void);
void sudoku_inti(void);
int sudoku_GameSolve();
void Sudoku_Game(void);
#endif /* SUDOKU_GAME_H_*/
