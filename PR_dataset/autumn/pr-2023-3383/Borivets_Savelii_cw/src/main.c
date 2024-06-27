#include "func_out.h"
#include "func_vvod_text.h"
#include "func_obr_text.h"//0
#include "func_translit.h"//1
#include "func_sort_sym.h"//2
#include "func_repl_digit.h"//3
#include "func_odd_del.h"//4
#include "freedom.h"
#include "func_cw.h"
#include "struct.h"

int main() {
  setlocale(LC_ALL,"");
  wprintf(L"Course work for option 5.12, created by Savelii Borivets\n");
  int command;
  wscanf(L"%d\n", &command);
  struct Text orig_text, obr_text;
  wchar_t ch;
  if (command == 5) {
    wprintf(L"Справка о фунциях:\n-Функция 0 - вывод текста с первичной обработкой.\n-Функция 1 - Транслитерация кириллических символов в тексте.\n-Функция 2 - Вывод всех специальных символов (№*$#@) для каждого предложения в порядке уменьшения их кода.\n-Функция 3 - Замена всех цифр в тексте их двоичным кодом.\n-Функция 4 - Удаление всех предложений с нечетными цифрами.\n-Функция 5 - Справка о функциях.\n");
    return 0;
  }
  orig_text = func_vvod_text();
  if (orig_text.cnt_sen == 0) {
    wprintf(L"error: нет текста\n");
    return 0;
  }
  obr_text = func_obr_text(orig_text);
  switch(command){
    case 0: 
      func_out(obr_text, 0);
      freedom(orig_text);
      break;
    case 1:
      func_out(func_translit(obr_text), 1);
      freedom(orig_text);
      break;
    case 2:
      func_out(func_sort_sym(obr_text), 1);
      freedom(orig_text);
      break;
    case 3:
      func_out(func_repl_digit(obr_text), 1);
      freedom(orig_text);
      break;
    case 4:
      func_out(func_odd_del(obr_text), 0);//используются предложения обработанного текста
      freedom(orig_text);
      break;
    case 9:
      func_out(func_cw(obr_text), 0);//используются предложения обработанного текста
      freedom(orig_text);
      break;
    default:
      wprintf(L"Error: Команды не существует");
      freedom(orig_text);
  }
  return 0;
}
