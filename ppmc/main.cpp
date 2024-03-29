#include <iostream>
#include <stdexcept>
#include <boost/program_options.hpp>
#include "AI.h"
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
			("-s", po::value< string >(&output)->default_value(""), "Archivo de salida")
			("-o", po::value<size_t>(&order)->default_value(3), "Orden")
			("-b", po::value<size_t>(&buffer)->default_value(1048576), "Buffer entrada/salida")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, options), vm);
		po::notify(vm);    

		conflicting_options(vm, "-c", "-x");
		conflicting_options(vm, "-x", "-o");

		if (vm["-s"].defaulted() ) {
			if (vm.count("-c")) {
				output = input + ".XX";
			} else {
				if( (input.find_last_of(".") == string::npos ) || 
				    ( input.substr(input.find_last_of(".")+1) != "XX" ) ) {
					throw invalid_argument(string("Para descomprimir sin archivo de salida, debe proveer un archivo con extensión XX"));
				}
				output = input.substr(0, input.size() - 3);
			}
		}

// 		cerr << "vamos a ";
// 		if (vm.count("-c")) {
// 			cerr << "comprimir ";
// 		} else {
// 			cerr << "descomprimir ";
// 		}
// 		cerr << input << " con orden " << order << " en " << output << " y buffer " << buffer << endl;

		FileReader in(input.c_str(), buffer);
		FileWriter out(output.c_str(), buffer);

		if (vm["-o"].defaulted()) {
			AI ai(in,input);
			order=ai.evaluate();
			//cerr << "defaulting order to " << order << endl;
		}
		
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
