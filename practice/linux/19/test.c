int div(int div_i, int div_j) {
    int a4, b4;
    char *c4;

    a4 = div_i + 3;
    b4 = div_j + 3;
    c4 = "div function";
    return (div_i / div_j);
}
int sub(int sub_i, int sub_j) {
    int a3, b3;
    char *c3;
    a3 = sub_i + 2;
    b3 = sub_j + 2;
    c3 = "sub function";
    div(a3, 0); // Error: divided by 0!
    return (sub_i - sub_j);
}
int add(int add_i, int add_j) {
    int a2, b2;
    char *c2;
    a2 = add_i + 1;
    b2 = add_j + 1;
    c2 = "add function";
    sub(a2, b2);
    return (add_i + add_j);
}
int main(int argc, char *argv[]) {
    int a1, b1;
    char *c1;
    a1 = 1;
    b1 = 0;
    c1 = "main function";
    add(a1, b1);
    return 0; }
