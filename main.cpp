#include <iostream>
#include <fstream>

using namespace std;

int checkInput(){
    int input;
    try {
        cin >> input;
        if (cin.fail()) {
            throw 1;
        }
    } catch (int exeption) {
        cout << "ERROR!!!";
        exit(0);
    }
    cin.sync();
    return input;
}
//1.С клавиатуры или с файла (*) (пользователь сам может выбрать способ ввода) вводится последовательность,
// содержащая от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр.
// Между соседними словами произвольное количество пробелов. За последним символом стоит точка.
string function1(){
    incorrect:
    cout << "Which type of input do you prefer?(1 - file; 2 - keyboard):";
    int input = checkInput();
    string str = "";
    if (input == 1){
        ifstream File;
        File.open("C:\\FirstCursProgramm\\C++\\stepik_lab_4\\lab_4.txt");
        if(File.is_open()){
            while(!File.eof()){
                string str1;
                getline(File, str1);
                str += str1;
            }
        } else{
            cout << "file could not be opened";
            return "";
        }
        File.close();
    } else if (input == 2){
        getline(cin, str);
    }else{
        goto incorrect;
    }
    return str;
}
//2. Необходимо отредактировать входной текст:
//·удалить лишние пробелы;
//·удалить лишние знаки препинания (под «лишними» подразумевается несколько подряд идущих знаков;
//·исправить регистр букв, если это требуется (пример некорректного использования регистра букв: пРиМЕр);
string function2(string str){
    string strRes = "";
    cout << "String before editing:" << "\n" << str << "\n";
    bool flag = true;
    for (int i = 0; i <= str.length(); i++){
        if (str[i] == ' '){
            if (flag){
                continue;
            }else {
                flag = true;
                strRes+=str[i];
            }
        }else if(str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z'){
            if (str[i]>='A' && str[i]<='Z' && !flag){
                strRes+=str[i]+32;
            }else{
                strRes+=str[i];
            }
            flag = false;
        }else{
            flag = false;
            if(str[i] == '.' && str[i+1] == '.' && str[i+2] == '.'){
                i+=2;
                strRes += "...";
                continue;
            }
            if(str[i] != str[i-1]){
                strRes += str[i];
            }
        }
    }
    cout << "String after editing:" << "\n" << strRes;

}

int main() {
    string str;
    //1.С клавиатуры или с файла (*) (пользователь сам может выбрать способ ввода) вводится последовательность,
    // содержащая от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр.
    // Между соседними словами произвольное количество пробелов. За последним символом стоит точка.
    str = function1();
    //2. Необходимо отредактировать входной текст:
    //·удалить лишние пробелы;
    //·удалить лишние знаки препинания (под «лишними» подразумевается несколько подряд идущих знаков;
    //·исправить регистр букв, если это требуется (пример некорректного использования регистра букв: пРиМЕр);
    function2(str);
    return 0;
}
