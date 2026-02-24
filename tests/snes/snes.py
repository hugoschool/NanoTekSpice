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
        command = os.popen(f"{NANOTEKSPICE_FILE} {self.ntsFile} < <(echo \"\") 1>/dev/null 2>/dev/null")

        status = command.close()
        if status:
            if os.waitstatus_to_exitcode(status) == self.exitCode:
                self.state = True
            else:
                self.state = False
        else:
            self.state = True

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

class LoggerTest(ContentTest):
    def __init__(self, ntsFile, inputFile, outputFile, binOutputFile):
        super().__init__(ntsFile, inputFile, outputFile)

        self.binOutputFile = os.path.join(BASE_DIR, "files", binOutputFile)

    def run(self):
        if os.path.exists("./log.bin"):
            os.remove("./log.bin")

        if super().run() == False:
            self.state = False
            return False

        binOutputContent = ""
        with open(self.binOutputFile, "r") as f:
            binOutputContent = f.read()

        with open("./log.bin", "r") as f:
            if binOutputContent != f.read():
                self.state = False
            else:
                self.state = True

        return self.state

class SNES:
    def __init__(self):
        self.tests = [
            # Elementary
            ContentTest(
                "components/elementary/and.nts",
                "components/elementary/and.input",
                "components/elementary/and.output"
            ),
            ContentTest(
                "components/elementary/or.nts",
                "components/elementary/or.input",
                "components/elementary/or.output"
            ),
            ContentTest(
                "components/elementary/false.nts",
                "components/elementary/true_false.input",
                "components/elementary/false.output"
            ),
            ContentTest(
                "components/elementary/true.nts",
                "components/elementary/true_false.input",
                "components/elementary/true.output"
            ),
            ContentTest(
                "components/elementary/not.nts",
                "components/elementary/not.input",
                "components/elementary/not.output"
            ),
            ContentTest(
                "components/elementary/xor.nts",
                "components/elementary/xor.input",
                "components/elementary/xor.output"
            ),
            ContentTest(
                "components/elementary/input_output.nts",
                "components/elementary/input_output.input",
                "components/elementary/input_output.output"
            ),
            ContentTest(
                "components/elementary/clock.nts",
                "components/elementary/clock.input",
                "components/elementary/clock.output"
            ),

            # Gates
            ContentTest(
                "components/gates/4001_nor.nts",
                "components/gates/common.input",
                "components/gates/4001_nor.output"
            ),
            ContentTest(
                "components/gates/4011_nand.nts",
                "components/gates/common.input",
                "components/gates/4011_nand.output"
            ),
            ContentTest(
                "components/gates/4030_xor.nts",
                "components/gates/common.input",
                "components/gates/4030_xor.output"
            ),
            ContentTest(
                "components/gates/4069_not.nts",
                "components/gates/4069_not.input",
                "components/gates/4069_not.output"
            ),
            ContentTest(
                "components/gates/4071_or.nts",
                "components/gates/common.input",
                "components/gates/4071_or.output"
            ),
            ContentTest(
                "components/gates/4081_and.nts",
                "components/gates/common.input",
                "components/gates/4081_and.output"
            ),

            # Advanced tests

            ## 4013
            # Test the first flipflop
            ContentTest(
                "components/advanced/4013_flipflop.nts",
                "components/advanced/4013/4013_flipflop.input",
                "components/advanced/4013/4013_flipflop.output"
            ),
            # Test the second flipflop
            ContentTest(
                "components/advanced/4013_flipflop.nts",
                "components/advanced/4013/4013_flipflop_2.input",
                "components/advanced/4013/4013_flipflop_2.output"
            ),
            # This is a test I'm uncertain about the result or even the validity.
            # It's extracted from the big 4013_flipflop test as to make it more appearant
            # TODO: remove it once confirmed if it's true/false
            ContentTest(
                "components/advanced/4013_flipflop.nts",
                "components/advanced/4013/4013_flipflop_unknown.input",
                "components/advanced/4013/4013_flipflop_unknown.output"
            ),

            ## Logger
            LoggerTest(
                "components/advanced/logger.nts",
                "components/advanced/logger.input",
                "components/advanced/logger.output",
                "components/advanced/logger.bin.output"
            ),

            # Parsing errors
            ExitCodeTest("parsing/empty_chipsets.nts"),
            ExitCodeTest("parsing/not_enough_arguments_chipsets.nts"),
            ExitCodeTest("parsing/not_enough_arguments_links.nts"),
            ExitCodeTest("parsing/too_many_arguments_chipsets.nts"),
            ExitCodeTest("parsing/too_many_arguments_links.nts"),
            ExitCodeTest("parsing/valid_with_invalid.nts"),
            ExitCodeTest("parsing/empty_with_comments.nts"),
            ExitCodeTest("parsing/empty.nts"),
            ExitCodeTest("parsing/unknown_link.nts"),
            ExitCodeTest("parsing/only_links.nts"),
            ExitCodeTest("nonexistant.file.unknown.fake"),
            ExitCodeTest("parsing/invalid_with_tabs.nts"),

            # Valid parsing
            ExitCodeTest("parsing/tabs_and_spaces.nts", 0),
            ExitCodeTest("parsing/line_with_comments.nts", 0),
            ExitCodeTest("parsing/valid_with_tabs.nts", 0),
            ExitCodeTest("parsing/valid_with_whitespaces.nts", 0),
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
