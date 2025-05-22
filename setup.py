from setuptools import setup

setup(
    name="Intelli",
    version="0.1.0",
    description="A lambda search engine for python.",
                url="https://intellisearch-gv0j.onrender.com/",
                    packages=["Intelli"],  # Your Python package directory
    # cffi_modules tells setuptools to run the specified build script
    # to compile the C extension.
    cffi_modules=["Intelli/build.py:ffibuilder"],
    # You need cffi as a build-time dependency
    setup_requires=["cffi>=1.0.0"],
    # And also as an install-time dependency for the user
    install_requires=["cffi>=1.0.0"],
    author="Jonas Granath",
    license="GLP-3.0 GNU license",
    zjip_safe=False,  # Generally good practice for packages with C extensions
)from setuptools import setup

setup(
    name="Intelli",
    version="0.1.0",
    description="A lambda search engine for python.",
    url="https://intellisearch-gv0j.onrender.com/",
    packages=["Intelli"],  # Your Python package directory
    # cffi_modules tells setuptools to run the specified build script
    # to compile the C extension.
    cffi_modules=["Intelli/build.py:ffibuilder"],
    # You need cffi as a build-time dependency
    setup_requires=["cffi>=1.0.0"],
    # And also as an install-time dependency for the user
    install_requires=["cffi>=1.0.0"],
    author="Jonas Granath",
    license="GLP-3.0 GNU license",
    zip_safe=False,  # Generally good practice for packages with C extensions
)
