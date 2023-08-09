#pragma once
#include <functional>
#include "../subprojects/readCon/CppCore/include/BaseTypes.hpp"
#include "include/Distance.hpp"
#include "../subprojects/readCon/CppCore/include/ReadCon.hpp"

using namespace yodecon::types;
using namespace atmdist::distance;
std::pair<double, std::string> atomdatum_diff(
    const AtomDatum& atmA, const AtomDatum& atmB,
    const Distance<double>& distanceFunc);
double conframe_diff(const yodecon::types::AtomDatum atmA, const yodecon::types::AtomDatum atmB);
