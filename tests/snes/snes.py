import os
import sys

BASE_DIR = os.path.dirname(os.path.realpath(__file__))
NANOTEKSPICE_FILE = os.path.join(os.path.join(BASE_DIR, "..", ".."), "nanotekspice")

class Colors:
    GREEN = '\033[92m'
    RED = '\033[91m'
    RESET = '\033[0m'

class Test:
    def __init__(self, ntsFile):
        self.ntsFile = os.path.join(BASE_DIR, "files", ntsFile)

        # True = success, False = failure
        self.state = False

    def run(self):
        pass

class ExitCodeTest(Test):
    def __init__(self, ntsFile, exitCode = 84):
        super().__init__(ntsFile)

        self.exitCode = exitCode

    def run(self):
        # TODO: this can be replaced with subprocess.Popen
        command = os.popen(f"{NANOTEKSPICE_FILE} {self.ntsFile} 1>/dev/null 2>/dev/null")

        status = command.close()
        if status:
            if os.waitstatus_to_exitcode(status) == self.exitCode:
                self.state = True
            else:
                self.state = False

        return self.state

class ContentTest(Test):
    def __init__(self, ntsFile, inputFile, outputFile):
        super().__init__(ntsFile)

        self.inputFile = os.path.join(BASE_DIR, "files", inputFile)
        self.outputFile = os.path.join(BASE_DIR, "files", outputFile)

    def run(self):
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
            ContentTest("and.nts", "and.input", "and.output"),
            ContentTest("or.nts", "or.input", "or.output"),
            ContentTest("false.nts", "true_false.input", "false.output"),
            ContentTest("true.nts", "true_false.input", "true.output"),
            ContentTest("not.nts", "not.input", "not.output"),
            ContentTest("xor.nts", "xor.input", "xor.output"),
            # TODO: all gates
            # TODO: clock
            # TODO: input_output

            # Parsing errors
            ExitCodeTest("empty_with_comments.nts"),
            ExitCodeTest("empty.nts"),
            ExitCodeTest("unknown_link.nts"),
            ExitCodeTest("only_links.nts"),
            ExitCodeTest("nonexistant.file.unknown.fake"),
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
                print(f"Test {Colors.RED}{os.path.basename(test.ntsFile)} failed{Colors.RESET}", file=sys.stderr)

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
