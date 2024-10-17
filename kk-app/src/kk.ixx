module;

export module kk;

extern "C" void puts(const char *);

export namespace kk {

    void foo() {
        puts("foo");
    }
}