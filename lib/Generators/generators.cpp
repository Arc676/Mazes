#include "Generators/generators.h"

const char* Generators::algoToString(GeneratorAlgo algo) {
	switch (algo) {
		case RANDOM_MAZE:
			return "Random maze";
		case RECURSIVE_DIVISION:
			return "Recursive division";
		default:
			return "Unknown algorithm";
	}
}
