# Ghost-ocr
Extract text from 'glimpsing' a pdf.

The idea is to call this code as a subprocess in e.g. python for machine learning purposes.

## Getting Started

The project is built using CMake version >= 3.9.3. A few CMake scripts should give enough information regarding what is missing.

### Prerequisites

Ghostscript, libpng, tesseract-ocr (don't forget the language data files found externally). 

## Running the tests

Set build test ON in the project CMake file. Thereafter, building again should download googletest gtest/gmock. The tests are based on these libraries.

## Contributing

Feel free to contributing. As for now, the only requirements for contributing is using the same clang-format.

## Authors

* **August von Hacht** - *Initial work* - [vonhachtaugust](https://github.com/vonhachtaugust)

See also the list of [contributors](https://github.com/vonhachtaugust/GameTheory/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
