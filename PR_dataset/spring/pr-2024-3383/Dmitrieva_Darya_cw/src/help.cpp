#include "help.h"
void HELP(){
    cout<<"Course work for option 5.4, created by Darya Dmitrieva"<<endl;
    cout<<endl;
    cout<<"Программа предназначена для обработки BMP изображений:"<<endl;
    cout<<"- 3-ая версия BMP"<<endl;
    cout<<"- 24 бит/пиксель - глубина цвета"<<endl;
    cout<<endl;
    cout<<"Доступный функционал:"<<endl;
    cout<<"-h/--help  -  Вывод справки"<<endl;
    cout<<"-f/--info  -  Вывод информации об изображении"<<endl;
    cout<<"-i/--input  -  Имя входного изображения"<<endl;
    cout<<"-o/--output  -  Имя выходного изображения"<<endl;
    cout<<endl;
    cout<<"-I/--inverse  -  Флаг для выполнения инверсия цвета в заданной области"<<endl;
    cout<<"Область задается флагами:"<<endl;
    cout<<"-l/--left_up  -  Значение задаётся в формате `left.up`, где left – координата по x, up – координата по y"<<endl;
    cout<<"-r/--right_down  -  Значение задаётся в формате `right.below`, где right – координата по x, below – координата по y"<<endl;
    cout<<endl;
    cout<<"-g/--gray  -   Флаг для преобразования в Ч/Б область изображения"<<endl;
    cout<<"Область задается флагами:"<<endl;
    cout<<"-l/--left_up  -  Значение задаётся в формате `left.up`, где left – координата по x, up – координата по y"<<endl;
    cout<<"-r/--right_down  -  Значение задаётся в формате `right.below`, где right – координата по x, below – координата по y"<<endl;
    cout<<endl;
    cout<<"-d/--line  -  Флаг для рисования отрезка"<<endl;
    cout<<"Отрезок определяется:"<<endl;
    cout<<"-s/--start  -  Значение задаётся в формате `x.y`, где x – координата по x, y – координата по y"<<endl;
    cout<<"-e/--end  -  Значение задаётся в формате `x.y`, где x – координата по x, y – координата по y"<<endl;
    cout<<"-t/--thickness  -  Толщина линии"<<endl;
    cout<<"-c/--color  -  Цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту"<<endl;
    cout<<endl;
    cout<<"-H/--resize  -  Флаг для изменение размера изображения с его обрезкой или расширением фона"<<endl;
    cout<<"Функционал определяется"<<endl;
    cout<<"--<side>  -   Может принимать значения left, right, above, below"<<endl;
    cout<<"  <change>  -   Число: положительное означает расширение, отрицательное означает обрезку"<<endl;
    cout<<endl;
}
