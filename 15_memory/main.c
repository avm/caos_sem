   
struct foo {
    char c;  // 0
    int x;   // 4

    double d;  //  8
    char str[10];  // 16

    struct foo* next;  // 28
    char c2; // 32
};

static int x;

void main() {
    static char hello_array[] = "hello";
    static char hello2[] = "hello";
    static char* hello_const = "hello";
    hello_const++;

    static struct foo bar[2];
    printf("%d\n", sizeof(struct foo));
    bar[0].next = bar + 1;
}
