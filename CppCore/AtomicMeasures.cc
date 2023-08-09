#include "include/AtomicMeasures.hpp"

using namespace yodecon::types;
using namespace atmdist::distance;

std::pair<double, std::string> atomdatum_diff(
    const AtomDatum& atmA, const AtomDatum& atmB,
    const Distance<double>& distanceFunc) {

  // Construct vectors for the two atoms' coordinates
  std::vector<double> vecA = {atmA.x, atmA.y, atmA.z};
  std::vector<double> vecB = {atmB.x, atmB.y, atmB.z};

  double diff = distanceFunc(vecA, vecB);
  std::vector<std::string> symbols = {atmA.symbol, atmB.symbol};
  std::vector<int> atomicNumbers = yodecon::symbols_to_atomic_numbers(symbols);

  // Order the atomic numbers to ensure symmetry
  std::sort(atomicNumbers.begin(), atomicNumbers.end());

  // Convert the ordered atomic numbers back to symbols
  std::vector<std::string> orderedSymbols = yodecon::atomic_numbers_to_symbols(atomicNumbers);

  // Concatenate the ordered symbols to create the identifier
  std::string identifier = orderedSymbols[0] + "_" + orderedSymbols[1];

  return {diff, identifier};
}
