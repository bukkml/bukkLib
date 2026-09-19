#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof_(char* s);

int main() {
    char* s = "123.456e-6";
    printf("%f\n", atof_(s));

    return 0;
}

double atof_(char* s) {
    double var, power;

    int i, sign;


    for (i = 0; isspace(s[i]); i++);

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '-' || s[i] == '+')
        i++;

    for (var = 0.0; isdigit(s[i]); i++)
        var = var * 10.0 + s[i] - '0';

    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        var = var * 10 + s[i] - '0';
        power *= 10.0;
    }

    var /= power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        int e_sign = (s[i] == '-') ? -1 : 1;

        if (s[i] == '-' || s[i] == '+')
            i++;

        int expanent;
        for (expanent = 0; isdigit(s[i]); i++) 
            expanent = expanent * 10 + s[i] - '0';

        var = var * pow(10, expanent * e_sign);
    }

    return sign * var;
}
