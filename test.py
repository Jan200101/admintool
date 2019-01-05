from os import name, environ, access, pathsep, X_OK
from os.path import isfile, join
from subprocess import Popen, PIPE
from time import sleep


def which(program) -> bool:
    for direc in environ["PATH"].split(pathsep):
        file = join(direc, program)
        if isfile(file) and access(file, X_OK):
            return True
    return False


SUCCESS = "!!!SUCCESS!!!\n"
FAILURE = "!!!FAILURE!!!\n"


def main() -> None:

    if name != 'nt' and which("make"):
        print("================= RUNNING LINUX TESTS =================")

        print("[RELEASE]")
        if test("Release"):
            print(FAILURE)
            exit(1)
        print(SUCCESS)

        print("[DEBUG]")
        if test("Debug"):
            print(FAILURE)
            exit(1)
        print(SUCCESS)

    if which("mingw32-make"):
        print("================= RUNNING WINDOWS TESTS =================")

        print("[RELEASE]")
        if test("Release", True):
            print(FAILURE)
            exit(1)
        print(SUCCESS)

        print("[DEBUG]")
        if test("Debug", True):
            print(FAILURE)
            exit(1)
        print(SUCCESS)


def test(type: str, windows: bool = False) -> bool:

    if not windows:
        make = "make"
        args = ""
    else:
        make = "mingw32-make"
        args = "WIN=1"

    cleanup = Popen(f'{make} clean', shell=True, stdout=PIPE, stderr=PIPE)
    while cleanup.poll() is None:
        sleep(0.5)
    del cleanup

    proc = Popen(f"{make} TARGET={type} {args}", shell=True, stdout=PIPE, stderr=PIPE)

    while proc.poll() is None:
        sleep(0.5)

    if proc.returncode != 0:
        print(proc.returncode)
        output = proc.communicate()
        for message in output:
            print(message.decode())
        return 1

    return 0

if __name__ == "__main__":
    main()
