#ifndef HELPS
#define HELPS


#define ERR_UNKNOWN_FILE 40
#define ERR_INPUTQUALS 41
#define ERR_WRONGCOLOR 42

const std::string RED = "red";
const std::string BLUE = "blue";
const std::string GREEN = "green";

const std::string MESSAGE_HelpInfo = "Course work for option 3.2, created by Savva Starkov.\n\
--input, -i: Задает имя входного изображения. Если флаг не указан, предполагается, что имя входного изображения является последним аргументом.\n\
--output, -o: Задает имя выходного изображения. Если флаг не указан, предполагается, что имя выходного изображения является последним аргументом.\n\
--info: Печатает информацию об изображении и завершает работу.\n\
--help, -h: Выводит эту справку.\n\
--inverse: Инвертирует цвета на всем изображении.\n\
--component_sum: Устанавливает компоненту цвета как сумму двух других.\n\
--component_name: Задает, какую компоненту цвета нужно изменить. Возможные значения: red, green, blue.\n ";
extern uint32_t image_size;

const std::string MESSAGE_ArgcError = "Error: Too few arguments";
const std::string MESSAGE_UnknownFlag = "Unknown flag!";
const std::string MESSAGE_WrongColor = "Wrong color!";
#endif