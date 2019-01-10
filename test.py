from os import name, environ, access, pathsep, X_OK
from os.path import isfile, join
from multiprocessing import cpu_count as _cpu_count
from subprocess import Popen, PIPE
from shutil import rmtree
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
    cpu_count = _cpu_count()

    rmtree("obj", ignore_errors=True)

    if name != 'nt' and which("make"):
        print("================= RUNNING LINUX TESTS =================")

        print("[RELEASE]")
        if test("Release", cpu_count):
            print(FAILURE)
        else: print(SUCCESS)

        print("[DEBUG]")
        if test("Debug", cpu_count):
            print(FAILURE)
        else: print(SUCCESS)

    if which("mingw32-make"):
        print("================ RUNNING WINDOWS TESTS ================")

        print("[RELEASE]")
        if test("Release", cpu_count, True):
            print(FAILURE)
        else: print(SUCCESS)

        print("[DEBUG]")
        if test("Debug", cpu_count, True):
            print(FAILURE)
        else: print(SUCCESS)


def test(type: str, cpu_count: int, windows: bool = False) -> bool:

    if not windows:
        make = f"make -j{cpu_count}"
        args = ""
    else:
        make = "mingw32-make"
        args = f"WIN=1 -j{cpu_count}"

    proc = Popen(f"{make} TARGET={type} {args}", shell=True, stdout=PIPE, stderr=PIPE)

    while proc.poll() is None:
        sleep(1)

    rmtree("obj", ignore_errors=True)

    if proc.returncode != 0:
        print(proc.returncode)
        output = proc.communicate()
        for message in output:
            print(message.decode())
        return 1

    return 0

if __name__ == "__main__":
    main()
