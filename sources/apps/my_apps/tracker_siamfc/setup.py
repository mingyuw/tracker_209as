from setuptools import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(
       "caller_tracker.pyx",            # Cython source
      ))