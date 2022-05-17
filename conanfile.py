from conans import ConanFile, CMake, tools
from conans.errors import ConanException
import os

class SimpleDBus(ConanFile):
   name = "simpledbus"
   license = "MIT"
   description = "A simple C++ wrapper around DBus with a commercially-friendly licence"
   settings = "os", "compiler", "build_type", "arch"
   requires = "dbus/1.12.20", "fmt/7.1.3"
   options = {
      "log_level": ["VERBOSE_3","VERBOSE_2","VERBOSE_1","VERBOSE_0","DEBUG","INFO","WARNING","ERROR","FATAL"],
      "shared": [True, False]
   }
   default_options = {
      "fmt:header_only" : True,
      "log_level" : "FATAL"
   }
   generators = ["cmake_find_package","cmake"]
   
   exports_sources = "CMakeLists.txt", "include/*",  "src/*",  "examples/*"

   def build(self):
      cmake = CMake(self)
      cmake.definitions["SIMPLEDBUS_LOG_LEVEL"] = self.options.log_level
      cmake.definitions["CONAN_BUILD"] = True
      cmake.configure()
      cmake.build()

   def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        if self.options.shared == True:
           self.copy("*.so", dst="lib", keep_path=False)
        else:
           self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*", dst="bin", src="examples/notification/bin", keep_path=False)

   def package_info(self):
      self.cpp_info.libs = tools.collect_libs(self)
   
   def deploy(self):
      self.copy("*", dst="bin", src="bin")
