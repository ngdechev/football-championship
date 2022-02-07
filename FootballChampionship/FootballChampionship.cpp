// Библиотеки
#include <iostream>
#include <string> 
#include <stdlib.h> 
#include <time.h>
#include <iomanip>
#include <fstream>

using namespace std;

// Максимален размер на масива за отборите / колко отбори най-много могат да се въведат
const unsigned int N = 5;

// Файлове
fstream fp;

// Структура за запазване на данните за генерираните мачове
struct Games {
	string hostTeamName;
	string guestTeamName;
	int hostGoals;
	int guestGoals;
};

// Структура за запазване на данните за футболните отбори
struct FootballTeam {
	int registrationNumber;
	string teamName;
	int createdYear;
	string city;
	Games footballGames[2 * N];
};

// Прототипи на функциите
void addTeams(FootballTeam team[], int& size, int numberOfTeams); // Добаване на отбори
void printTeams(FootballTeam team[], int size); // Принтиране на отборите на екрана
void earliestCreatedTeam(FootballTeam team[], int size); // Най-рано създадения отбор 
void footballMatches(FootballTeam team[], int size); // Генериране на срещите / мачовете
void queries(FootballTeam team[], int size); // Справки с подменюта
// Функции справки
void displayTeamsInOrder(FootballTeam team[], int size);
void maxGoals(FootballTeam team[], int size);

void saveToFile(FootballTeam team[], int size); // Запазване във файл
// Опции за запазване във файл
void saveToTextFile(FootballTeam team[], int size);
void saveToBinaryFile(FootballTeam team[], int size);

// Добаване на отбори
void addTeams(FootballTeam team[], int& size, int numberOfTeams) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Добаване на отбори ==========" << endl << endl;

	// Създаваме буферна променлива за отбор за да запазим данните за 1 отбор и после ще го добавим в главния масив от отбори
	FootballTeam buff;

	// Потребителят въвежда само 1 отбор
	if (numberOfTeams == 1) {
		cin.ignore();
		cout << "Въведи име на отбора: ";
		getline(cin, buff.teamName);
		cout << "Въведи година на създаване на отбора: ";
		cin >> buff.createdYear;
		cout << "Въведете град на основаване на отбора: ";
		cin >> buff.city;
		cout << endl;

		buff.registrationNumber = (N - size) + 1;

		// Добавяме 1 отбор към главния масив от отбори
		team[N - size] = buff;

		// Показва колко отбора могат още да се добавят
		size--;
	}
	else { // Потребителят въвежда няколко отбора
		for (int i = 0; i < numberOfTeams; i++) {
			cin.ignore();
			cout << "Въведи име на отбора: ";
			getline(cin, team[N - size].teamName);
			cout << "Въведи година на създаване на отбора: ";
			cin >> team[N - size].createdYear;
			cout << "Въведете град на основаване на отбора: ";
			cin >> team[N - size].city;
			cout << endl;

			team[N - size].registrationNumber = (N - size) + 1;

			// Показва колко отбора могат още да се добавят
			size--;
		}
	}

	// Проверка дали може да се въведат още отбори
	size > 0 ? cout << "\nМожете да въведете още " << size << " отбора." << endl : cout << "\nНе можете да въведете повече отбори!" << endl;
}

// Принтиране на отборите на екрана
void printTeams(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Извеждане на отборите ==========" << endl << endl;

	// Извеждане на отборите на екрана
	for (int i = 0; i < N - size; i++)
	{
		cout << "Регистрация номер: " << "#000" << team[i].registrationNumber << endl;
		cout << "Име на отбор: " << team[i].teamName << endl;
		cout << "Година на създаване на отбора: " << team[i].createdYear << endl;
		cout << "Град на основаване: " << team[i].city << endl << endl;
	}
}

// Най-ранно създадения отбор 
void earliestCreatedTeam(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Най-рано създадения отбор ==========" << endl << endl;

	FootballTeam temp;
	temp = team[0];

	for (int i = 1; i < N - size; i++) {
		if (temp.createdYear > team[i].createdYear) {
			temp.createdYear = team[i].createdYear;
			temp.teamName = team[i].teamName;
		}
	}

	cout << "Най-ранно създаденият отбор е " << temp.teamName << " създаден през " << temp.createdYear << " година." << endl << endl;
}

// Генериране на срещите / мачовете
void footballMatches(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Генериране на футболни срещи (мачове) ==========" << endl << endl;

	srand(unsigned int(time(NULL)));

	// Индекс за срещите / мачовете
	int k(0);

	// Заглавен ред на таблицата
	cout << "| Host Team Name | " << setw(12) << "Guest Team Name | " << setw(12) << "Host Goals | " << setw(12) << "Guest Goals |" << endl << endl;

	for (int i = 0; i < (N - size); i++)
	{
		for (int j = 0; j < (N - size); j++)
		{
			if (i != j) {
				// Генериране на срещите / мачовете
				team[i].footballGames[k].hostTeamName = team[i].teamName;
				team[i].footballGames[k].guestTeamName = team[j].teamName;
				team[i].footballGames[k].hostGoals = rand() % 10 + 1;
				team[i].footballGames[k].guestGoals = rand() % 10 + 1;

				team[j].footballGames[k].hostTeamName = team[i].teamName;
				team[j].footballGames[k].guestTeamName = team[j].teamName;
				team[j].footballGames[k].hostGoals = team[i].footballGames[k].hostGoals;
				team[j].footballGames[k].guestGoals = team[i].footballGames[k].guestGoals;

				// Извеждане на резултатите от срещите в таблица
				cout << team[i].footballGames[k].hostTeamName << setw(17) << team[i].footballGames[k].guestTeamName << setw(15) << team[i].footballGames[k].hostGoals
					<< setw(15) << team[i].footballGames[k].guestGoals << endl;

				k++;
			}
		}
	}
	cout << endl;
}

// Търсене на отбори
void searchTeams(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Търсене на отбор ==========" << endl << endl;

	string searchedTeam;
	bool flag(false);
	int k(0);

	// Въвеждане на името на отбора
	cout << "Въведете име на отбор: ";
	cin.ignore();
	getline(cin, searchedTeam);

	for (int i = 0; i < (N - size) * 2; i++)
	{
		for (int j = 0; j < (N - size) * 2; j++)
		{
			if (searchedTeam == team[i].teamName) {
				// Ако има намерен отбор флага става true
				flag = true;

				cout << team[i].footballGames[k].hostTeamName << " vs " << team[j].footballGames[k].guestTeamName << " -> " << "[ " << team[i].footballGames[k].hostGoals
					<< " : " << team[i].footballGames[k].guestGoals << " ]" << endl;

				k++;
			}
		}
	}
	
	// Ако няма намерен отбор с въведенето име
	if (!flag) cout << "Няма намерен отбор с име " << searchedTeam << "." << endl;
}

// Справки с подменюта
void queries(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	// Избор от менюто
	int userChoice(0);

	// Меню за справките
	do {
		cout << "\n=========== Меню - Справки ===========" << endl;
		cout << "1.Извеждане на всички участниците в подреден ред" << endl;
		cout << "2.Извеждане на отбора отбелязал най-много попадения" << endl;
		cout << "3.Изход" << endl;
		cout << "Избор: ";

		cin >> userChoice;
	} while (userChoice < 1 || userChoice > 3);
	switch (userChoice) {
	case 1:
		// Извеждане на всички участниците в подреден ред
		displayTeamsInOrder(team, size);
		break; 
	case 2:
		// Извеждане на отбора отбелязал най-много попадения
		maxGoals(team, size);
		break; 
	} 
} 

// Извеждане на всички участниците в подреден ред
void displayTeamsInOrder(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	FootballTeam buff;
	int choice(0);

	bool flag(true);

	do {
		cout << "\n========== Извеждане на всички участниците в подреден ред ==========" << endl << endl;
		cout << "1.Година на основаване на отбора." << endl;
		cout << "2.Спечелени точки." << endl;
		cout << "3.Изход" << endl;
		cout << "Избор: ";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	switch (choice) {
	case 1:
		cout << "\n========== Сортиране по година на основаване ==========" << endl << endl;

		// Сортиране на отборите по година на основаване
		for (int k = (N - size); k > 1; k--) {
			if (flag == false) break;
			else flag = false;

			for (int i = 0; i < k - 1; i++) {
				if (team[i].createdYear < team[i + 1].createdYear)
				{
					buff = team[i];
					team[i] = team[i + 1];
					team[i + 1] = buff;

					flag = true;
				}
			}
		}

		// Извеждане на сортираните отбори по година на основаване
		for (int i = 0; i < (N - size); i++)
		{
			cout << "Регистрация номер: " << "#000" << team[i].registrationNumber << endl;
			cout << "Име на отбор: " << team[i].teamName << endl;
			cout << "Година на създаване на отбора: " << team[i].createdYear << endl;
			cout << "Град на основаване: " << team[i].city << endl << endl;
		}
		break;
	case 2:
		cout << "\n========== Спечелени точки ==========" << endl << endl;

		FootballTeam buffTeam, tempTeam[N];
		int points[N], tempPoints;

		for (int i = 0; i < (N - size); i++)
		{
			// Дава стойност 0 на всеки елемент
			points[i] = 0;
			// Копира отборите в друг масив
			tempTeam[i] = team[i];
		}

		// Генериране на точките
		for (int i = 0; i < (N - size); i++) {
			for (int j = 0; j < (N - size); j++) {
				if (j != i) {
					if (team[i].footballGames[i].hostGoals == team[i].footballGames[i].guestGoals) {
						points[i] += 1;
						points[j] += 1;
					}
					if (team[i].footballGames[i].hostGoals > team[i].footballGames[i].guestGoals) {
						points[i] += 3;
					}
					if (team[i].footballGames[j].hostGoals < team[i].footballGames[j].guestGoals) {
						points[j] += 1;
					}
				}
			}
		}

		// Сортиране
		for (int k = (N - size); k > 1; k--) {
			if (flag == false) break;
			else flag = false;

			for (int i = 0; i < k - 1; i++) {
				// Сортиране на отборите
				if (points[i] < points[i + 1]) {
					buffTeam = tempTeam[i];
					tempTeam[i] = tempTeam[i + 1];
					tempTeam[i + 1] = buffTeam;

					// Сортиране на точките
					tempPoints = points[i];
					points[i] = points[i + 1];
					points[i + 1] = tempPoints;

					flag = true;
				}
			}
		}

		for (int i = 0; i < (N - size); i++) cout << "Отбор: " << tempTeam[i].teamName << ", Спечелени точки: " << points[i] << endl;

		break;
	}
}

// Извеждане на отбора отбелязал най-много попадения
void maxGoals(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	cout << "\n========== Извеждане на отбора отбелязал най-много попадения ==========" << endl << endl;

	FootballTeam teamBuff, tempTeam[N];
	int goals[N], goalsBuff;

	for (int i = 0; i < (N - size); i++) {
		// Дава стойност 0 на всеки елемент
		goals[i] = 0;
		// Копира отборите
		tempTeam[i] = team[i];
	}

	// Събира головете на отборите
	for (int i = 0; i < (N - size); i++) {
		for (int j = 0; j < (N - size); j++) {
			if (i != j) {
				goals[i] = goals[i] + team[i].footballGames[j].hostGoals;
				goals[j] = goals[j] + team[i].footballGames[j].guestGoals;
			}
		}
	}

	// Сортиране
	for (int k = (N - size); k > 1; k--) {
		for (int i = 0; i < k - 1; i++) {
			if (goals[i] < goals[i + 1]) {
				// Сортиране на головете
				goalsBuff = goals[i];
				goals[i] = goals[i + 1];
				goals[i + 1] = goalsBuff;

				// Сортиране на отборите
				teamBuff = tempTeam[i];
				tempTeam[i] = tempTeam[i + 1];
				tempTeam[i + 1] = teamBuff;
			}
		}
	}

	cout << "Oтбора отбелязал най-много попадения е " << tempTeam[0].teamName << " с " << goals[0] << " вкарани голове." << endl;
}

// Запазване във файл
void saveToFile(FootballTeam team[], int size) {
	setlocale(LC_ALL, "bg_BG");

	int k(0), userChoice(0);

	do {
		cout << "=========== Меню - Запазване във файл ===========" << endl;
		cout << "1.Запазване в текстов файл" << endl;
		cout << "2.Запазване в двоичен файл" << endl;
		cout << "3.Изход" << endl;
		cout << "Избор: ";

		cin >> userChoice;
	} while (userChoice < 1 || userChoice > 3);
	switch (userChoice) {
	case 1:
		saveToTextFile(team, size);
		break;
	case 2:
		saveToBinaryFile(team, size);
		break;
	}
}

// Запазване в текстов файл
void saveToTextFile(FootballTeam team[], int size) {
	int k(0);

	// Отваряме файла за запис
	fp.open("footballMatches.txt", ios::out);

	// Проверка за грешка
	if (!fp) {
		cout << "Грешка при създаването на файла!" << endl;
		exit(1);
	}

	// Записване данните във файла
	for (int i = 0; i < (N - size); i++)
	{
		fp << "Регистрация номер: " << "#000" << team[i].registrationNumber << endl;
		fp << "Име на отбор: " << team[i].teamName << endl;
		fp << "Година на създаване на отбора: " << team[i].createdYear << endl;
		fp << "Град на основаване: " << team[i].city << endl << endl;
	}

	fp << "\nРезултати от футболните мачове (срещи): " << endl << endl;

	// Заглавен ред на таблицата
	fp << "| Host Team Name | " << setw(12) << "Guest Team Name | " << setw(12) << "Host Goals | " << setw(12) << "Guest Goals |" << endl << endl;
	for (int i = 0; i < (N - size); i++) {
		for (int j = 0; j < (N - size); j++) {
			if (i != j) {
				fp << team[i].footballGames[k].hostTeamName << setw(17) << team[i].footballGames[k].guestTeamName << setw(15) << team[i].footballGames[k].hostGoals
					<< setw(15) << team[i].footballGames[k].guestGoals << endl << endl;

				k++;
			}
		}
	}

	// Затваряме файла
	fp.close();

	// Проверка дали файлът е създаден успешно
	if (fp) cout << "Файлът, с име footballMatches.txt, е създаден успешно!" << endl;
}

// Запазване в двоичен файл
void saveToBinaryFile(FootballTeam team[], int size) {
	int k(0);

	// Отваряме файла за запис
	fp.open("footballMatches.dat", ios::out | ios::binary);

	// Проверка за грешка
	if (!fp) {
		cout << "Грешка при създаването на файла!" << endl;
		exit(1);
	}

	// Записване данните във файла
	for (int i = 0; i < (N - size); i++)
	{
		fp << "Регистрация номер: " << "#000" << team[i].registrationNumber << endl;
		fp << "Име на отбор: " << team[i].teamName << endl;
		fp << "Година на създаване на отбора: " << team[i].createdYear << endl;
		fp << "Град на основаване: " << team[i].city << endl << endl;
	}

	fp << "\nРезултати от футболните мачове (срещи): " << endl << endl;

	// Заглавен ред на таблицата
	cout << "| Host Team Name | " << setw(12) << "Guest Team Name | " << setw(12) << "Host Goals | " << setw(12) << "Guest Goals |" << endl << endl;

	for (int i = 0; i < (N - size); i++) {
		for (int j = 0; j < (N - size); j++) {
			if (i != j) {
				fp << team[i].footballGames[k].hostTeamName << setw(17) << team[i].footballGames[k].guestTeamName << setw(15) << team[i].footballGames[k].hostGoals
					<< setw(15) << team[i].footballGames[k].guestGoals << endl << endl;

				k++;
			}
		}
	}
	
	// Затваряме файла
	fp.close();

	// Проверка дали файлът е създаден успешно
	if (fp) cout << "Файлът, с име footballMatches.dat, е създаден успешно!" << endl;
}

int main() {
	setlocale(LC_ALL, "bg_BG");

	int userChoice, numberOfTeams(0), size = N;
	bool flag = false;
	FootballTeam teams[N];

	do {
		do {
			cout << "=========== Меню ===========" << endl;
			cout << "1.Въвеждане на участници" << endl;
			cout << "2.Извеждане на участници" << endl;
			cout << "3.Извеждане на най-ранно създадения отбор" << endl;
			cout << "4.Генериране на срещите (мачовете)" << endl;
			cout << "5.Търсене на отбор" << endl;
			cout << "6.Справки" << endl;
			cout << "7.Запазване във файл" << endl;
			cout << "0.Изход" << endl;
			cout << "Избор [0-7]: ";

			cin >> userChoice;
		} while (userChoice < 0 || userChoice > 7); // 7

		// Изчистване на екрана
		//system("cls");

		switch (userChoice) {
		case 0:
			exit(0);
			break;
		case 1:
			cout << "=========== Въвеждане на участници ===========" << endl << endl;

			do {
				cout << "Моля въведете число в интервала [1-5]: ";
				cin >> numberOfTeams;
			} while (numberOfTeams < 1 || numberOfTeams > size);

			addTeams(teams, size, numberOfTeams);
			break;
		case 2:
			printTeams(teams, size);
			break;
		case 3:
			earliestCreatedTeam(teams, size);
			break;
		case 4:
			footballMatches(teams, size);
			break;
		case 5:
			searchTeams(teams, size);
			break;
		case 6:
			queries(teams, size);
			break;
		case 7:
			saveToFile(teams, size);
			break;
		}
	} while (userChoice != 7);

	system("pause>null");
	return 0;
}