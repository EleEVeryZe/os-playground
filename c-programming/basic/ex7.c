/*
Contagem de Caracteres: Crie uma função que conte quantas vezes um caractere aparece em uma string usando apenas aritmética de ponteiros.
*/
int countChar(char *strg, char chr) {
    int ocorr = 0;
    int i = 0;
    while (*(strg + i++) != '\0'){
        if (*(strg + i) == chr)
            ocorr++;
    }
    return ocorr;
}

int main() {
    char chr = 'b';
    char *srtg = "abbabb";
    printf("Char:%c shows %d times in '%s' ", chr, countChar("abbabb", 'b'), srtg);
}