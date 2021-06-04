#ifndef DEFINES_H
#define DEFINES_H

#define REALLOC_SIZE 2000
#define COLOR_NAME_SIZE 30
#define HEADER_SIZE 8
#define FILE_SIZE 20

#define OPEN_FILE_ERROR "Файл не может быть открыт. Поверьте, верно ли вы указали полное имя файла\n"
#define OPEN_FILE_ERROR_CODE 1

#define FILE_FORMAT_ERROR "Передан не PNG файл\n"
#define FILE_FORMAT_ERROR_CODE 2

#define PNG_CREATE_READ_STRUCT_ERROR "Ошибка создания png read struct\n"
#define PNG_CREATE_READ_STRUCT_ERROR_CODE 3

#define PNG_CREATE_INFO_STRUCT_ERROR "Ошибка создания png info struct\n"
#define PNG_CREATE_INFO_STRUCT_ERROR_CODE 4

#define INIT_IO_ERROR "Ошибка во время инициализации\n"
#define INIT_IO_ERROR_CODE 5

#define READ_IMAGE_ERROR "Ошибка при чтении изображения\n"
#define READ_IMAGE_ERROR_CODE 6

#define PNG_CREATE_WRITE_STRUCT_ERROR "Ошибка при создании png write struct\n"
#define PNG_CREATE_WRITE_STRUCT_ERROR_CODE 7

#define WRITE_IMAGE_ERROR "Ошибка при записи изображения\n"
#define WRITE_IMAGE_ERROR_CODE 8

#define COORDINATES_ERROR "Переданы некоррекорректные значения для координат или были забыты ключи --start/--end\n"
#define COORDINATES_ERROR_CODE 9

#define WRITE_COLOR_TO_CHANGE_ERROR "Передан цвет, который отсутствует в таблице цветов. Чтобы посмотреть таблицу цветов, запустите программу с ключом --help (-h)\n"
#define WRITE_COLOR_TO_CHANGE_ERROR_CODE 10

#define SQUARE_PARAMS_ERROR "Переданы некорректные значения для стророны и/или толщины линий квадрата\n"
#define SQUARE_PARAMS_ERROR_CODE 11

#define INCORRECT_MODE_ERROR "Передан некорректный режим работы. Чтобы узнать список доступных режимов, запустите программу с ключом --help (-h)\n"
#define INCORRECT_MODE_ERROR_CODE 12

#define WRONG_ARGS_ERROR "Переданы неверные ключи / пропущены их аргументы / путь к файлу указан неверно. Чтобы узнать список доступных ключей и их аргументов, запустите программу с ключом --help (-h)\n"
#define WRONG_ARGS_ERROR_CODE 13

#define PNG_COLOR_TYPE_ERROR "Тип цветов изображения должен быть RGBA. Выберите другое изображение и перезапустите программу\n"
#define PNG_COLOR_TYPE_ERROR_CODE 14

#define NO_ENOUGH_SPACE "Недостаточно места\n"
#define NO_ENOUGH_SPACE_CODE 15

#define WRITE_COORDINATES_ERROR "Координаты переданы некоррентно. Чтобы узнать, как правильно предать координаты, запустите программу с ключом --help (-h)\n"
#define WRITE_COORDINATES_ERROR_CODE 16

#define WRITE_SQUARE_PARAMS_ERROR "Параметры квадрата переданы некорректно. Чтобы узнать, как правильно передать параметры квадрата, запустите программу с ключом --help (-h)\n"
#define WRITE_SQUARE_PARAMS_ERROR_CODE 17

#define NO_FUNCTION_SELECTED_ERROR "Не выбран режим обработки изображения. Чтобы узнать, список режимов обработки изображения, запустите программу с ключом --help (-h)\n"
#define NO_FUNCTION_SELECTED_ERROR_CODE 18

#endif 