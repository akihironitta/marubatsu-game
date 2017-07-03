/*
  [NOTES]
  -------
  |1|2|3|
  -------
  |4|5|6|
  -------
  |7|8|9|
  -------
*/

#include <stdio.h> 
#include <string.h>

#define NONE 0 
#define MARU 1 
#define BATU 2 
#define SIZE 3
#define first 1
#define second 2

void print_board();                // 盤面表示用関数を作成する
int check_end();                   //  終了条件チェック
int judge_input(char input[]);     // 入力文字列に対応するボードの番号を返す
void put_char_on_board(int, int); // ボード上に記号設置

int board[SIZE][SIZE]={0};     //盤面の状態を示す配列; 0: , 1:o, 2:x
char mark[3]={' ', 'o', 'x'};  // 表示用のマーク
char senkou[32];  // 先攻の人が言ったこと 
char koukou[32];  // 後攻の人が言ったこと
int j[9+1] = {0}; // j[0]は使わない，ボードに何も書いていない:0，もうすでにある:1

int main(void)
{
  print_board(); 

  int round = 0;
  while(1)
    {
      round++;
      printf("\n=== %dターン目です ===\n", round);
      
      /* 先攻 ここから */
      while(1)
        {
          printf("\no >> ");
          scanf("%s", senkou);
          if( judge_input(senkou) == 0 ) // if the operator is not defined, 
            {
              printf("\n操作 \"%s\" は定義されていません．\n", senkou);
            }
          else // if the operator is defined, 
            {
              if( j[judge_input(senkou)] != 0 ) // if not empty on the board, 
                {
                  printf("\nそこはもうだめです．違うところでお願いします．\n");
                }
              else
                {
                  j[judge_input(senkou)] = 1;
                  put_char_on_board(judge_input(senkou), first);
                  print_board();
                  if(check_end())
                    { 
                      printf("\no の勝ち!!!\n"); 
                      break; 
                    } 
                  break;
                }
            }
        }
      /* 先攻 ここまで */

      /* 後攻 ここから */
      while(1)
        {
          printf("\nx >> ");
          scanf("%s", koukou);
          if( judge_input(koukou) == 0 ) // if the operator is not defined, 
            {
              printf("\n操作 \"%s\" は定義されていません．\n", koukou);
            }
          else // if the operator is defined, 
            {
              if( j[judge_input(koukou)] != 0 ) // if not empty on the board, 
                {
                  printf("\nそこはもうだめです．違うところでお願いします．");
                }
              else
                {
                  j[judge_input(koukou)] = 1;
                  put_char_on_board(judge_input(koukou), second);
                  print_board();
                  if(check_end())
                    { 
                      printf("\nx の勝ち!!!\n"); 
                      break; 
                    } 
                  break;
                }
            }
        }
      /* 後攻 ここまで */
    } 

  printf("✳✳✳ O WA RI ✳✳✳\n");
  
  return 0;
} 

void print_board(void) 
{ 
  printf("-------------\n" 
         "| %c | %c | %c |\n" 
         "-------------\n" 
         "| %c | %c | %c |\n" 
         "-------------\n"
         "| %c | %c | %c |\n" 
         "-------------\n", 
         mark[board[0][0]], 
         mark[board[0][1]], 
         mark[board[0][2]], 
         mark[board[1][0]], 
         mark[board[1][1]], 
         mark[board[1][2]], 
         mark[board[2][0]], 
         mark[board[2][1]], 
         mark[board[2][2]] 
         ); 
  return;
} 

void put_char_on_board(int i, int player) 
{ 
  switch(i){ 
  case 1: 
    board[0][0] = player; 
    break; 
  case 2: 
    board[0][1] = player; 
    break; 
  case 3: 
    board[0][2] = player; 
    break; 
  case 4: 
    board[1][0] = player; 
    break; 
  case 5: 
    board[1][1] = player; 
    break; 
  case 6: 
    board[1][2] = player; 
    break; 
  case 7: 
    board[2][0] = player; 
    break; 
  case 8: 
    board[2][1] = player; 
    break; 
  case 9: 
    board[2][2] = player; 
    break; 
  } 
} 

/* 盤面の終了条件チェック */
int check_end() 
{ 

  if((board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] !=0) || 
     (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] !=0) || 
     (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] !=0) || 
     (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] !=0) || 
     (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] !=0) || 
     (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] !=0) || 
     (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] !=0) || 
     (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] !=0))
    { 
      return 1; 
    } 
  else
    {
      return 0;
    }
}

int
judge_input(char input[])
{
  if(strcmp(input, "左上")==0)
    {
      return 1;
    }
  else if(strcmp(input, "上")==0)
    {
      return 2;
    }
  else if(strcmp(input, "右上")==0)
    {
      return 3;
    }
  else if(strcmp(input, "左")==0)
    {
      return 4;
    }
  else if(strcmp(input, "真ん中")==0)
    {
      return 5;
    }
  else if(strcmp(input, "右")==0)
    {
      return 6;
    }
  else if(strcmp(input, "左下")==0)
    {
      return 7;
    }
  else if(strcmp(input, "下")==0)
    {
      return 8;
    }
  else if(strcmp(input, "右下")==0)
    {
      return 9;
    }
  else /* ERROR */
    {
      return 0;
    }
  
}
