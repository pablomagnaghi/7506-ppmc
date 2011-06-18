#include <iostream>
#include <stdexcept>
#include <boost/program_options.hpp>
#include "PPMC.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "PPMCCompressor.h"
#include "PPMCUncompressor.h"

using namespace ppmc;
using namespace util;
using namespace std;

namespace po = boost::program_options;

class bad_arguments:public exception {};

void conflicting_options(const po::variables_map& vm,
                         const char* opt1, const char* opt2) {
    if (vm.count(opt1) && !vm[opt1].defaulted()
        && vm.count(opt2) && !vm[opt2].defaulted())
        throw invalid_argument(string("Opciones en conflicto '")
                          + opt1 + "' y '" + opt2 + "'.");
}

int main(int argc, char* argv[]) {
	try {
		string input;
		string output;
		size_t buffer;
		size_t order;
		po::options_description options("Modo");

		options.add_options()
			("-c", po::value< string >(&input), "Archivo de entrada")
			("-x", po::value< string >(&input), "Archivo de entrada")
			("-s", po::value< string >(&output), "Archivo de salida")
			("-o", po::value<size_t>(&order)->default_value(3), "Orden")
			("-b", po::value<size_t>(&buffer)->default_value(2048), "Buffer entrada/salida")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, options), vm);
		po::notify(vm);    

		conflicting_options(vm, "-c", "-x");
		conflicting_options(vm, "-x", "-o");

		if (output =="" ) {
			if (vm.count("-c")) {
				output = input + ".XX";
			} else {
				output = input.substr(0, input.size() - 3);
			}
		}
		
// 		cout << "vamos a ";
// 		if (vm.count("-c")) {
// 			cout << "comprimir ";
// 		} else {
// 			cout << "descomprimir ";
// 		}
// 		cout << input << " con orden " << order << " en " << output << " y buffer " << buffer << endl;

		FileReader in(input.c_str(), buffer);
		FileWriter out(output.c_str(), buffer);
		
		if (vm.count("-c")) {
			PPMCCompressor c(&in,&out,order);
			c.compress();
		} else if(vm.count("-x")) {
			PPMCUncompressor d(&in,&out);
			d.uncompress();
		} else {
			throw invalid_argument(string("Debe pedir \"-c\" para comprimir o \"-x\" para descomprimir y una ruta válida '"));
		}
	} catch (std::logic_error& e) {
		cerr << e.what() << endl;
		return 1;
	} catch (ios_base::failure& e) {
		cerr <<  e.what() << endl;
		return 2;
	} catch (exception& e) {
		cerr << "Error interno: " << e.what() << endl;
		return 3;
	}

	return 0;
}
