from setuptools import setup, Extension

module = Extension('sortarr', sources=['sortarr.c'])

setup(name='sortarr',
      version='1.0',
      description='Sorts int values',
      ext_modules=[module])