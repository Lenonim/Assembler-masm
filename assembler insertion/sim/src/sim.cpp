#include <cstring>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <Windows.h>

bool is_text(char* str) {
	bool flag = 0;
	int strlen = std::strlen(str);
	__asm {
		mov eax, str // ��������� ��������� �� ������ ����� � eax
		mov ecx, strlen // ��������� ����� ������ � �������
		sub ecx, 1 // ��������� ������� �� 1, ����� �� ������� � ��������������� ���� ��� ���������
		mov bl, '.' // ��������� �������� ����� � ������ 
		
		start_cycle:
		cmp byte ptr[eax + ecx], bl // ���������� ��������� ������� � �������� 
		je _out // ���� ���������� ������� �����...
			loop start_cycle
			jmp _end // ����� ������� �� ������� � ������ 0
		_out: // ... �� 
			mov flag, 1 // ������������ ���� � 1
		_end:
	}
	return flag;
}

bool special_condition(char* str) {
	bool general_flag = 0;
	int strlen = std::strlen(str);
	__asm {
		mov eax, str // ������� � esi ����� ������� �������� ������
		mov ecx, strlen // ���������� � ������� �������� ����� ������ 
		mov esi, 0 // ���������� ��� ��������

		_lo: // ���� � ����
			mov bl, [eax + esi] // ���������� � bl ������� ������
			mov bh, '0' // �������� � ������ 0

// -------- �������� �� �����
			cmp bh, bl // ���������� ��� ������ � ����
			jbe _con // ���� ������ ������ ���� ����� 0...
				jmp _loop_continue // ����� �� ��������� �� ��������� �������� �����
			_con: // ... �� �� ���������� ���������
				mov bh, '9' // ������� � ������ 9
				cmp bh, bl // ���� ������ ������ ���� ����� 9...
				jae _condition_continue // ...�� ��� �������� ��������� ������
					jmp _loop_continue // ����� �� ��������� �� ��������� �������� �����
			_condition_continue:

			add esi, 1 // ����������� �������� �� 1
			mov bl, [eax + esi] // ���������� � bl ��������� ������ ��� ���������� ��������
			sub esi, 1 // ��������� �������� �� 1
			mov bh, 'a' // ���������� � ������ a

// -------- �������� ���������� ������� �� �������� ��������� �����
			cmp bh, bl // ���� ������ ������ ���� ����� �...
			jbe _cont
				mov general_flag, 0 // ������������� ���� � 0
				jmp _result // ������� �� �����, �.�. ����� ����� �� �������� ��������� �����
			_cont: // ... �� ��������� ��������� �������� 
				mov bh, 'z' // ���������� � ������ z
				cmp bh, bl // ���� ������ ������ ���� ����� z...
				jae _gen
					mov general_flag, 0 // ������������� ���� � 1
					jmp _result // ������� �� �����, �.�. ����� ����� �� �������� ��������� �����
				_gen: // ...��
					mov general_flag, 1 // ������������� ���� � 1

			_loop_continue: 
			add esi, 1 // ����������� �������� �� 1
		loop _lo // ���������� ������� �� 1 � ��������� �� ��������� ��������		
		_result:
	}
	return general_flag;
}

char swap_letters(char h) {
	char alphabeth[34] = "�����Ũ��������������������������";
	int len_alph = std::strlen(alphabeth);
	__asm {
		lea esi, [alphabeth] // ��������� ��������� �� ������ ������� �������� � esi
		lea edi, [alphabeth] // ��������� ��������� �� ������ ������� �������� � edi ��� �������� � �����

		mov ecx, len_alph // ���������� � ������� �������� ����� ��������
		dec ecx // ��������� ������� �� 1
		_l: // ���� � ����
			inc edi // ������� ��������� edi ������ �� 1
		loop _l // ��������� ������� �� 1 � ��������� �� ����� �������� �����

		mov al, h // ���������� ������ � ������� al
		mov ecx, len_alph // ��������� � ������� ����� ��������

		_loop: // ���� � ����
		cmp al, [esi] // ���� ���������� ������ ������ � ��������...
		je _change_letter
			inc esi // ������� ��������� ������ �� 1
			dec edi // ������� ��������� ����� �� 1
			loop _loop // ��������� ������� �� 1 � �������� �� ����� ��������
			jmp _end_prog // ���� ���������� ������ �� ����� ���������, �� �������������� ����� �� ������� ����� ���������� �����
		_change_letter: // ...��
			mov al, [edi] // ��������� ���������� ����� � al 
			mov h, al // � ���������� � � ���������� ������
		_end_prog:
	}
	return h;
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[100];
	std::cout << "������� ������: ";
	std::cin.getline(str, 100);

	if (is_text(str)) {
		std::cout << "�������� �� ����� ��������!\n";
		if (special_condition(str)) {
			std::cout << "�������� ������������ ������� ���������!\n";
			for (int i = 0; i < std::strlen(str); i++)
				str[i] = swap_letters(str[i]);
			std::cout << str << "\n";
		}
		else
			std::cout << "�������� ������������ ������� �� ���������!\n";
	}
	else
		std::cout << "��� �� �����!\n";

	return 0;
}
