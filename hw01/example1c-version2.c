#include <stdio.h>
#include <ctype.h>
#include <string.h>

void delete_space(char *s) {
    int j = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}

int main() {
    char input[1000];
    gets(input);
    delete_space(input);
    int len = strlen(input);
    int ans = 0;
    int i = 0;

    // 处理第一个数字
    while (i < len && input[i] != '=' && isdigit(input[i])) {
        ans = ans * 10 + (input[i] - '0');
        i++;
    }

    while (i < len && input[i] != '=') {
        if (input[i] == '+' || input[i] == '-') {
            char op1 = input[i];
            i++;
            int part1 = 0;

            // 读取紧随的数字
            while (i < len && isdigit(input[i]) && input[i] != '=') {
                part1 = part1 * 10 + (input[i] - '0');
                i++;
            }

            // 处理后续的乘除运算
            while (i < len && input[i] != '+' && input[i] != '-' && input[i] != '=') {
                char op = input[i];
                i++;
                int num = 0;
                int flag = 0;

                // 读取操作数
                while (i < len && isdigit(input[i]) && input[i] != '=') {
                    num = num * 10 + (input[i] - '0');
                    i++;
                    flag = 1;
                }

                if (!flag) num = 1;
                if (op == '*') part1 *= num;
                else if (op == '/') part1 /= num;
            }

            // 更新结果
            if (op1 == '+') ans += part1;
            else ans -= part1;

        } else if (input[i] == '*' || input[i] == '/') {
            // 直接处理乘除运算
            while (i < len && input[i] != '+' && input[i] != '-' && input[i] != '=') {
                char op = input[i];
                i++;
                int num = 0;

                // 读取操作数
                while (i < len && isdigit(input[i]) && input[i] != '=') {
                    num = num * 10 + (input[i] - '0');
                    i++;
                }

                // 更新结果
                if (op == '*') ans *= num;
                else if (op == '/') ans /= num;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}