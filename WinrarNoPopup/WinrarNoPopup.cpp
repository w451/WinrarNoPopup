#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#define PAUSE() system("pause");

using namespace std;

vector<vector<BYTE>> signatures = { {0x48, 0x8b, 0x0d, 0x3a, 0xaf, 0x12, 0x00, 0x4c, 0x8d, 0x0d, 0x23, 0xa2, 0x03, 0x00, 0x4c, 0x8b, 0xc0, 0x4c, 0x89, 0x7c, 0x24, 0x20, 0x48, 0x8d, 0x15, 0x24, 0xd8, 0x0a, 0x00, 0xff, 0x15, 0x3e, 0x65, 0x09, 0x00 }, 
	{ 0x48, 0x8b, 0x0d, 0xd9, 0xaf, 0x12, 0x00, 0x4c, 0x8d, 0x05, 0x5a, 0xd4, 0x09, 0x00, 0x4c, 0x89, 0x7c, 0x24, 0x58, 0x48, 0x8d, 0x15, 0xa6, 0xd8, 0x0a, 0x00, 0x48, 0x89, 0x4c, 0x24, 0x50, 0x44, 0x8b, 0xce, 0x4c, 0x89, 0x7c, 0x24, 0x48, 0x33, 0xc9, 0x4c, 0x89, 0x7c, 0x24, 0x40, 0x44, 0x89, 0x74, 0x24, 0x38, 0x89, 0x6c, 0x24, 0x30, 0x89, 0x7c, 0x24, 0x28, 0x89, 0x5c, 0x24, 0x20, 0xff, 0x15, 0x63, 0x65, 0x09, 0x00 } };
string emptyval;
int wmain(int argc, wchar_t* argv[])
{
	if (argc < 2) {
		cout << "Where is winrar man? (Drag and drop winrar exe onto me)" << endl;
		PAUSE();
		return -1;
	}

	HANDLE h = CreateFileW(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (h == INVALID_HANDLE_VALUE) {
		cout << "Couldn't find the file?: "<< GetLastError() << endl;
		PAUSE();
		return -1;
	}
	DWORD d = GetFileSize(h, nullptr);

	BYTE* buffer = new BYTE[d];
	if (!ReadFile(h, buffer, d, nullptr, nullptr)) {
		cout << "Couldn't read file?: "<<GetLastError() << endl;
		CloseHandle(h);
		PAUSE();
		return -1;
	}

	HANDLE backup = CreateFileW((wstring(argv[1])+L"_BACKUP").c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	bool error = false;
	if (backup != INVALID_HANDLE_VALUE) {
		if (!WriteFile(backup, buffer, d, nullptr, nullptr)) {
			error = true;
			cout << "Couldn't write backup" << endl;
		}
		else {
			cout << "Succesfully made a backup!" << endl;
		}
		CloseHandle(backup);
	}
	else {
		error = true;
		cout << "Couldn't open backup file" << endl;
	}

	if (error) {
		cout << "Couldn't make backup... enter to continue anyways. Otherwise just close me." << endl;
		PAUSE();
	}

	for (vector<BYTE> signature : signatures) {
		DWORD loc = -1;

		for (DWORD x = 0; x < d - signature.size() - 1; x++) {
			bool found = true;
			for (DWORD y = 0; y < signature.size(); y++) {
				if (buffer[x + y] != signature[y]) {
					found = false;
				}
			}
			if (found) {
				loc = x;
				break;
			}
		}

		if (loc != -1) {
			cout << "Found: " << hex << loc << endl;
			memset(buffer + loc, 0x90, signature.size());
		}
		else {
			cout << "Couldn't find " << signature.size() << endl;
		}
	}

	SetFilePointer(h, 0, 0, FILE_BEGIN);

	if (!WriteFile(h, buffer, d, nullptr, nullptr)) {
		cout << "Couldn't write to file?: " << GetLastError() << endl;
		CloseHandle(h);
		PAUSE();
		return -1;
	}
	else {
		cout << "Should be good man" << endl;
	}


	CloseHandle(h);

	PAUSE();

	return 0;
}