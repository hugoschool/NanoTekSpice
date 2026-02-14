import os
import sys

BASE_DIR = os.path.dirname(os.path.realpath(__file__))
NANOTEKSPICE_FILE = os.path.join(os.path.join(BASE_DIR, "..", ".."), "nanotekspice")

class Colors:
    GREEN = '\033[92m'
    RED = '\033[91m'
    RESET = '\033[0m'

class Test:
    def __init__(self, ntsFile, inputFile, outputFile, exitCodeCheck = False):
        # True = success, False = failure
        self.state = False

        self.ntsFile = os.path.join(BASE_DIR, "files", ntsFile)
        self.inputFile = os.path.join(BASE_DIR, "files", inputFile)
        self.outputFile = os.path.join(BASE_DIR, "files", outputFile)

        # exitCodeCheck checks for an 84 return (mostly for parsing)
        self.exitCodeCheck = exitCodeCheck

    def run(self):
        if self.exitCodeCheck:
            return self.exitCodeRun()
        else:
            return self.fileRun()

    def exitCodeRun(self):
        # TODO: this can be replaced with subprocess.Popen
        command = os.popen(f"{NANOTEKSPICE_FILE} {self.ntsFile} 1>/dev/null 2>/dev/null")

        status = command.close()
        if status:
            if os.waitstatus_to_exitcode(status) == 84:
                self.state = True
            else:
                self.state = False

        return self.state

    def fileRun(self):
        # diff --ignore-all-space to ignore trailing newline messages
        command = os.popen(f"diff --ignore-all-space <({NANOTEKSPICE_FILE} {self.ntsFile} < {self.inputFile}) {self.outputFile} 2>&1")

        if len(command.read()) > 0:
            self.state = False
        else:
            self.state = True
        command.close()
        return self.state

class SNES:
    def __init__(self):
        self.tests = [
            Test("and.nts", "and.input", "and.output"),
            Test("or.nts", "or.input", "or.output"),
            Test("false.nts", "true_false.input", "false.output"),
            Test("true.nts", "true_false.input", "true.output"),
            # TODO: all gates
            # TODO: clock
            # TODO: input_output
            # TODO: not
            # TODO: xor

            # Parsing errors
            Test("empty_with_comments.nts", "", "", True),
            Test("empty.nts", "", "", True),
        ]
        self.passed_tests = 0
        self.failed_tests = 0

    def run(self):
        print("Running tests...")

        for test in self.tests:
            if test.run():
                self.passed_tests += 1
            else:
                self.failed_tests += 1

    def results(self):
        print(f"{len(self.tests)} tests: {Colors.GREEN}{self.passed_tests} passed{Colors.RESET}, {Colors.RED}{self.failed_tests} failed{Colors.RESET}")

        for test in self.tests:
            if test.state == False:
                print(f"Test {Colors.RED}{test.ntsFile} failed{Colors.RESET}", file=sys.stderr)

if __name__ == "__main__":
    if not os.path.isfile(NANOTEKSPICE_FILE):
        print("NanoTekSpice isn't built")
        sys.exit(1)

    snes = SNES()

    print("SNES - Super Nano(TekSpice) Execution Suite")
    print("--------------------------------------------")
    print("")
    snes.run()
    snes.results()

    if snes.failed_tests > 0:
        sys.exit(1)
