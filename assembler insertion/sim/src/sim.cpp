#include <cstring>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <Windows.h>

bool is_text(char* str) {
	bool flag = 0;
	int strlen = std::strlen(str);
	__asm {
		mov eax, str // сохраняем указатель на первый симвл в eax
		mov ecx, strlen // сохраняем длину стркои в счётчик
		sub ecx, 1 // уменьшаем счётчик на 1, чтобы не попасть в детерминирующий ноль при сравнении
		mov bl, '.' // сохраняем значение точки в буффер 
		
		start_cycle:
		cmp byte ptr[eax + ecx], bl // сравниваем последний элемент с буффером 
		je _out // если последнеий элемент точка...
			loop start_cycle
			jmp _end // иначе выходим из функции с флагом 0
		_out: // ... то 
			mov flag, 1 // истанавиваем флаг в 1
		_end:
	}
	return flag;
}

bool special_condition(char* str) {
	bool general_flag = 0;
	int strlen = std::strlen(str);
	__asm {
		mov eax, str // передаём в esi адрес первого элемента строки
		mov ecx, strlen // записываем в счётчик значение длины строки 
		mov esi, 0 // переменная для смещения

		_lo: // вход в цикл
			mov bl, [eax + esi] // записываем в bl текущий символ
			mov bh, '0' // помещаем в буффер 0

// -------- проверка на число
			cmp bh, bl // сравниваем наш символ с нулём
			jbe _con // если символ больше либо равен 0...
				jmp _loop_continue // иначе мы переходим на следующую итерацию цикла
			_con: // ... то мы продолжаем сравнения
				mov bh, '9' // пмещаем в буффер 9
				cmp bh, bl // если символ меньше либо равен 9...
				jae _condition_continue // ...то идём смотреть следующий символ
					jmp _loop_continue // иначе мы переходим на следующую итерацию цикла
			_condition_continue:

			add esi, 1 // увеличиваем смещение на 1
			mov bl, [eax + esi] // записываем в bl следующий символ для дальнейших проверок
			sub esi, 1 // уменьшаем смещение на 1
			mov bh, 'a' // записываем в буффер a

// -------- проверка следующего символа на строчкую латинскую букву
			cmp bh, bl // если символ больше либо равен а...
			jbe _cont
				mov general_flag, 0 // устанавливаем флаг в 0
				jmp _result // выходим из цикла, т.к. после числа не строчная латинская буква
			_cont: // ... то выполняем следующую проверку 
				mov bh, 'z' // записываем в буффер z
				cmp bh, bl // если символ меньше либо равен z...
				jae _gen
					mov general_flag, 0 // устанавливаем флаг в 1
					jmp _result // выходим из цикла, т.к. после числа не строчная латинская буква
				_gen: // ...то
					mov general_flag, 1 // устанавливаем флаг в 1

			_loop_continue: 
			add esi, 1 // увеличиваем смещение на 1
		loop _lo // уменьшаяем счётчик на 1 и переходим на следующую итерацию		
		_result:
	}
	return general_flag;
}

char swap_letters(char h) {
	char alphabeth[34] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	int len_alph = std::strlen(alphabeth);
	__asm {
		lea esi, [alphabeth] // сохраняем указатель на первый элемент алфавита в esi
		lea edi, [alphabeth] // сохраняем указатель на первый элемент алфавита в edi для смещения в конец

		mov ecx, len_alph // записываем в счётчик значение длины алфавита
		dec ecx // уменьшаем счётчик на 1
		_l: // вход в цикл
			inc edi // смещаем указатель edi вправо на 1
		loop _l // уменьшаем счётчик на 1 и переходим на новую итерацию цикла

		mov al, h // перемещаем символ в регистр al
		mov ecx, len_alph // сохраняем в счётчик длину алфавита

		_loop: // вход в цикл
		cmp al, [esi] // если переданный символ найден в алфавите...
		je _change_letter
			inc esi // смещаем указатель вправо на 1
			dec edi // смещаем указатель влево на 1
			loop _loop // уменьшаем счётчик на 1 и переходи на новую итерацию
			jmp _end_prog // если переданный символ не буква кириллицы, то организовываем выход из функции после завершения цикла
		_change_letter: // ...то
			mov al, [edi] // сохраняем зеркальную букву в al 
			mov h, al // и записываем её в переданный символ
		_end_prog:
	}
	return h;
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[100];
	std::cout << "введите строку: ";
	std::cin.getline(str, 100);

	if (is_text(str)) {
		std::cout << "Проверка на текст пройдена!\n";
		if (special_condition(str)) {
			std::cout << "Проверка специального условия выполнена!\n";
			for (int i = 0; i < std::strlen(str); i++)
				str[i] = swap_letters(str[i]);
			std::cout << str << "\n";
		}
		else
			std::cout << "Проверка специального условия не выполнена!\n";
	}
	else
		std::cout << "Это не текст!\n";

	return 0;
}
