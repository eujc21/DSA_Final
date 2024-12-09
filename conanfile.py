from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class MyProjectConan(ConanFile):
    name = "ds_3180" # Choose a name for your project
    version = "1.0"     # Choose a version for your project
    exports_sources = "include/*" # Export the include directory
    settings = "os", "compiler", "build_type", "arch" # Add this line

    def requirements(self):
        self.requires("fmt/11.0.2")
        self.requires("rapidcsv/8.84")
        self.requires("nlohmann_json/3.11.3")


    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_VERBOSE_MAKEFILE"] = True # Example: Add a CMake variable
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def package(self):
        self.copy("*.h", dst="include", src="include")

    def build(slef):
        cmake == CMake(self)
        cmake.configure()
        cmake.build()
        # This will run the tests if test package is found
        if not self.conf.get("tools.build:skip_test", default=False):
            camke.test()


