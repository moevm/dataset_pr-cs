#include <wchar.h>
#include <stdlib.h>


#include "temp.h"


/*
ac
odio
tempor
orci
dapibus
ultrices
in
iaculis
nunc
sed
augue
lacus
viverra
vitae
congue
eu
consequat
ac
felis
donec
et
odio
pellentesque
diam
volutpat
commodo
sed
egestas
egestas
fringilla
phasellus
faucibus
scelerisque
eleifend
donec
pretium
vulputate
sapien
nec
sagittis
aliquam
malesuada
bibendum
arcu
vitae
elementum
curabitur
vitae
nunc
sed
velit
dignissim
sodales
ut
eu
sem
integer
vitae
justo
eget
magna
fermentum
iaculis
eu
non
diam
phasellus
vestibulum
lorem
sed
risus
ultricies
tristique
nulla
aliquet
enim
tortor
at
auctor
urna
nunc
id
cursus
metus
aliquam
eleifend
mi
in
nulla
posuere
sollicitudin
aliquam
ultrices
sagittis
orci
a
scelerisque
purus
semper
eget
*/


void secret(wchar_t task)
{
	switch (task)
	{
		case (7):
			wprintf(L"[Инфо] \e[0;32mБип!\e[0m\n");
			break;
		case (42):
			wprintf(L"[Инфо] Получен Вопрос-Сразу-Обо-Всём. Вычисленный Ответ-Сразу-На-Всё совпал с кодом Вопроса. Сообщение об ошибке отправлено разработчику.\n");
			break;
		case (181):
			wprintf(L"[Инфо] Йо-хо-хо!");
			break;
		case (9773):
			wprintf(L"[Инфо] Правильный символ.");
			break;
	}
}