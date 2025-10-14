int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        exec("hog", 0);
    }

    int pid2 = fork();
    if (pid2 == 0) {
        exec("sleeper", 0);
    }

    while (1) {
        sleep(200);
    }
}
